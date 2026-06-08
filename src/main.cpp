#include <iostream>

#define WIN_H 600
#define WIN_W 800
#define BUFF_H 600
#define BUFF_W 800

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int main(void) {

    std::cout << "Hello World." << std::endl;

    fflush(stdout);
    unsigned char *img = (unsigned char *) calloc(4 * WIN_H * WIN_W, 1);
    for (int i = 0; i < WIN_H * WIN_W * 4; i += 4) {
        img[i] = 255;
        img[i + 3] = 255;
    }

    std::string filename = "test1.png";
    int x = stbi_write_png(
        filename.c_str(),
        WIN_W,
        WIN_H,
        4,
        img,
        4 * WIN_W
    );
        
    return x;
} 