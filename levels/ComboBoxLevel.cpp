#include <iostream>
#include "ComboBoxLevel.h"
#include "../app.h"
#include "../controls.h"

void ComboBoxLevel::load(HWND hwnd) {
    comboBox = CreateWindowW(L"Combobox", NULL,
                         WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
                         100, 260, 200, 120, hwnd, (HMENU) ID_COMBOBOX_1,
                         App::getInstance()->getHandleInstance(), NULL);
    const wchar_t *items[] = { L"Завтрак", L"Обед",
                               L"Ланч", L"Ужин", L"Полдник" };
    for (int index = 0; index < 5; ++index) {
        SendMessageW(comboBox, CB_ADDSTRING, 0, (LPARAM) items[index]);
    }
}

void ComboBoxLevel::unload() {
    DestroyWindow(comboBox);
    finished = true;
}

void ComboBoxLevel::handleMessage(HWND whnd, UINT message_code, WPARAM w_param, LPARAM l_param) {
    if (finished) {
        return;
    }
    if (LOWORD(w_param) != ID_COMBOBOX_1) {
        return;
    }
    switch (message_code) {
        case WM_COMMAND:
            if (HIWORD(w_param) == CBN_SELCHANGE) {
                LRESULT selected = SendMessage(comboBox, CB_GETCURSEL, 0, 0);
                if (selected == 3) {
                    App::getInstance()->nextLevel();
                }
            } else
            if (HIWORD(w_param) == BN_CLICKED) {
                SendMessage(comboBox, CB_SHOWDROPDOWN, (WPARAM) TRUE, 0);
            }
            break;
    }
}

std::wstring ComboBoxLevel::getText() {
    return L"Выберите в списке надпись \"Ужин\".";
}
