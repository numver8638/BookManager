#pragma once

#include <string>

class DrawContext;

enum class KeyType {
    Unknown,
    Character,
    Escape,
    Backspace,
    Up,
    Down,
    Left,
    Right,
    Enter
};

struct KeyEvent {
    KeyType Key = KeyType::Unknown;
    int Char = 0;
};

class View {
    friend class ViewManager;

private:
    std::string m_name;
    bool m_updateRequired = false;
    bool m_leave = false;

public:
    View(std::string name)
        : m_name(std::move(name)) {}


    ~View() = default;

    virtual bool IsModal() const { return false; }

    void RequireUpdate() { m_updateRequired = true; }

    const std::string& GetName() const { return m_name; }

    virtual void OnEnter() {}

    virtual void OnKeyPressed(KeyEvent event) {}

    virtual void OnRender() {}

    virtual void OnModalClosed(int returnID) {}

    void Leave() { m_leave = true; }
};

class ModalView : public View {
private:
    int m_return = 0;

public:
    explicit ModalView(std::string name)
        : View(std::move(name)) {}

    bool IsModal() const override { return true; }

    void SetReturn(int value) { m_return = value; }

    int GetReturn() const { return m_return; }
};
