#pragma once
#include <string>
#include "utils/vec3.h"


// default number of channels
#define NUM_CHANNELS 4

class ImageWriter {
public:
    int w_channels;
    ImageWriter(int num_channels);
    ~ImageWriter(void);
    int write_image(std::string fname, int w, int h, void *buffer);
};


