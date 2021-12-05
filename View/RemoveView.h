#pragma once

#include "SelectViewBase.h"

class RemoveView final : public View, SelectViewBase {
    using Base = SelectViewBase;

public:
    explicit RemoveView(BookManager& manager)
        : View("remove"), SelectViewBase(manager) {}
    
    void OnEnter() override;

    void OnKeyPressed(KeyEvent) override;

    void OnModalClosed(int) override;

    void OnSelected(Book*) override;

    void OnRender() override;
};