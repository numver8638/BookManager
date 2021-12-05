#include "ListView.h"

#include <cstdio>

#include "../Book.h"
#include "../BookManager.h"
#include "../ViewManager.h"
#include "Constants.h"
#include "Util.h"

void ListView::OnEnter() {
    m_index = 0;
    m_maxPage = (m_manager.GetBookCount() / 10) + ((m_manager.GetBookCount() % 10 != 0) ? 1 : 0);
}

void ListView::OnKeyPressed(KeyEvent event) {
    switch (event.Key) {
        case KeyType::Escape:
            return Leave();

        case KeyType::Left:
            if (m_index > 0) { --m_index; }
            break;

        case KeyType::Right:
            if (m_index < (m_maxPage - 1)) { ++m_index; }
            break;

        default:
            break;
    }

    RequireUpdate();
}

void ListView::OnRender() {
    std::printf(" ========== 책  목록 보기 (%s) ==========\n", (m_by == OrderBy::Identifier ? "식별자 순" : "이름 순"));

    auto books = m_manager.GetBooks(m_by, m_index * 10, 10);
    auto [id_padding, name_padding, author_padding, publisher_padding, price_padding] = CalcuateWidth(books);
    auto cursor = 1;

    std::printf("%s %-*s %-*s %-*s %-*s %-8s %-*s\n",
        "순서", id_padding, "식별자", name_padding, "이름", author_padding, "작가",
        publisher_padding, "출판사", "출간일", price_padding, "가격");

    for (const auto* book : books) {
        std::printf("%02d: %-*d %-*s %-*s %-*s %s %-*d\n",
            cursor, id_padding, book->Identifier, name_padding, book->Name.c_str(), author_padding, book->Author.c_str(), 
            publisher_padding, book->Publisher.c_str(), book->ReleaseDate.c_str(), price_padding, book->Price);
        ++cursor;
    }

    std::printf("\n       << %d / %d >>\n", (m_index + 1), m_maxPage);
}