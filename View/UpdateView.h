#pragma once

#include "SelectViewBase.h"

struct Book;
class BookManager;

class UpdateView final : public View, SelectViewBase {
    using Base = SelectViewBase;

public:
    explicit UpdateView(BookManager& manager)
        : View("update"), SelectViewBase(manager) {}
    
    void OnEnter() override;

    void OnKeyPressed(KeyEvent) override;

    void OnModalClosed(int) override;

    void OnSelected(Book*) override;

    void OnRender() override;
};