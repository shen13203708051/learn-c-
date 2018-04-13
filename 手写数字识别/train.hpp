#ifndef _DEF_HEAD_TRAIN
#define _DEF_HEAD_TRAIN
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<string>
#include<iostream>
#include<vector>
#include<cmath>
int readImg();
cv::Mat calMean(const cv::Mat& src);
void saveXML();
double calDistance1(const cv::Mat& a,const cv::Mat& b,int flags);
#endif