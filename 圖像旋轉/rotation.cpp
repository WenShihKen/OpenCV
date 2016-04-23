#include"rotation.h"

int main()
{
	printf("You can change the scale at header. Default is 1.");
	printf("Please input the displacement:");
	double displacement_x, displacement_y;
	cin >> displacement_x >> displacement_y;
	double degree;
	cout << "Angle:";
	cin >> degree;
	IplImage *original_image = cvLoadImage("a.jpg", 1);
	IplImage *new_image;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	double _sin = sin(2 * acos(0)*degree / 180), _cos = cos(2 * acos(0)*degree / 180);
	double new_height = new_h*abs(_cos) + new_w*abs(_sin), new_width = new_w*abs(_cos) + new_h*abs(_sin);

	cvShowImage("Original_image", original_image);//秀圖
	new_image = cvCreateImage(CvSize((w*_cos+h*_sin)*scale, (w*_sin+h*_cos)*scale), IPL_DEPTH_8U, 3);//創新的圖

	int x = 0, y = 0, buffer = 0;
	
	for (int i = 0; i < original_image->height; i++, buffer += original_image->widthStep) {
		for (int j = 0; j < original_image->widthStep; j += 3) {
			blue[i][j / 3] = original_image->imageData[buffer + j];
			green[i][j / 3] = original_image->imageData[buffer + j + 1];
			red[i][j / 3] = original_image->imageData[buffer + j + 2];
		}
	}
	double h2, w2;
	w2 = 0.5*w, h2 = 0.5*h;
	
	double offset_x, offset_y;
	offset_x = -new_width /2*_cos - new_height /2*_sin + w2*scale;
	offset_y = new_width /2*_sin - new_height /2*_cos + h2*scale;

	cout << offset_x << " " << offset_y << endl;

	for (int ny = 0; ny < new_image->height; ny++) {
		for (int nx = 0; nx < new_image->width; nx++) {
		
			x = (int)((nx*_cos + ny * _sin+offset_x)+displacement_x) / scale;
			y = (int)((-nx*_sin +ny*_cos+offset_y)+displacement_y) / scale;
			if (x >= 0 && y >= 0 && x < w&&y < h) {
				new_blue[ny][nx] = blue[y][x];
				new_green[ny][nx] = green[y][x];
				new_red[ny][nx] = red[y][x];
			}
		}
	}

	buffer = 0;
	for (int i = 0; i < new_image->height; i++, buffer += new_image->widthStep) {
		for (int j = 0; j < new_image->widthStep; j += 3) {
			new_image->imageData[buffer + j] = new_blue[i][j / 3];
			new_image->imageData[buffer + j + 1] = new_green[i][j / 3];
			new_image->imageData[buffer + j + 2] = new_red[i][j / 3];
		}
	}

	cvShowImage("Change_image", new_image);

	cvWaitKey(0);
}