#include<iostream>
#include<graphics.h>
using namespace std;
const int N=100;
void Knapsack(int v[],int w[],int c,int n,int m[N][101])
{
	int jmax=min(w[n-1]-1,c);
	for(int j=0;j<=jmax;j++)
		m[n][j]=0;
	for(int j=w[n-1];j<=c;j++)
		m[n][j]=v[n-1];
	for(int i=n-1;i>=1;i--)
	{
		jmax=min(w[i-1]-1,c);
		for(int j=0;j<=jmax;j++)
			m[i][j]=m[i+1][j];
		for(int j=w[i-1];j<=c;j++)
			m[i][j]=max(m[i+1][j],m[i+1][j-w[i-1]]+v[i-1]);
	}
	m[1][c]=m[2][c];
	if(c>=w[0]) m[1][c]=max(m[1][c],m[2][c-w[0]]+v[0]);
	cout<<endl<<"构成的m数组为:"<<endl;
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<=c;j++)
			printf("%3d   ",m[i][j]);
		printf("\n");
	}
	printf("\n");	
}
void traceback(int m[N][101],int w[],int c,int n,int x[])
{
	for(int i=1;i<n;i++)
		if(m[i][c]==m[i+1][c]) 
		{
			x[i]=0;
			printf("因为%d等于%d，所以第%d个物品没有放进背包\n",m[i][c],m[i+1][c],i);
		}
		else
			{
				x[i]=1;
				printf("因为%d不等于%d，所以第%d个物品放进了背包\n",m[i][c],m[i+1][c],i);
				c=c-w[i-1];
			}
	x[n]=(m[n][c])?1:0;
	if(m[n][c])
		printf("因为%d不等于0，所以第%d个物品放进了背包\n",m[n][c],n);
	else
		printf("因为%d等于0，所以第%d个物品没有放进背包\n",m[n][c],n);
}
void show(int n,int c,int m[N][101],int w[N])
{
	initgraph(640,480,SHOWCONSOLE);
	setbkcolor(WHITE);
	cleardevice();

	settextcolor(BLACK);
	int x=10,y=40;
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<=c;j++)
		{
			TCHAR s[5];
			_stprintf(s, _T("%d"), m[i][j]);        
			outtextxy(x, y, s);
			x+=40;
		}
		x=10;
		y+=30;
	}
	setlinecolor(BLACK);
	x=10;
	y-=60;
	for(int i=n-1;i>=1;i--)
	{
		for(int j=0;j<=c;j++)
		{
			if(m[i][j]==m[i+1][j])//把m[i][j]和m[i+1][j]连起来
			{
				line(x+5,y+10,x+5,y+30);Sleep(800);
			}
			else//把m[i][j]和m[i+1][j-w[i-1]]连起来
			{
				line(x+5,y+10,x-40*w[i-1]+5,y+30);Sleep(800);
			}
			x+=40;
		}
		x=10;
		y-=30;
	}
	system("pause");
}
int main()
{
	int n,c,w[N],v[N];
	int m[N][101];
	int x[N];
	cout<<"请输入物品个数n:";
	cin>>n;
	cout<<"请输入背包容量c:";
	cin>>c;
	cout<<"请输入各物品的重量:";
	for(int i=0;i<n;i++)
		cin>>w[i];
	cout<<"请输入各物品的价值:";
	for(int i=0;i<n;i++)
		cin>>v[i];
	Knapsack(v,w,c,n,m);
	traceback(m,w,c,n,x);
	printf("\n1表示该物品放进去了，0表示该物品没放进去,所有物品的放入情况为:\n\n");	
	puts("物品\t\t重量\t\t价值\t\t放入背包情况");
	for(int i=0;i<n;i++)
		printf("%3d\t\t%3d\t\t%3d\t\t%3d\n",i+1,w[i],v[i],x[i+1]);
	printf("\n价值总和为:%d\n",m[1][c]);
	show(n,c,m,w);
	return 0;
}