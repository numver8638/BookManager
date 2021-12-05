#include "ConfirmModalView.h"

#include <cstdio>

#include "Constants.h"

void ConfirmModalView::OnKeyPressed(KeyEvent event) {
    switch (event.Key) {
        case KeyType::Escape:
            SetReturn(m_no);
            return Leave();

        case KeyType::Up:
            if (m_cursor != 0) { m_cursor = 0; }
            break;

        case KeyType::Down:
            if (m_cursor != 1) { m_cursor = 1; }
            break;

        case KeyType::Enter:
            SetReturn((m_cursor == 0) ? m_no : m_yes);
            return Leave();

        default:
            // ignored
            break;
    }

    RequireUpdate();
}

void ConfirmModalView::OnRender() {
    std::printf("\n    %s\n\n", m_message.c_str());
    std::printf("%s<< 아니오 >>\n", ((m_cursor == 0) ? CURSOR_PRESENT : CURSOR_NOT_PRESENT));
    std::printf("%s<< 예 >>\n", ((m_cursor == 1) ? CURSOR_PRESENT : CURSOR_NOT_PRESENT));
}