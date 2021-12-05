#include "SelectViewBase.h"

#include "../Book.h"
#include "../BookManager.h"
#include "Constants.h"
#include "Util.h"

Book* SelectViewBase::GetSelected() const {
    auto index = (m_index * 10) + (m_cursor - 1);
    return (index < m_result.size()) ? m_result[index] : nullptr;
}

void SelectViewBase::Reset() {
    m_search.Reset();
    m_cursor = 0;
    m_result.clear();
    m_index = 0;
    m_maxPage = 1;
}

void SelectViewBase::Reload() {
    m_cursor = 0;
    m_result = m_manager.SearchByName(m_search.ToString());
    m_index = 0;
    m_maxPage = (m_result.size() / 10) + (m_result.size() % 10 == 0 ? 0 : 1);
}

void SelectViewBase::OnKeyPressed(KeyEvent event) {
    switch (event.Key) {
        case KeyType::Up:
            if (m_cursor > 0) { --m_cursor; }
            break;

        case KeyType::Down: {
            int maxCursor = (m_index + 1) * 10 < m_result.size() ? 10 : (m_result.size() % 10);
            if (m_cursor < maxCursor) { ++m_cursor; }
            break;
        }

        case KeyType::Left:
            if (m_index > 0) { --m_index; }
            break;

        case KeyType::Right:
            if (m_index < (m_maxPage - 1)) { ++m_index; }
            break;

        case KeyType::Enter:
            (m_cursor == 0) ? Reload() : OnSelected(GetSelected());
            break;

        default:
            if (m_cursor == 0) { m_search.OnKeyPressed(event); }
            break;
    }
}

void SelectViewBase::OnRender() {
    std::printf(" ====== 책 검색하기 ======\n");
    std::printf("%s 이름 검색> %s\n\n", ((m_cursor == 0) ? CURSOR_PRESENT : CURSOR_NOT_PRESENT), m_search.ToString().c_str());

    if (!m_result.empty()) {
        auto begin = m_result.begin() + (m_index * 10);
        auto end = (m_result.size() < ((m_index + 1) * 10)) ? m_result.end() : (begin + 10);

        std::vector<Book*> books = { begin, end };
        auto [id_padding, name_padding, author_padding, publisher_padding, price_padding] = CalcuateWidth(books);

        std::printf("   %s %-*s %-*s %-*s %-*s %-8s %-*s\n",
            "순서", id_padding, "식별자", name_padding, "이름", author_padding, "작가",
            publisher_padding, "출판사", "출간일", price_padding, "가격");

        auto cursor = 1;
        for (const auto* book : books) {
            std::printf("%s%02d: %-*d %-*s %-*s %-*s %s %-*d\n", (m_cursor == cursor) ? CURSOR_PRESENT : CURSOR_NOT_PRESENT,
                cursor, id_padding, book->Identifier, name_padding, book->Name.c_str(), author_padding, book->Author.c_str(), 
                publisher_padding, book->Publisher.c_str(), book->ReleaseDate.c_str(), price_padding, book->Price);
            ++cursor;
        }

        std::printf("\n       << %d / %d >>\n", (m_index + 1), m_maxPage);
    }
    else {
        std::printf("\n        검색 결과가 없습니다.");
    }
}
