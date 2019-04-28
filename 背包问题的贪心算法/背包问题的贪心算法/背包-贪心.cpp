#include<iostream>
#include<algorithm>
using namespace std;
const int N=100;
class Items
{
public:
	float w,v;
};
Items item[N];
bool cmp(Items p1,Items p2)
{
	return p1.v/p1.w>p2.v/p2.w;
}
void knapsack(Items its[],float x[],float c,int n)
{
	sort(its,its+n,cmp);
	puts("\n将所有物品按照价值重量的比值从高到低排列为:");
	printf("物品\t\t重量\t\t价值\t\t价值重量比\n");
	for(int i=0;i<n;i++)
		printf("%2d\t\t%.2f\t\t%.2f\t\t%.2f\n",i+1,its[i].w,its[i].v,its[i].v/its[i].w);
	for(int i=0;i<n;i++)
		x[i]=0;
	int i=0;float total=0;
	while(its[i].w<=c)
	{
		x[i]=1;
		total+=its[i].v;
		c-=its[i].w;
		i++;
	}
	x[i]=c/its[i].w;
	total+=x[i]*its[i].v;
	printf("\n各物品的装入情况如下:\n");
	printf("(1表示完全装入，0表示完全不装入，0到1之间表示装入部分占物品重量的比例)\n");
	printf("物品\t\t重量\t\t价值\t\t装入比例\n");
	for(int i=0;i<n;i++)
		printf("%2d\t\t%.2f\t\t%.2f\t\t%.2f\n",i+1,its[i].w,its[i].v,x[i]);
	printf("\n总价值为:%.2f\n",total);
}
int main()
{
	int n;
	float x[N];
	float c;
	cout<<"请输入物品个数:";
	cin>>n;
	cout<<"请输入背包容量:";
	cin>>c;
	cout<<"请输入各物品的重量和价值:"<<endl;
	for(int i=0;i<n;i++)
		cin>>item[i].w>>item[i].v;
	knapsack(item,x,c,n);
	return 0;
}
