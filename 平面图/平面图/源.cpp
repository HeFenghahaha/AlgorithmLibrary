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
/**************************************************����Ԥ����*************************************************************************/
void Creat(Mgraph *g);                       //����һ��ͼ
int Judge(int numb);                         //�жϱ�������Ƿ����
void printnum(Mgraph *g);                    //�������Լ�����;
void Search(Mgraph *g);                      //�鿴������Ϣ
void shortpath(Mgraph *g);                   //������֮�����·��
void floyde_print(Mgraph *g, int b, int e);    //Floyde�����·��
void print_shortpath(Mgraph *g);             //���·���������
void Allpath(Mgraph *g, int b, int e);         //������֮������·��
void print_Allpath(Mgraph *g);               //�������·��
void bestpath(Mgraph *g);                    //;���ྰ�����·��
void Dfs_coila(Mgraph *g, int i);             //�ؽڵ�
void Coila_search(Mgraph *g);                //У԰ͼ�ؽڵ�
int printplan();                             //���ƽ��ͼ
int menu();                                  //������˵�
int main();                                  //����������ʵ��
/*************************************************************����ͼ��������Ϣ*********************************************************/
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
/*************************************************************�쳣������********************************************************/
int Judge(int numb)
{
	if (numb < 0 || numb>9)
	{
		printf("\n");
		printf("                                                ��������������0-9֮�����\n");
		return 0;
	}
	return 1;
}

/*************************************************************�������Լ�����************************************************************/
void printnum(Mgraph *g)
{
	int i;
	printf("\n");
	printf("                                                                                �����ż�����\n");
	for (i = 0; i < g->n; i++)
	{
		printf("                               %d: %s\n", g->vertex[i].num, g->vertex[i].name);
	}
}
/**************************************************************���������Ϣ****************************************************************/
void Search(Mgraph *g)
{
	int a;
	while (1)
	{
		printf("������Ҫ��ѯ�ľ�����:");
		scanf_s("%d", &a);
		if (Judge(a))
			break;
	}
	printf("\n��������:%s\n", g->vertex[a].name);
	printf("\n�������:%s\n", g->vertex[a].disc);
	printf("\n");
}
/***********************************************************Ѱ��������֮�����̾���******************************************************/
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
		printf("                                                �����������:");
		scanf_s("%d", &b);
		if (Judge(b))
			break;
	}
	printf("\n");
	while (1)
	{
		printf("\n");
		printf("                                                �������յ���:");
		scanf_s("%d", &e);
		if (Judge(e))
			break;
	}

	printf("\n                                                %s��%s����̾���Ϊ:%d��\n\n", g->vertex[b].name, g->vertex[e].name, dist[b][e]);
	printf("                                                �������·��:");
	printf("%s->", g->vertex[b].name);
	floyde_print(g, b, e);
	printf("%s\n\n", g->vertex[e].name);
	printf("\n");

}
/*****************************************************������֮�������·��******************************************************************/
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
				printf("                                                ��%d����·:", count++);
				for (j = 0; j < top; j++)
				{
					printf("%s->", g->vertex[pathstack[j]].name);
					if (j < top - 1)
						dis = dis + g->edges[pathstack[j]][pathstack[j + 1]];
				}
				dis = dis + g->edges[pathstack[top - 1]][e];
				printf("%s\n", g->vertex[e].name);
				printf("                                                �ܳ���Ϊ: %d��\n\n", dis);
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
		printf("                                                �����������:");
		scanf_s("%d", &b);
		if (Judge(b))
			break;
	}
	while (1)
	{
		printf("\n");
		printf("                                                �������յ���:");
		scanf_s("%d", &e);
		if (Judge(e))
			break;
	}
	printf("\n");
	Allpath(g, b, e);
	printf("\n");
}
/*********************************************************�ྰ�������·��*****************************************************************/
void bestpath(Mgraph *g)
{
	int b;
	int vnum[M] = { 0 }, j = 1;
	int i, d = 0;
	while (1)
	{
		printf("\n");
		printf("                                                ������Ҫ��ѯ�ĵ�%d������ı��(����0��������):", j);
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
			printf("                                                ������Ҫ�����ĵ�%d��������:", j);
			scanf_s("%d", &b);
			vnum[j - 1] = b + 1;
			if (Judge(vnum[j - 1]))
				break;
		}
		printf("\n");
	}
	printf("                                                ������ѷ���·��:");
	for (i = 0; vnum[i] > 0 && vnum[i + 1] > 0; i++)
	{
		printf("%s->", g->vertex[vnum[i] - 1].name);
		floyde_print(g, vnum[i] - 1, vnum[i + 1] - 1);
		d += dist[vnum[i] - 1][vnum[i + 1] - 1];
	}

	printf("%s\n\n", g->vertex[vnum[j - 2] - 1].name);
	printf("\n");
	printf("                                                ȫ��·��Ϊ: %d��\n", d);
}
/*********************************************************��ȱ���Ѱ�ҹؽڵ�***************************************************************/
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

