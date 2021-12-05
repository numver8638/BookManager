#pragma once

#include <cstdio>
#include <string>

class BinaryInputStream {
private:
    FILE* m_file = nullptr;

public:
    BinaryInputStream(const std::string& path) {
        m_file = std::fopen(path.c_str(), "rb");
    }

    ~BinaryInputStream() {
        if (m_file != nullptr) std::fclose(m_file);
    }

    bool IsOpen() const {
        return m_file != nullptr;
    }

    bool IsEOF() const { return std::feof(m_file); }

    template <typename T>
    BinaryInputStream& operator >>(T& value) {
        char buffer[sizeof(T)];
        std::fread(buffer, sizeof(buffer), 1, m_file);
        value = *reinterpret_cast<T*>(buffer);

        return *this;
    }

    BinaryInputStream& operator >>(std::string& value) {
        size_t length;
        *this >> length;

        char* buf = new char[length];
        auto readLength = std::fread(buf, 1, length, m_file);

        value.assign(buf, readLength);

        delete[] buf;
        return *this;
    }
};

class BinaryOutputStream {
private:
    FILE* m_file = nullptr;

public:
    BinaryOutputStream(const std::string& path) {
        m_file = std::fopen(path.c_str(), "wb");
    }

    ~BinaryOutputStream() {
        if (m_file != nullptr) std::fclose(m_file);
    }

    bool IsOpen() const { return m_file != nullptr; }

    template <typename T>
    BinaryOutputStream& operator <<(T value) {
        std::fwrite(&value, sizeof(T), 1, m_file);
        return *this;
    }

    BinaryOutputStream& operator <<(const std::string& value) {
        *this << value.length();
        std::fwrite(value.c_str(), 1, value.length(), m_file);
        return *this;
    }
};