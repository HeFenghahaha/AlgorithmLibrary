#include<stdio.h>
#include<stdlib.h>
/*#define MAXSIZE 100
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
void quicksort(table *t, int left, int right)
{
	int i, j;
	if (left < right)
	{
		i = left; j = right;
		t->r[0] = t->r[i];
		do
		{
			while (i<j&&t->r[j].number>t->r[0].number) j--;
			if(i<j)
			{
				t->r[i].number = t->r[j].number; i++;
			}
			while (i < j&&t->r[i].number < t->r[0].number) i++;
			if (i < j)
			{
				t->r[j].number = t->r[i].number; j--;
			}
		} while (i != j);
		t->r[i] = t->r[0];
		quicksort(t, left, i - 1);
		quicksort(t, i + 1, right);
	}
}*/
int main()
{
	/*int n, i,j;
	table *t = (table *)malloc(sizeof(table));
	printf("�����������ĸ���n:");
	scanf_s("%d", &n);
	printf("�����������������ѧ�š����������š�Ժϵ��\n");
	for (i = 1; i <= n; i++)
	{
		printf("������ѧ��:\n");
		scanf_s("%d", &t->r[i].number);
		printf("����������:\n");
		scanf_s("%s", &t->r[i].name);
		printf("�����뿨��:\n");
		scanf_s("%s", &t->r[i].card);
		printf("������Ժϵ:\n");
		scanf_s("%d", &t->r[i].yuan);
	}
	quicksort(t, 1,n );
	printf("�����Ľ������:\n");
	printf("ѧ��\t\t����\t\t����\t\tԺϵ\n");
	for (i = 1; i <= n; i++)
	{
		printf("%d\t\t",t->r[i].number);
		printf("%s\t\t",t->r[i].name);
		printf("%s\t\t",t->r[i].card);
		printf("%d\n",t->r[i].yuan);
	}*/
	int a = 5;
	int b = a / 2;
	printf("%d", b);
	system("pause");
	return 0;
}