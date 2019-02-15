#include "../src/load_img.hpp"
#include "../src/display_img.hpp"

int main() {
    std::string png_test = "../test/test_png.png";
    std::string jpg_test = "../test/test_jpg.jpg";

    std::cout << "This shouldn't raise any exception" << std::endl;

    Image* png_image;

    try {
        png_image = new Image(png_test);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    Display_FB::display_img(*png_image, Display_FB::DEFAULT_FB);

    delete png_image;

    return 0;

}
