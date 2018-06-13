#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <fstream>

using namespace cv;
using namespace std;

Mat fundaMentalMatrix;
vector<Point_<float> > matching_pts_1,matching_pts_2;
vector<int> inlier_index;
vector<Point2f> points1,points2;

void detect_features(const Mat img, const Mat img_)
{
	// cout<<"here"<<endl;
	Mat img_1=img.clone();
	Mat img_2=img_.clone();
	vector<KeyPoint> keypoints_1,keypoints_2;
	int minHessian = 400;
	double max_dist = 0; double min_dist = 0.01;
	SurfFeatureDetector detector(minHessian);

	detector.detect( img_1, keypoints_1 );
	detector.detect( img_2, keypoints_2 );

	//-- Step 2: Calculate descriptors (feature vectors)
	SurfDescriptorExtractor extractor;

	Mat descriptors_1, descriptors_2;

	extractor.compute( img_1, keypoints_1, descriptors_1 );
	extractor.compute( img_2, keypoints_2, descriptors_2 );
	FlannBasedMatcher matcher;
  	std::vector< DMatch > matches;
  	matcher.match( descriptors_1, descriptors_2, matches );

  	std::vector< DMatch > good_matches;

    for( int i = 0; i < descriptors_1.rows; i++ )
    { if( matches[i].distance <= max(1.5*min_dist, 0.1) )
      { 
      	good_matches.push_back( matches[i]);
      	 
      }
    }
    //add all the points in good matches to matching_pts
    Mat img_1_matches=img.clone(),img_2_matches=img_.clone();
    for (int i = 0; i < good_matches.size(); ++i)
    {
    	// cout<<"queryIdx: "<<good_matches[i].queryIdx<<", trainIdx: "<<good_matches[i].trainIdx<<endl;
    	matching_pts_1.push_back(keypoints_1[good_matches[i].queryIdx].pt);	
    	matching_pts_2.push_back(keypoints_2[good_matches[i].trainIdx].pt);	
    	// circle(img_1_matches,keypoints_1[good_matches[i].queryIdx].pt,3,Scalar(0,255,0));
    	// circle(img_2_matches,keypoints_2[good_matches[i].trainIdx].pt,3,Scalar(0,255,0));
    }
    // imshow("pts in 1",img_1_matches);
    // imshow("pts in 2",img_2_matches);
    
    //-- Draw only "good" matches
    Mat img_matches;
    drawMatches( img_1, keypoints_1, img_2, keypoints_2,
                 good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
                 vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );

    //-- Show detected matches
    imshow( "Good Matches", img_matches ); 
}

void calc_fundamental_matrix()
{
	// cout<<"here"<<endl;
	Mat mask;
	fundaMentalMatrix=findFundamentalMat(matching_pts_1,matching_pts_2,CV_FM_RANSAC,2,0.99,mask);
	for (int i = 0; i < fundaMentalMatrix.rows; ++i)
	{
		for (int j = 0; j < fundaMentalMatrix.cols; ++j)
		{
			cout<<fundaMentalMatrix.at<double>(i,j);
		}
	}
	//showing the fundamental matrix: 
	cout<<"\n**********************Fundamental Matrix***********************"<<endl;
	for (int i = 0; i < fundaMentalMatrix.rows; ++i)
	{
		for (int j = 0; j < fundaMentalMatrix.cols; ++j)
		{
			cout<<fundaMentalMatrix.at<double>(i,j)<<" ";
		}
		cout<<endl;
	}
	cout<<"*****************************************************************"<<endl;
	//calculating the inliers
	for (int i = 0; i < mask.rows; ++i)
	{
		if((unsigned int)mask.at<uchar>(i)==1)
		{
			inlier_index.push_back(i);
			points1.push_back(matching_pts_1[i]);
			points2.push_back(matching_pts_2[i]);
			cout<<"Matching Point in 1- ("<<matching_pts_1[i].x<<","<<matching_pts_1[i].y<<") - in 2- ("<<matching_pts_2[i].x<<","<<matching_pts_2[i].y<<")"<<endl;
		}

	}
}

void drawEpipolarLines(const Mat& imgl,const Mat& imgr)
{
	Mat img_1=imgl.clone();
	Mat img_2=imgr.clone();
	CV_Assert(img_1.size() == img_2.size() && img_1.type() == img_2.type());

	Mat outImg_l;
	Mat outImg_r;

	cvtColor(img_1,outImg_l,CV_GRAY2BGR);
	cvtColor(img_2,outImg_r,CV_GRAY2BGR);

	vector< Vec<float,3> > epilines1,epilines2;
	computeCorrespondEpilines(points1, 1, fundaMentalMatrix, epilines1);
	computeCorrespondEpilines(points2, 2, fundaMentalMatrix, epilines2);

	CV_Assert(points1.size() == points2.size() &&
        points2.size() == epilines1.size() &&
        epilines1.size() == epilines2.size());

	cout<<epilines1.size()<<", "<<epilines2.size()<<endl;
	cv::RNG rng(0);
	for(size_t i=0; i<points1.size(); i++)
  	{
	    /*
	     * Epipolar lines of the 1st point set are drawn in the 2nd image and vice-versa
	     */
	    cv::Scalar color(rng(256),rng(256),rng(256));
 
	    cv::line(outImg_r,
	      cv::Point(0,-epilines1[i][2]/epilines1[i][1]),
	      cv::Point(imgl.cols,-(epilines1[i][2]+epilines1[i][0]*imgl.cols)/epilines1[i][1]),
	      color);
	    cv::circle(outImg_l, points1[i], 3, color, -1, CV_AA);
 
	    cv::line(outImg_l,
	      cv::Point(0,-epilines2[i][2]/epilines2[i][1]),
	      cv::Point(imgr.cols,-(epilines2[i][2]+epilines2[i][0]*imgr.cols)/epilines2[i][1]),
	      color);
	    cv::circle(outImg_r, points2[i], 3, color, -1, CV_AA);
	}
  	cv::imshow("epilines_l", outImg_l);
  	cv::imshow("epilines_r", outImg_r);
}

int main()
{
	Mat img_left=imread("./Sunrise_Lt.jpg",CV_LOAD_IMAGE_GRAYSCALE);
	Mat img_right=imread("./Sunrise_Rt.jpg",CV_LOAD_IMAGE_GRAYSCALE);
	imshow("lt",img_left);
	imshow("rt",img_right);
	detect_features(img_left,img_right);
	calc_fundamental_matrix();
	drawEpipolarLines(img_left,img_right);
	waitKey(0);
}