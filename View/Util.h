#pragma once

#include <algorithm>
#include <tuple>

#include "../Book.h"

inline int CountRadix(int value) {
    int radix = 1;
    while (value / 10) { value /= 10; ++radix; }
    return radix;
}

inline 
std::tuple<int, int, int, int, int> CalcuateWidth(const std::vector<Book*>& books) {
    int identifier_padding = 0,
        name_padding = 0,
        author_padding = 0,
        publisher_padding = 0,
        price_padding = 0;
    
    for (const auto* book : books) {
        identifier_padding = std::max(identifier_padding, book->Identifier);
        name_padding = std::max(name_padding, (int)book->Name.length());
        author_padding = std::max(name_padding, (int)book->Author.length());
        publisher_padding = std::max(name_padding, (int)book->Publisher.length());
        price_padding = std::max(name_padding, book->Price);
    }

    return { CountRadix(identifier_padding), name_padding, author_padding, publisher_padding, CountRadix(price_padding) };
}