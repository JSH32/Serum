#include "resources.h"

void* GetFileAsBuffer(cmrc::file& file) {
    return (void*)&*file.begin();
}