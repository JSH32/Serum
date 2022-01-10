#include "resources.h"

void* getFileAsBuffer(const cmrc::file& file) {
    return (void*)&*file.begin();
}