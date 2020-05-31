#include <iostream>
#include "RadioButtonDialogLevel.h"
#include "../app.h"
#include "../controls.h"

void RadioButtonDialogLevel::load(HWND hwnd) {
    button = CreateWindowW(L"Button", L"Открыть диалог",
                           WS_VISIBLE | WS_CHILD,
                           135, 260, 130, 40, hwnd, (HMENU) ID_BUTTON_5, NULL, NULL);
}

void RadioButtonDialogLevel::unload() {
    DestroyWindow(button);
}

void RadioButtonDialogLevel::handleMessage(HWND hwnd, UINT message_code, WPARAM w_param, LPARAM l_param) {
    switch (message_code) {
        case WM_COMMAND:
            if (LOWORD(w_param) == ID_BUTTON_5) {
                showDialog(hwnd);
            }
            break;
    }
}

void RadioButtonDialogLevel::showDialog(HWND hwnd) {
    std::cout << "show!";
    WNDCLASSEXW dialogClass;
    ZeroMemory(&dialogClass, sizeof(WNDCLASSEX));
    dialogClass.cbClsExtra = NULL;
    dialogClass.cbSize = sizeof(WNDCLASSEX);
    dialogClass.cbWndExtra = NULL;
    dialogClass.hbrBackground = (HBRUSH) COLOR_WINDOW;
    dialogClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    dialogClass.hIcon = NULL;
    dialogClass.hIconSm = NULL;
    dialogClass.hInstance = App::getInstance()->getHandleInstance();
    dialogClass.lpfnWndProc = (WNDPROC) DialogMessagesHandler;
    dialogClass.lpszClassName = L"Dialog";
    dialogClass.lpszMenuName = NULL;
    dialogClass.style = CS_HREDRAW | CS_VREDRAW;

    if (!RegisterClassExW(&dialogClass)) {
        int nResult = GetLastError();
        MessageBoxW(NULL,
                    L"Window class creation failed for window 2",
                    L"Window Class Failed",
                    MB_ICONERROR);
    }

    RECT rect;
    GetWindowRect(hwnd, &rect);

    dialog = CreateWindowExW(NULL,
                            dialogClass.lpszClassName,
                            L"Выберите лишнее",
                            WS_OVERLAPPED,
                            rect.left + 100,
                            rect.top + 50,
                            200,
                            300,
                            NULL,
                            0,
                            App::getInstance()->getHandleInstance(),
                            NULL);

    ShowWindow(dialog, 1);
}

std::wstring RadioButtonDialogLevel::getText() {
    return L"Нажмите на кнопку \"Открыть диалог\""
           " (см. первое задание, если возникнут трудности). Затем в диалоговом окне "
           "с помощью Радиокнопок выберите лишний пункт и нажмите на кнопку \"Отправить\".";
}

LRESULT DialogMessagesHandler(HWND hwnd, UINT message_code, WPARAM w_param, LPARAM l_param) {
    switch (message_code) {
        case WM_CREATE:
            CreateWindowW(L"Button", L"Отправить",
                                   WS_VISIBLE | WS_CHILD,
                                   50, 236, 100, 30, hwnd, (HMENU) ID_BUTTON_6, NULL, NULL);
            break;
        case WM_COMMAND:
            if (LOWORD(w_param) == ID_BUTTON_6) {
                App::getInstance()->nextLevel();
                DestroyWindow(hwnd);
            }
            break;
        default:
            return DefWindowProcW(hwnd, message_code, w_param, l_param);
    }
}
