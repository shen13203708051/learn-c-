#include<iostream>
#include<fstream>
using namespace std;

/******fcm聚类********/
//filename:数据文件的路径（最好是绝对路径），windows下使用‘/’
//N：样本点个数，数据的行数
//d：属性的个数（维度）,数据的列数
void read(char filename[], int N, int d);