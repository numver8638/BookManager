#include "BookManager.h"

#include <algorithm>
#include <functional>
#include <iostream>

#include "Book.h"
#include "Streams.h"

constexpr uint32_t DB_SIGNATURE = 0x31564244; // DBV1

static inline std::vector<Book*> GetBooksInternal(const std::vector<Book*>& indexes, size_t begin, size_t count) {
    size_t actualCount = (indexes.size() > (begin + count)) ? count : (indexes.size() - begin);
    auto itBegin = indexes.begin() + begin;
    auto itEnd = itBegin + actualCount;

    return { itBegin, itEnd };
}

static inline void UpdateIndex(std::vector<Book*>& indexes, Book* value, std::function<bool(Book*)> fn) {
    auto it = std::find_if(indexes.begin(), indexes.end(), fn);
    indexes.insert(it, value);
}

/*
 * Serialize format: int - int, string - size_t char[]
 */

BinaryInputStream& operator >>(BinaryInputStream& IS, Book& book) {
    IS >> book.Identifier >> book.Name >> book.Author >> book.ReleaseDate >> book.Publisher >> book.Price;
    return IS;
}

BinaryOutputStream& operator <<(BinaryOutputStream& OS, const Book& book) {
    OS << book.Identifier << book.Name << book.Author << book.ReleaseDate << book.Publisher << book.Price;
    return OS;
}

void BookManager::LoadData() {
    BinaryInputStream file(m_db);

    if (!file.IsOpen()) {
        std::cerr << "[warning] Cannot load database." << std::endl;
        return;
    }

    uint32_t signature, count;
    file >> signature >> count;

    if (signature != DB_SIGNATURE) {
        std::cerr << "[error] Invalid database. Data cannot be loaded." << std::endl;
        return;
    }

    uint32_t i; // for check.
    for (i = 0; i < count && !file.IsEOF(); i++) {
        Book book;
        file >> book;

        AddBook(std::move(book));
    }

    if (i != count) {
        std::cerr << "[warning] Data was truncated." << std::endl;
    }
}

void BookManager::SaveData() {
    BinaryOutputStream file(m_db);

    if (!file.IsOpen()) {
        std::cerr << "[error] Cannon save database. Data might be lost." << std::endl;
        return;
    }

    file << DB_SIGNATURE << (uint32_t)m_books.size();
    for (auto* book : m_books) {
        file << *book;
    }
}

BookManager::~BookManager() {
    SaveData();
    std::for_each(m_books.begin(), m_books.end(), [](Book* ptr) { delete ptr; });
}

std::vector<Book*> BookManager::GetBooks(OrderBy by, int begin, int count) {
    switch (by) {
    case OrderBy::Identifier:
        return GetBooksInternal(m_indexOfIdentifier, begin, count);

    case OrderBy::Name:
        return GetBooksInternal(m_indexOfName, begin, count);

    default:
        return {};
    }
}

std::vector<Book*> BookManager::SearchByName(const std::string& partialName) const {
    std::vector<Book*> books;
    for (auto* book : m_books) {
        if (book->Name.find(partialName, 0) != std::string::npos) {
            books.emplace_back(book);
        }
    }

    return books;
}

void BookManager::AddBook(Book book) {
    m_books.push_back(new Book(std::move(book)));

    Book* ref = m_books.back();

    UpdateIndex(m_indexOfIdentifier, ref, [&ref](Book* book) {
        return book->Identifier > ref->Identifier;
    });
    UpdateIndex(m_indexOfName, ref, [&ref](Book* book) {
        return book->Name > ref->Name;
    });

    SaveData();
}

void BookManager::RemoveBook(Book* book) {
    auto remove = [](std::vector<Book*>& vec, Book* val) {
        auto it = std::find(vec.begin(), vec.end(), val);

        vec.erase(it);
    };

    remove(m_books, book);
    remove(m_indexOfIdentifier, book);
    remove(m_indexOfName, book);

    delete book;

    SaveData();
}