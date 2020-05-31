#include <iostream>
#include "CalendarLevel.h"
#include "../app.h"
#include <commctrl.h>
#include <string>
#include <strsafe.h>
#include "../controls.h"

void CalendarLevel::load(HWND hwnd) {
    calendar = CreateWindowW(MONTHCAL_CLASSW, L"",
                           WS_BORDER | WS_CHILD | WS_VISIBLE | MCS_NOTODAYCIRCLE,
                           100, 100, 200, 175, hwnd, (HMENU) ID_CALENDAR_1, NULL, NULL);

    MessageBoxW(hwnd, L"Уи́льям Ге́нри Гейтс III (англ. William Henry Gates III; 28 октября 1955, Сиэтл, Вашингтон), "
                      L"более известный как Билл Гейтс (англ. Bill Gates) — американский предприниматель и общественный деятель, "
                      L"филантроп, один из создателей (совместно с Полом Алленом) и бывший крупнейший акционер компании Microsoft - "
                      L"компании, которая разработала операционную систему Windows. Выберите на календаре дату его рождения. "
                      L"(Вы можете выбрать 2015 год рождения, чтобы быстрее справится с заданием!)",
                      L"Задание", MB_ICONQUESTION);
}

void CalendarLevel::unload() {
    DestroyWindow(calendar);
}

void CalendarLevel::handleMessage(HWND whnd, UINT message_code, WPARAM w_param, LPARAM l_param) {
    LPNMHDR lpNmHdr;

    switch (message_code) {
        case WM_NOTIFY:
            lpNmHdr = (LPNMHDR) l_param;

            if (lpNmHdr->code == MCN_SELECT) {
                SYSTEMTIME time;

                ZeroMemory(&time, sizeof(SYSTEMTIME));
                SendMessage(calendar, MCM_GETCURSEL, 0, (LPARAM) &time);

                if (time.wDay == 28 && time.wMonth == 10 && (time.wYear == 1955 || time.wYear == 2015)) {
                    App::getInstance()->nextLevel();
                } else {
                    MessageBeep(MB_HELP);
                    MessageBoxW(whnd,
                                L"Выберите 28 октября (1955/2015) г.",
                                L"Неверная дата",
                                MB_HELP);
                }
            }

            break;
    }
}

std::wstring CalendarLevel::getText() {
    return L"Выберите на календаре 28 октября (1955/2015) г.";
}
