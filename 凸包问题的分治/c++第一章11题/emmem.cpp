#include<iostream>
#include<cmath>
#include<algorithm>
#include<graphics.h>
using namespace std;
const int N=100;
void uhull(int,int);   //函数声明
void dhull(int,int);   //函数声明
class Point     //定义类
{
public:
	double x,y;
};
Point p[N],s[N];   //定义对象数组，数组中的每一个元素都是类对象
int n,m=0;
bool cmp (Point q,Point r)  //将p数组按x的值从小到大排序
{
	return q.x<r.x;
}
double judge(Point p1,Point p2,Point p3)  //判断点p3在直线p1和p2的左侧还是右侧
{
	return p1.x*p2.y+p3.x*p1.y+p2.x*p3.y-p3.x*p2.y-p2.x*p1.y-p1.x*p3.y;
}
double dist(Point p1,Point p2,Point p3)   //计算点p3到直线p1p2的距离
{
	return abs((p2.y-p1.y)*p3.x+(p1.x-p2.x)*p3.y+(p1.y-p2.y)*p1.x+(p2.x-p1.x)*p1.y)/sqrt(pow(p2.y-p1.y,2)+pow(p1.x-p2.x,2));
}
void uhull(int x,int y)    //上凸包
{
	int i,j,l,r;
	double dis=-1;
	j=-1;
	if(x<=y)
	{l=x;r=y;}
	else
	{l=y;r=x;}
	for(i=l+1;i<r;i++)
	{
		if(judge(p[x],p[y],p[i])>=0)
			if(dist(p[x],p[y],p[i])>dis)
			{
				dis=dist(p[x],p[y],p[i]);
				j=i;
			}
	}
	if(j==-1)
	{
		s[m++]=p[y];return;
	}
	int uh,dh;
	if(judge(p[x],p[j],p[y])<=0)
	{uh=x;dh=y;}
	else
	{uh=y;dh=x;}
	dhull(dh,j);
	uhull(uh,j);
}
void dhull(int x,int y)   //下凸包
{
	int i,j,l,r;
	double dis=-1;
	j=-1;
	if(x<=y)
	{l=x;r=y;}
	else
	{l=y;r=x;}
	for(i=l+1;i<r;i++)
	{
		if(judge(p[x],p[y],p[i])<=0)
			if(dist(p[x],p[y],p[i])>dis)
			{
				dis=dist(p[x],p[y],p[i]);
				j=i;
			}
	}
	if(j==-1)
	{
		s[m++]=p[x];return ;
	}
	int uh,dh;
	if(judge(p[x],p[j],p[y])<0)
	{uh=x;dh=y;}
	else
	{uh=y;dh=x;}
	dhull(dh,j);
	uhull(uh,j);
}
void convex_hull(int n)
{
	sort(p,p+n,cmp);
	dhull(0,n-1);
	uhull(0,n-1);
	cout<<"构成凸包的极点为:"<<endl;
	for(int i=0;i<m;i++)
		cout<<"("<<s[i].x<<","<<s[i].y<<")"<<endl;
	cout<<"构成凸包极点的个数为:"<<m<<endl;
}
void draw()
{
	initgraph(640,480,SHOWCONSOLE);  //初始化绘图窗口
	setbkcolor(WHITE);    //设置背景颜色
	cleardevice();        //用背景色清空屏幕
	
	setorigin(320,240);  //设置坐标原点
	setaspectratio(1, -1);//x轴向右为正，y轴向上为正
	setlinecolor(BLACK);   //设置当前连线的颜色
	//建立坐标系
	line(200,0,-200,0);  //建立x轴
	line(180,20,200,0);
	line(180,-20,200,0);

	line(0,200,0,-200);  //建立y轴
	line(0,200,20,180);
	line(0,200,-20,180);
	for(int i=0;i<n;i++)
	{
		circle(p[i].x*10,p[i].y*10,1);
		Sleep(800);       //相当于延时函数，每画一个点，间隔一定的时间
	}
	setlinecolor(BLUE);
	for(int i=0;i<m-1;i++)
	{
		line(s[i].x*10,s[i].y*10,s[i+1].x*10,s[i+1].y*10);
		Sleep(1000);     //相当于延时函数，使得连线时具有动态效果，不会显得突兀 
	}
	line(s[0].x*10,s[0].y*10,s[m-1].x*10,s[m-1].y*10);
	system("pause");
}
int main()
{
	cout<<"请输入点的个数n:";
	cin>>n;
	cout<<"请输入各个点的横坐标和纵坐标:"<<endl;
	for(int i=0;i<n;i++)
		cin>>p[i].x>>p[i].y;
	convex_hull(n);
	draw();
	return 0;
}
