#ifndef COLORLEVEL_H
#define COLORLEVEL_H

#include "../Level.h"

class ColorLevel : public Level {
public:
    void load(HWND window_handle) override;

    void unload() override;

    void handleMessage(HWND window_handle, UINT message_code, WPARAM w_param, LPARAM l_param) override;

    std::wstring getText() override;

    RGBTRIPLE ShowColorDialog(HWND hwnd);

private:
    HWND button;
};

#endif  // COLORLEVEL_H
