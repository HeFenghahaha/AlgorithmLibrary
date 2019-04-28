#include<iostream>
#include<cmath>
#include<algorithm>
#include<graphics.h>
using namespace std;
const int N=100;
void uhull(int,int);   //��������
void dhull(int,int);   //��������
class Point     //������
{
public:
	double x,y;
};
Point p[N],s[N];   //����������飬�����е�ÿһ��Ԫ�ض��������
int n,m=0;
bool cmp (Point q,Point r)  //��p���鰴x��ֵ��С��������
{
	return q.x<r.x;
}
double judge(Point p1,Point p2,Point p3)  //�жϵ�p3��ֱ��p1��p2����໹���Ҳ�
{
	return p1.x*p2.y+p3.x*p1.y+p2.x*p3.y-p3.x*p2.y-p2.x*p1.y-p1.x*p3.y;
}
double dist(Point p1,Point p2,Point p3)   //�����p3��ֱ��p1p2�ľ���
{
	return abs((p2.y-p1.y)*p3.x+(p1.x-p2.x)*p3.y+(p1.y-p2.y)*p1.x+(p2.x-p1.x)*p1.y)/sqrt(pow(p2.y-p1.y,2)+pow(p1.x-p2.x,2));
}
void uhull(int x,int y)    //��͹��
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
void dhull(int x,int y)   //��͹��
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
	cout<<"����͹���ļ���Ϊ:"<<endl;
	for(int i=0;i<m;i++)
		cout<<"("<<s[i].x<<","<<s[i].y<<")"<<endl;
	cout<<"����͹������ĸ���Ϊ:"<<m<<endl;
}
void draw()
{
	initgraph(640,480,SHOWCONSOLE);  //��ʼ����ͼ����
	setbkcolor(WHITE);    //���ñ�����ɫ
	cleardevice();        //�ñ���ɫ�����Ļ
	
	setorigin(320,240);  //��������ԭ��
	setaspectratio(1, -1);//x������Ϊ����y������Ϊ��
	setlinecolor(BLACK);   //���õ�ǰ���ߵ���ɫ
	//��������ϵ
	line(200,0,-200,0);  //����x��
	line(180,20,200,0);
	line(180,-20,200,0);

	line(0,200,0,-200);  //����y��
	line(0,200,20,180);
	line(0,200,-20,180);
	for(int i=0;i<n;i++)
	{
		circle(p[i].x*10,p[i].y*10,1);
		Sleep(800);       //�൱����ʱ������ÿ��һ���㣬���һ����ʱ��
	}
	setlinecolor(BLUE);
	for(int i=0;i<m-1;i++)
	{
		line(s[i].x*10,s[i].y*10,s[i+1].x*10,s[i+1].y*10);
		Sleep(1000);     //�൱����ʱ������ʹ������ʱ���ж�̬Ч���������Ե�ͻأ 
	}
	line(s[0].x*10,s[0].y*10,s[m-1].x*10,s[m-1].y*10);
	system("pause");
}
int main()
{
	cout<<"�������ĸ���n:";
	cin>>n;
	cout<<"�����������ĺ������������:"<<endl;
	for(int i=0;i<n;i++)
		cin>>p[i].x>>p[i].y;
	convex_hull(n);
	draw();
	return 0;
}
