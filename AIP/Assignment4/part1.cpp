#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <cmath>
using namespace std;
using namespace cv;

Mat img_norm;
Mat M(3,3,CV_32FC1,Scalar(0));
float R=1,G=1,B=1;
int Scale_1=1,Scale_2=1,Scale_0=1;

void onMouse(int event, int x, int y, int, void* )
{
	if( event != EVENT_LBUTTONDOWN )
        return;
    static Mat img_temp=img_norm.clone();
    Mat img_xyz;
    // cout<<"here1"<<endl;
    cvtColor(img_temp,img_xyz,COLOR_BGR2XYZ);
    // cout<<"here2"<<endl;
    R=(int)img_xyz.at<Vec3b>(y,x)[0];
    G=(int)img_xyz.at<Vec3b>(y,x)[1];
    B=(int)img_xyz.at<Vec3b>(y,x)[2];
	cout<<"Reference Values set to :- ["<<R<<","<<G<<","<<B<<"]"<<endl;
}

Mat calc_Transformed(const Mat img, float R_, float G_, float B_)
{
	Mat M_inv=M.inv();
	Mat img_1=img.clone();
	Mat img_xyz;
	cvtColor(img_1,img_xyz,COLOR_BGR2XYZ);
	// cout<<"1"<<endl;
	float alpha,beta,gamma;
	alpha= R_/R;
	beta=G_/G;
	gamma=B_/B;

	
	for (int i = 0; i < img.rows; ++i)
	{
		for (int j = 0; j < img.cols; ++j)
		{
			Mat temp(3,1,CV_32FC1,Scalar(0));
			for (int k = 0; k < 3; ++k)
			{
				for (int l = 0; l < 3; ++l)
				{
					temp.at<float>(k,0)+=M.at<float>(k,l)*(float)img_xyz.at<Vec3b>(i,j)[l];
				}
			}

			Mat temp_1(3,1,CV_32FC1,Scalar(0));
			temp_1.at<float>(0,0)=alpha*temp.at<float>(0,0);
			temp_1.at<float>(1,0)=beta*temp.at<float>(1,0);
			temp_1.at<float>(2,0)=gamma*temp.at<float>(2,0);

			Mat temp_2(3,1,CV_32FC1,Scalar(0));
			for (int k = 0; k < 3; ++k)
			{
				for (int l = 0; l < 3; ++l)
				{
					temp_2.at<float>(k,0)+=M_inv.at<float>(k,l)*temp_1.at<float>(l,0);
				}
			}
			// if(temp_2.at<float>(0,0)<255)
			// 	img_xyz.at<Vec3b>(i,j)[0]=Scale_0*(int)temp_2.at<float>(0,0);
			// else 
			// 	temp_2.at<float>(0,0)=255;

			// if(temp_2.at<float>(1,0)<255)
			// 	img_xyz.at<Vec3b>(i,j)[1]=Scale_1*(int)temp_2.at<float>(1,0);
			// else 
			// 	temp_2.at<float>(1,0)=255;

			// if(temp_2.at<float>(2,0)<255)
			// 	img_xyz.at<Vec3b>(i,j)[0]=Scale_2*(int)temp_2.at<float>(2,0);
			// else 
			// 	temp_2.at<float>(2,0)=255;

			img_xyz.at<Vec3b>(i,j)[0]=Scale_0*(int)temp_2.at<float>(0,0);
			img_xyz.at<Vec3b>(i,j)[1]=Scale_1*(int)temp_2.at<float>(1,0);
			img_xyz.at<Vec3b>(i,j)[2]=Scale_2*(int)temp_2.at<float>(2,0);
		}
	}
	Mat img_rgb;
	// cout<<"2"<<endl;
	cvtColor(img_xyz,img_rgb,COLOR_XYZ2BGR);
	// cout<<"3"<<endl;
	return img_rgb;
}

