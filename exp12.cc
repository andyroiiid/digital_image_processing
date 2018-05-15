#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;

Mat image;
Mat processed = Mat::zeros(Size(256, 256), CV_8UC1);

String windowName = "Affine Transformed";

int x1, x2, x3;
int py1, py2, py3;

void updateProcessed(int _1 = 0, void * _2 = nullptr)
{
    Point2f srcTri[3] = {
        Point2f(x1, py1),
        Point2f(x2, py2),
        Point2f(x3, py3)
    };

    Point2f dstTri[3] = {
        Point2f(0, 0),
        Point2f(image.cols-1, 0),
        Point2f(0, image.rows-1)
    };

    Mat affineTransformMat(2, 3, CV_32FC1);
    affineTransformMat = getAffineTransform(srcTri, dstTri);

    warpAffine(image, processed, affineTransformMat, processed.size());

    imshow(windowName, processed);
}

int main(int argc, const char* argv[])
{
    if (argc != 2)
    {
        std::cout << "usage: " << argv[0] << " <Image Path>" << std::endl;
        return -1;
    }

    image = imread(argv[1], IMREAD_GRAYSCALE);

    if (!image.data)
    {
        std::cout << "No image data" << std::endl;
        return -1;
    }

    namedWindow(argv[1], WINDOW_AUTOSIZE);
    imshow(argv[1], image);

    x1 = 0;
    py1 = 0;
    x2 = image.cols-1;
    py2 = 0;
    x3 = 0;
    py3 = image.rows-1;
    updateProcessed();

    createTrackbar("x1", windowName, &x1, image.cols-1, updateProcessed);
    createTrackbar("x2", windowName, &x2, image.cols-1, updateProcessed);
    createTrackbar("x3", windowName, &x3, image.cols-1, updateProcessed);
    createTrackbar("y1", windowName, &py1, image.rows-1, updateProcessed);
    createTrackbar("y2", windowName, &py2, image.rows-1, updateProcessed);
    createTrackbar("y3", windowName, &py3, image.rows-1, updateProcessed);

    namedWindow(windowName, WINDOW_AUTOSIZE);

    waitKey(0);

    return 0;
}