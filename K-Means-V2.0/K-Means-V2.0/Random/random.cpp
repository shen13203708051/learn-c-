#include"random.h"
Random::Random(uint max, uint num)//���캯�������ڹ�����󲢳�ʼ������
{
	_randomMax = max;
	_randomNum = num;
}

//�������������
void Random::generate(int* p)//pָ��洢����������飬�����С��Maxnum������Numcount
{
	int i(0), j;// m(0);//�������,j����������֮ǰ��ֵ     m����while�ܹ�ѭ���Ĵ�������ֵ����ʱʹ�ã�
	srand((unsigned int)time(0));//�������������
	while (1)
	{
		*(p + i) = rand() % _randomMax;//����������������б�����һ��λ��
		for (j = 0; j < i; j++)
		{
			if (*(p + i) == *(p + j))//�ӵ�һ��ֵ��ʼ���бȽϣ����������ȵ�ֵ���˳�forѭ��
				break;
		}
		if (j == i)//���j==i˵������forѭ����û��������ȵ�ֵ����i+1������i���ӣ���������һ�������ֵ��д��i�����У����Ž��бȽ�
			i++;
		//m++;
		if (i == _randomNum)//���������Ժ��˳�ѭ��
		{
			//cout << m << endl;
			break;
		}
	}
}

//����raise������fall������
void Random::sort(int *p, char *pmode)
{
	int temp;//��������ʱ��Ϊ�м����
	for (int i(0); i < _randomNum; i++);

}
