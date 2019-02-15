#include "../src/load_img.hpp"

int main() {
    std::string png_test = "../test/test_png.png";
    std::string jpg_test = "../test/test_jpg.jpg";

    Image img_zero;

    if (img_zero.width != 0 || img_zero.heigth != 0) {
        std::cout << "Ops, something went wrong with the default constructor."
                  << std::endl;
    }

    std::cout << "\nThis shouldn't raise any exception:\n" << std::endl;

    Image* png_img;

    try {
        png_img = new Image(png_test);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    std::cout << "Reported img heigth: " << png_img->heigth << std::endl
              << "Reported img width: " << png_img->width << std::endl << std::endl;

    Image* jpg_img;

    try {
        jpg_img = new Image(jpg_test);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    std::cout << "Reported img heigth: " << jpg_img->heigth << std::endl
              << "Reported img width: " << jpg_img->width << std::endl << std::endl;

    delete jpg_img;
    delete png_img;

    std::cout << "This should rise \"Error opening file.\":\n" << std::endl;

    try {
        Image img("foo");
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    try {
        Image img("foo.foo");
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    try {
        Image img("foo.");
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

}