#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <bits/stdc++.h>

using namespace cv;
using namespace std;

const int thresh=140;

Mat binarize(const Mat img)
{
	Mat img_binary(img.rows,img.cols,CV_8UC1,Scalar(0));
	for (int i = 0; i < img.rows; ++i)
	{
		for (int j = 0; j < img.cols ; ++j)
		{
			if(img.at<uchar>(i,j)>thresh)
				img_binary.at<uchar>(i,j)=255;
		}
	}
	return img_binary;
}

//separating lines in a paragraph 
/*
enter the details here 
*/

void line_separation(const Mat img)
{
	
}


int main()
{
	Mat image;
	image=imread("text.png",CV_LOAD_IMAGE_GRAYSCALE);
	imshow("show",image);
	Mat image_binary=binarize(image);
	imshow("show binary",image_binary);
	imwrite("./image_binary.png",image_binary);
	line_separation(image_binary);
	waitKey(0);
}