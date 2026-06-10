#pragma once
#include "utils/type_config.h"
#include <cstdint>

class Texture {
public:
    uint32_t length, width;
    Texture();
    ~Texture();
};