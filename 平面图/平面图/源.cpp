#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define Root -1
#define COILA 1
#define M 20
#define FINITY 100000
typedef int edgetype;
typedef struct
{
	int num;
	char name[40]; 
	char disc[400];
} vertextype;
typedef struct
{
	vertextype vertex[M];
	edgetype edges[M][M];
	int n, e;
}Mgraph;
/**************************************************函数预览表*************************************************************************/
void Creat(Mgraph *g);                       //创建一个图
int Judge(int numb);                         //判断编号输入是否合理
void printnum(Mgraph *g);                    //输出编号以及名称;
void Search(Mgraph *g);                      //查看景点信息
void shortpath(Mgraph *g);                   //两景点之间最短路径
void floyde_print(Mgraph *g, int b, int e);    //Floyde求最短路径
void print_shortpath(Mgraph *g);             //最短路径输出函数
void Allpath(Mgraph *g, int b, int e);         //两景点之间所有路径
void print_Allpath(Mgraph *g);               //输出所有路径
void bestpath(Mgraph *g);                    //途经多景点最佳路径
void Dfs_coila(Mgraph *g, int i);             //关节点
void Coila_search(Mgraph *g);                //校园图关节点
int printplan();                             //输出平面图
int menu();                                  //输出主菜单
int main();                                  //主函数功能实现
/*************************************************************创建图并读入信息*********************************************************/
void Creat(Mgraph *g,char *s)
{
	int i, j, k, e;
	FILE *rf;
	rf = fopen_s(s, "r");
	if (!rf) 
	{
		printf("error!");
		return;
	}
	if (rf)
	{
		fscanf_s(rf, "%d%d", &g->n, &g->e);
		for (i = 0; i < g->n; i++)
		{
			fscanf_s(rf, "%d%s%s", &g->vertex[i].num, &g->vertex[i].name,&g->vertex[i].disc);
		}

		for (i = 0; i < g->n; i++)
		{
			for (j = 0; j < g->n; j++)
			{
				if (i == j) g->edges[i][j] = 0;
				else g->edges[i][j] = FINITY;
			}
		}
		for (k = 0; k < g->e; k++)
		{
			fscanf_s(rf, "%d%d%d", &i, &j, &e);
			g->edges[i][j] = g->edges[j][i] = e;
		}
		fclose(rf);
	}
	else g->n = 0;
}
/*************************************************************异常处理区********************************************************/
int Judge(int numb)
{
	if (numb < 0 || numb>9)
	{
		printf("\n");
		printf("                                                输入有误！请输入0-9之间的数\n");
		return 0;
	}
	return 1;
}

