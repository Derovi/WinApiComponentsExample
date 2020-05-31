#include <iostream>
#include "ButtonLevel.h"
#include "../app.h"
#include "../controls.h"

void ButtonLevel::load(HWND hwnd) {
    button = CreateWindowW(L"Button", L"КНОПКА",
                           WS_VISIBLE | WS_CHILD,
                           150, 260, 100, 40, hwnd, (HMENU) ID_BUTTON_1, NULL, NULL);
}

void ButtonLevel::unload() {
    DestroyWindow(button);
}

void ButtonLevel::handleMessage(HWND whnd, UINT message_code, WPARAM w_param, LPARAM l_param) {
    switch (message_code) {
        case WM_COMMAND:
            if (LOWORD(w_param) == ID_BUTTON_1) {
                App::getInstance()->nextLevel();
            }
            break;
    }
}

std::wstring ButtonLevel::getText() {
    return L"Используйте устройство \"Мышь\" и нажмите на кнопку. "
           "(Мышь - координатное устройство для управления курсором и отдачи различных команд компьютеру, "
           "а не небольшой грызун с острой мордочкой, усиками и длинным хвостом, как это принято считать "
           "у людей, которые еще не знакомы с компьютерной техникой)";
}
