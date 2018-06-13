#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
	Mat img_left=imread("./Sunrise_Lt.jpg",CV_LOAD_IMAGE_COLOR);
	Mat img_right=imread("./Sunrise_Rt.jpg",CV_LOAD_IMAGE_COLOR);
	imshow("lt",img_left);
	imshow("rt",img_right);
	waitKey(0);
}