/*************************************************************输出编号以及名称************************************************************/
void printnum(Mgraph *g)
{
	int i;
	printf("\n");
	printf("                                                                                景点编号及名称\n");
	for (i = 0; i < g->n; i++)
	{
		printf("                               %d: %s\n", g->vertex[i].num, g->vertex[i].name);
	}
}
/**************************************************************输出景点信息****************************************************************/
void Search(Mgraph *g)
{
	int a;
	while (1)
	{
		printf("请输入要查询的景点编号:");
		scanf_s("%d", &a);
		if (Judge(a))
			break;
	}
	printf("\n景点名称:%s\n", g->vertex[a].name);
	printf("\n景点介绍:%s\n", g->vertex[a].disc);
	printf("\n");
}
/***********************************************************寻找两景点之间的最短距离******************************************************/
int dist[M][M];
int path[M][M];
void shortpath(Mgraph *g)
{
	int i, j, k;
	for (i = 0; i < g->n; i++)
		for (j = 0; j < g->n; j++)
		{
			dist[i][j] = g->edges[i][j];
			if (i != j && dist[i][j] < FINITY) path[i][j] = i;
			else
				path[i][j] = -1;
		}
	for (k = 0; k < g->n; k++)
		for (i = 0; i < g->n; i++)
			for (j = 0; j < g->n; j++)
			{
				if (dist[i][j] > (dist[i][k] + dist[k][j]))
				{
					dist[i][j] = dist[i][k] + dist[k][j];
					path[i][j] = k;
				}
			}
}
void floyde_print(Mgraph *g, int b, int e)
{
	if (path[b][e] == -1 || path[b][e] == e || path[b][e] == b)
		return;
	else
	{
		floyde_print(g, b, path[b][e]);
		printf("%s->", g->vertex[path[b][e]].name);
		floyde_print(g, path[b][e], e);
	}
}
void print_shortpath(Mgraph *g)
{
	int b, e;
	while (1)
	{
		printf("\n");
		printf("                                                请输入起点编号:");
		scanf_s("%d", &b);
		if (Judge(b))
			break;
	}
	printf("\n");
	while (1)
	{
		printf("\n");
		printf("                                                请输入终点编号:");
		scanf_s("%d", &e);
		if (Judge(e))
			break;
	}

	printf("\n                                                %s到%s的最短距离为:%d米\n\n", g->vertex[b].name, g->vertex[e].name, dist[b][e]);
	printf("                                                最佳游览路线:");
	printf("%s->", g->vertex[b].name);
	floyde_print(g, b, e);
	printf("%s\n\n", g->vertex[e].name);
	printf("\n");

}
/*****************************************************两景点之间的所有路径******************************************************************/
int pathstack[M], top, count;
int visited[M] = { 0 };
void Allpath(Mgraph *g, int b, int e)
{
	int i, j, dis = 0;
	top = 0; count = 1;
	pathstack[top++] = b;
	visited[b] = 1;
	for (i = 0; i < g->n; i++)
	{
		if (g->edges[b][i] > 0 && g->edges[b][i] != FINITY && !visited[i])
		{
			if (i == e)
			{
				printf("                                                第%d条道路:", count++);
				for (j = 0; j < top; j++)
				{
					printf("%s->", g->vertex[pathstack[j]].name);
					if (j < top - 1)
						dis = dis + g->edges[pathstack[j]][pathstack[j + 1]];
				}
				dis = dis + g->edges[pathstack[top - 1]][e];
				printf("%s\n", g->vertex[e].name);
				printf("                                                总长度为: %d米\n\n", dis);
			}
			else
				Allpath(g, i, e);
		}
	}
}
void print_Allpath(Mgraph *g)
{
	int b, e;
	count = 1;
	top = 0;
	memset(pathstack, 0, sizeof(pathstack));
	memset(visited, 0, sizeof(visited));
	while (1)
	{
		printf("\n");
		printf("                                                请输入起点编号:");
		scanf_s("%d", &b);
		if (Judge(b))
			break;
	}
	while (1)
	{
		printf("\n");
		printf("                                                请输入终点编号:");
		scanf_s("%d", &e);
		if (Judge(e))
			break;
	}
	printf("\n");
	Allpath(g, b, e);
	printf("\n");
}
/*********************************************************多景点求最佳路径*****************************************************************/
void bestpath(Mgraph *g)
{
	int b;
	int vnum[M] = { 0 }, j = 1;
	int i, d = 0;
	while (1)
	{
		printf("\n");
		printf("                                                请输入要查询的第%d个景点的编号(输入0结束输入):", j);
		scanf_s("%d", &b);
		vnum[j - 1] = b + 1;
		if (Judge(vnum[j - 1]))
			break;
	}
	printf("\n");
	while (vnum[j - 1] != 0 && j < 12)
	{
		if (vnum[j - 1] == -1) break;
		j++;
		while (1)
		{
			printf("\n");
			printf("                                                请输入要游览的第%d个景点编号:", j);
			scanf_s("%d", &b);
			vnum[j - 1] = b + 1;
			if (Judge(vnum[j - 1]))
				break;
		}
		printf("\n");
	}
	printf("                                                这是最佳访问路径:");
	for (i = 0; vnum[i] > 0 && vnum[i + 1] > 0; i++)
	{
		printf("%s->", g->vertex[vnum[i] - 1].name);
		floyde_print(g, vnum[i] - 1, vnum[i + 1] - 1);
		d += dist[vnum[i] - 1][vnum[i + 1] - 1];
	}

	printf("%s\n\n", g->vertex[vnum[j - 2] - 1].name);
	printf("\n");
	printf("                                                全程路径为: %d米\n", d);
}
/*********************************************************深度遍历寻找关节点***************************************************************/
int visi[M], coila[M] = { 0 };
int coilanum;
void Dfs_coila(Mgraph *g, int i)
{
	int child = 0;
	int j;
	if (visi[i] != Root)
	{
		visi[i] = 1;
	}
	for (j = 0; j < g->n; j++)
	{
		if (g->edges[i][j] != 0 && g->edges[i][j] != FINITY && !visi[j])
		{
			child++;
			Dfs_coila(g, j);
		}
	}
	if (visi[i] == Root && child >= 2)
	{
		coilanum++;
		coila[i] = COILA;
	}
}

/**********************************************************求校园图交通图关节点************************************************************/
void Coila_search(Mgraph *g)
{
	int i;
	coilanum = 0;
	for (i = 0; i < g->n; i++)
	{
		memset(visi, 0, sizeof(visi));
		visi[i] = Root;
		Dfs_coila(g, i);
	}
	printf("                                                校园图关节点个数为: %d\n\n                                                分别为:", coilanum);
	for (i = 0; i < g->n; i++)
	{
		if (coila[i] == COILA)
		{
			printf("%s\t", g->vertex[i].name);
		}
	}
	printf("\n");
}

