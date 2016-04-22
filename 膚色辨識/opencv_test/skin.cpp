#include <cv.h>  //Computer Vision
#include <highgui.h> //GUI¤¶­±ªº¨ç¦¡®w
#include <stdio.h>


uchar b[2048][2048];
uchar g[2048][2048];
uchar r[2048][2048];
uchar Y[2048][2048];
uchar Cb[2048][2048];
uchar Cr[2048][2048];

int main()
{
	IplImage* Image1 = cvLoadImage("a.jpg", 1);
	IplImage* Image2 = cvLoadImage("a.jpg", 1);
	for (int i = 0; i<Image1->height; i++)
	{
		for (int j = 0; j<Image1->widthStep; j = j + 3)
		{
			b[i][j / 3] = Image1->imageData[i*Image1->widthStep + j];
			g[i][j / 3] = Image1->imageData[i*Image1->widthStep + j + 1];
			r[i][j / 3] = Image1->imageData[i*Image1->widthStep + j + 2];
		}
	}

	for (int i = 0; i<Image1->height; i++)
	{
		for (int j = 0; j<Image1->width; j++)
		{
			Y[i][j] = (0.299*r[i][j] + 0.587*g[i][j] + 0.114*b[i][j]);
			Cb[i][j] = (0.500*b[i][j] - 0.331*r[i][j] - 0.169*g[i][j] + 127);
			Cr[i][j] = (0.500*r[i][j] - 0.419*g[i][j] - 0.081*b[i][j] + 127);
		}
	}
	char* buf = Image1->imageData;
	
	for (int i = 0; i<Image1->height; i++, buf += Image1->widthStep)
	{
		for (int j = 0; j < Image1->widthStep; j = j + 3)
		{
			if ((Cb[i][j / 3] >77 && Cb[i][j / 3] < 127) &&
				(Cr[i][j / 3] > 133 && Cr[i][j / 3]< 173))
			{
				buf[j] = 255;
				buf[j + 1] = 255;
				buf[j + 2] = 255;
			}
			else
			{
				buf[j] = 0;
				buf[j + 1] = 0;
				buf[j + 2] = 0;
			}
		}
	}


	cvShowImage("SkinDetection", Image1);
	cvShowImage("picture", Image2);
	cvWaitKey(0);
	cvReleaseImage(&Image1);
}