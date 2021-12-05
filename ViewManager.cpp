#include "ViewManager.h"

#include <cassert>

#include "View.h"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

static bool HasValue() {
    auto in = GetStdHandle(STD_INPUT_HANDLE);
    DWORD count;

    GetNumberOfConsoleInputEvents(in, &count);
    return count > 0;
}
#else 
#include <sys/select.h>

static bool HasValue() {
    timeval tv;
    fd_set read_fds;
    auto fd = fileno(stdin);

    tv.tv_sec = 0;
    tv.tv_usec = 0;

    FD_ZERO(&read_fds);
    FD_SET(fd, &read_fds);

    auto result = select(fd + 1, &read_fds, nullptr, nullptr, &tv);

    return FD_ISSET(fd, &read_fds);
}
#endif

// static
std::unordered_map<std::string, View*> ViewManager::m_map;
std::stack<View*> ViewManager::m_views;
bool ViewManager::m_exitRequested = false;

// static
void ViewManager::HandleRender(View* view) {
    if (view->m_updateRequired) {
        view->m_updateRequired = false;

        std::printf("\033[2J\033[1;1H"); // clear screen

        view->OnRender();
    }
}

// static
bool ViewManager::HandleLeave(View* view) {
    if (view->m_leave) {
        view->m_leave = false;
        auto* prev = view;
        m_views.pop();

        if (prev->IsModal()) {
            assert(!m_views.empty());
            auto* modal = dynamic_cast<ModalView*>(prev);
            m_views.top()->OnModalClosed(modal->GetReturn());

            delete modal;
        }

        return true;
    }

    return false;
}

// static
KeyType ViewManager::HandleEscape() {
    if (!HasValue()) {
        return KeyType::Escape;
    }
    else if (fgetc(stdin) == '[') {
        switch (fgetc(stdin)) {
        case 'A': return KeyType::Up;
        case 'B': return KeyType::Down;
        case 'C': return KeyType::Right;
        case 'D': return KeyType::Left;
        default: return KeyType::Unknown;
        }
    }
    else {
        return KeyType::Unknown;
    }
}

// static
void ViewManager::HandleKeyPress(View* view) {
    auto ch = fgetc(stdin);
    KeyEvent event;

    switch (ch) {
    case '\033':
        event.Key = HandleEscape();
        break;

    case '\r': case '\n':
        event.Key = KeyType::Enter;
        break;

    case 0x7F:
        event.Key = KeyType::Backspace;
        break;

    default:
        event.Key = KeyType::Character;
        event.Char = ch;
        break;
    }

    if (event.Key != KeyType::Unknown) {
        view->OnKeyPressed(event);
    }
}

// static
void ViewManager::RegisterView(std::initializer_list<View*> list) {
    for (auto* View : list) {
        m_map.insert({ View->m_name, View });
    }
}

// static
void ViewManager::Push(const std::string& name) {
    auto it = m_map.find(name);

    assert((it != m_map.end()) && "never be null.");

    auto* view = it->second;

    view->OnEnter();

    m_views.push(view);
    view->m_updateRequired = true; // always to be updated on load.
}

// static
void ViewManager::PushModal(ModalView* modal) {
    modal->OnEnter();
    m_views.push(modal);
    modal->m_updateRequired = true;
}

// static
int ViewManager::StartLoop() {
    while (!m_views.empty()) {
        auto* view = m_views.top();

        HandleRender(view);
        if (HandleLeave(view)) { continue; }
        HandleKeyPress(view);
    }

    return 0;
}
