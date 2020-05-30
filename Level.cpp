#include "Level.h"
#include "app.h"

HINSTANCE Level::getHandleInstance() {
    return App::getInstance()->getHandleInstance();
}
