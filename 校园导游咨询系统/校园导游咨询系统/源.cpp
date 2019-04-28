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
/**************************************************函数预览表*************************************************************************/
void Creat(Mgraph *g);                       //创建一个图
int Judge(int numb);                         //判断编号输入是否合理
void printnum(Mgraph *g);                    //输出编号以及名称;
void Search(Mgraph *g);                      //查看景点信息
void shortpath(Mgraph *g);                   //两景点之间最短路径
void floyde_print(Mgraph *g, int b, int e);    //Floyde求最短路径
void print_shortpath(Mgraph *g);             //最短路径输出函数
void dfspath(Mgraph *g, int b, int e);        //两景点之间所有路径
void allpath(Mgraph *g);               //输出所有路径
                                      //途经多景点最佳路径
void Dfs_coila(Mgraph *g, int i);             //关节点
void Coila_search(Mgraph *g);                //校园图关节点
int printplan();                             //输出平面图
int menu();                                  //输出主菜单
int main();                                  //主函数功能实现
/*************************************************************创建图并读入信息*********************************************************/
void Creat(Mgraph *g)
{
	int i, j;
	g->n = 10;
	g->e = 14;
	for (i = 0; i < g->n; i++)
		g->vertex[i].num = i;
	g->vertex[0].name= "德怀楼";
	g->vertex[0].disc = "德怀楼位于学校大门的正前方，是进入学校前的第一道亮丽的风景线!\n";
	g->vertex[1].name = "柏林园";
	g->vertex[1].disc = "柏林园位于中北大学最西边，西倚二龙山，南临汾河水，毗邻太原名胜窦大夫祠，青山碧水，风景旖旎!\n";
	g->vertex[2].name = "铁路公园";
	g->vertex[2].disc = "铁路公园位于学校中部，二道门东侧，是新建成的，铁轨沿线布置了绿皮火车，铁路信号灯，雕塑等，让我们仿佛穿越回那个“老古董”曾经存在的年代!\n";
	g->vertex[3].name = "中北酒店";
	g->vertex[3].disc= "中北酒店位于学校东南部，为游客提供了便利，在学校内就可以找到休息之地!\n";
	g->vertex[4].name = "二龙山";
	g->vertex[4].disc = " 中北大学依山傍水，校外有河流经过，校内与一座山相邻接，名叫二龙山，位于学校最西边，学生、老师、游客均可爬山，锻炼身体，登高望远；山上有长廊、瀑布，还有“中北大学”四个大字，二龙山又名烈士山，景色秀丽，是少有的和校园相依托的风景区!\n";
	g->vertex[5].name = "图书馆";
	g->vertex[5].disc = "中北大学图书馆是山西省最大的图书馆，位于中央大道，11号楼西侧，共有7层楼，还有地下室，里面收藏有大量的图书，图书馆外还有漂亮的喷泉，来往的学生都会在门口观赏几眼，特别美；图书馆是一个学习的好地方，同学们可以尽情地遨游在知识的海洋里！\n";
	g->vertex[6].name = "行知广场";
	g->vertex[6].disc = "行知广场位于主楼南侧，广场面积大，可以举办一些大型的院校活动；晚上的行知广场特别热闹，人也很多，学生可在广场上练跳舞、练唱歌、吹口琴等;行知广场位于大学的中心，樱花树立在行知广场两旁。\n";
	g->vertex[7].name= "游泳馆";
	g->vertex[7].disc = "游泳馆位于学校最北边，在游泳馆里面学生可以学习游泳，锻炼身体，放松情绪；这也是学生上游泳课的地方！\n";
	g->vertex[8].name = "瑾瑜国际中心";
	g->vertex[8].disc = "瑾瑜国际会议中心位于学校最北边，在游泳馆西面，这里常开一些院级或者校级的重大会议，学校部分高层领导都会出席会议;瑾瑜国际中心是中北大学最大的学术报告厅，里面记载了各项大大小小的活动！\n";
	g->vertex[9].name = "龙山餐厅";
	g->vertex[9].disc = "龙山餐厅位于学校东北面，全校最大、最豪华的餐厅，主要是供东区的学生教师用餐，餐厅里有丰富美味的各种佳肴，不但菜系丰富，而且美味至极，让人难忘;龙山餐厅具有三层，宽敞的餐厅，各式各样的美味别具一格!\n";
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
//任意两结点间的所有路径
int pathstack[M], top, count;             //全局变量，pathstack[M]是一个栈，用来保存结点，count是计数器
int visited[M] = { 0 };                          //全局变量,用来标记顶点是否被访问过，标记为0是未访问，标记为1是已访问
void dfspath(Mgraph *g, int b, int e)     //深度遍历所有路径   
{
	int i, j, dis = 0;                   //初始化长度dis为0
	pathstack[top++] = b;               //把结点b加入栈中
	visited[b] = 1;                     //把b标记为已访问
	for (i = 0; i < g->n; i++)
	{
		if (g->edges[b][i] > 0 && g->edges[b][i] != FINITY && !visited[i])     //结点b到结点i有路且结点i未访问过
		{
			if (i == e)                       //查询到终点e
			{
				printf("                                                第%d条路:", count++);
				for (j = 0; j < top; j++)
				{
					printf("%s->", g->vertex[pathstack[j]].name);     //从栈底开始输出所有结点的名字
					if (j < top - 1)
						dis = dis + g->edges[pathstack[j]][pathstack[j + 1]];   //计算总长度
				}
				dis = dis + g->edges[pathstack[top - 1]][e];           //总长度还得加上栈顶结点到终点e的长度
				printf("%s\n", g->vertex[e].name);                     //输出终点的名字
				printf("                                                总长度为: %d米\n\n", dis);
			}
			else
			{
				dfspath(g, i, e);         //从结点i开始再进行深度遍历
				top--;                    //将栈顶元素出栈
				visited[i] = 0;           //把结点i重新标记为未访问 
			}
		}
	}
}
void allpath(Mgraph *g)
{
	int b, e;               //起点为b,终点为e
	count = 1;top = 0;
	while (1)
	{
		printf("                                                请输入起点编号:");
		scanf_s("%d", &b);
		if (Judge(b))     //判断输入的编号是否正确
			 break;
	}
	while (1)
	{
		printf("                                                请输入终点编号:");
		scanf_s("%d", &e);  
		if (Judge(e))    //判断输入的编号是否正确
			break;
	}
	printf("\n");
	dfspath(g, b, e);
	printf("                                                从%s到达%s一共有以上%d条路可以选择！\n", g->vertex[b].name, g->vertex[e].name, count - 1);
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
	select();
	system("pause");
	return 0;
}