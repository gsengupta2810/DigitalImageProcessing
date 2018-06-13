#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;
using namespace cv;

vector<Point2f> image1_pts,image2_pts;

static void onMouse(int event, int x, int y,int ,void* flag)
{
	if( event != EVENT_LBUTTONDOWN )
        return;
    if((int)flag ==1)
    {
    	image1_pts.push_back(Point(x,y));
    }
    else if((int)flag ==2)
    	image2_pts.push_back(Point(x,y));
}

void calc_Homography(Mat img1,Mat img2)
{
	cout<<"select four points in image 1 and corrosponding points in image 2"<<endl;
	Mat img_1=img1.clone();
	Mat img_2=img2.clone();
	namedWindow("image one",CV_WINDOW_AUTOSIZE);
	namedWindow("image two",CV_WINDOW_AUTOSIZE);
	imshow("image one",img_1);
	imshow("image two",img_2);
	setMouseCallback("image one",onMouse,(void*)1);
	setMouseCallback("image two",onMouse,(void*)2);
	while(1)
	{
		for (int i = 0; i < image1_pts.size(); ++i)
		{
			circle(img_1,image1_pts[i],10,Scalar(0,0,255),10,8);
		}
		for (int i = 0; i < image2_pts.size(); ++i)
		{
			circle(img_2,image2_pts[i],10,Scalar(0,0,255),10,8);
		}
		imshow("image one",img_1);
		imshow("image two",img_2);
		if(image1_pts.size()>4){
			cout<<"sufficient points selected"<<endl;
		}
		if(image2_pts.size()>4){
			cout<<"sufficient points selected"<<endl;
		}
		if(image1_pts.size()>4 && image2_pts.size()>4)
			break;
		if(waitKey(10)>0)
			break;
	}
	Mat homography=findHomography(image1_pts,image2_pts,CV_RANSAC);
	cout<<"Homography Matrix is: "<<endl;
	for (int i = 0; i < homography.rows; ++i)
	{
		for (int j = 0; j <homography.cols ; ++j)
		{
			cout<<(float)homography.at<uchar>(i,j)<<" ";
		}
		cout<<endl;
	}
}

void calc_Homography_from_features(Mat img1,Mat img2,vector<Point2f> pt1,vector<Point2f> pt2)
{
	cout<<"select four points in image 1 and corrosponding points in image 2"<<endl;
	Mat img_1=img1.clone();
	Mat img_2=img2.clone();
	Mat homography=findHomography(pt1,pt2,CV_RANSAC);
	cout<<"Homography Matrix from SIFT/SURF feature detector is: "<<endl;
	for (int i = 0; i < homography.rows; ++i)
	{
		for (int j = 0; j <homography.cols ; ++j)
		{
			cout<<(float)homography.at<uchar>(i,j)<<" ";
		}
		cout<<endl;
	}
}

vector<KeyPoint> feature_detect(Mat img, char check)
{

    vector<KeyPoint> keypoints;
	if(check==0)
	{
		SiftFeatureDetector detector;
	    detector.detect(img, keypoints);
	}
	else if(check==1)
	{
		SurfFeatureDetector detector;
	    detector.detect(img, keypoints);
	}
    return keypoints;
}

void match_features(Mat img1,Mat img2,int check)
{
	Mat img_1=img1.clone();
	Mat img_2=img2.clone();
	vector<KeyPoint> keypoints_1,keypoints_2;
	keypoints_1=feature_detect(img_1,check);
	keypoints_2=feature_detect(img_2,check);

	//Calculating homography from features 
	vector<Point2f> pts1,pts2;
	for (int i = 0; i < keypoints_1.size(); ++i)
	{
		pts1.push_back(keypoints_1[i].pt);
		pts2.push_back(keypoints_2[i].pt);
	}
	calc_Homography_from_features(img_1,img_2,pts1,pts2);
	
	SiftDescriptorExtractor extractor;
 	Mat descriptors_1, descriptors_2;
    extractor.compute( img_1, keypoints_1, descriptors_1 );
    extractor.compute( img_2, keypoints_2, descriptors_2 );
    
    //-- Step 3: Matching descriptor vectors using FLANN matcher
  	FlannBasedMatcher matcher;
    std::vector< DMatch > matches;
    matcher.match( descriptors_1, descriptors_2, matches );
    double max_dist = 0; double min_dist = 100;

	  //-- Quick calculation of max and min distances between keypoints
	  for( int i = 0; i < descriptors_1.rows; i++ )
	  { double dist = matches[i].distance;
	    if( dist < min_dist ) min_dist = dist;
	    if( dist > max_dist ) max_dist = dist;
	  }

	  printf("-- Max dist : %f \n", max_dist );
	  printf("-- Min dist : %f \n", min_dist );

	  //-- Draw only "good" matches (i.e. whose distance is less than 2*min_dist,
	  //-- or a small arbitary value ( 0.02 ) in the event that min_dist is very
	  //-- small)
	  //-- PS.- radiusMatch can also be used here.
	  std::vector< DMatch > good_matches;

	  for( int i = 0; i < descriptors_1.rows; i++ )
	  { if( matches[i].distance <= max(1.5*min_dist, 0.02) )
	    { good_matches.push_back( matches[i]); }
	  }

	  //-- Draw only "good" matches
	  Mat img_matches;
	  drawMatches( img_1, keypoints_1, img_2, keypoints_2,
	               good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
	               vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );

	  //-- Show detected matches
	  imshow( "Good Matches", img_matches );

	  // for( int i = 0; i < (int)good_matches.size(); i++ )
	  // { printf( "-- Good Match [%d] Keypoint 1: %d  -- Keypoint 2: %d  \n", i, good_matches[i].queryIdx, good_matches[i].trainIdx ); }

}

int main(int argv,char* argc[])
{
	if(argv<2)
	{
		cout<<"Number of arguments less than required"<<endl;
		return 0;
	}
	Mat img_1=imread(argc[1],CV_LOAD_IMAGE_COLOR);
	Mat img_2=imread(argc[2],CV_LOAD_IMAGE_COLOR);
	calc_Homography(img_1,img_2);
	match_features(img_1,img_2,0);
	waitKey(0);
	return 0;
}