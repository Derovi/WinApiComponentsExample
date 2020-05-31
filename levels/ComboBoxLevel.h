#ifndef COMBOBOXLEVEL_H
#define COMBOBOXLEVEL_H

#include <vector>
#include "../Level.h"

class ComboBoxLevel : public Level {
public:

    void load(HWND window_handle) override;

    void unload() override;

    void handleMessage(HWND window_handle, UINT message_code, WPARAM w_param, LPARAM l_param) override;

    std::wstring getText() override;

private:
    HWND comboBox;
};

#endif  // COMBOBOXLEVEL_H
