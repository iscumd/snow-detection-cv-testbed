#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

static const int TOP_MASK_HEIGHT = 225; // Number of rows of pixels to mask at the top of the image
static const cv::Scalar BLACK(0, 0, 0), WHITE(255, 255, 255);

/**
Applies a rectangular mask.
Input:
 -srcImg: the image to mask
 -outImg: an image to store the filtered image
 -topMaskHeight: the pixel height of the top bar of the mask; optional
 */
void maskImage(cv::Mat srcImg, cv::Mat& outImg, int topMaskHeight = TOP_MASK_HEIGHT) {
    cv::Mat mask = cv::Mat(srcImg.size(), CV_8U, WHITE);
    cv::rectangle(mask, cv::Point(0, 0), cv::Point(srcImg.cols - 1, topMaskHeight - 1), BLACK, cv::FILLED);
    cv::bitwise_and(srcImg, mask, outImg);
}

int main(int argc, char** argv) {
    cv::Mat inImg = cv::imread("snow-driveway.jpg");

    cv::namedWindow("inImg", cv::WINDOW_AUTOSIZE);
    cv::imshow("inImg", inImg);

    cv::Mat binImg(inImg.size(), CV_8U);
    cv::cvtColor(inImg, binImg, cv::COLOR_BGR2GRAY);
    cv::threshold(binImg, binImg, 100, 255, cv::THRESH_BINARY);

    cv::namedWindow("binImg", cv::WINDOW_AUTOSIZE);
    cv::imshow("binImg", binImg);

    cv::Mat outImg;
    maskImage(binImg, outImg);

    cv::namedWindow("outImg", cv::WINDOW_AUTOSIZE);
    cv::imshow("outImg", outImg);

    cv::waitKey(0);

}