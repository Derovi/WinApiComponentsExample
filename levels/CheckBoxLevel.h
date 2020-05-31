#ifndef CHECKBOXLEVEL_H
#define CHECKBOXLEVEL_H


#include "../Level.h"

class CheckBoxLevel : public Level {
public:
    void load(HWND window_handle) override;

    void unload() override;

    void handleMessage(HWND window_handle, UINT message_code, WPARAM w_param, LPARAM l_param) override;

    std::wstring getText() override;

private:
    HWND checkbox;

    int ID_BUTTON = 1;
};

#endif  // CHECKBOXLEVEL_H
