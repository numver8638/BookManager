#include "EditModalView.h"

#include "../BookManager.h"
#include "../ViewManager.h"
#include "ConfirmModalView.h"
#include "Constants.h"

// static
const std::string EditModalView::TITLE = " ====== 책 정보 수정하기 ======\n";

void EditModalView::OnEnter() {
    Base::Reset();
    GetInputs()[Base::IDENTIFIER].Set(std::to_string(m_book->Identifier));
    GetInputs()[Base::NAME].Set(m_book->Name);
    GetInputs()[Base::AUTHOR].Set(m_book->Author);
    GetInputs()[Base::RELEASE_DATE].Set(m_book->ReleaseDate);
    GetInputs()[Base::PUBLISHER].Set(m_book->Publisher);
    GetInputs()[Base::PRICE].Set(std::to_string(m_book->Price));
}

void EditModalView::OnKeyPressed(KeyEvent event) {
    switch (event.Key) {
        case KeyType::Escape:
            SetReturn(m_no);
            return Leave();

        default:
            Base::OnKeyPressed(event);
            break;
    }

    RequireUpdate();
}

void EditModalView::OnVerified(Book book) {
    m_created = std::move(book);
    ViewManager::PushModal(new ConfirmModalView("수정하겠습니까?", YES, NO));
}

void EditModalView::OnModalClosed(int retval) {
    if (retval == YES) {
        GetManager().RemoveBook(m_book);
        GetManager().AddBook(std::move(m_created));
        SetReturn(m_yes);
        Leave();
    }
}

void EditModalView::OnRender() {
    Base::OnRender();
}
