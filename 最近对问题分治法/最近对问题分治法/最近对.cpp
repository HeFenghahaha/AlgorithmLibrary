#include<iostream>
#include<algorithm>
#include<cmath>
#include<graphics.h>
using namespace std;
const int N=100;
class Point
{
public:
	double x,y;
};
Point points[N],pdraw[2];
int n;
bool cmpx(Point p1,Point p2)
{
	return p1.x<p2.x;
}
bool cmpy(Point p1,Point p2)
{
	return p1.y<p2.y;
}
double dist(Point p1,Point p2)
{
	return sqrt(pow(p1.x-p2.x,2)+pow(p1.y-p2.y,2));
}
double mind(double d1,double d2,double d3)
{
	if(d2<d1) d1=d2;
	if(d3<d1) d1=d3;
	return d1;
}
double min2(double d1,double d2)
{
	if(d1<d2) return d1;
	else return d2;
}
double merge(Point p[],double mx,double d)
{
	Point pm[N];
	int size=0;
	for(int i=0;i<n;i++)
		if(abs(p[i].x-mx)<=d)
			pm[size++]=p[i];
	for(int i=0;i<size-1;i++)
		for(int j=i+1;j<size;j++)
			if(abs(pm[j].y-pm[i].y)<=d)
			{
				double dm=dist(pm[i],pm[j]);
				if(dm<d)
				{
					d=dm;
					pdraw[0]=pm[i];
					pdraw[1]=pm[j];
				}
			}
	return d;
}
double closedis(Point p[],int lo,int hi)
{
	if(hi-lo==1)
	{
		pdraw[0]=p[lo];
		pdraw[1]=p[hi];
		return dist(p[lo],p[hi]);
	}
	else if(hi-lo==2)
	{
		double d1=dist(p[lo],p[lo+1]);
		double d2=dist(p[lo+1],p[hi]);
		double d3=dist(p[lo],p[hi]);
		if(mind(d1,d2,d3)==d1)
		{pdraw[0]=p[lo];pdraw[1]=p[lo+1];}
		if(mind(d1,d2,d3)==d2)
		{pdraw[0]=p[lo+1];pdraw[1]=p[hi];}
		if(mind(d1,d2,d3)==d3)
		{pdraw[0]=p[lo];pdraw[1]=p[hi];}
		return mind(d1,d2,d3);
	}
	else
	{
		int m=(lo+hi)/2;
		double mx=p[m].x;
		double dl=closedis(points,lo,m);
		double dr=closedis(points,m,hi);
		double d=min2(dl,dr);
		return merge(points,mx,d);
	}
}
void draw(int n)
{
	initgraph(640,480,SHOWCONSOLE);  //初始化图形窗口
	setbkcolor(WHITE);
	cleardevice();

	setorigin(320,240);  //坐标原点
	setaspectratio(1,-1);
	setlinecolor(BLUE);
	line(-200,0,200,0);
	line(180,20,200,0);
	line(180,-20,200,0);

	line(0,200,0,-200);
	line(0,200,-20,180);
	line(0,200,20,180);

	for(int i=0;i<n;i++)
	{
		circle(points[i].x*10,points[i].y*10,1);
		Sleep(800);
	}
	//line(pd[0].x*10,pd[0].y*10,pd[1].x*10,pd[1].y*10);
	system("pause");
}
int main()
{
	cout<<"请输入点的个数:";
	cin>>n;
	cout<<"请依次输入各点的横坐标和纵坐标:"<<endl;
	for(int i=0;i<n;i++)
		cin>>points[i].x>>points[i].y;
	sort(points,points+n,cmpx);
	cout<<"最近距离为:"<<closedis(points,0,n-1)<<endl;
	draw(n);
	return 0;
}