#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;
using namespace cv;

int main()
{
	Mat img=imread("./cap.bmp",CV_LOAD_IMAGE_GRAYSCALE);
	imshow("img",img);

	Mat fx(img.rows,img.cols,CV_8SC1,Scalar(0));
	Mat fy(img.rows,img.cols,CV_8SC1,Scalar(0));
	int x_mask[3][3]={-1,0,1,
					  -1,0,1,
					  -1,0,1};
    int y_mask[3][3]={-1,-1,1,
					   0,0,0,
					   1,1,1};
	for (int i = 1; i < img.rows-1; ++i)
	{
		for (int j = 1; j < img.cols-1; ++j)
		{
			int sum_x=0,sum_y=0;
			for (int k = -1; k < 2; ++k)
			{
				for (int l = -1; l < 2; ++l)
				{
					sum_x+=img.at<uchar>(i+k,j+l)*x_mask[k+1][l+1];
					sum_y+=img.at<uchar>(i+k,j+l)*y_mask[k+1][l+1];
				}
			}
			fx.at<schar>(i,j)=sum_x;
			fy.at<schar>(i,j)=sum_y;
		}
	}
	int thresh=10;
	namedWindow("corners",WINDOW_AUTOSIZE);
	createTrackbar( "thresh", "corners", &thresh, 1000);
	while(1)
	{
		Mat img_corners(img.rows,img.cols,CV_8UC1,Scalar(0));
		for (int i = 0; i < img.rows; ++i)
		{
			for (int j = 0; j <img.cols; ++j)
			{
				float hm=0;
				Mat H(3,3,CV_32SC1);
				H.at<schar>(0,0)=fx.at<schar>(i,j)*fx.at<schar>(i,j);
				H.at<schar>(0,1)=fx.at<schar>(i,j)*fy.at<schar>(i,j);
				H.at<schar>(1,0)=fy.at<schar>(i,j)*fx.at<schar>(i,j);
				H.at<schar>(1,1)=fy.at<schar>(i,j)*fy.at<schar>(i,j);
				hm=float(float(H.at<schar>(0,0))*float(H.at<schar>(1,1))-float(H.at<schar>(1,0))*float(H.at<schar>(0,1)))/float(float(H.at<schar>(0,0))+float(H.at<schar>(1,1)));
				if(hm>thresh)
					img_corners.at<uchar>(i,j)=255;
			}	
		}
		imshow("corners",img_corners);
		if(waitKey(10)>0)
			break;
	}
	waitKey(0);
	return 0;
}