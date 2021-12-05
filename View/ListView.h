#pragma once

#include "../View.h"

enum class OrderBy;
class BookManager;

class ListView final : public View {
private:
    BookManager& m_manager;
    OrderBy m_by;
    int m_index = 0;
    int m_maxPage = 0;

public:
    ListView(std::string name, BookManager& manager, OrderBy by)
        : View(std::move(name)), m_manager(manager), m_by(by) {}
    
    void OnEnter() override;

    void OnKeyPressed(KeyEvent) override;

    void OnRender() override;
};