#pragma once

#include<highgui.hpp>
#include<iostream>
#include<stdio.h>
#include<math.h>

#define threshold 30
//#define h 551
//#define w 552
//#define scale 1
//#define new_h (int)(h*scale)
//#define new_w  (int)(w*scale)
uchar blue[2000][2000];
uchar green[2000][2000];
uchar red[2000][2000];
uchar new_blue[2000][2000];
uchar new_green[2000][2000];
uchar new_red[2000][2000];

using namespace std;
using namespace cv;