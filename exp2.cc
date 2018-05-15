#include <opencv2/opencv.hpp>

using namespace cv;

void getHistogram(const Mat &image, double hist[], String windowName)
{
    memset(hist, 0, sizeof(double) * 256);
    for (int y = 0; y < image.rows; y++) {
        for (int x = 0; x < image.cols; x++) {
            uchar intensity = image.at<uchar>(y, x);
            hist[intensity]++;
        }
    }

    double maxHist = 0;
    for (int i = 0; i < 256; i++) {
        hist[i] /= image.rows * image.cols;
        maxHist = hist[i] > maxHist ? hist[i] : maxHist;
    }

    Mat histImg = Mat::zeros(256, 256, CV_8UC1);
    for (int i = 0; i < 256; i++) {
        int binHeight = hist[i] / maxHist * 255;
        for (int j = 0; j < binHeight; j++) {
            histImg.at<uchar>(255 - j, i) = 255;
        }
    }

    namedWindow(windowName, WINDOW_AUTOSIZE);
    imshow(windowName, histImg);
}

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

    namedWindow(argv[1], WINDOW_AUTOSIZE);
    imshow(argv[1], image);

    double hist[256];
    getHistogram(image, hist, "Original Histogram");

    // double Ts[256];
    // double T = 0;
    // for (int i = 0; i < 256; i++) {
    //     T += hist[i];
    //     Ts[i] = T;
    // }

    // // get the histogram mapping
    // int S[256];
    // for (int i = 0; i < 256; i++) {
    //     S[i] = 0;
    //     for (int j = 0; j < 256; j++) {
    //         if (fabs(Ts[i] - j / 255.0) < fabs(Ts[i] - S[i] / 255.0)) {
    //             S[i] = j;
    //         }
    //     }
    // }

    Mat processed;
    equalizeHist(image, processed);
    // Mat processed = image.clone();
    // for (int y = 0; y < processed.rows; y++) {
    //     for (int x = 0; x < processed.cols; x++) {
    //         uchar intensity = processed.at<uchar>(y, x);
    //         processed.at<uchar>(y, x) = S[intensity];
    //     }
    // }

    namedWindow("Processed", WINDOW_AUTOSIZE);
    imshow("Processed", processed);

    getHistogram(processed, hist, "Processed Histogram");

    waitKey(0);

    return 0;
}