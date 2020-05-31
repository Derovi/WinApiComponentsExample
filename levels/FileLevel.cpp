#include <iostream>
#include <fstream>
#include "FileLevel.h"
#include "../app.h"
#include "../controls.h"

void FileLevel::load(HWND hwnd) {
    button1 = CreateWindowW(L"Button", L"Сохранить код",
                            WS_VISIBLE | WS_CHILD,
                            140, 240, 120, 25, hwnd, (HMENU) ID_BUTTON_3, NULL, NULL);

    button2 = CreateWindowW(L"Button", L"Загрузить код",
                            WS_VISIBLE | WS_CHILD,
                            140, 270, 120, 25, hwnd, (HMENU) ID_BUTTON_4, NULL, NULL);
}

void FileLevel::unload() {
    DestroyWindow(button1);
    DestroyWindow(button2);
}

void FileLevel::handleMessage(HWND hwnd, UINT message_code, WPARAM w_param, LPARAM l_param) {
    switch (message_code) {
        case WM_COMMAND:
            if (LOWORD(w_param) == ID_BUTTON_3) {
                saveFileDialog(hwnd);
            } else
            if (LOWORD(w_param) == ID_BUTTON_4) {
                openFileDialog(hwnd);
            }
            break;
    }
}

std::wstring FileLevel::getText() {
    return L"Сначала нажмите на кнопку \"Сохранить код\""
           " (см. первое задание, если возникнут трудности). Выберите путь для сохранения файла с кодом "
           "Затем нажмите на кнопку \"Загрузить код\" (см. первое задание, если возникнут трудности) и выберите "
           "файл, в который вы сохранили код.";
}

void FileLevel::openFileDialog(HWND hwnd) {
    OPENFILENAME ofn;
    TCHAR szFile[MAX_PATH];

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = '\0';
    ofn.hwndOwner = hwnd;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = TEXT("All files(*.*)\0*.*\0");
    ofn.nFilterIndex = 1;
    ofn.lpstrInitialDir = NULL;
    ofn.lpstrFileTitle = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&ofn)) {
        LoadFile(hwnd, ofn.lpstrFile);
    }
}

void FileLevel::LoadFile(HWND hwnd, LPSTR file) {
    HANDLE hFile;
    DWORD dwSize;
    DWORD dw;

    LPBYTE lpBuffer = NULL;

    hFile = CreateFile(file, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
    dwSize = GetFileSize(hFile, NULL);
    lpBuffer = (LPBYTE) HeapAlloc(GetProcessHeap(),
                                  HEAP_GENERATE_EXCEPTIONS, dwSize + 1);
    ReadFile(hFile, (LPWSTR)lpBuffer, dwSize, &dw, NULL);
    CloseHandle(hFile);
    lpBuffer[dwSize] = 0;

    if (std::string((LPSTR) lpBuffer) == "HH_557UFnj14.5") {
        App::getInstance()->nextLevel();
    } else {
        MessageBeep(MB_HELP);
        MessageBoxW(hwnd,
                    L"Код не совпадает! Выберите другой файл.",
                    L"Ошибка!",
                    MB_HELP);
    }
    HeapFree(GetProcessHeap(), 0, lpBuffer);
}

void FileLevel::saveFileDialog(HWND hwnd) {
    OPENFILENAME ofn;
    TCHAR szFile[MAX_PATH];

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = '\0';
    ofn.hwndOwner = hwnd;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = TEXT("All files(*.*)\0*.*\0");
    ofn.nFilterIndex = 1;
    ofn.lpstrInitialDir = NULL;
    ofn.lpstrFileTitle = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetSaveFileName(&ofn)) {
        saveFile(hwnd, ofn.lpstrFile);
    }
}

void FileLevel::saveFile(HWND hwnd, LPSTR filename) {
    std::ofstream file;
    file.open(std::string(filename));
    file << "HH_557UFnj14.5";
    file.close();
}
