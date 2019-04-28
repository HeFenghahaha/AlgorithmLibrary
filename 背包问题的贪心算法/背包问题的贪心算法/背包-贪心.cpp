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
	puts("\n��������Ʒ���ռ�ֵ�����ı�ֵ�Ӹߵ�������Ϊ:");
	printf("��Ʒ\t\t����\t\t��ֵ\t\t��ֵ������\n");
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
	printf("\n����Ʒ��װ���������:\n");
	printf("(1��ʾ��ȫװ�룬0��ʾ��ȫ��װ�룬0��1֮���ʾװ�벿��ռ��Ʒ�����ı���)\n");
	printf("��Ʒ\t\t����\t\t��ֵ\t\tװ�����\n");
	for(int i=0;i<n;i++)
		printf("%2d\t\t%.2f\t\t%.2f\t\t%.2f\n",i+1,its[i].w,its[i].v,x[i]);
	printf("\n�ܼ�ֵΪ:%.2f\n",total);
}
int main()
{
	int n;
	float x[N];
	float c;
	cout<<"��������Ʒ����:";
	cin>>n;
	cout<<"�����뱳������:";
	cin>>c;
	cout<<"���������Ʒ�������ͼ�ֵ:"<<endl;
	for(int i=0;i<n;i++)
		cin>>item[i].w>>item[i].v;
	knapsack(item,x,c,n);
	return 0;
}
