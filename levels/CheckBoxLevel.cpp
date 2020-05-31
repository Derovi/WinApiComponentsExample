#include <iostream>
#include "CheckBoxLevel.h"
#include "../app.h"
#include "../controls.h"

void CheckBoxLevel::load(HWND hwnd) {
    checkbox = CreateWindowW(L"Button", L"Windows - увлекательно",
                           WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
                           100, 230, 300, 20, hwnd, (HMENU) ID_CHECKBOX_1, NULL, NULL);

    checkbox = CreateWindowW(L"Button", L"Win Api - современно",
                             WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
                             100, 260, 300, 20, hwnd, (HMENU) ID_CHECKBOX_2, NULL, NULL);
}

void CheckBoxLevel::unload() {
    DestroyWindow(checkbox);
}

void CheckBoxLevel::handleMessage(HWND hwnd, UINT message_code, WPARAM w_param, LPARAM l_param) {
    switch (message_code) {
        case WM_COMMAND:
            if (LOWORD(w_param) == ID_CHECKBOX_1) {
                BOOL checked = IsDlgButtonChecked(hwnd, ID_CHECKBOX_1);
                if (checked) {
                    CheckDlgButton(hwnd, ID_CHECKBOX_1, BST_UNCHECKED);
                } else {
                    CheckDlgButton(hwnd, ID_CHECKBOX_1, BST_CHECKED);
                }
            }
            if (LOWORD(w_param) == ID_CHECKBOX_2) {
                BOOL checked = IsDlgButtonChecked(hwnd, ID_CHECKBOX_2);
                if (checked) {
                    CheckDlgButton(hwnd, ID_CHECKBOX_2, BST_UNCHECKED);
                } else {
                    CheckDlgButton(hwnd, ID_CHECKBOX_2, BST_CHECKED);
                }
            }
            if (IsDlgButtonChecked(hwnd, ID_CHECKBOX_1) && IsDlgButtonChecked(hwnd, ID_CHECKBOX_2)) {
                App::getInstance()->nextLevel();
            }
            break;
    }
}

std::wstring CheckBoxLevel::getText() {
    return L"Используйте устройство \"Мышь\" и нажмите на оба Флажка, чтобы их выделить. "
           "Флажок - элемент графического пользовательского интерфейса, позволяющий "
           "пользователю управлять параметром с двумя состояниями — ☑ включено и ☐ отключено. "
           "Спортивным пользователям стоит научится отличать Флажок в контексте операционной системы "
           "Windows и в контексте Street workout.";
}
