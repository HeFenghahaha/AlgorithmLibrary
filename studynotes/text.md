# 作业四：0-1背包问题的分支限界法

```c
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
const int N=100; 
class Node    //节点的数据结构
{
public:
    Node()   //默认构造函数
    {
        value = 0;
        weight = 0;
        level = 0;
        parent = 0;
        bound = 0;
    }
    float value;           //搜索到该节点时的总价值
    float weight;          //搜索到该节点时的总重量
    float bound;           //该节点的价值上界
    int level;             //该节点所处层次，从0开始
    Node *parent;  //指向父节点
};
struct cmp
{
    bool operator () (Node *a, Node *b) 
    {
        return a->bound < b->bound;
    }
};
class Item
{
public:
    float v;			//物品价值
    float   		//物品重量
};
Item items[N]; 
bool ItemCmp(Item item1, Item item2) //按价值重量比从大到小排列
{
    return item1.v/item1.w >item2.v/item2.w ;
}
float branchAndBound(Item items[], float c,int n);        //函数声明
float maxBound(Node *node, Item items[], float c,int n);  //函数声明

int main()
{
    int n;
    cout<<"请输入物品个数:";
    cin>>n;
    float c;
    cout<<"请输入背包容量:";
    cin>>c;
    cout<<"请输入各物品的重量和价值:"<<endl;
    for(int i=0;i<n;i++)
        cin>>items[i].w>>items[i].v;
    sort(items,items+n,ItemCmp);         //按价值率排序
    puts("\n\n物品\t\t重量\t\t价值\t\t价值/重量");
    for (int i = 0; i < n; i++) 
    {
        printf("%2d\t\t%.2f\t\t%.2f\t\t   %.2f\n",i+1,items[i].w,items[i].v,items[i].v/items[i].w);
    }
    cout << "选取方案为:(1表示物品装入，0表示物品未装入)" << endl;
    float maxValue=branchAndBound(items,c,n);
    cout <<endl<< "最大价值为:" << maxValue << endl;
    return 0;
}

float branchAndBound(Item items[], float c,int n)
{
    int x[N] ={0};
    float maxValue;                            //保存当前搜索到的最大价值
    Node *maxNode = new Node();                           //保存当前最大价值节点（叶节点）
    priority_queue<Node *, vector<Node *>, cmp> maxQueue; //最大价值优先队列
    Node *firstNode, *curNode;

    firstNode = new Node();
    firstNode->bound = maxBound(firstNode,items,c,n);
    firstNode->parent = NULL;
    maxQueue.push(firstNode); //入队第一个结点
    maxValue = 0;
    maxNode = firstNode;
    while (!maxQueue.empty())
    {
        curNode = maxQueue.top(); maxQueue.pop();
        //扩展左孩子结点
        if (curNode->weight + items[curNode->level].w <= c)
        {   //最大重量限界
            Node *leftNode = new Node();
            leftNode->value = curNode->value + items[curNode->level].v;
            leftNode->weight = curNode->weight + items[curNode->level].w;
            leftNode->level = curNode->level + 1;
            leftNode->parent = curNode;
            leftNode->bound =curNode->bound ;
            if (leftNode->level<n) 
            {
                maxQueue.push(leftNode);
            }
            if (maxValue < leftNode->value)
            {
                maxValue = leftNode->value;
                maxNode = leftNode;
            }
        }
        //扩展右孩子结点
        if (maxBound(curNode, items, c,n)>maxValue)
        { //最大价值上界限界
            Node *rightNode = new Node();
            rightNode->value = curNode->value;
            rightNode->weight = curNode->weight;
            rightNode->level = curNode->level + 1;
            rightNode->parent = curNode;
            rightNode->bound = maxBound(rightNode,items,c,n);
            if (rightNode->level < n) 
                maxQueue.push(rightNode);
        }
    }
        curNode = maxNode;
        while (curNode) 
        {
            int tempValue = curNode->value;
            curNode = curNode->parent;
            if (curNode && curNode->value != tempValue)
                x[curNode->level] = 1;
        }
        for (int i = 0; i < n; i++) //输出x数组
            cout << x[i] << " ";
        cout<<endl;
        for (int i = 0; i < n; i++)
            if(x[i])
                printf("物品%d被放入背包\n",i+1);
        cout << endl;
        return maxValue;
}
//限界函数
float maxBound(Node *node, Item items[], float c,int n)
{   //求以该节点为根的子树能达到的价值上界
    float maxValue,restc;//扩展到该节点时的剩余容量
    int i;
    maxValue = node->value;
    restc = c - node->weight;
    i = node->level;
    while (i<n && restc>items[i].w) 
    {
        maxValue += items[i].v;
        restc-= items[i].w;
        i++;
    }
    if (restc!= 0) 
    {
        maxValue += restc*(items[i].v/items[i].w);
    }
    return maxValue;
}
```