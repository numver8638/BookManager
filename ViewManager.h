#pragma once

#include <initializer_list>
#include <string>
#include <unordered_map>
#include <stack>

class View;
class ModalView;
enum class KeyType;

// All member functions & variables are static because this is singleton.
class ViewManager final {
private:
    static std::unordered_map<std::string, View*> m_map;
    static std::stack<View*> m_views;

    static bool m_exitRequested;

    static bool HandleLeave(View*);
    static void HandleRender(View*);
    static KeyType HandleEscape();
    static void HandleKeyPress(View*);

public:
    ViewManager() = delete;
    ViewManager(const ViewManager&) = delete;
    ViewManager(ViewManager&&) = delete;
    ViewManager& operator =(const ViewManager&) = delete;
    ViewManager& operator =(ViewManager&) = delete;

    static void RegisterView(std::initializer_list<View*>);
    static void Push(const std::string& name);
    static void PushModal(ModalView* view);
    static int StartLoop();

    static void RequestExit() { m_exitRequested = true; }
};
