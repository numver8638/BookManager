#include "SearchView.h"

void SearchView::OnEnter() {
    Base::Reset();
}

void SearchView::OnKeyPressed(KeyEvent event) {
    switch (event.Key) {
        case KeyType::Escape:
            return Leave();

        default:
            Base::OnKeyPressed(event);
            break;
    }

    RequireUpdate();
}

void SearchView::OnRender() {
    Base::OnRender();
}
