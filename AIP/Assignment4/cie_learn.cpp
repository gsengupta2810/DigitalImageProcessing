#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <cmath>
using namespace std;
using namespace cv;

const int k_=10;

Point_<float> red,green,blue,white;
void desaturate_cie(const Mat img)
{
	Mat img_1;
	cvtColor(img,img_1,COLOR_BGR2XYZ);

	float** img_2_[2];
	for (int k = 0; k < 2; ++k)
	{
		img_2_[k]=new float* [img.rows];
		for (int i = 0; i < img.rows; ++i)
		{
			img_2_[k][i]=new float [img.cols];	
		}
	}
	
	for (int i = 0; i < img.rows; ++i)
	{
		for (int j = 0; j < img.cols; ++j)
		{
			if(img_1.at<Vec3b>(i,j)[0] + img_1.at<Vec3b>(i,j)[1] + img_1.at<Vec3b>(i,j)[2] !=0)
			{
				// cout<<"---------------"<<endl;
				// cout<<(float)img_1.at<Vec3b>(i,j)[0]/(float)((float)img_1.at<Vec3b>(i,j)[0]+(float)img_1.at<Vec3b>(i,j)[1]+(float)img_1.at<Vec3b>(i,j)[2])<<endl;
				img_2_[0][i][j]=(float)img_1.at<Vec3b>(i,j)[0]/(float)((float)img_1.at<Vec3b>(i,j)[0]+(float)img_1.at<Vec3b>(i,j)[1]+(float)img_1.at<Vec3b>(i,j)[2]);
				img_2_[1][i][j]=(float)img_1.at<Vec3b>(i,j)[1]/(float)((float)img_1.at<Vec3b>(i,j)[0]+(float)img_1.at<Vec3b>(i,j)[1]+(float)img_1.at<Vec3b>(i,j)[2]);
				// cout<<"****"<<img_2_[0][i][j]<<endl;
			}
		}
	}

	int Y_avg=0,count=0,Y_w;
	for (int i = 0; i < img_1.rows; ++i)
	{
		for (int j = 0; j < img_1.cols; ++j)
		{
			Y_avg+=img.at<Vec3b>(i,j)[1];
			count++;
		}
	}
	Y_avg/=count;
	Y_w=k_*Y_avg;

	for (int i = 0; i < img.rows; ++i)
	{
		for (int j = 0; j < img.cols; ++j)
		{
			float y1=img_1.at<Vec3b>(i,j)[1];
			// cout<<"img_2_[0][i][j]= "<<img_2_[0][i][j]<<", img_2_[1][i][j]="<<img_2_[1][i][j]<<endl;
			img_2_[0][i][j]=(float)((white.x*Y_w)/(white.y)+(img_2_[0][i][j]*y1)/img_2_[1][i][j])/(float)((float)(Y_w/white.y)+y1/img_2_[1][i][j]);
			img_2_[1][i][j]=(float)(Y_w+y1)/(float)((float)(Y_w/white.y)+y1/img_2_[1][i][j]);
			// cout<<"img_2_[0][i][j]= "<<img_2_[0][i][j]<<", img_2_[1][i][j]="<<img_2_[1][i][j]<<endl;
			// cout<<"-----------------------"<<endl;
		}
	}

	for (int i = 0; i < img.rows; ++i)
	{
		for (int j = 0; j < img.cols; ++j)
		{
			// cout<<"-------------------------"<<endl;
			if(sqrt((img_2_[0][i][j]-white.x)*(img_2_[0][i][j]-white.x)+(img_2_[1][i][j]-white.y)*(img_2_[1][i][j]-white.y))>0.06)
			{
				img_1.at<Vec3b>(i,j)[0]=(float)(img_2_[0][i][j])*(float)(img_1.at<Vec3b>(i,j)[0]+img_1.at<Vec3b>(i,j)[1]+img_1.at<Vec3b>(i,j)[2]);
				img_1.at<Vec3b>(i,j)[1]=(float)(img_2_[1][i][j])*(float)(img_1.at<Vec3b>(i,j)[0]+img_1.at<Vec3b>(i,j)[1]+img_1.at<Vec3b>(i,j)[2]);
			}
			// cout<<"at[0] = "<<(int)img_1.at<Vec3b>(i,j)[0]<<", at[1]="<<(int)img_1.at<Vec3b>(i,j)[1]<<", at[2]="<<(int)img_1.at<Vec3b>(i,j)[2]<<endl;
		}
	}
	Mat img_2;
	cvtColor(img_1,img_2,COLOR_XYZ2BGR);
	imshow("De-saturated",img_2);
	imwrite("./desaturated.jpg",img_2);

}

