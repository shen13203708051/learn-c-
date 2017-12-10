#include<iostream>
#include<fstream>
#include<typeinfo>
#include<ctime>
#include<cmath>
#include"./Random/random.h"
using namespace std;
const int K = 3;//��������
const int iterationNum = 100;//��������

/*******����ֵ������������*********/
//p:һά������
//size:���鳤��
//max:ִ�д˺����Ժ����Ϊ��������ֵ��manindex�����ֵ������
//minͬ�ϣ�ֻ��������Сֵ
void mostValue(float *p, int size, float &max, int &maxindex, float &min, int &minindex)
{
	max = *p; min = *p;//���ֵ����Сֵ����ʼ��Ϊ����ĵ�һ��ֵ
	for (int i(0); i < size; i++)//�����������
	{
		if (max < *(p + i))//�����ǰmax�е�ֵС��Ҫ�Ƚϵ�ֵ����Ѵ�ֵ��max
		{
			max = *(p + i);
			maxindex = i;
		}
		if (min > *(p + i))//�����ǰmin�е�ֵ����Ҫ�Ƚϵ�ֵ����Ѵ�ֵ��min
		{
			min = *(p + i);
			minindex = i;
		}
	}
}

/*******kmeans�㷨********/
//*pdata:���о����������     
//k:Ҫ����ĸ���
//dataRow:������������ĸ���  ���� 
//dataColumn:ÿ�����������Ը��� ����
void kmeans(float **pdata, const int k, int dataRow, int dataColumn)
{
	float center[3][2] = { 0 };//����������ģ���������λ��
	float distance[1500][3] = { 0 };//����ÿ�����������ĵ�ľ��룬ÿ�е�ֵΪ��ǰ���������������ĵľ��룬�ܹ�1500��
	int cenindex[K] = { 104,768,1356 };//����ȫ�����飬��ž�������
	float maxN[2] = { 0 }, minN[2] = {0};//
	int maxindex[2] = { 0 }, minindex[2] = { 0 };
	int classflag[1500] = {0};//�������ʶ��ABC
	float tempf[3][2] = { 0 };//��������ʱ��������ʱ�洢����ֵ,3:���࣬2����������
	int tempi[3] = { 0 };//��������ʱ��������ʱ�洢���ݸ���
	int iteration = 100,itreTemp(1);//��������

	//���������0-1500�ڵ�����
	Random myrandom1(1500, k);//������������Ӷ���ʼ���������ģ���0-1500���м������ѡK������K:�������ĵĸ���
	//myrandom1.generate(cenindex);
	//0-500��500-1000��1000-1500��һ�����ģ�ԭ���ݾ��������ֲ��ģ�
	Random myrandom2(500, k);
	myrandom2.generate(cenindex);
	cenindex[1] += 500;
	cenindex[2] += 1000;



	//���ݹ�һ������(��ǰֵ-��Сֵ)/(���ֵ��ȥ��Сֵ)
	for (int i(0); i < 1500; i++)
	{
		if (maxN[0] < *((float*)pdata + i * 2 + 0))//�����ǰmax�е�ֵС��Ҫ�Ƚϵ�ֵ����Ѵ�ֵ��max
		{
			maxN[0] = *((float*)pdata + i * 2 + 0);
			maxindex[0] = i;
		}
		if (minN[0] > *((float*)pdata + i * 2 + 0))//�����ǰmin�е�ֵ����Ҫ�Ƚϵ�ֵ����Ѵ�ֵ��min
		{
			minN[0] = *((float*)pdata + i * 2 + 0);
			minindex[0] = i;
		}

		if (maxN[1] < *((float*)pdata + i * 2 + 1))//�����ǰmax�е�ֵС��Ҫ�Ƚϵ�ֵ����Ѵ�ֵ��max
		{
			maxN[1] = *((float*)pdata + i * 2 + 1);
			maxindex[1] = i;
		}
		if (minN[1] > *((float*)pdata + i * 2 + 1))//�����ǰmin�е�ֵ����Ҫ�Ƚϵ�ֵ����Ѵ�ֵ��min
		{
			minN[1] = *((float*)pdata + i * 2 + 1);
			minindex[1] = i;
		}
	}
	cout << "��һ����ֵ" << maxN[0] << '\t' << minN[0] << endl;
	cout << "�ڶ�����ֵ" << maxN[1] << '\t' << minN[1] << endl;
	for (int i(0); i < 1500; i++)
	{
		*((float*)pdata + i * 2 + 0) = (*((float*)pdata + i * 2 + 0) - minN[0]) / (maxN[0] - minN[0]);
		*((float*)pdata + i * 2 + 1) = (*((float*)pdata + i * 2 + 1) - minN[1]) / (maxN[1] - minN[1]);
	}

	//�����ѡ��ľ������ķ��붨���������
	for (int i(0); i < k; i++)//���ѡ��ĳ�ʼ������
	{
		//cout << "��" << cenindex[i] +1<<"��ֵ��"<<* ((float*)pdata + cenindex[i] * i + 0) << '\t' << *((float*)pdata + cenindex[i] * i + 1) << '\t';
		//cout << endl;
		center[i][0] = *((float*)pdata + cenindex[i] * 2 + 0);//��ѡ�����ľ������ķ��붨��ľ������������У���������
		center[i][1] = *((float*)pdata + cenindex[i] * 2 + 1);
	}
	cout << endl;

	//���������������
	for (int i(0); i < k; i++)//���ѡ��ĳ�ʼ������
	{
		cout << "��" << cenindex[i] + 1 << "��ֵ��" << center[i][0] << '\t' << center[i][1] << '\t';
		cout << endl;
	}
	cout << endl;
	while (iteration)
	{
	
		//����ÿ����������������ĵþ���
		for (int i(0); i < 1500; i++)
		{
			distance[i][0] = sqrt(pow((*((float*)pdata + i * 2 + 0) - center[0][0]), 2) + pow((*((float*)pdata + i * 2 + 1) - center[0][1]), 2));
			distance[i][1] = sqrt(pow((*((float*)pdata + i * 2 + 0) - center[1][0]), 2) + pow((*((float*)pdata + i * 2 + 1) - center[1][1]), 2));
			distance[i][2] = sqrt(pow((*((float*)pdata + i * 2 + 0) - center[2][0]), 2) + pow((*((float*)pdata + i * 2 + 1) - center[2][1]), 2));
			//cout << distance[i][0] << '\t' << distance[i][1] << '\t' << distance[i][2] << '\t' << endl;
		}

		//ѡ�����������е����ֵ
		for (int i(0); i < 1500; i++)
		{
			if (distance[i][0]<=distance[i][1] && distance[i][0] <= distance[i][2])
				classflag[i] = 1;
			if (distance[i][1] <= distance[i][0] && distance[i][1] <= distance[i][2])
				classflag[i] = 2;
			if (distance[2][0] <= distance[i][0] && distance[i][2] <= distance[i][1])
				classflag[i] = 3;
	
		}
		//�����������������
		/*for (int i(0); i < 1500; i++)
		{
			cout << distance[i][0] << '\t' << distance[i][1] << '\t' << distance[i][2] << '\t' << classflag[i] << endl;
		}*/

		//ͳ��ÿ����ĸ��������¾�������
		for (int i(0); i < 1500; i++)
		{
			switch (classflag[i])
			{
			case 1://���ΪAʱ��������Ե�ƽ��ֵ��
				tempf[0][0] += *((float*)pdata + i * 2 + 0);
				tempf[0][1] += *((float*)pdata + i * 2 + 1);
				tempi[0]++;
				break;
			case 2://���ΪAʱ��������Ե�ƽ��ֵ��
				tempf[1][0] += *((float*)pdata + i * 2 + 0);
				tempf[1][1] += *((float*)pdata + i * 2 + 1);
				tempi[1]++;
				break;
			case 3://���ΪAʱ��������Ե�ƽ��ֵ��
				tempf[2][0] += *((float*)pdata + i * 2 + 0);
				tempf[2][1] += *((float*)pdata + i * 2 + 1);
				tempi[2]++;
				break;
			default:break;
			}
		}
		//��������
		for (int i(0); i < k; i++)//���ѡ��ĳ�ʼ������
		{
			//cout << "��" << cenindex[i] +1<<"��ֵ��"<<* ((float*)pdata + cenindex[i] * i + 0) << '\t' << *((float*)pdata + cenindex[i] * i + 1) << '\t';
			//cout << endl;
			center[i][0] = tempf[i][0]/tempi[i];//��ѡ�����ľ������ķ��붨��ľ������������У���������
			center[i][1] = tempf[i][1] / tempi[i];
		}
		cout << "��" << itreTemp << "�ε���" << endl;
		cout << "1��ĸ�����" << center[0][0] << ',' << center[0][1] <<'\t'<< tempi[0] << endl;
		cout << "2��ĸ�����" << center[1][0] << ',' << center[1][1] << '\t' << tempi[1] << endl;
		cout << "3��ĸ�����" << center[2][0] << ',' << center[2][1] << '\t' << tempi[2] << endl;
		cout << endl;
		iteration--;
		itreTemp++;
		for (int i(0); i < 3; i++)
		{
			tempf[i][0] = 0;//���ò���
			tempf[i][1] = 0;//���ò���
			tempi[i] = 0;//���ò���
		}
		
		
	}
}


int main()
{
	/*******��ȡ���ݺ���**********/
	float data[1500][2] = { 0 };//���ڱ�����ⲿ�����ĸ�˹����
	//int cenindex[K] = { 0 };//����������ĵ����������γ�ʼ��Ϊ�����
	ifstream infile;
	infile.open("data.txt");
	for (int i = 0; i < 1500; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			infile >> data[i][j];
		}
	}
	infile.close();

	kmeans((float**)data, K, 1500,2);
	cout << endl;
	system("pause");
	return 0;
}



