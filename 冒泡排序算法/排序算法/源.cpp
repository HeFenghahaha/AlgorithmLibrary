#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100
typedef struct node
{
	char name[20];
	int number;
	char card[10];
	int yuan;
}node;
typedef struct {
	node r[MAXSIZE];
	int length;
}table;
void bubblesort(table *t)
{
	int i=1,j,d=1;
	while(i<=t->length&&d)
	{
		d = 0;
		for(j=1;j<=t->length-i;j++)
			if (t->r[j + 1].number < t->r[j].number)
			{
				t->r[0] = t->r[j];
				t->r[j] = t->r[j+1];
				t->r[j+1] = t->r[0];
				d = 1;
			}
		i++;
	}
}
int main()
{
	int n, i;
	char c;
	table *t=(table *)malloc(sizeof(table));
	printf("请输入待排序的个数n:");
	scanf_s("%d", &n);
	t->length = n;
	printf("请依次输入各个学生的姓名、卡号、学号、院系：\n");
	for (i = 1; i<=n; i++)
	{
		printf("请输入姓名:\n"); c = getchar();
		gets_s(t->r[i].name); c= getchar();
		printf("请输入学号:\n");
		scanf_s("%d", &t->r[i].number);
		printf("请输入院系:\n");
		scanf_s("%d", &t->r[i].yuan);
		printf("请输入卡号:\n"); c = getchar();
		gets_s(t->r[i].card);c = getchar();
	}
	printf("排序后的结点序列:\n");
	bubblesort(t);
	printf("学号\t\t姓名\t\t卡号\t\t院系\n");
	for (i = 1; i<= n; i++)
	{
		printf("%d\t\t", t->r[i].number);
		printf("%s\t\t", t->r[i].name);
		printf("%s\t\t", t->r[i].card);
		printf("%d\n", t->r[i].yuan);
	}
	system("pause");
	return 0;
}