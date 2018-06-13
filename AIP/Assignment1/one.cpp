#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;
using namespace cv;

Mat gray(Mat img)
{
	Mat img1=img.clone();
	Mat img2;
	cvtColor(img1,img2,CV_BGR2GRAY);
	return img2;
}
Mat add_gaussian_noise(Mat img, float sd)
{
	// imGray is the grayscale of the input image
	Mat imGray=gray(img);
	Mat noise = Mat(imGray.size(),CV_32F);
	Mat result;
	normalize(imGray, result, 0.0, 1.0, CV_MINMAX, CV_32F);
	randn(noise, 0, sd);
	result = result + noise;
	normalize(result, result, 0.0, 1.0, CV_MINMAX, CV_32F);
	return result;
}

float calc_psnr(Mat noisy,Mat orig)
{
	float m=0;
	for (int i = 0; i < noisy.rows; ++i)
	{
		for (int j = 0; j < noisy.cols; ++j)
		{
			m+=(orig.at<uchar>(i,j)-noisy.at<uchar>(i,j))*(orig.at<uchar>(i,j)-noisy.at<uchar>(i,j));
		}
	}
	m=m/float(float(noisy.rows)*float(noisy.cols));
	float psnr=20*log10(255)-10*log10(m);
	return psnr;
}

int main()
{
	// **************** Loading the image ************************ 
	Mat img1=imread("./cap.bmp",CV_LOAD_IMAGE_COLOR);
	Mat img2=imread("./lego.tif",CV_LOAD_IMAGE_COLOR);
	
	imwrite("./output/cap.jpg",img1);
	imwrite("./output/lego.jpg",img2);
	
	//************ Converting to grayscale **********
	Mat img1_gray=gray(img1);
	Mat img2_gray=gray(img2);
	
	imwrite("./output/cap_gray.jpg",img1_gray);
	imwrite("./output/lego_gray.jpg",img2_gray);

	//*********** Add gaussian noise to the image and filter *******	
	cout<<"enter standard deviation"<<endl;
	float sd;
	cin>>sd;
	Mat noisy=add_gaussian_noise(img1,sd);
	imshow("Noisy_image.png",noisy);
	Mat median_filtered=noisy.clone();
	Mat mean_filtered=noisy.clone();
	blur(noisy,median_filtered,Size(5,5));
	imshow("Mean_Filtered.png",mean_filtered);
	medianBlur (noisy,median_filtered,3);
	imshow("Median_Filtered.png",median_filtered);

	//************ Calculating the PSNR ************ 
	cout<<"Noisy image PSNR = "<<float(calc_psnr(noisy,img1_gray))<<endl;
	cout<<"Mean filtered image PSNR = "<<calc_psnr(mean_filtered,img1_gray)<<endl;
	cout<<"Median filtered image PSNR = "<<calc_psnr(median_filtered,img1_gray)<<endl;
	
	fstream file;
	file.open("./PSNR.csv",fstream::out);
	file<<"image,PSNR_value"<<endl;
	file<<"noisy,"<<float(calc_psnr(noisy,img1_gray))<<endl;
	file<<"mean_filtered,"<<calc_psnr(mean_filtered,img1_gray)<<endl;
	file<<"median_filtered,"<<calc_psnr(median_filtered,img1_gray)<<endl;
	file.close();

	// ************ 

	waitKey(0);
}