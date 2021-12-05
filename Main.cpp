#include <iostream>

#include "Book.h"
#include "BookManager.h"
#include "ViewManager.h"

// View List
#include "View/AddView.h"
#include "View/ListView.h"
#include "View/MainView.h"
#include "View/RemoveView.h"
#include "View/SearchView.h"
#include "View/UpdateView.h"


#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <fcntl.h>
#include <io.h>
#else
#include <termios.h>
#endif

class ConsoleInitializer {
private:
    #ifdef _WIN32
    DWORD m_outMode, m_inMode;
    void InitConsole() {
        auto out = GetStdHandle(STD_OUTPUT_HANDLE);
        
        DWORD mode = 0;
        GetConsoleMode(out, &mode);
        m_outMode = mode;
        mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(out, mode);

        auto in = GetStdHandle(STD_INPUT_HANDLE);
        GetConsoleMode(in, &mode);
        m_inMode = mode;
        mode &= ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT);
        mode |= ENABLE_VIRTUAL_TERMINAL_INPUT;
        SetConsoleMode(in, mode);

        _setmode(_fileno(stdin), O_BINARY);

    }
    
    void FiniConsole() {
        auto out = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleMode(out, m_outMode);
        
        auto in = GetStdHandle(STD_INPUT_HANDLE);
        SetConsoleMode(in, m_inMode);
    }
    #else
    struct termios m_prev;
    void InitConsole() {
        struct termios current;

        tcgetattr(0, &current);
        
        m_prev = current;
        
        current.c_lflag &= ~(ICANON|ECHO);
        current.c_cc[VMIN] = 1;
        current.c_cc[VTIME] = 0;
        tcsetattr(0, TCSANOW, &current);
        std::printf("\033[?25l"); // Hide cursor
    }
    
    void FiniConsole() {
        tcsetattr(0, TCSANOW, &m_prev);
        std::printf("\033[?25h"); // Restore cursor
    }
    #endif
public:
    ConsoleInitializer() {
        InitConsole();
        setvbuf(stdin, nullptr, _IONBF, 0);
    }
    
    ~ConsoleInitializer() {
        FiniConsole();
    }
};


int main() {
    ConsoleInitializer console;

    BookManager manager("Bookdb_1701169.dat");

    std::initializer_list<View*> init = {
        new MainView,
        new ListView("list_order_by_identifier", manager, OrderBy::Identifier),
        new ListView("list_order_by_name", manager, OrderBy::Name),
        new AddView(manager),
        new UpdateView(manager),
        new RemoveView(manager),
        new SearchView(manager)
    };

    ViewManager::RegisterView(init);
    ViewManager::Push("main");

    return ViewManager::StartLoop();
}
