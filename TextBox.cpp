#include "TextBox.h"

#include "View.h"

void TextBox::OnKeyPressed(KeyEvent event) {
    switch (event.Key) {
        case KeyType::Backspace:
            // handle UTF-8
            if (!m_buffer.empty()) {
                if ((unsigned char)(m_buffer.back()) > 0x80) {
                    do {
                        m_buffer.pop_back();
                    } while (((unsigned char)(m_buffer.back()) & 0xC0) == 0x80);
                }
                m_buffer.pop_back();
            }
            break;

        case KeyType::Character:
            m_buffer.push_back(event.Char);
            break;

        default:
            // ignore
            break;
    }
}
