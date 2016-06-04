#include<opencv\cv.h>
#include<opencv\highgui.h>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace cv;

int main()
{
	Mat image;
	image = imread("lena.png", 1);
	namedWindow("lena", CV_WINDOW_AUTOSIZE);
	imshow("lena", image);
	waitKey(0);
	return 0;
}