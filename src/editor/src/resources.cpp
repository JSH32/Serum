#include "resources.h"

void* getFileAsBuffer(cmrc::file& file) {
    return (void*)&*file.begin();
}