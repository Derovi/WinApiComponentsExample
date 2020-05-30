#include <windows.h>
#include "app.h"

INT WinMain(HINSTANCE instance_handle_arg, HINSTANCE,
            LPSTR /* command_line */, int n_cmd_show) {
    return App().exec(instance_handle_arg, n_cmd_show);
}
