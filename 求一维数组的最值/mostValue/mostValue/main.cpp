#include<iostream>
using namespace std;

void mostValue(float *p, int size, float &max, int &maxindex, float &min, int &minindex)
{
	max = *p; min = *p;//最大值和最小值都初始化为数组的第一个值
	maxindex = 0; minindex = 0;
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

void mostValue(int *p, int size, int &max, int &maxindex, int &min, int &minindex)
{
	max = *p; min = *p;//最大值和最小值都初始化为数组的第一个值
	maxindex = 0; minindex = 0;
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

int main()
{
	float a[5] = { 0.26, 0.25, 0.52, 0.41, 0.36 };
	int b[5] = { 5, 6, 8, 9, 2 };
	float maxa, mina;
	int maxb, minb;
	int maxind, minind;
	mostValue(a, 5, maxa, maxind, mina, minind);//调用方式
	cout << maxa << '\t' << maxind << '\t' << mina << '\t' << minind << endl;
	mostValue(b, 5, maxb, maxind, minb, minind);
	cout << maxb << '\t' << maxind << '\t' << minb << '\t' << minind << endl;
	system("pause");
	return 0;
}