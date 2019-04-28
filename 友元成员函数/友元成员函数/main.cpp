#include"Time.h"
Time::Time(int h,int m,int s)
{
	hour=h;minute=m;second=s;
}
void Time::display(Date d)
{
	cout<<d.year<<"."<<d.mounth<<"."<<d.day<<endl;
	cout<<hour<<":"<<minute<<":"<<second<<endl;
}
Date::Date(int y,int m,int d)
{
	year=y;mounth=m;day=d;
}
int main()
{
	Time t1(11,48,20);
	Date d1(2019,4,19);
	t1.display(d1);
	return 0;
}