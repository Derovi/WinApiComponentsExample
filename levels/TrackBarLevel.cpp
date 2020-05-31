#include <iostream>
#include "TrackBarLevel.h"
#include <commctrl.h>
#include "../app.h"
#include "../controls.h"

void TrackBarLevel::load(HWND hwnd) {
    trackbar = CreateWindowW(TRACKBAR_CLASSW, L"Trackbar Control",
                         WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS,
                         100, 260, 200, 30, hwnd, (HMENU) ID_TRACKBAR_1, NULL, NULL);

    SendMessageW(trackbar, TBM_SETRANGE,  TRUE, MAKELONG(0, 100));
    SendMessageW(trackbar, TBM_SETPAGESIZE, 0,  10);
    SendMessageW(trackbar, TBM_SETTICFREQ, 10, 0);
    SendMessageW(trackbar, TBM_SETPOS, FALSE, 0);
    //SendMessageW(trackbar, TBM_SETBUDDY, TRUE, (LPARAM) hLeftLabel);
    //SendMessageW(trackbar, TBM_SETBUDDY, FALSE, (LPARAM) hRightLabel);
}

void TrackBarLevel::unload() {
    DestroyWindow(trackbar);
}

void TrackBarLevel::handleMessage(HWND whnd, UINT message_code, WPARAM w_param, LPARAM l_param) {
    if (finished) {
        return;
    }
    //std::cout << "handle! " << currentCount << std::endl;
    switch (message_code) {
        case WM_HSCROLL:
            LRESULT pos = SendMessageW(trackbar, TBM_GETPOS, 0, 0);
            if (pos == 100) {
                finished = true;
                App::getInstance()->nextLevel();
            }
            break;
    }
}

std::wstring TrackBarLevel::getText() {
    return L"Используйте Пользунок и установите максимальное значение.";
}
