/*
*时间:2018/4/13
*作者：申思远
*功能：手写数字识别
*原理，KNN
*将MNIST中的图片和手写图片转换成相同的格式
*计算图片之间的欧氏距离（对应像素点相减，平方，在相加，开方）
*选择距离中的k个最小值
*k个值中哪个数字多就是哪个数字
*/
#include<iostream>
#include<cstdlib>
#include<opencv2/highgui.hpp>
#include<opencv2/core.hpp>
#include<opencv2/imgproc.hpp>
#include<string>
#include"readMNIST.hpp"
#include"train.hpp"
#include<vector>
using namespace std;
using namespace cv;

const int num_train=60000;//使用训练集的个数
const int K=10;//定义k的大小

//格式化自己写的图片（112*112）白底黑字
/*
*变换成和数字库中图片格式相同的格式
*腐蚀
*二值化
*/
Mat formatInputImage(string filename)//格式化自己输入的图片，用画图软件写出来的图
{
    Mat src=imread(filename,IMREAD_GRAYSCALE);
    Mat dst;
    Mat kernel=getStructuringElement(MORPH_RECT,Size(5,5));
    resize(src,dst,Size(112,112));
    erode(dst,dst,kernel);
    threshold(dst,dst,200,255,THRESH_BINARY);
    return dst;
}

int main(int argc,char *argv[])
{
    int mm;//执行函数时输入要识别的索引号（测试集中的索引）
    if(argc>1)
        mm=atoi(argv[1]);
    else
        mm=10;
    double time0=getTickCount();//开始计时
    //读取数字库，保存到对应的向量中
    vector<Mat> trainImage=readImage("/home/shensy/Code/c++/opencv3编程入门/手写数字识别/database/binary/train-images-idx3-ubyte");
    vector<Mat> testImage=readImage("/home/shensy/Code/c++/opencv3编程入门/手写数字识别/database/binary/t10k-images-idx3-ubyte");
    vector<int> trainLabel=readLabel("/home/shensy/Code/c++/opencv3编程入门/手写数字识别/database/binary/train-labels-idx1-ubyte");
    //如果使用测试库中的图片，就使用此行代码，mm表示数字库中的索引号
    //Mat test=testImage[mm];
    //如果使用自己写的数字，就用此行代码
    Mat test=formatInputImage("/home/shensy/图片/shuzi/test.png");//要识别的数字
    Mat distance(1,num_train,CV_64FC1);//创建矩阵，放置测试图片和已知图片的距离
    for(int i=0;i<num_train;i++)
    {
        distance.at<double>(0,i)=calDistance1(trainImage[i],test,1);//testImage[?]是要测试的图片testImage[mm]
    }
    imshow("testImage[100]",test);//将要测试的图片显示出来
    // //找最小距离
    vector<int> mindis;
    for(int i=0;i<K;i++)
    {
        double minVal=0,maxVal=0;
        Point minIndex,maxIndex;
        minMaxLoc(distance,&minVal,&maxVal,&minIndex,&maxIndex);
        //cout<<"minVal"<<minVal<<"   "<<"maxVal"<<maxVal<<"  "<<minIndex<<"  "<<maxIndex<<endl;
        //cout<<trainLabel[minIndex.x]<<" ";
        distance.at<double>(0,minIndex.x)=maxVal;
        mindis.push_back(trainLabel[minIndex.x]);
    }
    // //cout<<endl;
    //开始识别
    //cout<<"开始识别"<<endl;
    Mat Identification(1,10,CV_32SC1,Scalar::all(0));
    for(int i=0;i<K;i++)
    {
        Identification.at<int>(0,mindis[i])=Identification.at<int>(0,mindis[i])+1;
    }
    Point result;
    minMaxLoc(Identification,NULL,NULL,NULL,&result);
    cout<<"识别结果"<<result.x<<endl;
    cout<<"消耗时间"<<(getTickCount()-time0)/(double)getTickFrequency()<<"s"<<endl;
    waitKey(0);
    return 0;
}