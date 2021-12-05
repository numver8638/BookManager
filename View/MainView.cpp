#include "MainView.h"

#include <cstdio>

#include "../ViewManager.h"
#include "Constants.h"

static const char* const MESSAGES[] = {
    "1. 전체 책 목록 보기 (식별자 순)\n",
    "2. 전체 책 목록 보기 (이름 순)\n",
    "3. 책 정보 추가하기\n",
    "4. 책 정보 수정하기\n",
    "5. 책 정보 삭제하기\n",
    "6. 책 정보 검색하기\n",
    "0. 나가기\n"
};

static const char* NAMES[] = {
    "list_order_by_identifier",
    "list_order_by_name",
    "add",
    "update",
    "remove",
    "search"
};

static constexpr int MAX_CURSOR = 7;

void MainView::OnEnter() {
    m_cursor = 0;
}

void MainView::OnKeyPressed(KeyEvent event) {
    switch (event.Key) {
        case KeyType::Up:
            if (m_cursor > 0) { --m_cursor; }
            break;

        case KeyType::Down:
            if (m_cursor < (MAX_CURSOR - 1)) { ++m_cursor; }
            break;
        
        case KeyType::Character:
            if (L'0' <= event.Char && event.Char <= L'6') {
                m_cursor = event.Char - L'0';
                m_cursor += (m_cursor == 0) ? 6 : -1;
            }
            break;

        case KeyType::Enter:
            (m_cursor == 6) ? Leave() : ViewManager::Push(NAMES[m_cursor]);
            break;

        default:
            // do nothing.
            break;
    }

    RequireUpdate();
}

void MainView::OnRender() {
    std::printf(" ====== 책 관리 프로그램 ======\n");

    for (auto i = 0; i < MAX_CURSOR; i++) {
        std::printf("%s%s", ((i == m_cursor) ? CURSOR_PRESENT : CURSOR_NOT_PRESENT), MESSAGES[i]);
    }

    std::printf("\n  번호: %d", ((m_cursor == 6) ? 0 : (m_cursor + 1)));
}