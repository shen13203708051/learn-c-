#include<iostream>
#include<opencv2/highgui.hpp>
#include<opencv2/core.hpp>
#include<opencv2/imgproc.hpp>
#include<string>
#include<fstream>
using namespace std;
using namespace cv;

static int ReverseInt(int i)  
{  
    unsigned char ch1, ch2, ch3, ch4;  
    ch1 = i & 255;  
    ch2 = (i >> 8) & 255;  
    ch3 = (i >> 16) & 255;  
    ch4 = (i >> 24) & 255;  
    return((int)ch1 << 24) + ((int)ch2 << 16) + ((int)ch3 << 8) + ch4;  
}  

int main()
{
	FileStorage ImageDataSet;
    ImageDataSet.open("/home/shensy/Code/c++/opencv3编程入门/手写数字识别/database/TestLabelDataSet.xml",FileStorage::WRITE);
    ifstream file;
	file.open("/home/shensy/Code/c++/opencv3编程入门/手写数字识别/database/t10k-labels-idx1-ubyte",ifstream::binary);
	int magic_number = 0;  
    int number_of_images = 0;  
    int n_rows = 0;  
    int n_cols = 0;
	file.read((char*)&magic_number, sizeof(magic_number));  
    file.read((char*)&number_of_images, sizeof(number_of_images));    
    magic_number=ReverseInt(magic_number); 
    number_of_images=ReverseInt(number_of_images);
    
    //cout<<ReverseInt(magic_number)<<"       "<<ReverseInt(number_of_images)<<"      "<<ReverseInt(n_rows)<<"        "<<ReverseInt(n_cols)<<endl;
    for(int i=0;i<number_of_images;i++)
    {
        string ss="label"+to_string(i);
        unsigned char temp=0;
        file.read((char*)&temp, sizeof(temp));
        ImageDataSet<<ss<<(int)temp;
        cout<<"保存第"<<i<<"个标签"<<endl;
    }

	file.close();
    ImageDataSet.release();
    //cout<<label<<endl;
    // Mat dst;
    // resize(tupian,dst,Size(),4,4);
    // Mat dst1;
    // threshold(dst,dst1,150,255,THRESH_BINARY);
    // imshow("0",tupian);
    // imshow("1",dst);
    // imshow("2",dst1);
    
    waitKey(0);
	return 0;
}
