#ifndef APP_H
#define APP_H

#include <windows.h>
#include <windowsx.h>
#include <winbase.h>
#include <vector>
#include "Level.h"

LRESULT MessagesHandler(
        HWND window_handle, UINT message_code, WPARAM w_param, LPARAM l_param);

class App {
  public:
    App();
    ~App() = default;

    static App* getInstance();

    int exec(HINSTANCE instance_handle_arg, int n_cmd_show);
    void nextLevel();

    HINSTANCE getHandleInstance();
    WNDCLASS &getWindowClass();

    LRESULT handleMessage(HWND window_handle, UINT message_code, WPARAM w_param, LPARAM l_param);

private:
    static App* instance;

    void createControls(HWND hwnd);
    void addMenus(HWND hwnd);

    std::vector<Level*> levels;
    int currentLevel;

    HINSTANCE handle_instance;
    HWND window_handle;
    WNDCLASS window_class;

    HWND progressBar;
    HWND text;
    HWND statusBar;
};

#endif
