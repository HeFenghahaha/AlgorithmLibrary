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
		cout<<"Ĭ�Ϲ��캯��������"<<endl;
	}
	CC(int m,int d,int y)
	{
		mouth=m;
		day=d;
		year=y;
		cout<<"���캯��������"<<endl;
	}
	~CC()
	{
		cout<<"��������������"<<day<<endl;
	}
	void print()
	{
		cout<<mouth<<","<<day<<","<<year<<endl;
	}
};