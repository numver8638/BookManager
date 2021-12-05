#include "AddView.h"

#include "ConfirmModalView.h"
#include "../ViewManager.h"
#include "../BookManager.h"
#include "../Book.h"
#include "Constants.h"

// static
const std::string AddView::TITLE = " ====== 책 정보 추가하기 ======\n";

void AddView::OnEnter() {
    Base::Reset();
}

void AddView::OnKeyPressed(KeyEvent event) {
    switch (event.Key) {
        case KeyType::Escape:
            Leave();
            break;

      default:
            Base::OnKeyPressed(event);
            break;
    }

    RequireUpdate();
}

void AddView::OnVerified(Book book) {
    m_created = std::move(book);
    ViewManager::PushModal(new ConfirmModalView("이어서 추가하겠습니까?", YES, NO));    
}

void AddView::OnRender() {
    Base::OnRender();
}

void AddView::OnModalClosed(int retval) {
    GetManager().AddBook(std::move(m_created));
    if (retval == YES) {
        OnEnter(); // reset
    }
    else {
        Leave();
    }
}
