#ifndef LOAD_IMG_HPP_
#define LOAD_IMG_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

#define png_infopp_NULL (png_infopp)NULL
#define int_p_NULL (int*)NULL

#include <boost/gil/extension/io/jpeg_io.hpp>
#include <boost/gil/extension/io/png_io.hpp>

template <class T>
bool element_is_on_vector(std::vector<T> v, T e){
    return !(std::find(v.begin(), v.end(), e) == v.end());
}

const std::vector<std::string> exts {
    "jpeg", "jpg", "png"
};


class Image {
public:
    // 3D Tensor to fit img values
    std::vector<std::vector<std::vector<uint8_t>>> mtx;
    
    size_t width;
    size_t heigth;

    Image(std::string filename) noexcept(false); 
    Image();

    ~Image() {};
private:
   const char* error_msg = "Error opening file.";

   int get_extension_index(std::string filename);

   void copy_to_mtx(boost::gil::rgb8_image_t img);

   int load_png(std::string filename);
   int load_jpg(std::string filename);
};

#endif