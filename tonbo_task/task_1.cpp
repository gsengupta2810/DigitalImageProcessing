#include <opencv2/opencv.hpp>
#include <iostream>
#include <bits/stdc++.h>
using namespace cv;
using namespace std;

void blob_detect(unsigned char** img,int rows,int cols)
{
	char** visited;
	visited=new char*[rows];
	for (int i = 0; i < rows; ++i)
	{
		visited[i]=new char[cols];
		for (int j = 0; j < cols; ++j)
		{
			visited[i][j]=-1;
		}
	}

	deque<Point> q;
	int count=1;
	for (int i = 1; i < rows-1; ++i)
	{
		for (int j = 1; j < cols-1; ++j)
		{
			if((int)img[i][j]==255 && (int)visited[i][j]==-1)
			{
				int m=i,n=j;
				q.push_back(Point(m,n));
				visited[m][n]=0;
				while(1)
				{
					for(int k=-1;k<2;k++)
					{
						for (int l = -1; l < 2; ++l)
						{
							if(img[m+k][n+l]==255 && (int)visited[m+k][n+l]==-1)
							{
								q.push_back(Point(m+k,n+l));
								visited[m+k][n+l]=0;
							}
						}
					}
					visited[q.front().x][q.front().y]=count;
					q.pop_front();
					if(q.empty()!=true)
					{
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
	cout<<"Number of blobs = "<<count-1<<endl;
	Mat blobs(rows,cols,CV_8UC3,Scalar(0,0,0));
	for (int k = 1; k <=count; ++k)
	{
		int a=rand()%k;
		int b=rand()%k;
		int c=rand()%k;
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				if(k==(int)visited[i][j])
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
int main(int argc,char** argv)
{
	if(argc<2)
	{
		cout<<"enter the image path"<<endl;
	    return 0;
	}

	unsigned char **image;
	Mat img=imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
	imshow("blobs",img);

	Mat binary=binarize(img);
	
	image=new unsigned char*[img.rows];

	for (int i = 0; i < img.rows; ++i)
	{
		image[i]=new unsigned char[img.cols];
		for (int j = 0; j < img.cols; ++j)
		{
			image[i][j]=binary.at<uchar>(i,j);
		}
	}
	
	blob_detect(image,img.rows,img.cols);
	waitKey(0);
}