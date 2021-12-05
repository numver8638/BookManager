#include "UpdateView.h"

#include "../ViewManager.h"
#include "EditModalView.h"
#include "Constants.h"

void UpdateView::OnEnter() {
    Base::Reset();
}

void UpdateView::OnKeyPressed(KeyEvent event) {
    switch (event.Key) {
        case KeyType::Escape:
            return Leave();

        default:
            Base::OnKeyPressed(event);
            break;
    }

    RequireUpdate();
}

void UpdateView::OnRender() {
    Base::OnRender();
}

void UpdateView::OnSelected(Book* book) {
    ViewManager::PushModal(new EditModalView(GetManager(), book, YES, NO));
}

void UpdateView::OnModalClosed(int retval) {
    if (retval == YES) {
        Base::Reload();
    }
}