#pragma once

#include <vector>

#include "../View.h"
#include "../TextBox.h"

struct Book;
class BookManager;

class SelectViewBase {
private:
    BookManager& m_manager;
    TextBox m_search;
    std::vector<Book*> m_result;
    int m_index = 0;
    int m_maxPage = 0;
    int m_cursor = 0;

protected:
    explicit SelectViewBase(BookManager& manager)
        : m_manager(manager) {}

    BookManager& GetManager() { return m_manager; }

    Book* GetSelected() const;

    void Reset();

    void Reload();

    void OnKeyPressed(KeyEvent);

    void OnRender();

    virtual void OnSelected(Book*) {}
};
