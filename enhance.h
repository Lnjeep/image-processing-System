#ifndef H_ENHANCE_H
#define H_ENHANCE_H
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include<iostream>
#include <Windows.h>
#include <ShlObj.h>
#include <iostream>
#include <chrono>
#define max2(a,b) (a>b?a:b)
#define max3(a,b,c) (a>b?max2(a,c):max2(b,c))
#define min2(a,b) (a<b?a:b)
#define min3(a,b,c) (a<b?min2(a,c):min2(b,c))
class Timer {
public:
    Timer() : t1(res::zero()), t2(res::zero()) {
        tic();
    }
    ~Timer() {}
    void tic() { t1 = clock::now(); }
    void toc(const char* str) {
        t2 = clock::now();
        std::cout << str << " time: " << std::chrono::duration_cast<res>(t2 - t1).count() / 1e3 <<
            "ms." << std::endl;
    }
private:
    typedef std::chrono::high_resolution_clock clock;
    typedef std::chrono::microseconds res;
    clock::time_point t1;
    clock::time_point t2;
};
cv::Mat GraylogTransform(cv::Mat srcImage, float c);
cv::Mat RGBlogTransform(cv::Mat srcImage, float c_log);
cv::Mat lpls(cv::Mat image);
cv::Mat standard(cv::Mat src);
cv::Mat qufan(cv::Mat image);
cv::Mat Saturation(cv::Mat src, int value);
#endif