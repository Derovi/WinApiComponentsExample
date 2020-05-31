#ifndef CALLENDARLEVEL_H
#define CALLENDARLEVEL_H

#include "../Level.h"

class CalendarLevel : public Level {
public:
    void load(HWND window_handle) override;

    void unload() override;

    void handleMessage(HWND window_handle, UINT message_code, WPARAM w_param, LPARAM l_param) override;

    std::wstring getText() override;

private:
    HWND calendar;
};

#endif  // CALLENDARLEVEL_H
