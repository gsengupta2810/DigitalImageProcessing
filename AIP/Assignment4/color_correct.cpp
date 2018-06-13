#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <cmath>
using namespace std;
using namespace cv;
int R_ref=1,G_ref=1,B_ref=1;
int L_ref=1,M_ref=1,S_ref=1;

Mat img_norm;
Mat convert_XYZ2LMS(const Mat xyz)
{
	// cout<<"here!!"<<endl;
	Mat xyz_1=xyz.clone();
	Mat lms(xyz.rows,xyz.cols,CV_32FC3,Scalar(0,0,0));
	Mat transformation_mat(3,3,CV_32FC1,Scalar(0));
	
	transformation_mat.at<float>(0,0)=0.7328;
	transformation_mat.at<float>(0,1)=0.4296;
	transformation_mat.at<float>(0,2)=-0.1624;

	transformation_mat.at<float>(1,0)=-0.7036;
	transformation_mat.at<float>(1,1)=1.6975;
	transformation_mat.at<float>(1,2)=0.0061;
	
	transformation_mat.at<float>(2,0)=0.0030;
	transformation_mat.at<float>(2,1)=0.0136;
	transformation_mat.at<float>(2,2)=0.9834;

	for (int i = 0; i < xyz.rows; ++i)
	{
		for (int j = 0; j < xyz.cols ; ++j)
		{
			Mat temp(3,1,CV_32FC1,Scalar(0));
			for (int k = 0; k < 3; ++k)
			{
				for (int l = 0; l < 3; ++l)
				{
					temp.at<float>(k,0)+= transformation_mat.at<float>(k,l)* xyz_1.at<Vec3b>(i,j)[l];
				}
			}
			lms.at<Vec3b>(i,j)[0]=(int)temp.at<float>(0,0);
			lms.at<Vec3b>(i,j)[1]=(int)temp.at<float>(1,0);
			lms.at<Vec3b>(i,j)[2]=(int)temp.at<float>(2,0);
		}
	}
	return lms;
}

Mat convert_LMS2XYZ(const Mat lms)
{
	Mat lms_1=lms.clone();
	Mat xyz(lms.rows,lms.cols,CV_32FC3,Scalar(0,0,0));
	Mat transformation_mat(3,3,CV_32FC1,Scalar(0));
	
	transformation_mat.at<float>(0,0)=1.0960;
	transformation_mat.at<float>(0,1)=-0.2789;
	transformation_mat.at<float>(0,2)=0.1905;

	transformation_mat.at<float>(1,0)=0.4543;
	transformation_mat.at<float>(1,1)=0.4735;
	transformation_mat.at<float>(1,2)=0.0075;
	
	transformation_mat.at<float>(2,0)=-0.0096;
	transformation_mat.at<float>(2,1)=-0.0056;
	transformation_mat.at<float>(2,2)=1.0152;

	for (int i = 0; i < xyz.rows; ++i)
	{
		for (int j = 0; j < xyz.cols ; ++j)
		{
			Mat temp(3,1,CV_32FC1,Scalar(0));
			// cout<<temp<<endl;
			for (int k = 0; k < 3; ++k)
			{
				for (int l = 0; l < 3; ++l)
				{
					temp.at<float>(k,0)+= transformation_mat.at<float>(k,l)* lms_1.at<Vec3b>(i,j)[l];
				}
			}
			// cout<<temp<<"\n---------------------"<<endl;
			xyz.at<Vec3b>(i,j)[0]=(int)temp.at<float>(0,0);
			xyz.at<Vec3b>(i,j)[1]=(int)temp.at<float>(1,0);
			xyz.at<Vec3b>(i,j)[2]=(int)temp.at<float>(2,0);
			// cout<<(int)xyz.at<Vec3b>(i,j)[0]<<","<<(int)xyz.at<Vec3b>(i,j)[1]<<","<<(int)xyz.at<Vec3b>(i,j)[2]<<endl;
		}
	}
	// cout<<xyz;
	return xyz;
}

void onMouse(int event, int x, int y, int, void* )
{
	if( event != EVENT_LBUTTONDOWN )
        return;
	R_ref=img_norm.at<Vec3b>(y,x)[2];
	G_ref=img_norm.at<Vec3b>(y,x)[1];
	B_ref=img_norm.at<Vec3b>(y,x)[0];
	cout<<"Reference Values set to :- ["<<B_ref<<","<<G_ref<<","<<R_ref<<"]"<<endl;
}

void onMouse_VK(int event, int x, int y, int, void* )
{
	if( event != EVENT_LBUTTONDOWN )
        return;
    Mat img_temp=img_norm.clone();
    Mat img_xyz;
    cvtColor(img_temp,img_xyz,COLOR_BGR2XYZ);
    Mat img_lms=convert_XYZ2LMS(img_xyz);
    L_ref=(int)img_lms.at<Vec3b>(y,x)[0];
    M_ref=(int)img_lms.at<Vec3b>(y,x)[1];
    S_ref=(int)img_lms.at<Vec3b>(y,x)[2];
	cout<<"Reference Values set to :- ["<<L_ref<<","<<M_ref<<","<<S_ref<<"]"<<endl;
}

