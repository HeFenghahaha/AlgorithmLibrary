#include<iostream>
using namespace std;
const int N=100;
int maxsum(int n,int a[])
{
	int sum=0,b=0;
	for(int i=1;i<=n;i++)
	{
		if(b>0)
			b+=a[i];
		else  
			b=a[i];
		if(b>sum)
			sum=b;
	}
	return sum;
}
int main()
{
	int n;
	int a[N];
	puts("请输入数列个数n:");
	cin>>n;
	printf("请依次输入%d个整数:\n",n);
	for(int i=1;i<=n;i++)
		cin>>a[i];
	cout<<"该序列的最大子段和的值为:"<<maxsum(n,a)<<endl;
	return 0;
}