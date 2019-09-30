#include"X.h"
Y::Y(int i, int j)
{
	a.x = i; X::y = j;
}
void Y::Display()
{
	cout << a.x << "   "<<X::y << endl;
}
int main()
{
	X  b;
	b.set(5);  b.display();
	Y c(3, 6);  c.Display();
	b.display();
	system("pause");
	return 0;
}