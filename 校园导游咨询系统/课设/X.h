#include<iostream>
using namespace std;
class X
{
	friend class Y;
private:
	int x;
	static int y;
public:
	void set(int i)
	{
		x = i;
	}
	void display()
	{
		cout << x << "   "<<y << endl;
	}
};
int X::y = 10;
class Y
{
private:
	X a;
public:
	Y(int, int);
	void Display();
};