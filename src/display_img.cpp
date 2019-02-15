#include "display_img.hpp"

namespace Display_FB {


int get_screen_size(uint32_t& width, uint32_t& height, const uint8_t fb_num) {

    // Opening virtual_size file to specified framebuffer num
    std::string fb_size_path = "/sys/class/graphics/fb" + std::to_string(fb_num) + "/virtual_size";
    std::ifstream fb_size_file(fb_size_path);

    if(!fb_size_file.is_open()) {
        std::cerr << "Could not determine screen size, aborting." << std::endl;

        return -1;
    }

    // Reading size from file, the expected output format is : width,height
    std::string size_tmp;
    std::getline(fb_size_file, size_tmp);

    // Parsing size into two unsigned integers
    size_t pos_comma = size_tmp.find(',');

    width = std::stoul(size_tmp.substr(0, pos_comma));
    height = std::stoul(size_tmp.substr(pos_comma + 1));

    return 0;
}

int display_img(Image& img, u_int8_t fb_num) {
    // Trying to open specified framebuffer device
    std::string fb_path = "/dev/fb" + std::to_string(fb_num);
    std::ofstream fb(fb_path, std::ios::binary);

    if(!fb) {
        std::cerr << "Cannot open " << fb_path << " for writting." << std::endl;
        std::cerr << "Check if the user is in the video group and if framebuffer file exists." << std::endl;

        return -1;
    }

    uint32_t scr_width; 
    uint32_t scr_height;

    if(get_screen_size(scr_width, scr_height, fb_num) == -1) {
        return -1;
    }

    // Default writing order is "BGRAlpha"
    uint8_t alpha = 0;

    for (auto line : img.mtx) {
        for (auto pixel : line) {
            fb.write((char*) &pixel[2], 1);
            fb.write((char*) &pixel[1], 1);
            fb.write((char*) &pixel[0], 1);
            fb.write((char*) &alpha, 1);
        }
        fb.seekp((scr_width - img.heigth)*4 , std::ios_base::cur);
    }

    return 0;
}

}
