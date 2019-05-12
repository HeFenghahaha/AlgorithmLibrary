# 优先队列的相关函数

```c
#include<iostream>
#include<queue>
using namespace std;
struct node
{
    friend bool operator < (node n1,node n2)
    {
        return n1.priority<n2.priority;
        //如果是小于号，按优先级值从大到小创建队列
        //如果是大于号，按优先级值从小到大创建队列
    }
    int priority;//优先级值
    int v;
};
int main()
{
    priority_queue<int> q1;//从大到小创建，即顶点元素为最大值
    for(int i=1;i<=5;i++)
        q1.push(i);        //添加元素到优先队列中
    int len=q1.size();     //队列中元素个数
    for(int i=1;i<=len;i++)
    {
        cout<<q1.top()<<" ";//输出顶点元素的值
        q1.pop();           //删除顶点元素
    }
    cout<<endl;

    priority_queue<int,vector<int>,greater<int>> q2;
    //从小到大创建，即顶点元素为最小值
    for(int i=6;i<=10;i++)
        q2.push(i);
    //int l=q2.size();
    while(q2.empty()!=1)
    //判断队列是否为空，队列非空时继续操作
    {
        cout<<q2.top()<<" ";
        q2.pop();
    }

    cout<<endl;
    priority_queue<node> q3;
    node b[5];
    b[0].priority=5;b[0].v=1;
    b[1].priority=9;b[1].v=2;
    b[2].priority=3;b[2].v=3;
    b[3].priority=25;b[3].v=4;
    b[4].priority=1;b[4].v=5;
    for(int i=0;i<5;i++)
        q3.push(b[i]);
    //int size=q3.size();
    cout<<"优先级"<<"\t"<<"值"<<endl;
    while(q3.empty()!=1)
    {
        cout<<q3.top().priority<<"\t"<<q3.top().v<<endl;
        q3.pop();
    }
    return 0;
}
```