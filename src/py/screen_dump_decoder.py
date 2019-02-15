import sys
import cv2 as cv

def fb2tensor(fb_file):
    

def main(argc, argv):
        if argc != 3:
                print("Usage : {} <path to dumped framebuffer file> <width,height>".format(argv[0]))
                exit() 


        fb_path = argv[1]

        width, height = argv[2].split(',')
        width = int(width)
        height = int(height)

        fb2tensor(f)

if __name__ == '__main__':
    main(len(sys.argv), sys.argv)
