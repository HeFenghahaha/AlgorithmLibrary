#include<stdio.h>
#include<stdlib.h>
#define FINITY 5000
#define M 20
typedef int edgetype;
typedef struct {
	edgetype vexs[M];
	edgetype edges[M][M];
	int n, e;
}Mgraph;
typedef enum{FALSE,TRUE} boolean;
typedef int dist[M];
typedef int path[M];
typedef int di[M][M];
typedef int pa[M][M];
void creat(Mgraph *g,int c)//建立有向网络的邻接矩阵
{
	int i, j, k, w;
	printf("请输入顶点数n和边数e:");
	scanf_s("%d%d", &g->n,&g->e);
	printf("请输入各顶点序号:");
	for (i = 0; i < g->n; i++)
		scanf_s("%d", &g->vexs[i]);
	for (i = 0; i < g->n; i++)
		for (j = 0; j < g->n; j++)
			if (i == j) g->edges[i][j] = 0;
			else g->edges[i][j] = FINITY;
	printf("请输入各边的信息:\n");
	for (k = 0; k < g->e; k++)
	{
		scanf_s("%d%d%d", &i, &j, &w);
		g->edges[i][j] = w;
		if(c==0)
			g->edges[j][i] = w;
	}
}
void dijkstra(Mgraph g, int v0, path p, dist d)//用Dijkstra算法求解单源最短路径
{
	boolean final[M];
	int i, k, v, min;
	for (v = 0; v < g.n; v++)
	{
		final[v] = FALSE;
		d[v] = g.edges[v0][v];
		if (d[v]<FINITY&&d[v] != 0)
			p[v] = v0;
		else  p[v] = -1;
	}
	final[v0] = TRUE; d[v0] = 0;
	for (i = 1; i < g.n; i++)
	{
		min = FINITY;
		for(k=0;k<g.n;++k)
			if(!final[k]&&d[k]<min)
			{
				v = k; min = d[k];
			}
		printf("\n%d---%d\n", g.vexs[v], min);
		if (min == FINITY) return;
		final[v] = TRUE;
		for(k=0;k<g.n;++k)
			if(!final[k]&&(min + g.edges[v][k]<d[k]))
			{
				d[k] = min + g.edges[v][k]; p[k] = v;
			}
	}
}
void print(Mgraph g, path p, dist d,int v0)//输出有向图的最短路径
{
	int st[M], i, pre, top = -1;
	for (i = 1; i < g.n; i++)
	{
		printf("\n顶点%d到顶点%d的最短距离是:%d,路径为:",v0,i,d[i]);
		st[++top] = i;
		pre = p[i];
		while (pre != -1)
		{
			st[++top] = pre;
			pre = p[pre];
		}
		while (top > 0)
			printf("%2d",st[top--]);
		printf("\n");
	}
	printf("\n\n");
}
void floyd(Mgraph g, pa p, di d)//用Floyd方法求所有顶点间的最短路径
{
	int i, j, k, m = -2;
	int sr[M], pre, top = -1;
	for(i=0;i<g.n;i++)
		for (j = 0; j < g.n; j++)
		{
			d[i][j] = g.edges[i][j];
			if (i != j && d[i][j] < FINITY)
				p[i][j] = i;
			else
				p[i][j] = -1;
		}
	for (k = 0; k < g.n; k++)
	{
		for(i=0;i<g.n;i++)
			for (j = 0; j < g.n; j++)
				if (d[i][j] > d[i][k] + d[k][j])
				{
					d[i][j] = d[i][k] + d[k][j];
					p[i][j] = k;
				}
	}
	for (i = 0; i < g.n; i++)
		for (j = 0; j < g.n; j++)
			if (i != j)
				printf("\n顶点%d到顶点%d的最短距离是：%d\n", i, j, d[i][j]);
	printf("\n");
}
int main()
{
	Mgraph g;
	path p;
	dist d;
	di dis;
	pa pat;
	int v0; 
	creat(&g,1);
	printf("请输入源点v0：");
	scanf_s("%d", &v0);
	dijkstra(g, v0, p, d);
	print(g, p, d,v0);
	floyd(g,pat,dis);
	system("pause");
	return 0;
}