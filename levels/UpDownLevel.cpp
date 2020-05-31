#include <iostream>
#include "UpDownLevel.h"
#include "../app.h"
#include "../controls.h"
#include <commctrl.h>

void UpDownLevel::load(HWND hwnd) {
    INITCOMMONCONTROLSEX icex;
    icex.dwICC = ICC_STANDARD_CLASSES;    // Set the Initialization Flag value.
    InitCommonControlsEx(&icex);          // Initialize the Common Controls Library to use
    // Buttons, Edit Controls, Static Controls, Listboxes,
    // Comboboxes, and  Scroll Bars.
    RECT rcClient;
    GetClientRect(hwnd, &rcClient);
    buddy = CreateWindowEx(WS_EX_LEFT | WS_EX_CLIENTEDGE | WS_EX_CONTEXTHELP,    //Extended window styles.
                   WC_EDIT,
                   NULL,
                   WS_CHILDWINDOW | WS_VISIBLE | WS_BORDER    // Window styles.
                   | ES_NUMBER | ES_LEFT,                     // Edit control styles.
                   100, 260,
                   200, 25,
                   hwnd,
                   NULL,
                   App::getInstance()->getHandleInstance(),
                   NULL);

    upDown = CreateWindowEx(WS_EX_LEFT | WS_EX_LTRREADING,
                              UPDOWN_CLASS,
                              NULL,
                              WS_CHILDWINDOW | WS_VISIBLE
                              | UDS_AUTOBUDDY | UDS_SETBUDDYINT | UDS_ALIGNRIGHT | UDS_ARROWKEYS | UDS_HOTTRACK,
                              0, 0,
                              0, 0,         // Set to zero to automatically size to fit the buddy window.
                              hwnd,
                              NULL,
                              App::getInstance()->getHandleInstance(),
                              NULL);

    SendMessage(upDown, UDM_SETPOS, 0, MAKELPARAM(5, 0));    // Sets the controls direction
    SendMessage(upDown, UDM_SETRANGE, 0, MAKELPARAM(10, -10));    // Sets the controls direction
    // and range.
}

void UpDownLevel::unload() {
    DestroyWindow(upDown);
    DestroyWindow(buddy);
}

void UpDownLevel::handleMessage(HWND whnd, UINT message_code, WPARAM w_param, LPARAM l_param) {
    //std::cout << "handle! " << currentCount << std::endl;
    switch (message_code) {
        case WM_NOTIFY:
            if (((LPNMHDR) l_param)->code == UDN_DELTAPOS) {
                auto lpnmud = (LPNMUPDOWN) l_param;
                count += lpnmud->iDelta;
                if (count == -1) {
                    App::getInstance()->nextLevel();
                }
            }
            break;
    }
}

std::wstring UpDownLevel::getText() {
    return L"Используйте стрелочки и установите значение -1.";
}
