#include"read.h"

/******fcm����********/
//filename:�����ļ���·��������Ǿ���·������windows��ʹ�á�/��
//N����������������ݵ�����
//d�����Եĸ�����ά�ȣ�,���ݵ�����
void read(char filename[],int N,int d)
{
	/*****************�����ά�ڴ�������*****************/
	//������ָ���б�����ָ��ÿһ�е�����
	float** data = new float*[N];//����ÿһ�е�ָ�룬N����ָ��ÿһ�У�
	for (int i(0); i < N; i++)
		data[i] = new float[d];//Ȼ��Ϊÿ�е�ָ������ά�����ж����о�������ٸ��ڴ棩

	/*****************��ȡ�����ļ�*****************************/
	//float data[1500][2] = { 0 };
	ifstream infile;
	infile.open(filename);
	for (int i = 0; i < N; i++)
	{
		for (int j(0); j < d; j++)
			infile >> data[i][j];//����Ѱַʵ���÷�����ֱ��ʹ��ָ��������ŵķ�ʽ����Ԫ��
	}
	infile.close();//һ���ǵùر��ļ�
	cout << data[0][0] << endl;
	cout << data[1499][0] << endl;

	/******************����������ڴ�**************/
	for (int i(0); i < N; i++)
		delete[]data[i];
	delete[]data;
}