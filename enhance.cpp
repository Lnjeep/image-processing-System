#include"enhance.h"
using namespace std;
cv::Mat standard(cv::Mat src)
{
    cv::Size srcSize = cv::Size(300, 320); //填入任意指定尺寸
    resize(src, src, srcSize, 0, 0, cv::INTER_LINEAR);
    return src;
}
cv::Mat GraylogTransform(cv::Mat srcImage, float c)
{
    if (srcImage.empty()) {
        cout << "打开失败" << endl;
    }
    Timer timer;
    timer.tic();
    cv:: Mat resultImage =cv::Mat::zeros(srcImage.size(), srcImage.type());
    srcImage.convertTo(resultImage, CV_32F);  //图像类型转换
    resultImage = resultImage + 1;            //图像矩阵元素加1
    log(resultImage, resultImage);
    resultImage = c * resultImage;
    //归一化处理
    normalize(resultImage, resultImage, 0, 255, cv::NORM_MINMAX);
    convertScaleAbs(resultImage, resultImage);
    timer.toc("gray log_enhance");
    return resultImage;
}
cv::Mat RGBlogTransform(cv::Mat srcImage, float c_log)
{
    if (srcImage.empty()) {
        cout << "打开失败" << endl;
    }
    CV_Assert(srcImage.channels() == 3);
    Timer timer;
    timer.tic();
    cv::Mat imageLog = cv::Mat::zeros(srcImage.size(), srcImage.type());
    srcImage.convertTo(imageLog, CV_32F);  //图像类型转换
    for (int i = 0; i < srcImage.rows; i++) {
        for (int j = 0; j < srcImage.cols; j++) {
            imageLog.at<cv::Vec3f>(i, j)[0] = c_log * log(1 + srcImage.at<cv::Vec3b>(i, j)[0]);
            imageLog.at<cv::Vec3f>(i, j)[1] = c_log * log(1 + srcImage.at<cv::Vec3b>(i, j)[1]);
            imageLog.at<cv::Vec3f>(i, j)[2] = c_log * log(1 + srcImage.at<cv::Vec3b>(i, j)[2]);
        }
    }
    //归一化到0~255
    normalize(imageLog, imageLog, 0, 255, CV_MINMAX);
    //转换成8bit图像显示
    convertScaleAbs(imageLog, imageLog);
    timer.toc("RGB log_enhance");
    return imageLog;
}

cv::Mat lpls(cv::Mat image)
{
    if (image.empty()){
        cout << "打开失败" << endl;
    }
    Timer timer;
    timer.tic();
    cv::Mat imageEnhance;
    cv::Mat kernel = (cv::Mat_<float>(3, 3) << 0, -1, 0, 0, 5, 0, 0, -1, 0);
    filter2D(image, imageEnhance, CV_8UC3, kernel);
    timer.toc("laplacian enhance");
    return imageEnhance;
}
/*
 * 线性函数中的图像取反，灰度级范围[0,L-1];取反s=L-1-r
 * Opencv 实现
 */
cv::Mat qufan(cv::Mat image)
{
    if (image.empty()) {
        std::cout << "打开失败" << std::endl;
    }
    Timer timer;
    timer.tic();
    cv::Mat temp = cv::Scalar(255, 255, 255) - image;
    timer.toc("reversal enhance");
    return temp;
}
cv::Mat Saturation(cv::Mat src, int percent)
{
    float Increment = percent * 1.0f / 100;
    cv::Mat temp = src.clone();
    Timer timer;
    timer.tic();
    int row = src.rows;
    int col = src.cols;
    for (int i = 0; i < row; ++i)
    {
        uchar* t = temp.ptr<uchar>(i);
        uchar* s = src.ptr<uchar>(i);
        for (int j = 0; j < col; ++j)
        {
            uchar b = s[3 * j];
            uchar g = s[3 * j + 1];
            uchar r = s[3 * j + 2];
            float max = max3(r, g, b);
            float min = min3(r, g, b);
            float delta, value;
            float L, S, alpha;
            delta = (max - min) / 255;
            if (delta == 0)
                continue;
            value = (max + min) / 255;
            L = value / 2;
            if (L < 0.5)
                S = delta / value;
            else
                S = delta / (2 - value);
            if (Increment >= 0)
            {
                if ((Increment + S) >= 1)
                    alpha = S;
                else
                    alpha = 1 - Increment;
                alpha = 1 / alpha - 1;
                t[3 * j + 2] = static_cast<uchar>(r + (r - L * 255) * alpha);
                t[3 * j + 1] = static_cast<uchar>(g + (g - L * 255) * alpha);
                t[3 * j] = static_cast<uchar>(b + (b - L * 255) * alpha);
            }
            else
            {
                alpha = Increment;
                t[3 * j + 2] = static_cast<uchar>(L * 255 + (r - L * 255) * (1 + alpha));
                t[3 * j + 1] = static_cast<uchar>(L * 255 + (g - L * 255) * (1 + alpha));
                t[3 * j] = static_cast<uchar>(L * 255 + (b - L * 255) * (1 + alpha));
            }
        }
    }
    timer.toc("Saturation enhance");
    return temp;
}