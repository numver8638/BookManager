#include "ModifyViewBase.h"

#include <cstdio>
#include <regex>

#include "Constants.h"

const std::regex REGEX_DIGIT("[0-9]+", std::regex_constants::ECMAScript);
const std::regex REGEX_DATE("[0-9]{4}/[0-9]{2}/[0-9]{2}", std::regex_constants::ECMAScript);

const char* const INPUTS[] = {
    "식별자: ",
    "이름: ",
    "저자: ",
    "출간일: ",
    "출판사: ",
    "가격: "
};

Book BuildBook(std::array<TextBox, 6>& inputs) {
    using Cursor = ModifyViewBase::Cursor;

    Book book;

    book.Identifier = std::stoi(inputs[Cursor::IDENTIFIER].ToString());
    book.Name = inputs[Cursor::NAME].ToString();
    book.Author = inputs[Cursor::AUTHOR].ToString();
    book.ReleaseDate = inputs[Cursor::RELEASE_DATE].ToString();
    book.Publisher = inputs[Cursor::PUBLISHER].ToString();
    book.Price = std::stoi(inputs[Cursor::PRICE].ToString());

    return book;
}

bool ModifyViewBase::IsIllFormed() {
    m_errors.clear();

    auto error = false;

    auto it = std::find_if(m_inputs.begin(), m_inputs.end(), [](TextBox& box) { return box.Empty(); });
    if (it != m_inputs.end()) {
        error = true;
        m_errors.push_back("[error] 입력이 비어있습니다.\n");
    }

    if (!std::regex_match(m_inputs[IDENTIFIER].ToString(), REGEX_DIGIT)) {
        error = true;
        m_errors.push_back("[error] 식별자에 숫자가 아닌 문자가 있습니다.");
    }

    if (!std::regex_match(m_inputs[RELEASE_DATE].ToString(), REGEX_DATE)) {
        error = true;
        m_errors.push_back("[error] 잘못된 날짜 형식입니다. YYYY/MM/dd 형식으로 입력해주세요.");
    }
    
    if (!std::regex_match(m_inputs[PRICE].ToString(), REGEX_DIGIT)) {
        error = true;
        m_errors.push_back("[error] 가격에 숫자가 아닌 문자가 있습니다.");
    }

    return error;
}

void ModifyViewBase::Reset() {
    m_cursor = 0;
    m_errors.clear();

    for (auto& input : m_inputs) {
        input.Reset();
    }
}

void ModifyViewBase::OnKeyPressed(KeyEvent event) {
    switch (event.Key) {
        case KeyType::Up:
            if (m_cursor > 0) { --m_cursor; }
            break;

        case KeyType::Down:
            if (m_cursor < ENTER) { ++m_cursor; }
            break;

        case KeyType::Enter:
            if (m_cursor != ENTER) {
                ++m_cursor;
            }
            else if (!IsIllFormed()) {
                auto book = BuildBook(m_inputs);
                this->OnVerified(std::move(book));
            }
            break;

        default:
            if (m_cursor < ENTER) {
                m_inputs[m_cursor].OnKeyPressed(event);
            }
            break;
    }
}

void ModifyViewBase::OnRender() {
    std::printf("%s\n", m_title.c_str());

    for (auto i = 0; i <= PRICE; i++) {
        std::printf("%s%s%s\n", (i == m_cursor ? CURSOR_PRESENT : CURSOR_NOT_PRESENT), INPUTS[i], m_inputs[i].ToString().c_str());
    }

    std::printf("\n");

    for (const auto* message : m_errors) {
        std::printf("%s\n", message);
    }

    std::printf("%s        << 확인 >>\n", (m_cursor == ENTER ? CURSOR_PRESENT : CURSOR_NOT_PRESENT));
}
