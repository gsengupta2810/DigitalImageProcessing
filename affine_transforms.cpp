#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

#define pi 3.14
bool side=true;

class Interpolation
{
	public:
		Mat linearInterpolation(Mat);
		Mat nearestNeighbourInterpolation(Mat);
		Mat CubicInterpolation(Mat);
};


void callbackTrue(int, void*)
{
	side=true;
}
void callbackFalse(int, void*)
{
	side=false;
}

void affineTranslate(Mat img)
{
	Mat img1=img.clone();
	int alpha=0,beta=0;
	namedWindow("translated",WINDOW_AUTOSIZE);
	createTrackbar("right","translated",&alpha,100,callbackTrue);
	createTrackbar("down","translated",&beta,100,callbackTrue);
	createTrackbar("left","translated",&alpha,100,callbackFalse);
	createTrackbar("up","translated",&beta,100,callbackFalse);
	while(1)
	{	
		Mat img2(img.rows,img.cols,CV_8UC3,Scalar(0,0,0));
		for(int k=0;k<2;k++)
		{
			for (int i = 0; i < img2.rows; ++i)
			{
				for(int j=0;j<img2.cols;j++)
				{
					int x1=0,y1=0;
					if(side==true)
					{
						x1=j+alpha;
						y1=i+beta;
					}
					else
					{
						x1=j-alpha;
						y1=i-beta;
					}
					//cout<<x1<<":"<<y1<<endl;
					if(x1<img2.cols&& x1>0 && y1>0 && y1<img2.rows)
					img2.at<Vec3b>(y1,x1)[k]=img1.at<Vec3b>(i,j)[k];
				}
			}
		}	
		imshow("translated",img2);
		if(waitKey(20)==32) break;
	}
}

void affineResize(Mat img)
{	
	Mat img1=img.clone();
	int n=1;
	namedWindow("resized",WINDOW_AUTOSIZE);
	createTrackbar("factor","resized",&n,3);
	while(1)
	{	
		Mat img2(n*img.rows,n*img.cols,CV_8UC3,Scalar(0,0,0));
		for(int k=0;k<2;k++)
		{
			for (int i = 0; i < img2.rows; ++i)
			{
				for(int j=0;j<img2.cols;j++)
				{
					int x1=n*j;
					int y1=n*i;
					//cout<<x1<<":"<<y1<<endl;
					if(x1<img2.cols&& x1>0 && y1>0 && y1<img2.rows)
					img2.at<Vec3b>(y1,x1)[k]=img1.at<Vec3b>(i,j)[k];
				}
			}
		}	
		imshow("resized",img2);
		if(waitKey(20)==32) break;
	}
}

void affineRotate(Mat img)
{
	Mat img1=img.clone();
	int theta=0;
	namedWindow("rotated",WINDOW_AUTOSIZE);
	createTrackbar("theta","rotated",&theta,180);
	while(1)
	{	
		Mat img2(img.rows,img.cols,CV_8UC3,Scalar(0,0,0));
		for(int k=0;k<2;k++)
		{
			for (int i = 0; i < img2.rows; ++i)
			{
				for(int j=0;j<img2.cols;j++)
				{
					int x1=img2.cols /2+cos(theta*pi/180)*(j-img2.cols/2)+sin(theta*pi/180)*(i-img2.rows/2);
					int y1=img2.rows/2-sin(theta*pi/180)*(j-img2.cols/2)+cos(theta*pi/180)*(i-img2.rows/2);
					//cout<<x1<<":"<<y1<<endl;
					if(x1<img.cols&& x1>0 && y1>0 && y1<img.rows)
					img2.at<Vec3b>(y1,x1)[k]=img1.at<Vec3b>(i,j)[k];
				}
			}
		}	
		imshow("rotated",img2);
		if(waitKey(20)==32) break;
	}
}

int main()
{
	Mat img;
	img=imread("test.jpg",CV_LOAD_IMAGE_COLOR);
	if(img.data)
	{
		namedWindow("window",WINDOW_NORMAL);
		imshow("window",img);
	}
	else cout<<"cant load image"<<endl;
	// while(1)
	// {
	// 	if(waitKey(10)==82||waitKey(10)==114)
	// 	affineRotate(img);
	// 	if(waitKey(10)==85||waitKey(10)==117)
	// 	affineResize(img);
	// 	if(waitKey(10)==84||waitKey(10)==116)
	// 	affineTranslate(img);
	// 	if(waitKey(10)==27)break;	
	// }
	affineRotate(img);
	waitKey(0);
	return 0;
}