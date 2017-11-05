#include"canny.h"

int main()
{
	double displacement_x = 0, displacement_y = 0, degree = 0.0, scale = 0.5;
	/*printf("Give the scale:");
	cin >> scale;
	printf("Give the displacement (x,y):");
	cin >> displacement_x >> displacement_y;*/
	cout << "旋轉度數:";
	cin >> degree;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	IplImage *original_image = cvLoadImage("456.jpg", 1), *new_image, *canny;
	double h = original_image->height, w = original_image->width;
	double new_h = int(h*scale), new_w = int(w*scale);
	double _sin = sin(2 * acos(0)*degree / 180), _cos = cos(2 * acos(0)*degree / 180);
	cout << _sin << "   " << _cos << endl;
	double new_height = new_h*abs(_cos) + new_w*abs(_sin), new_width = new_w*abs(_cos) + new_h*abs(_sin);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//cvShowImage("Original_image", original_image);//秀圖
	new_image = cvCreateImage(CvSize((w*abs(_cos) + h*abs(_sin))*scale, (w*abs(_sin) + h*abs(_cos))*scale), IPL_DEPTH_8U, 3);//創新的圖
	canny = cvCreateImage(CvSize((w*abs(_cos) + h*abs(_sin))*scale, (w*abs(_sin) + h*abs(_cos))*scale), IPL_DEPTH_8U, 3);
	int x = 0, y = 0, buffer = 0;

	for (int i = 0; i < original_image->height; i++, buffer += original_image->widthStep) {
		for (int j = 0; j < original_image->widthStep; j += 3) {
			blue[i][j / 3] = original_image->imageData[buffer + j];
			green[i][j / 3] = original_image->imageData[buffer + j + 1];
			red[i][j / 3] = original_image->imageData[buffer + j + 2];
		}
	}

	double h2 = 0.5*h, w2 = 0.5*w;
	double offset_x = -new_width / 2 * _cos - new_height / 2 * _sin + w2*scale;//偏移量x
	double offset_y = new_width / 2 * _sin - new_height / 2 * _cos + h2*scale;//偏移量y

	for (int ny = 0; ny < new_image->height; ny++)
		for (int nx = 0; nx < new_image->width; nx++) {
			x = (int)((nx*_cos + ny * _sin + offset_x) + displacement_x) / scale;
			y = (int)((-nx*_sin + ny*_cos + offset_y) + displacement_y) / scale;
			if (x >= 0 && y >= 0 && x < w&&y < h) {
				new_blue[ny][nx] = blue[y][x];
				new_green[ny][nx] = green[y][x];
				new_red[ny][nx] = red[y][x];
			}
		}

	buffer = 0;
	for (int i = 0; i < new_image->height; i++, buffer += new_image->widthStep)
		for (int j = 0; j < new_image->widthStep; j += 3) {
			new_image->imageData[buffer + j] = new_blue[i][j / 3];
			new_image->imageData[buffer + j + 1] = new_green[i][j / 3];
			new_image->imageData[buffer + j + 2] = new_red[i][j / 3];
			canny->imageData[buffer + j] = canny->imageData[buffer + j + 1] = canny->imageData[buffer + j + 2] = 0;
		}
	cvShowImage("Change_image", new_image);
	//canny edge
	buffer = 0;
	for (int i = 0; i < new_image->height; i++, buffer += new_image->widthStep) {
		for (int j = 0; j < new_image->widthStep; j += 3) {
			if ((abs(new_image->imageData[buffer + j] - new_image->imageData[buffer + 3 + j]) >= threshold) || abs((new_image->imageData[buffer + j + 1] - new_image->imageData[buffer + 3 + j + 1]) >= threshold) || abs((new_image->imageData[buffer + j + 2] - new_image->imageData[buffer + 3 + j + 2]) >= threshold) ||
				(abs(new_image->imageData[buffer + j] - new_image->imageData[buffer - 3 + j]) >= threshold) || abs((new_image->imageData[buffer + j + 1] - new_image->imageData[buffer - 3 + j + 1]) >= threshold || abs((new_image->imageData[buffer + j + 2] - new_image->imageData[buffer - 3 + j + 2]) >= threshold))) {//判斷差距
				canny->imageData[buffer + j] = canny->imageData[buffer + j + 1] = canny->imageData[buffer + j + 2] = 255;
			}
		}
	}

	//cvShowImage("Canny_image", canny);

	cvWaitKey(0);
}
