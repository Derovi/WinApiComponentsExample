#include <iostream>
#include "EditLevel.h"
#include "../app.h"
#include "../controls.h"

void EditLevel::load(HWND hwnd) {
    edit = CreateWindowW(L"Edit", NULL,
                         WS_CHILD | WS_VISIBLE | WS_BORDER,
                         100, 260, 200, 25, hwnd, (HMENU) ID_EDIT_1,
                         NULL, NULL);
}

void EditLevel::unload() {
    DestroyWindow(edit);
}

void EditLevel::handleMessage(HWND whnd, UINT message_code, WPARAM w_param, LPARAM l_param) {
    //std::cout << "handle! " << currentCount << std::endl;
    switch (message_code) {
        case WM_COMMAND:
            if (HIWORD(w_param) == EN_CHANGE) {
                int len = GetWindowTextLengthW(edit) + 1;
                wchar_t text[len];
                GetWindowTextW(edit, text, len);
                if (std::wstring(text) == std::wstring(L"Эйяфьядлайёкюдль")) {
                    App::getInstance()->nextLevel();
                    break;
                }
                ++currentCount;
                if (currentCount % 20 == 0) {
                    MessageBeep(MB_HELP);
                    MessageBoxW(whnd,
                                L"У вас явно не хватает навыков для прохождения этого задания. "
                                "Обратитесь к более опытному пользователю ПК за помощью! "
                                "Подсказка: Обратите внимание на букву ё и на регистр.",
                                L"Что-то не так",
                                MB_HELP);
                }
            }
            break;
    }
}

std::wstring EditLevel::getText() {
    return L"Используйте устройство \"Мышь\" и нажмите на поле ввода текста, выбрав его. "
           "Затем используйте КЛАВИАТУРУ - устройство, позволяющее пользователю вводить информацию в"
           " компьютер с помощью пальцев ваших рук или иных конечностей, не привышающих "
           "нескольких сантиметров в диамтре (Иначе возможны случайные нажатия соседних клавиш). "
           "Введите текст \"Эйяфьядлайёкюдль\".";
}
