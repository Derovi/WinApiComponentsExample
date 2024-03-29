#ifndef EDITLEVEL_H
#define EDITLEVEL_H

#include "../Level.h"

class EditLevel : public Level {
public:
    void load(HWND window_handle) override;

    void unload() override;

    void handleMessage(HWND window_handle, UINT message_code, WPARAM w_param, LPARAM l_param) override;

    std::wstring getText() override;

private:
    HWND edit;

    int currentCount = 0;
};

#endif  // EDITLEVEL_H
