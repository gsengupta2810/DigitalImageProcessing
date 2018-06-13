#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;
using namespace cv;

Mat compute_edge(Mat image)
{
	Mat img=image.clone();
	int convol_mat[5][5]={0,0,1,0,0,
						  0,1,2,1,0,
						  1,2,-16,2,1,
						  0,1,2,1,0,
						  0,0,1,0,0};
	Mat img_edge(img.rows,img.cols,CV_8UC1,Scalar(0));
    for (int i = 5; i < img.rows-5; ++i)
    {
    	for (int j = 5; j < img.cols-5; ++j)
    	{
    		int temp=0;
    		for (int k = -2; k < 3; ++k)
    		{
    			for (int l = -2; l < 3; ++l)
    			{
    				temp+=img.at<uchar>(i+k,j+l)*convol_mat[k+2][l+2];
    			}
    		}
    		if(fabs(temp)<2)
    		{
	    		img_edge.at<uchar>(i,j)=255;
    		}
    		
    	}	
    }
    imwrite("./outputs/LOG_edge.jpeg", img_edge);
    return img_edge;
}

Mat gray(Mat img)
{
	Mat img1=img.clone();
	Mat img2;
	cvtColor(img1,img2,CV_BGR2GRAY);
	return img2;
}

float epsilon(int pos, int n)
{
	if(pos==0)
		return sqrt(1/2);
	return 1;
}

float find_dst_coeff(Mat img,int u,int v,int n)
{
	float temp=0;
	for(int i = n*u; i < n*u+n; ++i)
	{
		for(int j = n*v; j < n*v+n ; ++j)
		{
			// cout<<cos(float((2*i+1)*u*3.14)/float(2*n))<<"*****"<<endl;
			temp+=cos(float((2*i+1)*u*3.14)/float(2*n))*cos(float((2*j+1)*u*3.14)/float(2*n));
			// cout<<temp<<"-- ";
		}
	}
	temp*=epsilon(u,n)*epsilon(v,n);
	return temp;
}

void partition_image_calc_DCT(Mat img)
{
	for (int i = 0; i < img.rows-8; i+=8)
	{
		for (int j = 0; j < img.cols-8; j+=8)
		{
			int u=i/8;
			int v=j/8;
			cout<<find_dst_coeff(img,u,v,8)<<endl;
		}
	}
}


int main()
{
	// **************** Loading the image ************************ 
	Mat img1=imread("./cap.bmp",CV_LOAD_IMAGE_COLOR);
	Mat img2=imread("./lego.tif",CV_LOAD_IMAGE_COLOR);
	
	//************ Converting to grayscale **********
	Mat img1_gray=gray(img1);
	Mat img2_gray=gray(img2);

	//************* Applying LOG filter to detect edges *************
	Mat edge=compute_edge(img2_gray);

	//************* DCT for blocks in image *************************
	partition_image_calc_DCT(img1_gray);
	
	waitKey(0);
}