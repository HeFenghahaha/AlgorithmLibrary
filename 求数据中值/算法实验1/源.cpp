#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100
typedef struct {
	int a[MAXSIZE];
}N;
void quick(N *t,int left, int right,int p)
{
	int i, j;
	if (left < right)
	{
		i = left; j = right;
		t->a[0] = t->a[i];
		do {
			while (i<j&&t->a[j] > t->a[0]) j--;
			if(i<j)
			{
				t->a[i] = t->a[j]; i++;
			}
			while (i<j&&t->a[i] < t->a[0]) i++;
			if (i < j)
			{
				t->a[j] = t->a[i]; j--;
			}
		} while (i!=j);
		t->a[i] = t->a[0];
		if (p < i)
			quick(t, left, i - 1, p);
		else if (p > i)
			quick(t, i + 1, right, p);
		else if(p==i)
			printf("这组数据的中值是%d\n",t->a[i]);
	}
}
int main()
{
	int n,i;
	N *t = (N *)malloc(sizeof(N));
	printf("请输入元素的个数n:");
	scanf_s("%d", &n);
	printf("请依次输入%d个整数:\n", n);
	for (i = 1; i <= n; i++)
		scanf_s("%d", &t->a[i]);
	quick(t, 1, n, n / 2);
	system("pause");
	return 0;
}