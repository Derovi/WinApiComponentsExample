#ifndef SAVEFILELEVEL_H
#define SAVEFILELEVEL_H

#include "../Level.h"

class FileLevel : public Level {
public:
    void load(HWND window_handle) override;

    void unload() override;

    void handleMessage(HWND window_handle, UINT message_code, WPARAM w_param, LPARAM l_param) override;

    std::wstring getText() override;

    void openFileDialog(HWND hwnd);
    void saveFileDialog(HWND hwnd);

private:
    HWND button1;
    HWND button2;

    void LoadFile(HWND hwnd, LPSTR file);
    void saveFile(HWND hwnd, LPSTR filename);
};
#endif  // SAVEFILELEVEL_H
