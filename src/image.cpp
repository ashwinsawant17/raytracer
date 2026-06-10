#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <string>
#include "image.h"


ImageWriter::ImageWriter(int num_channels) : w_channels(num_channels){}
ImageWriter::~ImageWriter() {};

int ImageWriter::write_image(std::string fname, int w, int h, void *buffer) {

    if (fname.ends_with(".png")) {
        stbi_write_png(fname.c_str(), w, h, w_channels, buffer, w * w_channels);
    } else if (fname.ends_with(".jpg")) {
        stbi_write_jpg(fname.c_str(), w, h, w_channels, buffer, w * w_channels);
    } else {
        stbi_write_bmp(fname.c_str(), w, h, w_channels, buffer);
    }
    
    return 0;
}