//*********************** Von Cries Chromatic Adaptation Transform************************
void VK_CAT(const Mat img)
{
	Mat img_1=img.clone();
	Mat img_xyz;

	M.at<float>(0,0)=0.3897;
	M.at<float>(0,1)=0.6890;
	M.at<float>(0,2)=-0.0787;

	M.at<float>(1,0)=-0.2298;
	M.at<float>(1,1)=1.1834;
	M.at<float>(1,2)=0.0464;

	M.at<float>(2,0)=0;
	M.at<float>(2,1)=0;
	M.at<float>(2,2)=1;
	
	imshow("white Point",img_1);
	cout<<"Click on a part of the image which is supposed to be white"<<endl;
	setMouseCallback("white Point",onMouse,0);

	namedWindow("VK_CAT corrected",WINDOW_AUTOSIZE);
	createTrackbar("Scale 0","VK_CAT corrected",&Scale_0,30);
	createTrackbar("Scale 1","VK_CAT corrected",&Scale_1,30);
	createTrackbar("Scale 2","VK_CAT corrected",&Scale_2,30);

	while(1)
	{
		float x=0.31382,y=0.33100;
		float Y=G,X=Y*x/y,Z=Y*(1-x-y)/y;
		Mat img_final=calc_Transformed(img_1,X,Y,Z);
		imshow("VK_CAT corrected",img_final);
		imwrite("./corrected_images/VK_CAT_corrected.jpg",img_final);
		if(waitKey(10)>0)
			break;
	}
}

void BFD(const Mat img)
{
	Mat img_1=img.clone();
	Mat img_xyz;

	M.at<float>(0,0)=0.8951;
	M.at<float>(0,1)=0.2664;
	M.at<float>(0,2)=-0.1614;

	M.at<float>(1,0)=-0.7502;
	M.at<float>(1,1)=1.7135;
	M.at<float>(1,2)=0.0367;

	M.at<float>(2,0)=0.0389;
	M.at<float>(2,1)=-0.0685;
	M.at<float>(2,2)=1.0296;
	
	imshow("white Point",img_1);
	cout<<"Click on a part of the image which is supposed to be white"<<endl;
	setMouseCallback("white Point",onMouse,0);

	namedWindow("BFD corrected",WINDOW_AUTOSIZE);
	createTrackbar("Scale 0","BFD corrected",&Scale_0,30);
	createTrackbar("Scale 1","BFD corrected",&Scale_1,30);
	createTrackbar("Scale 2","BFD corrected",&Scale_2,30);

	while(1)
	{
		float x=0.31382,y=0.33100;
		float Y=G,X=Y*x/y,Z=Y*(1-x-y)/y;
		Mat img_final=calc_Transformed(img_1,X,Y,Z);
		imshow("BFD corrected",img_final);
		imwrite("./corrected_images/BFD_corrected.jpg",img_final);
		if(waitKey(10)>0)
			break;
	}
}

void Sharp(const Mat img)
{
	Mat img_1=img.clone();
	Mat img_xyz;

	M.at<float>(0,0)=1.2694;
	M.at<float>(0,1)=-0.0988;
	M.at<float>(0,2)=-0.1706;

	M.at<float>(1,0)=-0.8364;
	M.at<float>(1,1)=1.8006;
	M.at<float>(1,2)=0.0357;

	M.at<float>(2,0)=0.0297;
	M.at<float>(2,1)=-0.0315;
	M.at<float>(2,2)=1.0018;
	
	imshow("white Point",img_1);
	cout<<"Click on a part of the image which is supposed to be white"<<endl;
	setMouseCallback("white Point",onMouse,0);

	namedWindow("Sharp corrected",WINDOW_AUTOSIZE);
	createTrackbar("Scale 0","Sharp corrected",&Scale_0,30);
	createTrackbar("Scale 1","Sharp corrected",&Scale_1,30);
	createTrackbar("Scale 2","Sharp corrected",&Scale_2,30);

	while(1)
	{
		float x=0.31382,y=0.33100;
		float Y=G,X=Y*x/y,Z=Y*(1-x-y)/y;
		Mat img_final=calc_Transformed(img_1,X,Y,Z);
		imshow("Sharp corrected",img_final);
		imwrite("./corrected_images/Sharp_corrected.jpg",img_final);
		if(waitKey(10)>0)
			break;
	}
}

int main()
{
	// img_norm=imread("./Indoor_normal_illumination.jpg",CV_LOAD_IMAGE_COLOR);
	// img_norm=imread("./Indoor_artifical_illumination.jpg",CV_LOAD_IMAGE_COLOR);
	img_norm=imread("./TheraWallPainting.jpg",CV_LOAD_IMAGE_COLOR); 
	
	// VK_CAT(img_norm);
	// BFD(img_norm);
	Sharp(img_norm);
	
	waitKey(0);
}