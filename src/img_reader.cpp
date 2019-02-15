#include "load_img.hpp"
#include "display_img.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage : " << argv[0] << " <path to img file>" << std::endl;
        return 1;
    }

    Image* img;

    try {
        img = new Image(argv[1]);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    Display_FB::display_img(*img, Display_FB::DEFAULT_FB);

    delete img;
    return 0;
}