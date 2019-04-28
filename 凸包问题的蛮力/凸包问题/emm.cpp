#include<iostream>
#include<graphics.h>
using namespace std;
const int N=1000;
class Point     //������
{
public:
	int x,y;
	int flag;
};
Point p[N];   //����������飬�����е�ÿһ��Ԫ�ض��������
int n;
void display(int d[],int e[],int b1)
{
	initgraph(640, 480,SHOWCONSOLE);  //��ʼ����ͼ����
	setbkcolor(BLACK);    //���ñ�����ɫ
	cleardevice();        //�ñ���ɫ�����Ļ
	
	setorigin(320,240);  //��������ԭ��
	setaspectratio(1, -1);//x������Ϊ����y������Ϊ��
	setlinecolor(BLUE);   //���õ�ǰ���ߵ���ɫ
	//��������ϵ
	line(200,0,-200,0);  //����x��
	line(180,20,200,0);
	line(180,-20,200,0);

	line(0,200,0,-200);  //����y��
	line(0,200,20,180);
	line(0,200,-20,180);
	for(int i=0;i<n;i++)
	{
		putpixel(p[i].x*10,p[i].y*10,WHITE);
		Sleep(800);        //�൱����ʱ������ÿ��һ���㣬���һ����ʱ��
	}
	setlinecolor(WHITE);
	for(int i=0;i<b1;i++)
	{
		line(p[d[i]].x*10,p[d[i]].y*10,p[e[i]].x*10,p[e[i]].y*10);
		Sleep(1000);     //�൱����ʱ������ʹ������ʱ���ж�̬Ч���������Ե�ͻأ 
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
		cout<<"����͹���ļ���Ϊ:"<<endl;
		for(int i=0;i<n;i++)
			if(p[i].flag==1)
				cout<<"("<<p[i].x<<","<<p[i].y<<")"<<endl;
		display(d,e,b1);
}
int main()
{
	cout<<"�������ĸ���n:";
	cin>>n;
	cout<<"�����������ĺ������������:"<<endl;
	for(int i=0;i<n;i++)
		cin>>p[i].x>>p[i].y;
	converhull();
	return 0;
}