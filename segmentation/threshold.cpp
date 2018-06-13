#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <climits>

using namespace cv;
using namespace std;
int thresh=200;

int threshold_advanced(const int k[],int rows,int cols)
{
	int sum_=0;
	for (int j = 0; j <256 ; ++j)
	{
		sum_+=j*k[j];
	}
	float mean=sum_/(rows*cols);
	//cout<<"mean="<<mean<<endl;
	int min_thresh=0;
	float sigmaW,sigmaB,min_ratio=(float)INT_MAX;
	for (int i = 0; i < 256; ++i)
	{
		float  deviation1=0,deviation2=0;
		float mean1,mean2;
		float sum=0;
		for (int j = 0; j <i ; ++j)
		{
			sum+=j*k[j];
		}
		mean1=sum/(rows*cols);
		sum=0;
		for (int j = i; j <256 ; ++j)
		{
			sum+=j*k[j];
		}
		mean2=sum/(rows*cols);
		for (int j = 0; j <i; ++j)
		{
			deviation1+=(j-mean1)*(j-mean1)*k[j]/(rows*cols);
		}
		for (int j = i; j <256; ++j)
		{
			deviation2+=(j-mean2)*(j-mean2)*k[j]/(rows*cols);
		}

		float h1,h2;
		for (int j = 0; j <i; ++j)
		{
			h1+=k[j]/(rows*cols);
		}
		for (int j = i; j <256; ++j)
		{
			h2+=k[j]/(rows*cols);
		}
		sigmaW=h1*deviation1+h2*deviation2;
		sigmaB=h1*(mean1-mean)*(mean1-mean)+h2*(mean2-mean)*(mean2-mean);
		//cout<<mean1<<","<<mean2<<","<<h1<<","<<h2<<","<<sigmaW<<","<<sigmaB<<endl;
		if(sigmaW/sigmaB<min_ratio)
		{
			min_ratio=sigmaW/sigmaB;
			min_thresh=i;
			//cout<<"setting min thresh to i="<<i<<endl;
		}
	}
	//cout<<"advanced min thresh = "<<min_thresh<<endl;
	return min_thresh;
}

int threshold_naive(const int k[])
{
	int max1=k[0],max2=k[1];
	int pos1,pos2;
	for (int i = 0; i <=255; ++i)
	{
		if(k[i]>max1)
		{
			max1=k[i];
			max2=max1;
			pos2=pos1;
			pos1=i;
		}
		else if(k[i]>max2)
		{
			max2=k[i];
			pos2=i;
		}
	}
	cout<<pos1<<","<<pos2<<endl;
	return (pos1+pos2)/2;
}

void histogram(const Mat img)
{
	Mat hist(301,256,CV_8UC1,Scalar(0));
	int k[256]={0};
	for (int i = 0; i < img.rows; ++i)
	{
		for (int j = 0; j < img.cols; ++j)
		{
			// if(k[img.at<uchar>(i,j)]/5<300)
			// {
				//hist.at<uchar>(hist.rows-1-k[img.at<uchar>(i,j)]/5,img.at<uchar>(i,j))=255;
				k[img.at<uchar>(i,j)]++;	
			// }
		}
	}
	//imshow("histogram",hist);
	for (int i = 0; i < 256; ++i)
	{
		cout<<k[i]<<",";
	}
	cout<<"-----------------"<<endl;
	thresh=threshold_naive(k);
	thresh=threshold_advanced(k,img.rows,img.cols);
}

void binarize(const Mat img)
{
	namedWindow("binary",CV_WINDOW_AUTOSIZE);
	createTrackbar("threshold","binary",&thresh,255);
	while(1)
	{
		Mat binary(img.rows,img.cols,CV_8UC1,Scalar(0));
		for (int i = 0; i < binary.rows; ++i)
		{
			for (int j = 0; j < binary.cols; ++j)
			{
				if(img.at<uchar>(i,j)>thresh)
					binary.at<uchar>(i,j)=255;
			}
		}
		imshow("binary",binary);
		if(waitKey(10)==32)
			break;
	}
}

int main()
{
	Mat image;
	image=imread("./text.jpg",CV_LOAD_IMAGE_GRAYSCALE);
	imshow("read image",image);
	histogram(image);
	binarize(image); 
	waitKey(0);
	return 0;
}