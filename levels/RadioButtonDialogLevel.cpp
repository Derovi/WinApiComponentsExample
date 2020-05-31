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

    RegisterClassExW(&dialogClass);

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

            CreateWindowW(L"Button", L"Лишнее",
                          WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
                          20, 20, 120, 180, hwnd, (HMENU) ID_GROUP_1, App::getInstance()->getHandleInstance(), NULL);
            CreateWindowW(L"Button", L"Windows",
                          WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                          30, 50, 100, 30, hwnd, (HMENU) ID_RADIO_1, App::getInstance()->getHandleInstance(), NULL);
            CreateWindowW(L"Button", L"Linux",
                          WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                          30, 75, 100, 30, hwnd, (HMENU) ID_RADIO_2, App::getInstance()->getHandleInstance(), NULL);
            CreateWindowW(L"Button", L"Android",
                          WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                          30, 100, 100, 30, hwnd, (HMENU) ID_RADIO_3, App::getInstance()->getHandleInstance(), NULL);
            CreateWindowW(L"Button", L"Морковь",
                          WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                          30, 125, 100, 30, hwnd, (HMENU) ID_RADIO_4, App::getInstance()->getHandleInstance(), NULL);
            CreateWindowW(L"Button", L"IOS",
                          WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                          30, 150, 100, 30, hwnd, (HMENU) ID_RADIO_5, App::getInstance()->getHandleInstance(), NULL);

            break;
        case WM_COMMAND:
            if (HIWORD(w_param) == BN_CLICKED) {
                switch (LOWORD(w_param)) {
                    case ID_BUTTON_6:
                        if (IsDlgButtonChecked(hwnd, ID_RADIO_4)) {
                            App::getInstance()->nextLevel();
                        } else {
                            MessageBeep(MB_HELP);
                            MessageBoxW(hwnd,
                                        L"Обратитесь за помощью к более опытному пользователю ПК.",
                                        L"Ошибка!",
                                        MB_HELP);
                        }
                        DestroyWindow(hwnd);
                        break;
                }
            }
        default:
            return DefWindowProcW(hwnd, message_code, w_param, l_param);
    }
}
