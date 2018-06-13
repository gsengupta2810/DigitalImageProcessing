#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

Mat noise_reduce(Mat img)
{
	Mat img1 = img.clone();

	Mat smoothed;
	// blur(img1, smoothed, Size(7,7),Point(0,0));
	GaussianBlur(img1, smoothed, Size(3,3),0,0);
	// medianBlur(img1, smoothed, Size(3,3),Point(0,0));

	return smoothed;
}

Mat edge(Mat img)
{
	Mat img1 = img.clone();
	Mat edge;
	Canny(img1,edge,50,120,3);
	return edge;
}

pair<vector<Vec4i>,Mat> line_detect(Mat orig_img, Mat edges)
{
	vector<Vec4i> lines;
	Mat lines_out;
	Mat lines_detected = orig_img.clone();

  	HoughLinesP(edges, lines, 1, CV_PI/180, 50, 50, 10);

  	for( size_t i = 0; i < lines.size(); i++ )
  	{
    	 line( lines_detected, Point(lines[i][0], lines[i][1]),
            Point(lines[i][2], lines[i][3]), Scalar(255), 1, 8 );
	}
	return pair<vector<Vec4i>,Mat>(lines,lines_detected);
}

pair<Mat,vector<vector<Point> > > contour_detect(Mat img)
{
	Mat img1 = img.clone();
	vector<vector<Point> > contours;
  	vector<Vec4i> hierarchy;

	findContours( img1, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
	Mat drawing = Mat::zeros( img1.size(), CV_8UC1);

	for( int i = 0; i< contours.size(); i++ )
    {
       drawContours( drawing, contours, i, Scalar(255), 2, 8, hierarchy, 0, Point() );
    }
    return pair<Mat,vector<vector<Point> > > (drawing,contours);

}	

// void detect_rectangles(vector<vec4i> line_eqs)
// {

// }

pair<vector<Vec4i>,Mat> line_detect_normal(Mat orig_img, Mat edges)
{
	vector<Vec4i> lines;
	Mat lines_out;
	Mat lines_detected = orig_img.clone();

  	HoughLines(edges, lines, 1, CV_PI/180, 50, 50, 10);

  	for( size_t i = 0; i < lines.size(); i++ )
  	{
    	 line( lines_detected, Point(lines[i][0], lines[i][1]),
            Point(lines[i][2], lines[i][3]), Scalar(255), 3, 8 );
	}
	return pair<vector<Vec4i>,Mat>(lines,lines_detected);
}

vector<Mat> detect_rectangles(Mat img, vector<vector<Point> > contours)
{
	vector<Mat> img1 ;
	vector<Mat> output_imgs;
	vector<vector<Point> > detected_rects;

	cout<<contours.size()<<endl;
	for( size_t k = 0; k < contours.size(); k++ )
	{
		vector<Point> contours0;
		approxPolyDP(Mat(contours[k]), contours0, 3, true);

        if(contours0.size() >=4 && contours0.size() <= 10)
        {
        	float area = contourArea(contours0);
        	// cout<<"Area = "<<area<<endl;
        	if(area>1000)
	        	detected_rects.push_back(contours0);
        }
	}
	cout<<detected_rects.size()<<endl;
	
	for( int i = 0; i< detected_rects.size(); i++ )
    {
    	img1.push_back(img.clone());
    	// Mat temp(img.rows,img.cols,CV_8UC1,Scalar(0));
    	// img1.push_back(temp);
        // drawContours( img1[i], detected_rects, i, Scalar(255), 2, 8);
	    // imshow("Output",img1[i]);

    	//--------------------------------------------------------------
     //    pair<vector<Vec4i>,Mat> lines_detected = line_detect(img1[i].clone(),img1[i]);
     //    vector<Vec4i> lines = lines_detected.first;
     //    Mat drawLines = lines_detected.second;
	    // imshow("Output",drawLines);
     //    cout<<"Lines size"<<lines.size()<<endl;
        //--------------------------------------------------------------------

    	Mat temp;
    	output_imgs.push_back(temp);

    	vector<Point> cur_pts = detected_rects[i];

    	Point2f inputpts[4];
    	Point2f outputpts[4];
    	
    	int x_min= INT_MAX,x_max=INT_MIN,y_min=INT_MAX,y_max=INT_MIN;

    	for(int j=0;j<cur_pts.size();j++)
    	{
    		int x = cur_pts[j].x;
    		int y = cur_pts[j].y;

    		if(x< x_min)
    			x_min=x;
    		if(x> x_max)
    			x_max=x;
    		if(y < y_min)
    			y_min = y;
    		if(y > y_max)
    			y_max = y;
    	}

    	inputpts[0].x = x_min;
    	inputpts[0].y = y_min;

    	inputpts[1].x = x_min;
    	inputpts[1].y = y_max;

    	inputpts[2].x = x_max;
    	inputpts[2].y = y_max;

    	inputpts[3].x = x_max;
    	inputpts[3].y = y_min;



    	//______________________________

    	outputpts[0].x = 0;
    	outputpts[0].y = 0;

    	outputpts[1].x = 0;
    	outputpts[1].y = 100;

    	outputpts[2].x = 400;
    	outputpts[2].y = 100;

    	outputpts[3].x = 400;
    	outputpts[3].y = 0;

    	// for(int k=0;k<4;k++)
	    // 	cout<<inputpts[k].x<<" "<<inputpts[k].y<<endl ;

    	Mat lambda( 2, 4, CV_32FC1 );
    	lambda = getPerspectiveTransform( inputpts, outputpts );
    	warpPerspective(img1[i],output_imgs[i],lambda,Size(400,100) );
    	
    	imshow("Input",img1[i]);
	    imshow("Output",output_imgs[i]);
	    waitKey(0);
    }

    return output_imgs;
}

Mat binarize(Mat img)
{
	Mat img1 = img.clone();

	Mat gray ;
	cvtColor(img1,gray, CV_BGR2GRAY);
	Mat dst;

	int threshold_value = 80;
	int threshold_type = 0;
	int const max_value = 255;
	int const max_type = 4;
	int const max_binary_value = 255;

	threshold( gray, dst, threshold_value, max_binary_value, threshold_type );
    // imshow( window_name, dst );
    return dst;
}

int main()
{
	Mat img = imread("./images/1.jpg",CV_LOAD_IMAGE_COLOR);
	imshow("original image",img);

	Mat noisefree = noise_reduce(img);
	imshow("smoothed image",noisefree);
	
	Mat edges = edge(noisefree);
	imshow("edge image",edges);

	pair<Mat,vector<vector<Point> > > contours_ret = contour_detect(edges);
	Mat contours_img = contours_ret.first;
	vector<vector<Point> > contours = contours_ret.second; 
	imshow("contour image",contours_img);

	// pair<vector<Vec4i>,Mat > lines = line_detect(img, contours);
	// Mat lines_detected = lines.second;
	// vector<Vec4i> line_eqs = lines.first;
	// imshow("lines image",lines_detected);

	vector<Mat> rects = detect_rectangles(noisefree,contours);

	for(int i=0;i<rects.size();i++)
	{
		Mat cur = rects[i];
		Mat binary = binarize(cur);
		imshow("binary image",binary);
		imwrite("binary.png", binary);
		waitKey(0);
	}



	waitKey(0); 
	return 0;
}