/*******************************************************平面图******************************************************************************/
int printplan()
{
	printf("                                                                                                                                                         \n");
	printf("                                                                                    中北大学校园景点平面图                                               \n");
	printf("                                                ===================================================================================================      \n");
	printf("                                                                               7.游泳馆---------8.瑾瑜国际中心------------------------9.龙山餐厅           \n");
	printf("                                                                                                      |                                  |               \n");
	printf("                                                                                                      |                                  |               \n");
	printf("                                                                                                      |                                  |               \n");
	printf("                                                                                                      |                                  |               \n");
	printf("                                                                               5.图书馆---------------┛                                  |               \n");
	printf("                                                                                    |                                                    |               \n");
	printf("                                                                                    |                                                    |               \n");
	printf("                                                                                    |                                                    |               \n");
	printf("                                              4.二龙山------┓----------------------┻------------┓                                        |               \n");
	printf("                                                            |                                 6.行知广场---------------------------------|               \n");
	printf("                                                            |                                     |                                      |               \n");
	printf("                                                            |                                     |                                      |               \n");
	printf("                                              1.柏林园------┓                                    ┗------- 2.铁路公园                     |               \n");
	printf("                                                            |                                                  |                         |               \n");
	printf("                                                            |                                                  |                         |               \n");
	printf("                                                            |                                                  |                         |               \n");
	printf("                                                            |                                                  |-----------------------3.中北酒店          \n");
	printf("                                                            |                                                  |                                         \n");
	printf("                                                            |                                                  |                                         \n");
	printf("                                                            |                                                  |                                         \n");
	printf("                                                         0.德怀楼---------------------------------------------┛                                         \n");
	printf("                                                            |                                                                                            \n");
	printf("                                                ===================================================================================================      \n");
	system("pause");
	return 0;
}

/********************************************************主菜单*****************************************************************************/
int menu()
{
	printf("                                                -----------------------------------------------------------------------------------------\n");
	printf("                                                          *         *     ****     *      ****    ****      *   *      ****  \n");
	printf("                                                          *    *    *     *        *      *       *  *     **   **     *     \n");
	printf("                                                           *  * *  *      ****     *      *       *  *    *  * *  *    ****  \n");
	printf("                                                            **   **       *        *      *       *  *   *    *    *   *     \n");
	printf("                                                             *   *        ****     ****   ****    ****   *         *   ****  \n");
	printf("                                                -----------------------------------------------------------------------------------------\n");
	printf("                                                                                                                                         \n");
	printf("                                                * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("                                                * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("                                                * *                         欢迎使用中北大学校园导航系统                              * *\n");
	printf("                                                * *                                                                                   * *\n");
	printf("                                                * *                             请选择您需要的功能:                                   * *\n");
	printf("                                                * *                                                                                   * *\n");
	printf("                                                * *             1.学校平面图                      5.两景点之间所有路径                * *\n");
	printf("                                                * *                                                                                   * *\n");
	printf("                                                * *             2.显示景点编号及名称              6.途径多景点的最佳路径              * *\n");
	printf("                                                * *                                                                                   * *\n");
	printf("                                                * *             3.主要景点信息介绍                7.校园图关节点                      * *\n");
	printf("                                                * *                                                                                   * *\n");
	printf("                                                * *             4.寻找两景点之间的最短距离        8.退出系统                          * *\n");
	printf("                                                * *                                                                                   * *\n");
	printf("                                                * *                                                                                   * *\n");
	printf("                                                * *                                                                                   * *\n");
	printf("                                                * *                                                                                   * *\n");
	printf("                                                * *                                                                                   * *\n");
	printf("                                                * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("                                                * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\n\n");
	return 0;
}
/**************************************************************功能选择*********************************************************************/
void select()
{
	int m;
	int i = 0, j = 1, flag = 0;
	Mgraph g;
	Creat(&g);
	shortpath(&g);
	while (j)
	{
		menu();
		while (1)
		{
			printf("\n");
			printf("                                                输入你想要的操作:");
			scanf_s("%d", &m); break;
		}
		printf("\n");
		switch (m)
		{
		case 1:
			printplan();
			system("pause");
			system("cls");
			break;
		case 2:
			system("cls");
			printplan();
			printnum(&g);
			system("pause");
			system("cls");
			break;
		case 3:
			system("cls");
			printplan();
			Search(&g);
			system("pause");
			system("cls");
			break;
		case 4:
			system("cls");
			printplan();
			print_shortpath(&g);
			system("pause");
			system("cls");
			break;
		case 5:
			system("cls");
			printplan();
			print_Allpath(&g);
			system("pause");
			system("cls");
			break;
		case 6:
			system("cls");
			printplan();
			bestpath(&g);
			system("pause");
			system("cls");
			break;
		case 7:
			system("cls");
			printplan();
			Coila_search(&g);
			system("pause");
			system("cls");
			break;
		case 8:
			system("cls");
			j = 0;
			break;
		default:
			printf("\t\t                                对不起，没有您对应的操作。\n\n");
			system("pause");
			system("cls");
			break;
		}
	}
}
/************************************************************测试（主函数）*****************************************************************/
int main()
{
	system("color f4");
	Mgraph g;
	char file[30];
	gets_s(file);
	Creat(&g, file);
	select();
	system("pause");
	return 0;
}