#pragma once

#include <string>

#include "../View.h"

class ConfirmModalView final : public ModalView {
private:
    std::string m_message;
    const int m_yes, m_no;

    int m_cursor = 0;

public:
    ConfirmModalView(std::string message, int yes, int no)
        : ModalView("confirm_modal"), m_message(std::move(message)), m_yes(yes), m_no(no) {}
    
    void OnKeyPressed(KeyEvent) override;

    void OnRender() override;
};