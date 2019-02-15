#include <iostream>

#define png_infopp_NULL (png_infopp)NULL
#define int_p_NULL (int*)NULL

#include <boost/gil/extension/io/png_io.hpp>

int main(int argc, char* argv[]) {

	boost::gil::rgb8_image_t img;

	try {
		boost::gil::png_read_and_convert_image(argv[1], img);
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
		return 1;
	}

	std::cout <<  "Read complete, got an image " << img.width()
		  << " by " << img.height() << " pixels\n";

	boost::gil::rgb8_pixel_t px = *(boost::gil::const_view(img).at(5, 10));

	std::cout << "The pixel at 5, 10 is " 
		  << (int)px[0] << ','
		  << (int)px[1] << ','
		  << (int)px[2] << '\n';

}
