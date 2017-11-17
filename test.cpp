#include<iostream>
#include<typeinfo>
//#include<string>
#include<cstring>
using namespace std; 
struct person
{
    int num;
    char name[20];
    char sex;
    char job;
    union
    {
        int classes;
        char position[10];
    };
};
int main()
{
    int i;
    person p[2];
    char temp[10];
    for(i=0;i<2;i++)
    {
        cin>>p[i].num>>p[i].name>>p[i].sex>>p[i].job;
        if(p[i].job=='s')
            {
                cin>>p[i].classes;
            }
        else
            {
                cin>>p[i].position;
            }
    }
    for(i=0;i<2;i++)
    {
        if(p[i].job=='s')
            cout<<p[i].name<<" is a student of class "<<p[i].classes<<endl;
        else
            cout<<p[i].name<<" is a teacher, he is a  "<<p[i].position<<endl;
    }
    return 0; 
}