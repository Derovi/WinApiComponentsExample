#ifndef RADIOBUTTONDIALOGLEVEL_H
#define RADIOBUTTONDIALOGLEVEL_H

#include "../Level.h"

LRESULT DialogMessagesHandler(
        HWND window_handle, UINT message_code, WPARAM w_param, LPARAM l_param);

class RadioButtonDialogLevel : public Level {
public:
    void load(HWND window_handle) override;

    void unload() override;

    void handleMessage(HWND window_handle, UINT message_code, WPARAM w_param, LPARAM l_param) override;

    std::wstring getText() override;

    void showDialog(HWND hwnd);

private:
    HWND button;
    HWND dialog;
};

#endif  // RADIOBUTTONDIALOGLEVEL_H
