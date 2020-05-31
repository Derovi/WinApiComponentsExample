#ifndef LEVEL_H
#define LEVEL_H

#include <windows.h>
#include <windowsx.h>
#include <winbase.h>
#include <string>

class Level {
public:
    virtual void load(HWND window_handle) = 0;
    virtual void unload() = 0;
    virtual void handleMessage(HWND window_handle, UINT message_code, WPARAM w_param, LPARAM l_param) = 0;
    virtual std::wstring getText() = 0;

    virtual ~Level() = default;
};

#endif  // LEVEL_H
