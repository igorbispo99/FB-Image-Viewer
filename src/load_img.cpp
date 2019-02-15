#include "load_img.hpp"

// Class Image
Image::Image() {
    this->width = 0;
    this->heigth = 0;
}

Image::Image(std::string filename) {
    int ext_index = this->get_extension_index(filename);

    if (ext_index == -1) {
        throw std::invalid_argument(this->error_msg);
    }

    std::string ext = exts[ext_index];

    if (ext == "jpg" || ext == "jpeg") {
        if (this->load_jpg(filename) == -1) {
            throw std::invalid_argument(this->error_msg);
        }
    } else if (ext == "png") {
        if (this->load_png(filename) == -1) {
            throw std::invalid_argument(this->error_msg);
        }
    } else {
        throw std::invalid_argument("This shouldn't happen.");
    }

}

int Image::get_extension_index(std::string filename) {
    // Trick to ignore dots at the beginning of filename
    int pos_last_dot = -1;

    for (size_t i = 0; i < filename.length(); i++){
        if (filename[i] == '.')
            pos_last_dot = (int) i;
    }

    // File extension isnt especified
    if (pos_last_dot == -1) {
        std::cerr << "No file extension." << std::endl;
        return -1;
    }

    std::string ext = filename.substr(pos_last_dot + 1);

    // Finding extension among the supported types
    size_t ext_index = 0;

    for (auto e : exts) {
        if (e == ext)
            break;
        ext_index += 1;
    }

    // Extension not found on the list
    if (ext_index == exts.size()) {
        std::cerr << "Invalid file extension." << std::endl;
        return -1;
    }

    return (int) ext_index;
}

void Image::copy_to_mtx(boost::gil::rgb8_image_t img) {
    this->heigth = (size_t) img.height();
    this->width = (size_t) img.width();

    for (size_t i = 0; i < this->heigth; i++) {
        std::vector<std::vector<uint8_t>> curr_line;

        for (size_t j = 0; j < this->width; j++) {
            boost::gil::rgb8_pixel_t px = *(boost::gil::const_view(img).at(j, i));

            std::vector<uint8_t> px_uint {
                (uint8_t)px[0],
                (uint8_t)px[1],
                (uint8_t)px[2]
            };

            curr_line.push_back(px_uint);
        }

        this->mtx.push_back(curr_line);
    }
}

int Image::load_png(std::string filename) {
    boost::gil::rgb8_image_t img;

    try {
		boost::gil::png_read_and_convert_image(filename, img);
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return -1;
	}

    this->copy_to_mtx(img);

    return 0;
}

int Image::load_jpg(std::string filename) {
    boost::gil::rgb8_image_t img;

    try {
		boost::gil::jpeg_read_and_convert_image(filename, img);
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return -1;
	}

    this->copy_to_mtx(img);

    return 0;
}