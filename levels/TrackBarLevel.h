#ifndef TRACKBARLEVEL_H
#define TRACKBARLEVEL_H

#include "../Level.h"

class TrackBarLevel : public Level {
public:
    void load(HWND window_handle) override;

    void unload() override;

    void handleMessage(HWND window_handle, UINT message_code, WPARAM w_param, LPARAM l_param) override;

    std::wstring getText() override;

private:
    HWND trackbar;

    bool finished = false;
};

#endif  // TRACKBARLEVEL_H
