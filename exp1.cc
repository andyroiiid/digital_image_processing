#include <opencv2/opencv.hpp>

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

    Mat processed = image.clone();
    for (int y = 0; y < processed.rows; y++) {
        for (int x = 0; x < processed.cols; x++) {
            float intensity = processed.at<uchar>(y, x) / 255.0;

            intensity = sqrt(intensity);

            processed.at<uchar>(y, x) = uchar(intensity * 255.0);
        }
    }

    namedWindow(argv[1], WINDOW_AUTOSIZE);
    imshow(argv[1], image);

    String windowName = "Gamma Corrected";
    namedWindow(windowName, WINDOW_AUTOSIZE);
    imshow(windowName, processed);

    waitKey(0);

    return 0;
}