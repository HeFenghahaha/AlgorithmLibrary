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
	const char *name,*disc;
} vertextype;
typedef struct
{
	vertextype vertex[M];
	edgetype edges[M][M];
	int beauties[M];
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
void dfspath(Mgraph *g, int b, int e);        //������֮������·��
void allpath(Mgraph *g);               //�������·��
                                      //;���ྰ�����·��
void Dfs_coila(Mgraph *g, int i);             //�ؽڵ�
void Coila_search(Mgraph *g);                //У԰ͼ�ؽڵ�
int printplan();                             //���ƽ��ͼ
int menu();                                  //������˵�
int main();                                  //����������ʵ��
/*************************************************************����ͼ��������Ϣ*********************************************************/
void Creat(Mgraph *g)
{
	int i, j;
	g->n = 10;
	g->e = 14;
	for (i = 0; i < g->n; i++)
		g->vertex[i].num = i;
	g->vertex[0].name= "�»�¥";
	g->vertex[0].disc = "�»�¥λ��ѧУ���ŵ���ǰ�����ǽ���ѧУǰ�ĵ�һ�������ķ羰��!\n";
	g->vertex[1].name = "����԰";
	g->vertex[1].disc = "����԰λ���б���ѧ�����ߣ����ж���ɽ�����ٷں�ˮ������̫ԭ��ʤ���������ɽ��ˮ���羰��!\n";
	g->vertex[2].name = "��·��԰";
	g->vertex[2].disc = "��·��԰λ��ѧУ�в��������Ŷ��࣬���½��ɵģ��������߲�������Ƥ�𳵣���·�źŵƣ����ܵȣ������Ƿ·�Խ���Ǹ����ϹŶ����������ڵ����!\n";
	g->vertex[3].name = "�б��Ƶ�";
	g->vertex[3].disc= "�б��Ƶ�λ��ѧУ���ϲ���Ϊ�ο��ṩ�˱�������ѧУ�ھͿ����ҵ���Ϣ֮��!\n";
	g->vertex[4].name = "����ɽ";
	g->vertex[4].disc = " �б���ѧ��ɽ��ˮ��У���к���������У����һ��ɽ���ڽӣ����ж���ɽ��λ��ѧУ�����ߣ�ѧ������ʦ���ο;�����ɽ���������壬�Ǹ���Զ��ɽ���г��ȡ��ٲ������С��б���ѧ���ĸ����֣�����ɽ������ʿɽ����ɫ�����������еĺ�У԰�����еķ羰��!\n";
	g->vertex[5].name = "ͼ���";
	g->vertex[5].disc = "�б���ѧͼ�����ɽ��ʡ����ͼ��ݣ�λ����������11��¥���࣬����7��¥�����е����ң������ղ��д�����ͼ�飬ͼ����⻹��Ư������Ȫ��������ѧ���������ſڹ��ͼ��ۣ��ر�����ͼ�����һ��ѧϰ�ĺõط���ͬѧ�ǿ��Ծ����������֪ʶ�ĺ����\n";
	g->vertex[6].name = "��֪�㳡";
	g->vertex[6].disc = "��֪�㳡λ����¥�ϲ࣬�㳡����󣬿��Ծٰ�һЩ���͵�ԺУ������ϵ���֪�㳡�ر����֣���Ҳ�ܶ࣬ѧ�����ڹ㳡�������衢�����衢�����ٵ�;��֪�㳡λ�ڴ�ѧ�����ģ�ӣ����������֪�㳡���ԡ�\n";
	g->vertex[7].name= "��Ӿ��";
	g->vertex[7].disc = "��Ӿ��λ��ѧУ��ߣ�����Ӿ������ѧ������ѧϰ��Ӿ���������壬������������Ҳ��ѧ������Ӿ�εĵط���\n";
	g->vertex[8].name = "�褹�������";
	g->vertex[8].disc = "�褹��ʻ�������λ��ѧУ��ߣ�����Ӿ�����棬���ﳣ��һЩԺ������У�����ش���飬ѧУ���ָ߲��쵼�����ϯ����;�褹����������б���ѧ����ѧ������������������˸�����СС�Ļ��\n";
	g->vertex[9].name = "��ɽ����";
	g->vertex[9].disc = "��ɽ����λ��ѧУ�����棬ȫУ���������Ĳ�������Ҫ�ǹ�������ѧ����ʦ�òͣ��������зḻ��ζ�ĸ��ּ��ȣ�������ϵ�ḻ��������ζ��������������;��ɽ�����������㣬���Ĳ�������ʽ��������ζ���һ��!\n";
	for (i = 0; i < g->n; i++)
		for (j = 0; j < g->n; j++)
			if (i == j) g->edges[i][j] = 0;
			else g->edges[i][j] = FINITY;
	g->edges[0][1] = g->edges[1][0] = 250;  //a0
	g->edges[0][2] = g->edges[2][0] = 300;  //a1
	g->edges[0][3] = g->edges[3][0] = 500;  //a2
	g->edges[1][4] = g->edges[4][1] = 350;  //a3
	g->edges[4][5] = g->edges[5][4] = 900;  //a4
	g->edges[5][6] = g->edges[6][5] = 50;   //a5
	g->edges[2][3] = g->edges[3][2] = 280;  //a7
	g->edges[2][6] = g->edges[6][2] = 150;  //a8
	g->edges[7][8] = g->edges[8][7] = 400;  //a9
	g->edges[5][8] = g->edges[8][5] = 250;  //a10
	g->edges[8][9] = g->edges[9][8] = 500;  //a11
	g->edges[6][9] = g->edges[9][6] = 800;  //a12
	g->edges[3][9] = g->edges[9][3] = 1000; //a13
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
//���������������·��
int pathstack[M], top, count;             //ȫ�ֱ�����pathstack[M]��һ��ջ�����������㣬count�Ǽ�����
int visited[M] = { 0 };                          //ȫ�ֱ���,������Ƕ����Ƿ񱻷��ʹ������Ϊ0��δ���ʣ����Ϊ1���ѷ���
void dfspath(Mgraph *g, int b, int e)     //��ȱ�������·��   
{
	int i, j, dis = 0;                   //��ʼ������disΪ0
	pathstack[top++] = b;               //�ѽ��b����ջ��
	visited[b] = 1;                     //��b���Ϊ�ѷ���
	for (i = 0; i < g->n; i++)
	{
		if (g->edges[b][i] > 0 && g->edges[b][i] != FINITY && !visited[i])     //���b�����i��·�ҽ��iδ���ʹ�
		{
			if (i == e)                       //��ѯ���յ�e
			{
				printf("                                                ��%d��·:", count++);
				for (j = 0; j < top; j++)
				{
					printf("%s->", g->vertex[pathstack[j]].name);     //��ջ�׿�ʼ������н�������
					if (j < top - 1)
						dis = dis + g->edges[pathstack[j]][pathstack[j + 1]];   //�����ܳ���
				}
				dis = dis + g->edges[pathstack[top - 1]][e];           //�ܳ��Ȼ��ü���ջ����㵽�յ�e�ĳ���
				printf("%s\n", g->vertex[e].name);                     //����յ������
				printf("                                                �ܳ���Ϊ: %d��\n\n", dis);
			}
			else
			{
				dfspath(g, i, e);         //�ӽ��i��ʼ�ٽ�����ȱ���
				top--;                    //��ջ��Ԫ�س�ջ
				visited[i] = 0;           //�ѽ��i���±��Ϊδ���� 
			}
		}
	}
}
void allpath(Mgraph *g)
{
	int b, e;               //���Ϊb,�յ�Ϊe
	count = 1;top = 0;
	while (1)
	{
		printf("                                                �����������:");
		scanf_s("%d", &b);
		if (Judge(b))     //�ж�����ı���Ƿ���ȷ
			 break;
	}
	while (1)
	{
		printf("                                                �������յ���:");
		scanf_s("%d", &e);  
		if (Judge(e))    //�ж�����ı���Ƿ���ȷ
			break;
	}
	printf("\n");
	dfspath(g, b, e);
	printf("                                                ��%s����%sһ��������%d��·����ѡ��\n", g->vertex[b].name, g->vertex[e].name, count - 1);
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
			allpath(&g);
			system("pause");
			system("cls");
			break;
		case 6:
			system("cls");
			printplan();
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
	select();
	system("pause");
	return 0;
}