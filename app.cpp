#include <iostream>
#include "app.h"
#include "levels/ButtonLevel.h"
#include <commctrl.h>
#include "controls.h"
#include "levels/EditLevel.h"
#include "levels/CheckBoxLevel.h"
#include "levels/CalendarLevel.h"
#include "levels/TrackBarLevel.h"
#include "levels/ComboBoxLevel.h"
#include "levels/UpDownLevel.h"
#include "levels/ColorLevel.h"
#include "levels/FileLevel.h"
#include "levels/RadioButtonDialogLevel.h"

App *App::instance = nullptr;

App::App() : currentLevel(0) {
    levels.push_back(new ButtonLevel());
    levels.push_back(new EditLevel());
    levels.push_back(new CheckBoxLevel());
    levels.push_back(new CalendarLevel());
    levels.push_back(new TrackBarLevel());
    levels.push_back(new UpDownLevel());
    levels.push_back(new ColorLevel());
    levels.push_back(new FileLevel());
    levels.push_back(new RadioButtonDialogLevel());
    levels.push_back(new ComboBoxLevel());
    instance = this;
}

App *App::getInstance() {
    return instance;
}

int App::exec(HINSTANCE instance_handle_arg, int n_cmd_show) {
    MSG msg;
    WNDCLASSW wc = {0};
    wc.lpszClassName = L"WindowsTest";
    wc.hInstance = instance_handle_arg;
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpfnWndProc = MessagesHandler;
    wc.hCursor = LoadCursor(0, IDC_ARROW);

    RegisterClassW(&wc);
    window_handle = CreateWindowW(wc.lpszClassName, L"БГУ. 2-ой семестр. Тест по Windows.",
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

    POINT point;
    HMENU hMenu;

    switch (msg) {
        case WM_CREATE:
            addMenus(hwnd);
            createControls(hwnd);
            levels.front()->load(hwnd);
            break;
        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case ID_MENU_1:
                    nextLevel();
                    break;
                case ID_MENU_2:
                    prevLevel();
                    break;
                case ID_MENU_3:
                    PostQuitMessage(0);
                    break;
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_RBUTTONUP:
            point.x = LOWORD(lParam);
            point.y = HIWORD(lParam);

            hMenu = CreatePopupMenu();
            ClientToScreen(hwnd, &point);

            AppendMenuW(hMenu, MF_STRING, ID_MENU_1, L"&Пропустить уровень");
            AppendMenuW(hMenu, MF_STRING, ID_MENU_2, L"&К прошлому уровню");
            AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL);
            AppendMenuW(hMenu, MF_STRING, ID_MENU_3, L"&Выйти");

            TrackPopupMenu(hMenu, TPM_RIGHTBUTTON, point.x, point.y, 0, hwnd, NULL);
            DestroyMenu(hMenu);
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
        MessageBeep(MB_OK);
        MessageBoxW(window_handle, L"Поздравляю! Вы успешно прошли тест по основным компонентам "
                                   "интерфейса приложений операционной системы Windows! Теперь вы "
                                   "в праве называть себя уверенным пользователем этой операционной системы.",
                    L"Успешное прохождение теста", MB_OK);
        PostQuitMessage(0);
    } else {
        levels[currentLevel]->unload();
        ++currentLevel;
        SetWindowTextW(text, levels[currentLevel]->getText().c_str());
        SetWindowTextW(statusBar, (L"Выполнено " + std::to_wstring(currentLevel) +
                                   L" из " + std::to_wstring(levels.size())).c_str());
        levels[currentLevel]->load(window_handle);
    }
}

void App::createControls(HWND hwnd) {
    INITCOMMONCONTROLSEX icex;

    icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icex.dwICC = ICC_PROGRESS_CLASS;
    InitCommonControlsEx(&icex);

    progressBar = CreateWindowEx(0, PROGRESS_CLASS, NULL,
                                 WS_CHILD | WS_VISIBLE | PBS_SMOOTH,
                                 0, 320, 400, 12, hwnd, NULL, NULL, NULL);

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
    HMENU hMenubar;
    HMENU hMenu;

    hMenubar = CreateMenu();
    hMenu = CreateMenu();

    AppendMenuW(hMenu, MF_STRING, ID_MENU_1, L"&Пропустить уровень");
    AppendMenuW(hMenu, MF_STRING, ID_MENU_2, L"&К прошлому уровню");
    AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hMenu, MF_STRING, ID_MENU_3, L"&Выйти");

    AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR) hMenu, L"&Управление");
    SetMenu(hwnd, hMenubar);
}

void App::prevLevel() {
    if (currentLevel == 0) {
        MessageBeep(MB_ICONINFORMATION);
        return;
    }
    levels[currentLevel]->unload();
    --currentLevel;
    SendMessage(progressBar, PBM_SETPOS, currentLevel, 0);
    SetWindowTextW(text, levels[currentLevel]->getText().c_str());
    SetWindowTextW(statusBar, (L"Выполнено " + std::to_wstring(currentLevel) +
                               L" из " + std::to_wstring(levels.size())).c_str());
    levels[currentLevel]->load(window_handle);
}

LRESULT MessagesHandler(HWND window_handle, UINT message_code, WPARAM w_param, LPARAM l_param) {
    return App::getInstance()->handleMessage(window_handle, message_code, w_param, l_param);
}