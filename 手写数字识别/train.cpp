#include"train.hpp"
std::vector<cv::Mat> train_data;//定义一个矩阵向量，用来保存读取的图片
int readImg()
{
    for(int i=0;i<10;i++)
    {
        std::string st1="/home/shensy/图片/shuzi/test"+std::to_string(i)+".png";//定义字符串保存图片路径
        cv::Mat src=cv::imread(st1,cv::IMREAD_GRAYSCALE);//读取数字图片，灰度图
        if(!src.data)//如果图片内容为空，则报错
        {
            std::cout<<"图片读取错误"<<std::endl;
            return -1;
        }
        train_data.push_back(src);//将图片数据压入向量中
    }
    //cv::imshow("src",train_data[1]);
    //std::cout<<train_data[1]<<std::endl;
    return 0;
}

/*
*矩阵分块求平均
*src：输入矩阵
*dst：输出矩阵
*/
cv::Mat calMean(const cv::Mat& src)
{
    int size=2;
    int src_row=src.rows;//输入矩阵的行数
    int src_col=src.cols;//输入矩阵的列数
    cv::Mat temp(src_row/size+1,src_col/size+1,CV_64FC1,cv::Scalar::all(0));//创建矩阵，用于存放求出的分块平均值，分块大小10*10，如果除不尽就多出一块儿
    for(int i=0;i<temp.rows-1;i++)
    {
        for(int j=0;j<temp.cols-1;j++)
        {
            int a,b;
            a=i*size>src_row?(src_row-size):i;
            b=j*size>src_col?(src_col-size):j;
            temp.at<double>(i,j)=(double)cv::mean(src(cv::Rect(a,b,size,size)))[0];
            //std::cout<<(double)cv::mean(src(cv::Rect(a,b,size,size)))[0]<<"  ";
        }
        //std::cout<<std::endl;
    }
    return temp;
}

void saveXML()
{
    cv::FileStorage file;
    std::string ss;
    int index=0;
    file.open("/home/shensy/Code/c++/opencv3编程入门/手写数字识别/file.xml",cv::FileStorage::WRITE);
    for(auto i:train_data)
    {
        ss="train_data"+std::to_string(index);//标签格式：train_data0,train_data1...
        file<<ss<<i;
        index++;
    }
    file.release();
}

/*
*计算两个矩阵的欧式距离
*对应元素相减，平方，相加，然后再开方
*/
double calDistance1(const cv::Mat& a,const cv::Mat& b,int flags)
{
    double dis=0;
    int row=a.rows;
    int col=a.cols;
    if(flags==0)
    {
        for(int i=0;i<row;i++)
        {
            for(int j=0;j<col;j++)
            {
                dis += ((a.at<double>(i,j)-b.at<double>(i,j))*(a.at<double>(i,j)-b.at<double>(i,j)));
                // std::cout<<dis<<" ";
                // std::cout<<"a"<<a.at<double>(i,j)<<" ";
                // std::cout<<"b"<<b.at<double>(i,j)<<" ";
            }
        }
    }
    else
    {
        for(int i=0;i<row;i++)
        {
            for(int j=0;j<col;j++)
            {
                dis += (double)((a.at<unsigned char>(i,j)-b.at<unsigned char>(i,j))*(a.at<unsigned char>(i,j)-b.at<unsigned char>(i,j)));
                // std::cout<<dis<<" ";
                // std::cout<<"a"<<(double)a.at<unsigned char>(i,j)<<" ";
                // std::cout<<"b"<<(double)b.at<unsigned char>(i,j)<<" ";
            }
        }
    }
    return sqrt(dis);
}
