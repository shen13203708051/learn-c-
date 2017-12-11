#include"read.h"

/******fcm聚类********/
//filename:数据文件的路径（最好是绝对路径），windows下使用‘/’
//N：样本点个数，数据的行数
//d：属性的个数（维度）,数据的列数
void read(char filename[],int N,int d)
{
	/*****************申请二维内存存放数据*****************/
	//先申请指针行变量，指向每一行的行首
	float** data = new float*[N];//申请每一行的指针，N个，指向每一行，
	for (int i(0); i < N; i++)
		data[i] = new float[d];//然后为每行的指针申请维数（有多少列就申请多少个内存）

	/*****************读取数据文件*****************************/
	//float data[1500][2] = { 0 };
	ifstream infile;
	infile.open(filename);
	for (int i = 0; i < N; i++)
	{
		for (int j(0); j < d; j++)
			infile >> data[i][j];//数组寻址实的用法，可直接使用指针加中括号的方式引用元素
	}
	infile.close();//一定记得关闭文件
	cout << data[0][0] << endl;
	cout << data[1499][0] << endl;

	/******************销毁申请的内存**************/
	for (int i(0); i < N; i++)
		delete[]data[i];
	delete[]data;
}