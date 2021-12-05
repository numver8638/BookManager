#pragma once

#include "ModifyViewBase.h"

class EditModalView final : public ModalView, ModifyViewBase {
    using Base = ModifyViewBase;

private:
    static const std::string TITLE;

    Book* const m_book;
    const int m_yes, m_no;
    Book m_created;

public:
    EditModalView(BookManager& manager, Book* book, int yes, int no)
        : ModalView("edit_modal"), ModifyViewBase(manager, TITLE), m_book(book), m_yes(yes), m_no(no) {}

    void OnEnter() override;

    void OnKeyPressed(KeyEvent) override;

    void OnRender() override;

    void OnModalClosed(int) override;

    void OnVerified(Book) override;
};