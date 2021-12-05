#pragma once

#include <string>
#include <vector>

struct Book;

enum class OrderBy {
    Identifier,
    Name
};

class BookManager final {
private:
    std::string m_db;

    std::vector<Book*> m_books;
    std::vector<Book*> m_indexOfIdentifier; // sorted by identifier, stored in index.
    std::vector<Book*> m_indexOfName; // sorted by name, stored in index.

    void LoadData();

    void SaveData();

public:
    BookManager(const std::string& path)
        : m_db(path) {
        LoadData();
    }

    ~BookManager();

    std::vector<Book*> GetBooks(OrderBy by, int begin, int count);

    std::vector<Book*> SearchByName(const std::string& partialName) const;

    void AddBook(Book book);

    void RemoveBook(Book* book);

    size_t GetBookCount() const { return m_books.size(); }
};