#include<iostream>
using namespace std;
class CC
{
private:
	int mouth,day,year;
public:
	CC()
	{
		mouth=day=year=0;
		cout<<"默认构造函数被调用"<<endl;
	}
	CC(int m,int d,int y)
	{
		mouth=m;
		day=d;
		year=y;
		cout<<"构造函数被调用"<<endl;
	}
	~CC()
	{
		cout<<"析构函数被调用"<<day<<endl;
	}
	void print()
	{
		cout<<mouth<<","<<day<<","<<year<<endl;
	}
};