void max_saturate_CIE(const Mat img)
{
	Mat img_1;
	cvtColor(img,img_1,COLOR_BGR2XYZ);
	// saturate here
	float** img_2_[2];
	for (int k = 0; k < 2; ++k)
	{
		img_2_[k]=new float* [img.rows];
		for (int i = 0; i < img.rows; ++i)
		{
			img_2_[k][i]=new float [img.cols];	
		}
	}
	
	for (int i = 0; i < img.rows; ++i)
	{
		for (int j = 0; j < img.cols; ++j)
		{
			if(img_1.at<Vec3b>(i,j)[0] + img_1.at<Vec3b>(i,j)[1] + img_1.at<Vec3b>(i,j)[2] !=0)
			{
				// cout<<"---------------"<<endl;
				// cout<<(float)img_1.at<Vec3b>(i,j)[0]/(float)((float)img_1.at<Vec3b>(i,j)[0]+(float)img_1.at<Vec3b>(i,j)[1]+(float)img_1.at<Vec3b>(i,j)[2])<<endl;
				img_2_[0][i][j]=(float)img_1.at<Vec3b>(i,j)[0]/(float)((float)img_1.at<Vec3b>(i,j)[0]+(float)img_1.at<Vec3b>(i,j)[1]+(float)img_1.at<Vec3b>(i,j)[2]);
				img_2_[1][i][j]=(float)img_1.at<Vec3b>(i,j)[1]/(float)((float)img_1.at<Vec3b>(i,j)[0]+(float)img_1.at<Vec3b>(i,j)[1]+(float)img_1.at<Vec3b>(i,j)[2]);
				// cout<<"****"<<img_2_[0][i][j]<<endl;
			}
		}
	}
	//visualising the color distribution
	// Mat img_visualise(400,600,CV_8UC3,Scalar(255,255,255));
	// for (int i = 0; i < img.rows; ++i)
	// {
	// 	for (int j = 0; j < img.cols; ++j)
	// 	{
	// 		img_visualise.at<Vec3b>(img_2_[0][i][j]*600,img_2_[1][i][j]*600)[0]=0;
	// 	}
	// }
	// //drawing the gammut
	// line(img_visualise,Point((int)(600*red.y),(int)(600*red.x)),Point((int)(600*blue.y),(int)(600*blue.x)),Scalar(0,255,0));
	// line(img_visualise,Point((int)(600*green.y),(int)(600*green.x)),Point((int)(600*blue.y),(int)(600*blue.x)),Scalar(0,0,255));
	// line(img_visualise,Point((int)(600*green.y),(int)(600*green.x)),Point((int)(600*red.y),(int)(600*red.x)),Scalar(255,0,0));
	// imshow("CIE distribution",img_visualise);

	//Increasing the saturation by taking the points to the lines joining primary colors
	for (int i = 0; i < img.rows; ++i)
	{
		for (int j = 0; j < img.cols; ++j)
		{
			Point_<float> c,extended;
			c.x=img_2_[0][i][j];
			c.y=img_2_[1][i][j];
			// if(sqrt((c.x-white.x)*(c.x-white.x)+(c.y-white.y)*(c.y-white.y))>0.06)
			// {
			// 	float m1,m2,m3,m_br,m_gr,m_gb,m_cw;
			// 	m1=float(blue.y-white.y)/float(blue.x-white.x);
			// 	m2=float(red.y-white.y)/float(red.x-white.x);
			// 	m3=float(green.y-white.y)/float(green.x-white.x);

			// 	m_gr=float(green.y-red.y)/float(green.x-red.x);
			// 	m_gb=float(green.y-blue.y)/float(green.x-blue.x);
			// 	m_br=float(blue.y-red.y)/float(blue.x-red.x);
			// 	m_cw=float(c.y-white.y)/float(c.x-white.x);

			// 	int l1,l2,l3;
			// 	int l1_r,l1_g,l2_b,l2_g,l3_r,l3_b;

			// 	l1=(c.y-blue.y-m1*(c.x-blue.x))/fabs(c.y-blue.y-m1*(c.x-blue.x));
			// 	l2=(c.y-red.y-m1*(c.x-red.x))/fabs(c.y-red.y-m1*(c.x-red.x));
			// 	l3=(c.y-green.y-m1*(c.x-green.x))/fabs(c.y-green.y-m1*(c.x-green.x));

			// 	l1_r=(red.y-blue.y-m1*(red.x-blue.x))/fabs(red.y-blue.y-m1*(red.x-blue.x));
			// 	l1_g=(green.y-blue.y-m1*(green.x-blue.x))/fabs(green.y-blue.y-m1*(green.x-blue.x));
			// 	l2_g=(green.y-red.y-m1*(green.x-red.x))/fabs(green.y-red.y-m1*(green.x-red.x));
			// 	l2_b=(blue.y-red.y-m1*(blue.x-red.x))/fabs(blue.y-red.y-m1*(blue.x-red.x));
			// 	l3_b=(blue.y-green.y-m1*(blue.x-green.x))/fabs(blue.y-green.y-m1*(blue.x-green.x));
			// 	l3_r=(red.y-green.y-m1*(red.x-green.x))/fabs(red.y-green.y-m1*(red.x-green.x));
				
			// 	// cout<<"l1: "<<l1<<" l2: "<<l2<<" l3: "<<l3<<endl;
			// 	// cout<<"l1_r: "<<l1_r<<" l1_g: "<<l1_g<<" l2_g: "<<l2_g<<" l2_b: "<<l2_b<<" l3_b: "<<l3_b<<" l3_r: "<<l3_r<<endl;

			// 	if(l1==l1_r && l2==l2_b)
			// 	{
			// 		// extend to b-r line 
			// 		cout<<" b-r "<<endl;
			// 		extended.x= (float)((float)(c.y-red.y)+(float)(m_br*red.x-m_cw*c.x))/(float)(m_br-m_cw);
			// 		extended.y= c.y+(float)(m_cw*(extended.x-c.x));
			// 	}
			// 	if(l2==l2_g && l3==l3_r)
			// 	{
			// 		//extend to g-r line
			// 		cout<<" g-r "<<endl;
			// 		extended.x= (float)((float)(c.y-red.y)+(float)(m_br*red.x-m_cw*c.x))/(float)(m_gr-m_cw);
			// 		extended.y= c.y+(float)(m_cw*(extended.x-c.x));
			// 	}
			// 	if(l1==l1_g && l3==l3_b)
			// 	{
			// 		//extend to g-b line
			// 		cout<<" g-b "<<endl;
			// 		extended.x= (float)((float)(c.y-blue.y)+(float)(m_br*blue.x-m_cw*c.x))/(float)(m_gb-m_cw);
			// 		extended.y= c.y+(float)(m_cw*(extended.x-c.x));
			// 	}
			// 	cout<<"------------"<<endl;
			// 	// cout<<"c - "<<c<<" extended- "<<extended<<endl;
			// }
			if(sqrt((c.x-white.x)*(c.x-white.x)+(c.y-white.y)*(c.y-white.y))>0.06)
			{
				float m_gb,m_gr,m_br,m_cw;
				m_gr=float(green.y-red.y)/float(green.x-red.x);
				m_gb=float(green.y-blue.y)/float(green.x-blue.x);
				m_br=float(blue.y-red.y)/float(blue.x-red.x);
				m_cw=float(c.y-white.y)/float(c.x-white.x);
				float d1,d2,d3; // d1-br, d2-bg, d3-rg 
				d1=(float)(fabs((red.y-blue.y)*c.x-(red.x-blue.x)*c.y+red.x*blue.y-blue.x*red.y))/(float)(sqrt((red.x-blue.x)*(red.x-blue.x)+(red.y-blue.y)*(red.y-blue.y)));
				d2=(float)(fabs((green.y-blue.y)*c.x-(green.x-blue.x)*c.y+green.x*blue.y-blue.x*green.y))/(float)(sqrt((green.x-blue.x)*(green.x-blue.x)+(green.y-blue.y)*(green.y-blue.y)));
				d3=(float)(fabs((red.y-green.y)*c.x-(red.x-green.x)*c.y+red.x*green.y-green.x*red.y))/(float)(sqrt((red.x-green.x)*(red.x-green.x)+(red.y-green.y)*(red.y-green.y)));
				if(d1<d2 && d1<d3)
				{
					// cout<<"br"<<endl;
					extended.x= (float)((float)(c.y-red.y)+(float)(m_br*red.x-m_cw*c.x))/(float)(m_br-m_cw);
					extended.y= c.y+(float)(m_cw*(extended.x-c.x));
				}
				if(d2<d1 && d2<d3)
				{
					// cout<<"bg"<<endl;
					extended.x= (float)((float)(c.y-blue.y)+(float)(m_gb*blue.x-m_cw*c.x))/(float)(m_gb-m_cw);
					extended.y= c.y+(float)(m_cw*(extended.x-c.x));
				}
				if( d3<d1 && d3<d2)
				{
					// cout<<"gr"<<endl;
					extended.x= (float)((float)(c.y-red.y)+(float)(m_gr*red.x-m_cw*c.x))/(float)(m_gr-m_cw);
					extended.y= c.y+(float)(m_cw*(extended.x-c.x));
				}
				// cout<<"c - "<<c<<" extended- "<<extended<<endl;
				// cout<<"-------------------"<<endl;
				img_2_[0][i][j]=extended.x;
				img_2_[1][i][j]=extended.y;
			}	
			// cout<<"img_2_[0][i][j]= "<<img_2_[0][i][j]<<", img_2_[1][i][j]="<<img_2_[1][i][j]<<endl;
			// cout<<"*************"<<endl;
		}
	}
	for (int i = 0; i < img.rows; ++i)
	{
		for (int j = 0; j < img.cols; ++j)
		{
			// cout<<"-------------------------"<<endl;
			// cout<<"img_2_[0][i][j]= "<<img_2_[0][i][j]<<", img_2_[1][i][j]="<<img_2_[1][i][j]<<endl;
			if(sqrt((img_2_[0][i][j]-white.x)*(img_2_[0][i][j]-white.x)+(img_2_[1][i][j]-white.y)*(img_2_[1][i][j]-white.y))>0.06)
			{
				img_1.at<Vec3b>(i,j)[0]=(float)(img_2_[0][i][j])*(float)(img_1.at<Vec3b>(i,j)[0]+img_1.at<Vec3b>(i,j)[1]+img_1.at<Vec3b>(i,j)[2]);
				img_1.at<Vec3b>(i,j)[1]=(float)(img_2_[1][i][j])*(float)(img_1.at<Vec3b>(i,j)[0]+img_1.at<Vec3b>(i,j)[1]+img_1.at<Vec3b>(i,j)[2]);
			}
			// cout<<"at[0] = "<<(int)img_1.at<Vec3b>(i,j)[0]<<", at[1]="<<(int)img_1.at<Vec3b>(i,j)[1]<<", at[2]="<<(int)img_1.at<Vec3b>(i,j)[2]<<endl;
		}
	}
	Mat img_2;
	cvtColor(img_1,img_2,COLOR_XYZ2BGR);
	imshow("saturated",img_2);
	imwrite("./saturated.jpg",img_2);
	desaturate_cie(img_2);

}

