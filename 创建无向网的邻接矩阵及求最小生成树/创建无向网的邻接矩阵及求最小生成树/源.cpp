#include<stdio.h>
#include<stdlib.h>
#define FINITY 5000
#define M 20
typedef char vertextype;
typedef int edgetype;
typedef struct {
	vertextype vexs[M];
	edgetype edges[M][M];
	int n, e;
}Mgraph;
typedef struct {
	int beg, en;
	int length;
}edge;
void creat(Mgraph *g, const char *s, int c)//建立无向网络的邻接矩阵
{
	int i, j, k, w;
	FILE *rf;
	rf = fopen(s, "r");
	if (rf)
	{
		fscanf_s(rf, "%d%d", &g->n, &g->e);
		for (i = 0; i < g->n; i++)
			fscanf_s(rf, "%c", &g->vexs[i]);
		for (i = 0; i < g->n; i++)
			for (j = 0; j < g->n; j++)
				if (i == j) g->edges[i][j] = 0;
				else g->edges[i][j] = FINITY;
		for (k = 0; k < g->e; k++)
		{
			fscanf_s(rf, "%d%d%d", &i, &j, &w);
			g->edges[i][j] = w;
			if (c == 0) g->edges[j][i] = w;
		}
		fclose(rf);
		printf("该无向网的邻接矩阵为：\n");
		for (i = 0; i < g->n; i++)
		{
			for (j = 0; j < g->n; j++)
				printf("%5d", g->edges[i][j]);
			printf("\n");
		}
	}
	else g->n = 0;
}
void prim(Mgraph g, edge tree[M - 1])//Prim算法求该无向网的最小生成树
{
	edge x;
	int d, min, j, k, s, v;
	for (v = 1; v <= g.n - 1; v++)
	{
		tree[v - 1].beg = 0;
		tree[v - 1].en = v;
		tree[v - 1].length = g.edges[0][v];
	}
	for (k = 0; k <= g.n - 3; k++)
	{
		min = tree[k].length;
		s = k;
		for (j = k + 1; j <= g.n - 2; j++)
			if (tree[j].length < min)
			{
				min = tree[j].length;
				s = j;
			}
		v = tree[s].en;
		x = tree[s]; tree[s] = tree[k]; tree[k] = x;
		for (j = k + 1; j <= g.n - 2; j++)
		{
			d = g.edges[v][tree[j].en];
			if (d < tree[j].length)
			{
				tree[j].length = d; tree[j].beg = v;
			}
		}
	}
	printf("最小生成树是：\n");
	for (j = 0; j <= g.n - 2; j++)
		printf("\n%c---%c %d\n", g.vexs[tree[j].beg], g.vexs[tree[j].en], tree[j].length);
	printf("这棵树的根是：%c\n", g.vexs[0]);
}
void quicksort(edge edges[], int left, int right)//对所以边的权值进行快速排序，从小到大
{
	edge x;
	int i, j, flag = 1;
	if (left < right)
	{
		i = left; j = right; x = edges[i];
		while (i < j)
		{
			while (i < j && x.length < edges[j].length) j--;
			if (i < j) edges[i++] = edges[j];
			while (i < j && x.length > edges[i].length) i++;
			if (i < j) edges[j--] = edges[i];
		}
		edges[i] = x;
		quicksort(edges, left, i - 1);
		quicksort(edges, i + 1, right);
	}
}
void getedge(Mgraph g, edge edges[])//从图g的邻接矩阵读取图的所有信息
{
	int i, j, k = 0;
	for (i = 0; i < g.n; i++)
		for (j = 0; j < i; j++)
			if (g.edges[i][j] != 0 && g.edges[i][j] < FINITY)
			{
				edges[k].beg = i;
				edges[k].en = j;
				edges[k++].length = g.edges[i][j];
			}
}
void kruskal(Mgraph g)
{
	int i, j, k = 0, ltfl;
	int cnvx[M];
	edge edges[M*M];
	edge tree[M];
	getedge(g, edges);
	quicksort(edges, 0, g.e - 1);
	for (i = 0; i < g.n; i++)
		cnvx[i] = 0;
	for (i = 0; i < g.n - 1; i++)
	{
		while (cnvx[edges[k].beg] == cnvx[edges[k].en])
			k++;
		tree[i] = edges[k];
		ltfl = cnvx[edges[k].en];
		for (j = 0; j < g.n; j++)
			if (cnvx[j] == ltfl)
				cnvx[j] = cnvx[edges[k].beg];
		k++;
	}
	printf("最小生成树是：\n");
	for (j = 0; j < g.n - 1; j++)
		printf("\n%c---%c%6d\n", g.vexs[tree[j].beg], g.vexs[tree[j].en], tree[j].length);
}
int main()
{
	Mgraph g;
	edge tree[M - 1];
	int m;
	creat(&g, "g7.txt", 0);
	printf("请选择：\n1.用Prim算法求该无向网的最小生成树\n2.用Kruskal算法求该无向网的最小生成树\n");
	printf("请输入数字1-2\n");
	scanf_s("%d", &m);
	switch (m)
	{
	case 1:prim(g, tree); break;
	case 2:kruskal(g); break;
	default:
		printf("error!没有这个选项！\n");
	}
	system("pause");
	return 0;
}