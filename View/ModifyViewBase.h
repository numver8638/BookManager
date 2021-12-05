#pragma once

#include <string>
#include <vector>
#include <array>

#include "../Book.h"
#include "../View.h"
#include "../TextBox.h"

class BookManager;

class ModifyViewBase {
private:
    BookManager& m_manager;

    std::string m_title;
    std::array<TextBox, 6> m_inputs;

    int m_cursor = 0;
    std::vector<const char*> m_errors;

    bool IsIllFormed();

public:
    enum Cursor {
        IDENTIFIER,
        NAME,
        AUTHOR,
        RELEASE_DATE,
        PUBLISHER,
        PRICE,
        ENTER
    };

protected:
    ModifyViewBase(BookManager& manager, std::string title)
        : m_manager(manager), m_title(std::move(title)) {}

    void Reset();
    
    BookManager& GetManager() { return m_manager; }

    const std::array<TextBox, 6>& GetInputs() const { return m_inputs; }

    std::array<TextBox, 6>& GetInputs() { return m_inputs; }

    void OnKeyPressed(KeyEvent);

    void OnRender();

    virtual void OnVerified(Book) {}
};