void Scale_RGB(const Mat img)
{
	imshow("natural illumination",img_norm);
	cout<<"Click on a white balanced part on the natural colored image"<<endl;
	setMouseCallback("natural illumination",onMouse,0);
	
	namedWindow("RGB_Scale",WINDOW_AUTOSIZE);
	while(1)
	{
		Mat img_1=img.clone();
		for (int i = 0; i < img.rows; ++i)
		{
			for (int j = 0; j < img.cols; ++j)
			{
				if(((float)img_1.at<Vec3b>(i,j)[2]*(float)255)/(float)R_ref<255)
					img_1.at<Vec3b>(i,j)[2]= ((float)img_1.at<Vec3b>(i,j)[2]*(float)255)/(float)R_ref;
				else 
					img_1.at<Vec3b>(i,j)[2]=255;
				
				if(((float)img_1.at<Vec3b>(i,j)[1]*(float)255)/(float)G_ref<255)
					img_1.at<Vec3b>(i,j)[1]= ((float)img_1.at<Vec3b>(i,j)[1]*(float)255)/(float)G_ref;
				else
					img_1.at<Vec3b>(i,j)[1]=255;
				
				if(((float)img_1.at<Vec3b>(i,j)[0]*(float)255)/(float)G_ref<255)
					img_1.at<Vec3b>(i,j)[0]= ((float)img_1.at<Vec3b>(i,j)[0]*(float)255)/(float)B_ref;
				else 
					img_1.at<Vec3b>(i,j)[0]=255;
			}
		}
		imshow("RGB_Scale",img_1);
		if(waitKey(10)>=0)
			break;
	}
}

void Scale_VK(const Mat img)
{
	imshow("natural illumination",img_norm);
	cout<<"Click on a white balanced part on the natural colored image"<<endl;
	setMouseCallback("natural illumination",onMouse_VK,0);
	namedWindow("VK_Scale",WINDOW_AUTOSIZE);
	
	while(1)
	{
		Mat img_1=img.clone();
		//convert RGB to XLS
		Mat img_XYZ;
		cvtColor(img_1,img_XYZ,COLOR_BGR2XYZ);
		// imshow("XYZ image",img_XYZ);
		//Convert XLS to LMS
		Mat img_lms_1=convert_XYZ2LMS(img_XYZ);
		Mat img_lms(img.rows,img.cols,CV_8UC3,Scalar(0,0,0));
		for (int i = 0; i < img.rows; ++i)
		{
			for (int j = 0; j < img.cols; ++j)
			{
				img_lms.at<Vec3b>(i,j)[0]=(int)img_lms_1.at<Vec3b>(i,j)[0];
				img_lms.at<Vec3b>(i,j)[1]=(int)img_lms_1.at<Vec3b>(i,j)[1];
				img_lms.at<Vec3b>(i,j)[2]=(int)img_lms_1.at<Vec3b>(i,j)[2];
			}
		}
		imshow("lms image",img_lms);
		// cout<<img_lms;

		//Scale LMS
		for (int i = 0; i < img.rows; ++i)
		{
			for (int j = 0; j < img.cols; ++j)
			{
				img_lms.at<Vec3b>(i,j)[0]= ((float)img_lms.at<Vec3b>(i,j)[0]*(float)1)/(float)L_ref;
				img_lms.at<Vec3b>(i,j)[1]= ((float)img_lms.at<Vec3b>(i,j)[1]*(float)1)/(float)M_ref;
				img_lms.at<Vec3b>(i,j)[2]= ((float)img_lms.at<Vec3b>(i,j)[2]*(float)1)/(float)S_ref;
			}
		}
		imshow("lms after scaling ",img_lms);
		// cout<<img_lms;
		//Convert lms back to XYZ
		Mat img_xyz_1=convert_LMS2XYZ(img_lms);
		Mat img_xyz(img.rows,img.cols,CV_8UC3,Scalar(0,0,0));
		for (int i = 0; i < img.rows; ++i)
		{
			for (int j = 0; j < img.cols; ++j)
			{
				img_xyz.at<Vec3b>(i,j)[0]=(int)img_xyz_1.at<Vec3b>(i,j)[0];
				img_xyz.at<Vec3b>(i,j)[1]=(int)img_xyz_1.at<Vec3b>(i,j)[1];
				img_xyz.at<Vec3b>(i,j)[2]=(int)img_xyz_1.at<Vec3b>(i,j)[2];
			}
		}
		//Convert back to RGB
		Mat img_rgb;
		cvtColor(img_xyz,img_rgb,COLOR_XYZ2BGR);
		// cout<<img_rgb;
		imshow("VK_Scale",img_rgb);
		if(waitKey(10)>=0)
			break;
	}
}

int main()
{
	img_norm=imread("./Indoor_normal_illumination.jpg");
	Mat img_art=imread("./Indoor_artifical_illumination.jpg");
	// Mat img_art=imread("./TheraWallPainting.jpg");
	imshow("Before Scaling ",img_art);
	Scale_RGB(img_art);
	// Scale_VK(img_art);
	waitKey(0);
}