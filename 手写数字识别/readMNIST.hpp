#ifndef _DEF_HEAD_READMNIST_ 
#define _DEF_HEAD_READMNIST_
#include<string>
#include<iostream>
#include<fstream>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<vector>
using namespace std;
using namespace cv;
vector<Mat> readImage(string ss);
vector<int> readLabel(string ss);
#endif