#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main()
{
	VideoCapture cap(0);
	while(1)
	{
		Mat img;
		cap>>img;
		imshow("video",img);
		if(waitKey(10)>=0) break;
	}
	waitKey(0);
}