/**********************************************************��У԰ͼ��ͨͼ�ؽڵ�************************************************************/
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
	printf("                                                У԰ͼ�ؽڵ����Ϊ: %d\n\n                                                �ֱ�Ϊ:", coilanum);
	for (i = 0; i < g->n; i++)
	{
		if (coila[i] == COILA)
		{
			printf("%s\t", g->vertex[i].name);
		}
	}
	printf("\n");
}

/*******************************************************ƽ��ͼ******************************************************************************/
int printplan()
{
	printf("                                                                                                                                                         \n");
	printf("                                                                                    �б���ѧУ԰����ƽ��ͼ                                               \n");
	printf("                                                ===================================================================================================      \n");
	printf("                                                                               7.��Ӿ��---------8.�褹�������------------------------9.��ɽ����           \n");
	printf("                                                                                                      |                                  |               \n");
	printf("                                                                                                      |                                  |               \n");
	printf("                                                                                                      |                                  |               \n");
	printf("                                                                                                      |                                  |               \n");
	printf("                                                                               5.ͼ���---------------��                                  |               \n");
	printf("                                                                                    |                                                    |               \n");
	printf("                                                                                    |                                                    |               \n");
	printf("                                                                                    |                                                    |               \n");
	printf("                                              4.����ɽ------��----------------------��------------��                                        |               \n");
	printf("                                                            |                                 6.��֪�㳡---------------------------------|               \n");
	printf("                                                            |                                     |                                      |               \n");
	printf("                                                            |                                     |                                      |               \n");
	printf("                                              1.����԰------��                                    ��------- 2.��·��԰                     |               \n");
	printf("                                                            |                                                  |                         |               \n");
	printf("                                                            |                                                  |                         |               \n");
	printf("                                                            |                                                  |                         |               \n");
	printf("                                                            |                                                  |-----------------------3.�б��Ƶ�          \n");
	printf("                                                            |                                                  |                                         \n");
	printf("                                                            |                                                  |                                         \n");
	printf("                                                            |                                                  |                                         \n");
	printf("                                                         0.�»�¥---------------------------------------------��                                         \n");
	printf("                                                            |                                                                                            \n");
	printf("                                                ===================================================================================================      \n");
	system("pause");
	return 0;
}

/********************************************************���˵�*****************************************************************************/
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
	printf("                                                * *                         ��ӭʹ���б���ѧУ԰����ϵͳ                              * *\n");
	printf("                                                * *                                                                                   * *\n");
	printf("                                                * *                             ��ѡ������Ҫ�Ĺ���:                                   * *\n");
	printf("                                                * *                                                                                   * *\n");
	printf("                                                * *             1.ѧУƽ��ͼ                      5.������֮������·��                * *\n");
	printf("                                                * *                                                                                   * *\n");
	printf("                                                * *             2.��ʾ�����ż�����              6.;���ྰ������·��              * *\n");
	printf("                                                * *                                                                                   * *\n");
	printf("                                                * *             3.��Ҫ������Ϣ����                7.У԰ͼ�ؽڵ�                      * *\n");
	printf("                                                * *                                                                                   * *\n");
	printf("                                                * *             4.Ѱ��������֮�����̾���        8.�˳�ϵͳ                          * *\n");
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
/**************************************************************����ѡ��*********************************************************************/
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
			printf("                                                ��������Ҫ�Ĳ���:");
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
			printf("\t\t                                �Բ���û������Ӧ�Ĳ�����\n\n");
			system("pause");
			system("cls");
			break;
		}
	}
}
/************************************************************���ԣ���������*****************************************************************/
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