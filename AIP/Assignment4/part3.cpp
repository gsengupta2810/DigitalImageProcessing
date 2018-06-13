#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <cmath>
using namespace std;
using namespace cv;

const int k=5;

int main()
{
	Mat img_norm=imread("./Indoor_normal_illumination.jpg",CV_LOAD_IMAGE_COLOR);
	// Mat img_norm=imread("./Indoor_artifical_illumination.jpg",CV_LOAD_IMAGE_COLOR);
	// Mat img_norm=imread("./TheraWallPainting.jpg",CV_LOAD_IMAGE_COLOR);
	Mat bestLabels;
	Mat centers;
	// kmeans(img_norm, k, bestLabels, cv::TermCriteria(1,1000,0.1), 10 , KMEANS_PP_CENTERS ,  centers);
}