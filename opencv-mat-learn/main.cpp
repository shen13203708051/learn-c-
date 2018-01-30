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
	cout << setiosflags(ios::left)<< setiosflags(ios::fixed)<< setprecision(2);//���ó����ݿ�����ʾ,С�������λ
	srand((unsigned)time(NULL));//�������������
	Mat A = (Mat_<int>(3, 2) << 11, 12, 21, 22, 31, 32);//�������A
	Mat B = Mat::zeros(10, 20,CV_32FC1);//�������BΪȫ�㣬��С10��20�У��������ͣ�int

	for (auto i : range(0, B.rows))//��B��֤��д�����
	{
		float *ptr = B.ptr<float>(i);//ÿ�ж���һ��ָ��ָ��ÿ�е���Ԫ��
		for (auto j : range(0, B.cols))//
			ptr[j]=abs(rand())%10/1.0F ;//дֵ
	}

	cout << "ԭ����B��" << endl;
	for (auto i : range(0, B.rows))//��ʾ
	{
		float *ptr = B.ptr<float>(i);
		for (auto j : range(0, B.cols))
			cout<<setw(6)<<ptr[j];//������ʾλ�ÿ��
		cout << endl;
	}

	cout << endl;
	//������Ƭ
	Mat C_temp = B(Rect(2,1,3,5));//��2�У���0��ʼ������1�У���0��ʼ��,�г���3��5��
	Mat C = C_temp.clone();//�������г����ľ��󿽱�������һ�������Ͼ�����ԭ�����һ���֣���clone֮��ľ�����һ��ȫ�µľ���
	cout << "����C(B�ĵ�2�е�3�п�ʼ������5�У�����3��)��" << endl;
	for (auto i : range(0, C.rows))
	{
		for (auto j : range(0, C.cols))
			cout << setw(8) << C.at<float>(i, j);
		cout << endl;
	}
	cout << endl;

	Mat D;//����һ���¾���D
	B(Rect(3, 2, 5, 5)).copyTo(D);//���г����ľ��󿽱���D����
	cout << "����D(B�ĵ����е����п�ʼ������5�У�����5��)��" << endl;
	for (auto i : range(0, D.rows))
	{
		for (auto j : range(0, D.cols))
			cout << setw(8) << D.at<float>(i, j);
		cout << endl;
	}
	cout << endl;

	Mat F = B(Rect(5, 1, 5, 5)).clone();//����һ������
	cout << "����F(B�ĵ�2�е�6�п�ʼ������5�У�����5��)��" << endl;
	for (auto i : range(0, F.rows))
	{
		for (auto j : range(0, F.cols))
			cout << setw(8) << F.at<float>(i, j);
		cout << endl;
	}
	cout << endl;

	//����ӷ�
	Mat sum_matrix = D + F;
	cout << "����D+����F��" << endl;
	for (auto i : range(0, sum_matrix.rows))
	{
		for (auto j : range(0, sum_matrix.cols))
			cout << setw(8) << sum_matrix.at<float>(i, j);
		cout << endl;
	}
	cout << endl;

	//����ӷ�
	Mat sub_matrix = D - F;
	cout << "����D-����F��" << endl;
	for (auto i : range(0, sub_matrix.rows))
	{
		for (auto j : range(0, sub_matrix.cols))
			cout << setw(8) << sub_matrix.at<float>(i, j);
		cout << endl;
	}
	cout << endl;

	//������
	Mat dot_matrix = D.mul(F);
	cout << "����D��˾���F��" << endl;
	for (auto i : range(0, dot_matrix.rows))
	{
		for (auto j : range(0, dot_matrix.cols))
			cout << setw(8) << dot_matrix.at<float>(i, j);
		cout << endl;
	}
	cout << endl;

	//����˷�(�˷�����Ҫ����������ͬΪfloat����ͬΪdouble����������)
	Mat product_matrix = D*F;
	cout << "����D��˾���F������˷�����" << endl;
	for (auto i : range(0, product_matrix.rows))
	{
		for (auto j : range(0, product_matrix.cols))
			cout << setw(8) << product_matrix.at<float>(i, j);
		cout << endl;
	}
	cout << endl;

	//���󱶳�
	Mat mul_mat = trans_matrix(D);
	cout << "����D��2����" << endl;
	for (auto i : range(0, mul_mat.rows))
	{
		for (auto j : range(0, mul_mat.cols))
			cout << setw(8) << mul_mat.at<float>(i, j);
		cout << endl;
	}
	cout << endl;

	//��������
	Mat invert_matrix;
	invert(D, invert_matrix);
	cout << "����D���棺" << endl;
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