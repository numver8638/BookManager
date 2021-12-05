#include "RemoveView.h"

#include <cassert>

#include "../BookManager.h"
#include "../ViewManager.h"
#include "ConfirmModalView.h"
#include "Constants.h"

void RemoveView::OnEnter() {
    Base::Reset();
}

void RemoveView::OnKeyPressed(KeyEvent event) {
    switch (event.Key) {
        case KeyType::Escape:
            return Leave();

        default:
            Base::OnKeyPressed(event);
            break;
    }

    RequireUpdate();
}

void RemoveView::OnRender() {
    Base::OnRender();
}


void RemoveView::OnSelected(Book* book) {
    ViewManager::PushModal(new ConfirmModalView("삭제하시겠습니까?", YES, NO));
}

void RemoveView::OnModalClosed(int retval) {
    if (retval == YES) {
        auto* selected = Base::GetSelected();

        assert(selected != nullptr);
    
        GetManager().RemoveBook(selected);
        Base::Reload();
    }
}