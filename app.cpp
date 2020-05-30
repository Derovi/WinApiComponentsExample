#include <iostream>
#include "app.h"
#include "levels/ButtonLevel.h"
#include <commctrl.h>

App *App::instance = nullptr;

App::App() : currentLevel(0) {
    levels.push_back(new ButtonLevel());
    levels.push_back(new ButtonLevel());
    levels.push_back(new ButtonLevel());
    levels.push_back(new ButtonLevel());
    instance = this;
}

App *App::getInstance() {
    return instance;
}

#define ID_BEEP 1
#define ID_QUIT 2

int App::exec(HINSTANCE instance_handle_arg, int n_cmd_show) {
    MSG msg;
    WNDCLASSW wc = {0};
    wc.lpszClassName = L"Buttons";
    wc.hInstance = instance_handle_arg;
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpfnWndProc = MessagesHandler;
    wc.hCursor = LoadCursor(0, IDC_ARROW);

    RegisterClassW(&wc);
    window_handle = CreateWindowW(wc.lpszClassName, L"Buttons",
                                  WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE,
                                  600, 600, 400, 400, 0, 0, instance_handle_arg, 0);

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int) msg.wParam;
}

HINSTANCE App::getHandleInstance() {
    return handle_instance;
}

WNDCLASS &App::getWindowClass() {
    return window_class;
}

LRESULT App::handleMessage(HWND hwnd, UINT msg,
                           WPARAM wParam, LPARAM lParam) {
    levels[currentLevel]->handleMessage(hwnd, msg, wParam, lParam);
    switch (msg) {
        case WM_CREATE:
            createControls(hwnd);
            levels.front()->load(hwnd);
            break;
        case WM_COMMAND:
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProcW(hwnd, msg, wParam, lParam);
    }
    return 0;
}

void App::nextLevel() {
    SendMessage(progressBar, PBM_STEPIT, 0, 0);
    if (currentLevel + 1 == levels.size()) {
        // !TODO finish game
        SetWindowTextW(statusBar, (L"Выполнено " + std::to_wstring(levels.size()) +
                                   L" из " + std::to_wstring(levels.size())).c_str());
        MessageBoxW(window_handle, L"Поздравляю! Вы успешно прошли тест по основным компонентам "
                                   "интерфейса приложений операционной системы Windows! Теперь вы "
                                   "в праве называть себя уверенным пользователем этой операционной системы.",
                                   L"Успешное прохождение теста", MB_OK);
        PostQuitMessage(0);
    } else {
        levels[currentLevel]->unload();
        ++currentLevel;
        levels[currentLevel]->load(window_handle);
        SetWindowTextW(text, levels[currentLevel]->getText().c_str());
        SetWindowTextW(statusBar, (L"Выполнено " + std::to_wstring(currentLevel) +
                                   L" из " + std::to_wstring(levels.size())).c_str());
    }
}

void App::createControls(HWND hwnd) {
    INITCOMMONCONTROLSEX icex;

    icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icex.dwICC = ICC_PROGRESS_CLASS;
    InitCommonControlsEx(&icex);

    progressBar = CreateWindowEx(0, PROGRESS_CLASS, NULL,
                                 WS_CHILD | WS_VISIBLE | PBS_SMOOTH,
                                 0, 338, 400, 12, hwnd, NULL, NULL, NULL);

    text = CreateWindowW(L"Static", levels[0]->getText().c_str(),
                         WS_CHILD | WS_VISIBLE | SS_LEFT,
                         20, 20, 300, 230,
                         hwnd, (HMENU) 100, NULL, NULL);

    statusBar = CreateStatusWindowW(WS_CHILD | WS_VISIBLE, (L"Выполнено 0 из " +
                                                            std::to_wstring(levels.size())).c_str(), hwnd, 100);

    SendMessage(progressBar, PBM_SETRANGE, 0, MAKELPARAM(0, levels.size()));
    SendMessage(progressBar, PBM_SETSTEP, 1, 0);
}

void App::addMenus(HWND hwnd) {
    /*HMENU hMenubar;
    HMENU hMenu;

    hMenubar = CreateMenu();
    hMenu = CreateMenu();

    AppendMenuW(hMenu, MF_STRING, IDM_FILE_NEW, L"&New");
    AppendMenuW(hMenu, MF_STRING, IDM_FILE_OPEN, L"&Open");
    AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hMenu, MF_STRING, IDM_FILE_QUIT, L"&Quit");

    AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR) hMenu, L"&File");
    SetMenu(hwnd, hMenubar);*/
}

LRESULT MessagesHandler(HWND window_handle, UINT message_code, WPARAM w_param, LPARAM l_param) {
    return App::getInstance()->handleMessage(window_handle, message_code, w_param, l_param);
}