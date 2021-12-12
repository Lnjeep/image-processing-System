#include"enhance.h"
#define CVUI_IMPLEMENTATION
#include "F:\C++\cvui-2.7.0\cvui.h"
#include "Shlobj.h"
#include"open.c"
#include<windows.h>
#define WINDOW_NAME "Image Processing"
using namespace std;
using namespace cv;
int main() {
    begain:
    cvui::init(WINDOW_NAME);
    cv::Mat frame = cv::Mat(cv::Size(550, 500), CV_8UC3);
    Mat resultImage1; int result1 = 0; int num1 = 0;
    Mat resultImage2; int result2 = 0; int num2 = 0;
    Mat resultImage3; int result3 = 0; int num3 = 0;
    Mat resultImage4; int result4 = 0; int num4 = 0;
    Mat resultImage5; int result5 = 0; int num5 = 0;
    int count = 0;
    while (true) {
        frame = Scalar(255,240,245);
        cvui::text(frame, 120, 20,"Image Processing",1, 0xff0000);
        cvui::text(frame, 110, 430, "Old Image", 0.5, 0x000000);
        cvui::text(frame, 30, 460, "Made by Intelligent science 1912", 0.5, 0x000000);
        cvui::text(frame, 110, 480, "LinJiaPeng", 0.5, 0x000000);
        cvui::rect(frame, 10, 100, 300, 320, 0x000000, 0xffffff);

        if (cvui::button(frame, 350, 80, 160, 30, "open image")) {
            destroyWindow("enhance image");
            count = 0;
            GetFile();
            count += 1;
            if (judge == 0) {
                goto begain;
            }
            else
                cout << "选择成功！" << endl;
        }
        if (count == 1) {
            Mat new_image = imread(_char);  
            Mat newimage = standard(new_image);
            cvui::image(frame, 10, 100, newimage);
        }

        if (cvui::button(frame, 350, 130, 160, 30, "gray log_enhance")) {
            if (count == 0) {
                MessageBox(NULL, TEXT("您还未选中图片"), TEXT("警告"), MB_ICONEXCLAMATION);
                goto begain;
            }
            result2 = 0; result3 = 0; result4 = 0; result5 = 0;
            Mat srcImage = imread(_char, IMREAD_GRAYSCALE);
            if (!srcImage.data)
                return -1;
            float c = 1.2;
            resultImage1 = GraylogTransform(srcImage, c);
            namedWindow("enhance image", WINDOW_KEEPRATIO);
            resizeWindow("enhance image", 400, 360);
            moveWindow("enhance image", 1000, 200);
            imshow("enhance image", resultImage1);
            result1 = 1;
        }

        if (cvui::button(frame, 350, 180, 160, 30, "RGB log_enhance")) {
            if (count == 0) {
                MessageBox(NULL, TEXT("您还未选中图片"), TEXT("警告"), MB_ICONEXCLAMATION);
                goto begain;
            }
            result1 = 0; result3 = 0; result4 = 0; result5 = 0;
            Mat srcImage = imread(_char, IMREAD_COLOR);
            resultImage2 = RGBlogTransform(srcImage, 1);
            namedWindow("enhance image", WINDOW_KEEPRATIO);
            resizeWindow("enhance image", 400, 360);
            moveWindow("enhance image", 1000, 200);
            imshow("enhance image", resultImage2);
            result2 = 1;
        }

        if (cvui::button(frame, 350, 230, 160, 30, "laplacian enhance")) {
            if (count == 0) {
                MessageBox(NULL, TEXT("您还未选中图片"), TEXT("警告"), MB_ICONEXCLAMATION);
                goto begain;
            }
            result1 = 0; result2 = 0; result4 = 0; result5 = 0;
            Mat srcImage = imread(_char, IMREAD_COLOR);
            resultImage3 = lpls(srcImage);
            namedWindow("enhance image", WINDOW_KEEPRATIO);
            resizeWindow("enhance image", 400, 360);
            moveWindow("enhance image", 1000, 200);
            imshow("enhance image", resultImage3);
            result3 = 1;
        }

        if (cvui::button(frame, 350, 280, 160, 30, "reversal enhance")) {
            if (count == 0) {
                MessageBox(NULL, TEXT("您还未选中图片"), TEXT("警告"), MB_ICONEXCLAMATION);
                goto begain;
            }
            result1 = 0; result2 = 0; result3 = 0; result5 = 0;
            Mat srcImage = imread(_char, IMREAD_COLOR);
            resultImage4 = qufan(srcImage);
            namedWindow("enhance image", WINDOW_KEEPRATIO);
            resizeWindow("enhance image", 400, 360);
            moveWindow("enhance image", 1000, 200);
            imshow("enhance image", resultImage4);
            result4 = 1;
        }

        if (cvui::button(frame, 350, 330, 160, 30, "saturation enhance")) {
            if (count == 0) {
                MessageBox(NULL, TEXT("您还未选中图片"), TEXT("警告"), MB_ICONEXCLAMATION);
                goto begain;
            }
            result1 = 0; result2 = 0; result3 = 0; result4 = 0;
            Mat srcImage = imread(_char, IMREAD_COLOR);
            resultImage5 = Saturation(srcImage, 50);
            namedWindow("enhance image", WINDOW_KEEPRATIO);
            resizeWindow("enhance image", 400, 360);
            moveWindow("enhance image", 1000, 200);
            imshow("enhance image", resultImage5);
            result5 = 1;
        }

        if(cvui::button(frame, 350, 380, 160, 30, "save image")) {
            if (count == 0) {
                MessageBox(NULL, TEXT("您还未选中图片，无法保存"), TEXT("警告"), MB_ICONEXCLAMATION);
                goto begain;
            }
            if (result1 == 1) {
                num1++;
                string imagname = "F:/图片/new/result1" + to_string(num1) + ".jpg";
                imwrite(imagname, resultImage1);
                MessageBox(NULL, TEXT("图像保存成功"), TEXT(""), MB_ICONASTERISK);
                cout << imagname<< "保存成功" << endl;
                destroyWindow("enhance image");
                result1 = 0;
            }
            if (result2 == 1) {
                num2++;
                string imagname = "F:/图片/new/result2" + to_string(num2) + ".jpg";
                imwrite(imagname, resultImage2);
                MessageBox(NULL, TEXT("图像保存成功"), TEXT(""), MB_ICONASTERISK);
                cout << imagname << "保存成功" << endl;
                destroyWindow("enhance image");
                result2 = 0;
            }
            if (result3 == 1) {
                num3++;
                string imagname = "F:/图片/new/result3" + to_string(num3) + ".jpg";
                imwrite(imagname, resultImage3);
                MessageBox(NULL, TEXT("图像保存成功"), TEXT(""), MB_ICONASTERISK);
                cout << imagname << "保存成功" << endl;
                destroyWindow("enhance image");
                result3 = 0;
            }
            if (result4 == 1) {
                num4++;
                string imagname = "F:/图片/new/result4" + to_string(num4) + ".jpg";
                imwrite(imagname, resultImage4);
                MessageBox(NULL, TEXT("图像保存成功"), TEXT(""), MB_ICONASTERISK);
                cout << imagname << "保存成功" << endl;
                destroyWindow("enhance image");
                result4 = 0;
            }
            if (result5 == 1) {
                num5++;
                string imagname = "F:/图片/new/result5" + to_string(num5) + ".jpg";
                imwrite(imagname, resultImage5);
                MessageBox(NULL, TEXT("图像保存成功"), TEXT(""), MB_ICONASTERISK);
                cout << imagname << "保存成功" << endl;
                destroyWindow("enhance image");
                result5 = 0;
            }
        }
        cvui::button(frame, 350, 430, 160, 30, "close window");
        cvui::imshow(WINDOW_NAME, frame);
        if (waitKey(20) == 27|| (cvui::button(frame, 350, 430, "close window")) ){
            cout << "欢迎您再次使用Image Processing处理系统 " << endl;
            break;
        }
    }
    return 0;
}