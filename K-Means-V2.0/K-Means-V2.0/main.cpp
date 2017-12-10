#include<iostream>
#include<fstream>
#include<typeinfo>
#include<ctime>
#include<cmath>
#include"./Random/random.h"
using namespace std;
const int K = 3;//定义类数
const int iterationNum = 100;//迭代次数

/*******求最值，并返回索引*********/
//p:一维数组名
//size:数组长度
//max:执行此函数以后更新为数组的最大值，manindex，最大值的索引
//min同上，只不是是最小值
void mostValue(float *p, int size, float &max, int &maxindex, float &min, int &minindex)
{
	max = *p; min = *p;//最大值和最小值都初始化为数组的第一个值
	for (int i(0); i < size; i++)//进行数组遍历
	{
		if (max < *(p + i))//如果当前max中的值小于要比较的值，则把此值给max
		{
			max = *(p + i);
			maxindex = i;
		}
		if (min > *(p + i))//如果当前min中的值大于要比较的值，则把此值给min
		{
			min = *(p + i);
			minindex = i;
		}
	}
}

/*******kmeans算法********/
//*pdata:进行聚类的数组名     
//k:要分类的个数
//dataRow:数组中样本点的个数  行数 
//dataColumn:每个样本的属性个数 列数
void kmeans(float **pdata, const int k, int dataRow, int dataColumn)
{
	float center[3][2] = { 0 };//定义聚类中心，放置中心位置
	float distance[1500][3] = { 0 };//放置每个样本离中心点的距离，每行的值为当前样本点离三个中心的距离，总共1500行
	int cenindex[K] = { 104,768,1356 };//定义全局数组，存放聚类中心
	float maxN[2] = { 0 }, minN[2] = {0};//
	int maxindex[2] = { 0 }, minindex[2] = { 0 };
	int classflag[1500] = {0};//定义类标识，ABC
	float tempf[3][2] = { 0 };//更新中心时，用来暂时存储数据值,3:三类，2：两个属性
	int tempi[3] = { 0 };//更新中心时，用来暂时存储数据个数
	int iteration = 100,itreTemp(1);//迭代次数

	//随机的生成0-1500内的中心
	Random myrandom1(1500, k);//产生随机数，从而初始化迭代中心，在0-1500）中间随机挑选K个数，K:聚类中心的个数
	//myrandom1.generate(cenindex);
	//0-500、500-1000、1000-1500各一个中心（原数据就是这样分布的）
	Random myrandom2(500, k);
	myrandom2.generate(cenindex);
	cenindex[1] += 500;
	cenindex[2] += 1000;



	//数据归一化处理：(当前值-最小值)/(最大值减去最小值)
	for (int i(0); i < 1500; i++)
	{
		if (maxN[0] < *((float*)pdata + i * 2 + 0))//如果当前max中的值小于要比较的值，则把此值给max
		{
			maxN[0] = *((float*)pdata + i * 2 + 0);
			maxindex[0] = i;
		}
		if (minN[0] > *((float*)pdata + i * 2 + 0))//如果当前min中的值大于要比较的值，则把此值给min
		{
			minN[0] = *((float*)pdata + i * 2 + 0);
			minindex[0] = i;
		}

		if (maxN[1] < *((float*)pdata + i * 2 + 1))//如果当前max中的值小于要比较的值，则把此值给max
		{
			maxN[1] = *((float*)pdata + i * 2 + 1);
			maxindex[1] = i;
		}
		if (minN[1] > *((float*)pdata + i * 2 + 1))//如果当前min中的值大于要比较的值，则把此值给min
		{
			minN[1] = *((float*)pdata + i * 2 + 1);
			minindex[1] = i;
		}
	}
	cout << "第一列最值" << maxN[0] << '\t' << minN[0] << endl;
	cout << "第二列最值" << maxN[1] << '\t' << minN[1] << endl;
	for (int i(0); i < 1500; i++)
	{
		*((float*)pdata + i * 2 + 0) = (*((float*)pdata + i * 2 + 0) - minN[0]) / (maxN[0] - minN[0]);
		*((float*)pdata + i * 2 + 1) = (*((float*)pdata + i * 2 + 1) - minN[1]) / (maxN[1] - minN[1]);
	}

	//将随机选择的聚类中心放入定义的数组中
	for (int i(0); i < k; i++)//输出选择的初始化中心
	{
		//cout << "第" << cenindex[i] +1<<"个值："<<* ((float*)pdata + cenindex[i] * i + 0) << '\t' << *((float*)pdata + cenindex[i] * i + 1) << '\t';
		//cout << endl;
		center[i][0] = *((float*)pdata + cenindex[i] * 2 + 0);//将选出来的聚类中心放入定义的聚类中心数组中，方便引用
		center[i][1] = *((float*)pdata + cenindex[i] * 2 + 1);
	}
	cout << endl;

	//调试输出聚类中心
	for (int i(0); i < k; i++)//输出选择的初始化中心
	{
		cout << "第" << cenindex[i] + 1 << "个值：" << center[i][0] << '\t' << center[i][1] << '\t';
		cout << endl;
	}
	cout << endl;
	while (iteration)
	{
	
		//计算每个样本点离聚类中心得距离
		for (int i(0); i < 1500; i++)
		{
			distance[i][0] = sqrt(pow((*((float*)pdata + i * 2 + 0) - center[0][0]), 2) + pow((*((float*)pdata + i * 2 + 1) - center[0][1]), 2));
			distance[i][1] = sqrt(pow((*((float*)pdata + i * 2 + 0) - center[1][0]), 2) + pow((*((float*)pdata + i * 2 + 1) - center[1][1]), 2));
			distance[i][2] = sqrt(pow((*((float*)pdata + i * 2 + 0) - center[2][0]), 2) + pow((*((float*)pdata + i * 2 + 1) - center[2][1]), 2));
			//cout << distance[i][0] << '\t' << distance[i][1] << '\t' << distance[i][2] << '\t' << endl;
		}

		//选择三个距离中的最大值
		for (int i(0); i < 1500; i++)
		{
			if (distance[i][0]<=distance[i][1] && distance[i][0] <= distance[i][2])
				classflag[i] = 1;
			if (distance[i][1] <= distance[i][0] && distance[i][1] <= distance[i][2])
				classflag[i] = 2;
			if (distance[2][0] <= distance[i][0] && distance[i][2] <= distance[i][1])
				classflag[i] = 3;
	
		}
		//调试输出：距离和类别
		/*for (int i(0); i < 1500; i++)
		{
			cout << distance[i][0] << '\t' << distance[i][1] << '\t' << distance[i][2] << '\t' << classflag[i] << endl;
		}*/

		//统计每个类的个数，更新聚类中心
		for (int i(0); i < 1500; i++)
		{
			switch (classflag[i])
			{
			case 1://类别为A时，求各属性的平均值，
				tempf[0][0] += *((float*)pdata + i * 2 + 0);
				tempf[0][1] += *((float*)pdata + i * 2 + 1);
				tempi[0]++;
				break;
			case 2://类别为A时，求各属性的平均值，
				tempf[1][0] += *((float*)pdata + i * 2 + 0);
				tempf[1][1] += *((float*)pdata + i * 2 + 1);
				tempi[1]++;
				break;
			case 3://类别为A时，求各属性的平均值，
				tempf[2][0] += *((float*)pdata + i * 2 + 0);
				tempf[2][1] += *((float*)pdata + i * 2 + 1);
				tempi[2]++;
				break;
			default:break;
			}
		}
		//更新中心
		for (int i(0); i < k; i++)//输出选择的初始化中心
		{
			//cout << "第" << cenindex[i] +1<<"个值："<<* ((float*)pdata + cenindex[i] * i + 0) << '\t' << *((float*)pdata + cenindex[i] * i + 1) << '\t';
			//cout << endl;
			center[i][0] = tempf[i][0]/tempi[i];//将选出来的聚类中心放入定义的聚类中心数组中，方便引用
			center[i][1] = tempf[i][1] / tempi[i];
		}
		cout << "第" << itreTemp << "次迭代" << endl;
		cout << "1类的个数：" << center[0][0] << ',' << center[0][1] <<'\t'<< tempi[0] << endl;
		cout << "2类的个数：" << center[1][0] << ',' << center[1][1] << '\t' << tempi[1] << endl;
		cout << "3类的个数：" << center[2][0] << ',' << center[2][1] << '\t' << tempi[2] << endl;
		cout << endl;
		iteration--;
		itreTemp++;
		for (int i(0); i < 3; i++)
		{
			tempf[i][0] = 0;//重置参数
			tempf[i][1] = 0;//重置参数
			tempi[i] = 0;//重置参数
		}
		
		
	}
}


int main()
{
	/*******读取数据函数**********/
	float data[1500][2] = { 0 };//用于保存从外部读到的高斯数据
	//int cenindex[K] = { 0 };//存放数据中心的索引，初次初始化为随机数
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



