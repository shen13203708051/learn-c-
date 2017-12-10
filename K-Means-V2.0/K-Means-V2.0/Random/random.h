#include<iostream>
#include<ctime>
typedef unsigned int uint;
class Random{//定义产生随机数的类
private://私有变量
	uint _randomMax, _randomNum;//randomMax:随机数的最大值     randomNum：随机数的个数
public:
	Random(uint max,uint num);//构造函数，初始化randomMax和randomNum两个私有变量
	~Random(){}//析构函数，销毁对象，暂时没有申请动态内存，所以此函数内容暂时为空
	void generate(int *p);//产生初始化时要求（小于_randomMax，个数为_randomNum）的随机数，*p为调用程序中存放此随机数组（一维）的数组名
	
	//排序算法暂时不写
	void sort(int *p,char *pmode);//排序，*p要排序的数组名字，*pmode：选择升序还是降序，raise:升序  fall：降序
};