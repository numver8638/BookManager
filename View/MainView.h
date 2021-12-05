#pragma once

#include "../View.h"

class MainView final : public View {
private:
    int m_cursor = 0;

public:
    MainView()
        : View("main") {}

    void OnEnter() override;

    void OnKeyPressed(KeyEvent event) override;

    void OnRender() override;
};