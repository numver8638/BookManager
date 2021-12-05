#pragma once

#include "SelectViewBase.h"

class BookManager;
struct Book;

class SearchView final : public View, SelectViewBase {
    using Base = SelectViewBase;

public:
    explicit SearchView(BookManager& manager)
        : View("search"), SelectViewBase(manager) {}
    
    void OnEnter() override;

    void OnKeyPressed(KeyEvent) override;

    void OnRender() override;
};