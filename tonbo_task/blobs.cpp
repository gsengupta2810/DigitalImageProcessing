#include <opencv2/opencv.hpp>
#include <iostream>
#include <bits/stdc++.h>
using namespace cv;
using namespace std;

void blob_detect(Mat img)
{
	Mat img1=img.clone();
	Mat visited(img.rows,img.cols,CV_8SC1,Scalar(-1));
	deque<Point> q;
	int count=1;
	for (int i = 1; i < img.rows-1; ++i)
	{
		for (int j = 1; j < img.cols-1; ++j)
		{
			if((int)img1.at<uchar>(i,j)==255 && (int)visited.at<schar>(i,j)==-1)
			{
				int m=i,n=j;
				q.push_back(Point(m,n));
				visited.at<schar>(m,n)=0;
				while(1)
				{
					for(int k=-1;k<2;k++)
					{
						for (int l = -1; l < 2; ++l)
						{
							if(img.at<uchar>(m+k,n+l)==255 && (int)visited.at<schar>(m+k,n+l)==-1)
							{
								q.push_back(Point(m+k,n+l));
								visited.at<schar>(m+k,n+l)=0;
							}
						}
					}
					visited.at<schar>(q.front().x,q.front().y)=count;
					q.pop_front();
					if(q.empty()!=true)
					{
						cout<<"q size = "<<q.size()<<" ||||| q top = "<<q.front().x<<","<<q.front().y<<endl;
						m=q.front().x;
						n=q.front().y;
					}
					else 
						break;
				}
				count++;
			}
		}
	}
	cout<<count<<endl;
	Mat blobs(img.rows,img.cols,CV_8UC3,Scalar(0,0,0));
	for (int k = 1; k <=count; ++k)
	{
		int a=rand()%k;
		int b=rand()%k;
		int c=rand()%k;
		for (int i = 0; i < img.rows; ++i)
		{
			for (int j = 0; j < img.cols; ++j)
			{
				if(k==(int)visited.at<schar>(i,j))
				{
					blobs.at<Vec3b>(i,j)[0]=255/(a+1);
					blobs.at<Vec3b>(i,j)[1]=255/(b+1);
					blobs.at<Vec3b>(i,j)[2]=255/(c+1);
				}
			}
		}
	}

	imshow("colored blobs",blobs);
}
Mat binarize(const Mat img)
{
	Mat img_binary(img.rows,img.cols,CV_8UC1,Scalar(0));
	for (int i = 0; i < img.rows; ++i)
	{
		for (int j = 0; j < img.cols ; ++j)
		{
			if(img.at<uchar>(i,j)>100)
				img_binary.at<uchar>(i,j)=255;
		}
	}
	imshow("binary",img_binary);
	return img_binary;
}
int main()
{
	Mat img=imread("./blobs_1.png",CV_LOAD_IMAGE_GRAYSCALE);
	imshow("blobs",img);
	Mat binary=binarize(img);
	blob_detect(binary);
	waitKey(0);
}