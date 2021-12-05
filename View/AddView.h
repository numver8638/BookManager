#pragma once

#include "../Book.h"
#include "ModifyViewBase.h"

class AddView final : public View, ModifyViewBase {
    using Base = ModifyViewBase;

private:
    static const std::string TITLE;

    Book m_created;
    void OnVerified(Book) override;

public:
    explicit AddView(BookManager& manager)
        : View("add"), ModifyViewBase(manager, TITLE) {}
    
    void OnEnter() override;

    void OnKeyPressed(KeyEvent) override;

    void OnRender() override;

    void OnModalClosed(int) override;
};
