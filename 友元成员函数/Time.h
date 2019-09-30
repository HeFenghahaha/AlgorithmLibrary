#include<iostream>
using namespace std;
class Date;
class Time
{
private:
	int hour,minute,second;
public:
	Time(int,int,int);
	void display(Date);
};
class Date
{
private:
	int year,mounth,day;
public:
	Date(int,int,int);
	friend void Time::display(Date);
};