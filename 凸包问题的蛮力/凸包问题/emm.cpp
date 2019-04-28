#include<iostream>
#include<graphics.h>
using namespace std;
const int N=1000;
class Point     //定义类
{
public:
	int x,y;
	int flag;
};
Point p[N];   //定义对象数组，数组中的每一个元素都是类对象
int n;
void display(int d[],int e[],int b1)
{
	initgraph(640, 480,SHOWCONSOLE);  //初始化绘图窗口
	setbkcolor(BLACK);    //设置背景颜色
	cleardevice();        //用背景色清空屏幕
	
	setorigin(320,240);  //设置坐标原点
	setaspectratio(1, -1);//x轴向右为正，y轴向上为正
	setlinecolor(BLUE);   //设置当前连线的颜色
	//建立坐标系
	line(200,0,-200,0);  //建立x轴
	line(180,20,200,0);
	line(180,-20,200,0);

	line(0,200,0,-200);  //建立y轴
	line(0,200,20,180);
	line(0,200,-20,180);
	for(int i=0;i<n;i++)
	{
		putpixel(p[i].x*10,p[i].y*10,WHITE);
		Sleep(800);        //相当于延时函数，每画一个点，间隔一定的时间
	}
	setlinecolor(WHITE);
	for(int i=0;i<b1;i++)
	{
		line(p[d[i]].x*10,p[d[i]].y*10,p[e[i]].x*10,p[e[i]].y*10);
		Sleep(1000);     //相当于延时函数，使得连线时具有动态效果，不会显得突兀 
	}
	system("pause");
}
void converhull()
{
	for(int i=0;i<n;i++)
		p[i].flag=0;
	int a,b,c,s1,s2;
	int d[N],e[N];
	int b1=0,e1=0;
	for(int i=0;i<=n-2;i++)
		for(int j=i+1;j<=n-1;j++)
		{
			a=p[j].y-p[i].y;
			b=p[i].x-p[j].x;
			c=(p[i].x*p[j].y)-(p[i].y*p[j].x);
			s1=0;s2=0;
			for(int k=0;k<n;k++)
			{
				if((k==i)||(k==j)) 
					continue;
				if((a*p[k].x+b*p[k].y)==c)
				{
					s1++;s2++;
				}
				if((a*p[k].x+b*p[k].y)>c)
					s1++;
				if((a*p[k].x+b*p[k].y)<c)
					s2++;
			}
			if((s1==(n-2))||(s2==(n-2)))
			{
				p[i].flag=1;
				p[j].flag=1;
				d[b1++]=i;
				e[e1++]=j;
			}
		}
		cout<<"构成凸包的极点为:"<<endl;
		for(int i=0;i<n;i++)
			if(p[i].flag==1)
				cout<<"("<<p[i].x<<","<<p[i].y<<")"<<endl;
		display(d,e,b1);
}
int main()
{
	cout<<"请输入点的个数n:";
	cin>>n;
	cout<<"请输入各个点的横坐标和纵坐标:"<<endl;
	for(int i=0;i<n;i++)
		cin>>p[i].x>>p[i].y;
	converhull();
	return 0;
}