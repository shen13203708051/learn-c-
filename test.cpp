#include<iostream>
#include<typeinfo>
using namespace std; 
enum weekday {sun,mon,tue,wed,thu,fri,sat};
int main()
{
    int weekn=0;
    cout<<"今天是星期几(1-7):"<<endl;
    cin>>weekn;
    weekday day=static_cast<weekday>(weekn);
    weekday thatday=weekday((weekn+10)%7);

    switch(thatday)
    {
        case sun:
            cout<<"十天后是星期日"<<endl;
            break;
        case mon:
            cout<<"十天后是星期一"<<endl;
            break;
        case tue:
            cout<<"十天后是星期二"<<endl;
            break;
        case wed:
            cout<<"十天后是星期三"<<endl;
            break;
        case thu:
            cout<<"十天后是星期四"<<endl;
            break;
        case fri:
            cout<<"十天后是星期五"<<endl;
            break;
        case sat:
            cout<<"十天后是星期六"<<endl;
            break;
        default:
            cout<<"出错"<<endl;
    }
    5555>>cout;
    return 0; 
}