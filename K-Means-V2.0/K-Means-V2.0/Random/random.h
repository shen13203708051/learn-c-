#include<iostream>
#include<ctime>
typedef unsigned int uint;
class Random{//����������������
private://˽�б���
	uint _randomMax, _randomNum;//randomMax:����������ֵ     randomNum��������ĸ���
public:
	Random(uint max,uint num);//���캯������ʼ��randomMax��randomNum����˽�б���
	~Random(){}//�������������ٶ�����ʱû�����붯̬�ڴ棬���Դ˺���������ʱΪ��
	void generate(int *p);//������ʼ��ʱҪ��С��_randomMax������Ϊ_randomNum�����������*pΪ���ó����д�Ŵ�������飨һά����������
	
	//�����㷨��ʱ��д
	void sort(int *p,char *pmode);//����*pҪ������������֣�*pmode��ѡ�������ǽ���raise:����  fall������
};