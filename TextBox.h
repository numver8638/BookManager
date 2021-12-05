#pragma once

#include <string>
#include <vector>

struct KeyEvent;

class TextBox final {
private:
    std::vector<char> m_buffer;

public:
    void Reset() { m_buffer.clear(); }

    size_t Length() const { return m_buffer.size(); }

    bool Empty() const { return m_buffer.empty(); }

    void Set(const std::string& str) { m_buffer.assign(str.begin(), str.end()); }

    std::string ToString() const { return std::string(m_buffer.begin(), m_buffer.end()); }

    void OnKeyPressed(KeyEvent);
};