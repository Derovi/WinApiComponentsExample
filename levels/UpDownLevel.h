#ifndef WINAPI2_UPDOWNLEVEL_H
#define WINAPI2_UPDOWNLEVEL_H

#include "../Level.h"

class UpDownLevel : public Level {
public:
    void load(HWND window_handle) override;

    void unload() override;

    void handleMessage(HWND window_handle, UINT message_code, WPARAM w_param, LPARAM l_param) override;

    std::wstring getText() override;

private:
    HWND upDown;

    int count = 5;
};

#endif  // UPDOWNLEVEL_H
