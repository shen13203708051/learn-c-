#include"readMNIST.hpp"

static int ReverseInt(int i)  //转换魔数，读取数据库中的图片数，行数，列数等信息  
{    
    unsigned char ch1, ch2, ch3, ch4;    
    ch1 = i & 255;    
    ch2 = (i >> 8) & 255;    
    ch3 = (i >> 16) & 255;    
    ch4 = (i >> 24) & 255;    
    return((int)ch1 << 24) + ((int)ch2 << 16) + ((int)ch3 << 8) + ch4;    
}  

vector<Mat> readImage(string ss)//"/home/shensy/Code/c++/opencv3编程入门/手写数字识别/database/t10k-images-idx3-ubyte"
{
    vector<Mat> savedata;
    ifstream file;  
    file.open(ss,ifstream::binary); 
    if(!file.is_open())
        cout<<"打开文件错误"<<endl; 
    int magic_number = 0;    
    int number_of_images = 0;    
    int n_rows = 0;    
    int n_cols = 0;  
    file.read((char*)&magic_number, sizeof(magic_number));    
    file.read((char*)&number_of_images, sizeof(number_of_images));      
    file.read((char*)&n_rows, sizeof(n_rows));     
    file.read((char*)&n_cols, sizeof(n_cols));   
    magic_number=ReverseInt(magic_number);   
    number_of_images=ReverseInt(number_of_images);  
    n_rows=ReverseInt(n_rows);  
    n_cols=ReverseInt(n_cols);  
      
    for(int i=0;i<number_of_images;i++)  
    {  
        Mat tupian(n_rows,n_cols,CV_8UC1);  
        for(int j=0;j<n_rows;j++)  
        {  
            for(int k=0;k<n_cols;k++)  
            {  
                unsigned char temp=0;  
                file.read((char*)&temp, sizeof(temp));  
                tupian.at<unsigned char>(j,k)=(int)temp;  
            }  
        }  
        Mat dst;
        resize(tupian,dst,Size(),4,4);
        threshold(dst,dst,180,255,THRESH_BINARY_INV);
        savedata.push_back(dst);  
        //cout<<"保存第"<<i<<"张图片"<<endl;  
    }  
    file.close(); 
    return savedata;
}

vector<int> readLabel(string ss)
{
    vector<int> saveLabel;
    ifstream file;  
    file.open(ss,ifstream::binary);  
    if(!file.is_open())
        cout<<"打开文件错误"<<endl; 
    int magic_number = 0;    
    int number_of_images = 0;    
    file.read((char*)&magic_number, sizeof(magic_number));    
    file.read((char*)&number_of_images, sizeof(number_of_images));      
    magic_number=ReverseInt(magic_number);   
    number_of_images=ReverseInt(number_of_images);  
      
    
    for(int i=0;i<number_of_images;i++)  
    {  
        string ss="label"+to_string(i);  
        unsigned char temp=0;  
        file.read((char*)&temp, sizeof(temp));  
        saveLabel.push_back((int)temp);  
        //cout<<"保存第"<<i<<"个标签"<<endl;  
    }  
    file.close(); 
    return  saveLabel;
}