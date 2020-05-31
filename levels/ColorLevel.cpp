#include <iostream>
#include "ColorLevel.h"
#include "../app.h"
#include "../controls.h"

void ColorLevel::load(HWND hwnd) {
    button = CreateWindowW(L"Button", L"Выбрать цвет",
                           WS_VISIBLE | WS_CHILD,
                           150, 260, 100, 40, hwnd, (HMENU) ID_BUTTON_2, NULL, NULL);
}

void ColorLevel::unload() {
    DestroyWindow(button);
}

void ColorLevel::handleMessage(HWND hwnd, UINT message_code, WPARAM w_param, LPARAM l_param) {
    switch (message_code) {
        case WM_COMMAND:
            if (LOWORD(w_param) == ID_BUTTON_2) {
                RGBTRIPLE color = showColorDialog(hwnd);
                if (color.rgbtBlue >= color.rgbtRed) {
                    MessageBeep(MB_HELP);
                    MessageBoxW(hwnd,
                                L"Ваш цвет больше синий, чем красный. "
                                "Если у вас есть проблемы с цветовосприятием, "
                                "пропустите этот уровень, используя контекстное меню!",
                                L"Ошибка!",
                                MB_HELP);
                } else if (color.rgbtGreen >= color.rgbtRed) {
                    MessageBeep(MB_HELP);
                    MessageBoxW(hwnd,
                                L"Ваш цвет больше зеленый, чем красный. "
                                "Если у вас есть проблемы с цветовосприятием, "
                                "пропустите этот уровень, используя контекстное меню!",
                                L"Ошибка!",
                                MB_HELP);
                } else {
                    App::getInstance()->nextLevel();
                }
            }
            break;
    }
}

RGBTRIPLE ColorLevel::showColorDialog(HWND hwnd) {
    CHOOSECOLOR color;
    static COLORREF crCustClr[16];
    ZeroMemory(&color, sizeof(color));
    color.lStructSize = sizeof(color);
    color.hwndOwner = hwnd;
    color.lpCustColors = (LPDWORD) crCustClr;
    color.rgbResult = RGB(0, 255, 0);
    color.Flags = CC_FULLOPEN | CC_RGBINIT;
    ChooseColor(&color);
    std::cout << color.rgbResult << std::endl;
    RGBTRIPLE rgb;
    rgb.rgbtRed = GetRValue(color.rgbResult);
    rgb.rgbtGreen = GetGValue(color.rgbResult);
    rgb.rgbtBlue = GetBValue(color.rgbResult);
    return rgb;
}

std::wstring ColorLevel::getText() {
    return L"Выберите красный цвет. Для этого нажмите на кнопку \"Выбрать цвет\""
           " (см. первое задание, если возникнут трудности). Затем в диалоговом окне "
           "выберите красный цвет.";
}
