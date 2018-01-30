#include<iostream>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<ctime>
#include<cstdlib>
#include<cmath>
#include<iomanip>
#include"myFunction.h"

using namespace std;
using namespace cv;
int main(int argc,char* argv[])
{
	cout << setiosflags(ios::left)<< setiosflags(ios::fixed)<< setprecision(2);//设置成数据靠左显示,小数点后两位
	srand((unsigned)time(NULL));//设置随机数种子
	Mat A = (Mat_<int>(3, 2) << 11, 12, 21, 22, 31, 32);//定义矩阵A
	Mat B = Mat::zeros(10, 20,CV_32FC1);//定义矩阵B为全零，大小10行20列，数据类型：int

	for (auto i : range(0, B.rows))//像B举证中写随机数
	{
		float *ptr = B.ptr<float>(i);//每行定义一个指针指向每行的首元素
		for (auto j : range(0, B.cols))//
			ptr[j]=abs(rand())%10/1.0F ;//写值
	}

	cout << "原矩阵B：" << endl;
	for (auto i : range(0, B.rows))//显示
	{
		float *ptr = B.ptr<float>(i);
		for (auto j : range(0, B.cols))
			cout<<setw(6)<<ptr[j];//设置显示位置宽度
		cout << endl;
	}

	cout << endl;
	//矩阵切片
	Mat C_temp = B(Rect(2,1,3,5));//第2列（从0开始），第1行（从0开始）,切出来3列5行
	Mat C = C_temp.clone();//将上述切出来的矩阵拷贝给另外一个矩阵，上矩阵上原矩阵的一部分，而clone之后的矩阵是一个全新的矩阵
	cout << "矩阵C(B的第2行第3列开始，往后5行，往后3列)：" << endl;
	for (auto i : range(0, C.rows))
	{
		for (auto j : range(0, C.cols))
			cout << setw(8) << C.at<float>(i, j);
		cout << endl;
	}
	cout << endl;

	Mat D;//定义一个新矩阵D
	B(Rect(3, 2, 5, 5)).copyTo(D);//将切出来的矩阵拷贝给D矩阵
	cout << "矩阵D(B的第三行第四列开始，往后5行，往后5列)：" << endl;
	for (auto i : range(0, D.rows))
	{
		for (auto j : range(0, D.cols))
			cout << setw(8) << D.at<float>(i, j);
		cout << endl;
	}
	cout << endl;

	Mat F = B(Rect(5, 1, 5, 5)).clone();//定义一个矩阵
	cout << "矩阵F(B的第2行第6列开始，往后5行，往后5列)：" << endl;
	for (auto i : range(0, F.rows))
	{
		for (auto j : range(0, F.cols))
			cout << setw(8) << F.at<float>(i, j);
		cout << endl;
	}
	cout << endl;

	//矩阵加法
	Mat sum_matrix = D + F;
	cout << "矩阵D+矩阵F：" << endl;
	for (auto i : range(0, sum_matrix.rows))
	{
		for (auto j : range(0, sum_matrix.cols))
			cout << setw(8) << sum_matrix.at<float>(i, j);
		cout << endl;
	}
	cout << endl;

	//矩阵加法
	Mat sub_matrix = D - F;
	cout << "矩阵D-矩阵F：" << endl;
	for (auto i : range(0, sub_matrix.rows))
	{
		for (auto j : range(0, sub_matrix.cols))
			cout << setw(8) << sub_matrix.at<float>(i, j);
		cout << endl;
	}
	cout << endl;

	//矩阵点乘
	Mat dot_matrix = D.mul(F);
	cout << "矩阵D点乘矩阵F：" << endl;
	for (auto i : range(0, dot_matrix.rows))
	{
		for (auto j : range(0, dot_matrix.cols))
			cout << setw(8) << dot_matrix.at<float>(i, j);
		cout << endl;
	}
	cout << endl;

	//矩阵乘法(乘法必须要求两个矩阵同为float或者同为double，否则会出错)
	Mat product_matrix = D*F;
	cout << "矩阵D叉乘矩阵F（矩阵乘法）：" << endl;
	for (auto i : range(0, product_matrix.rows))
	{
		for (auto j : range(0, product_matrix.cols))
			cout << setw(8) << product_matrix.at<float>(i, j);
		cout << endl;
	}
	cout << endl;

	//矩阵倍乘
	Mat mul_mat = trans_matrix(D);
	cout << "矩阵D的2倍：" << endl;
	for (auto i : range(0, mul_mat.rows))
	{
		for (auto j : range(0, mul_mat.cols))
			cout << setw(8) << mul_mat.at<float>(i, j);
		cout << endl;
	}
	cout << endl;

	//矩阵求逆
	Mat invert_matrix;
	invert(D, invert_matrix);
	cout << "矩阵D求逆：" << endl;
	for (auto i : range(0, invert_matrix.rows))
	{
		for (auto j : range(0, invert_matrix.cols))
			cout << setw(8) << invert_matrix.at<float>(i, j);
		cout << endl;
	}
	cout << endl;

	waitKey(0);
	cout << "Hello" << endl;
	system("pause");
	return EXIT_SUCCESS;
}