#include"random.h"
Random::Random(uint max, uint num)//构造函数，用于构造对象并初始化对象
{
	_randomMax = max;
	_randomNum = num;
}

//产生随机数函数
void Random::generate(int* p)//p指向存储随机数的数组，随机数小于Maxnum，个数Numcount
{
	int i(0), j;// m(0);//计算个数,j：用来遍历之前的值     m用来while总共循环的次数（此值调试时使用）
	srand((unsigned int)time(0));//产生随机数种子
	while (1)
	{
		*(p + i) = rand() % _randomMax;//产生随机数，放入列表的最后一个位置
		for (j = 0; j < i; j++)
		{
			if (*(p + i) == *(p + j))//从第一个值开始进行比较，如果出现相等的值则退出for循环
				break;
		}
		if (j == i)//如果j==i说明上述for循环中没有遇到相等的值，则i+1，否则i不加，继续产生一个随机数值，写入i索引中，接着进行比较
			i++;
		//m++;
		if (i == _randomNum)//个数到了以后退出循环
		{
			//cout << m << endl;
			break;
		}
	}
}

//排序，raise：升序，fall：降序
void Random::sort(int *p, char *pmode)
{
	int temp;//交换变量时作为中间变量
	for (int i(0); i < _randomNum; i++);

}
