#ifndef DISPLAY_IMG_HPP_
#define DISPLAY_IMG_HPP_

#include "load_img.hpp"

namespace Display_FB {

const uint8_t DEFAULT_FB = 0;

int get_screen_size(uint32_t& width, uint32_t& height, const uint8_t fb_num);

int display_img(Image& img, const uint8_t fb_num);

}

#endif