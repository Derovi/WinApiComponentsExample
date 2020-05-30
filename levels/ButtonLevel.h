#ifndef BUTTONLEVEL_H
#define BUTTONLEVEL_H

#include "../Level.h"

class ButtonLevel : public Level {
public:
    void load(HWND window_handle) override;

    void unload() override;

    void handleMessage(HWND window_handle, UINT message_code, WPARAM w_param, LPARAM l_param) override;

    std::wstring getText() override;

private:
    HWND button;

    int ID_BUTTON = 1;
};

#endif  // BUTTONLEVEL_H
