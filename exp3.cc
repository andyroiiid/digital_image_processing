#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;

int main(int argc, const char* argv[])
{
    if (argc != 2)
    {
        std::cout << "usage: " << argv[0] << " <Image Path>" << std::endl;
        return -1;
    }

    Mat image;
    image = imread(argv[1], IMREAD_GRAYSCALE);

    if (!image.data)
    {
        std::cout << "No image data" << std::endl;
        return -1;
    }

    Mat processed;

    medianBlur(image, processed, 3);

    namedWindow(argv[1], WINDOW_AUTOSIZE);
    imshow(argv[1], image);

    String windowName = "Median Filtered";
    namedWindow(windowName, WINDOW_AUTOSIZE);
    imshow(windowName, processed);

    waitKey(0);

    return 0;
}