void max_saturate_hsv(const Mat img)
{
	Mat img_1=img.clone();
	cvtColor(img,img_1,COLOR_BGR2HSV);
	for (int i = 0; i < img_1.rows; ++i)
	{
		for (int j = 0; j < img_1.cols ; ++j)
		{
			img_1.at<Vec3b>(i,j)[1]=(float)img_1.at<Vec3b>(i,j)[1]+(float)10*(float)img_1.at<Vec3b>(i,j)[1]/(float)100;
		}
	}
	Mat img_2;
	cvtColor(img_1,img_2,COLOR_HSV2BGR);
	imshow("saturated",img_2);
	desaturate_cie(img_2);
}

int main()
{
	red.x=0.412453/(0.212671+0.069334+0.412453);
	red.y=0.212671/(0.212671+0.069334+0.412453);
	green.x=0.357580/(0.357580 + 0.715160 + 0.0619193);
	green.y=0.715160 / (0.357580 + 0.715160 + 0.0619193);
	blue.x=0.0680423/(0.0680423+0.062169+0.950227);
	blue.y=0.062169/(0.0680423+0.062169+0.950227);
	white.x=0.3127;
	white.y=0.3290;

	cout<<"red "<<red<<" green "<<green<<" blue "<<blue<<endl;
	Mat img;
	// img=imread("./test_1.png");
	img=imread("./Indoor_normal_illumination.jpg");
	imshow("normal",img);

	//filtering image before saturating step
	Mat blurred;
	// GaussianBlur(img,blurred,Size(3,3),0);
	// max_saturate_CIE(img);
	// max_saturate_CIE(img);
	// max_saturate_hsv(blurred);
	max_saturate_hsv(img);
	waitKey(0);
}