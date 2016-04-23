#pragma once

#include<highgui.hpp>
#include<iostream>
#include<stdio.h>
#include<math.h>

#define nnn 
#define h 208
#define w 236
#define scale 2
#define new_h (int)(h*scale)
#define new_w  (int)(w*scale)
uchar blue[h][w];
uchar green[h][w];
uchar red[h][w];
uchar new_blue[4096][4096];
uchar new_green[4096][4096];
uchar new_red[4096][4096];

using namespace std;