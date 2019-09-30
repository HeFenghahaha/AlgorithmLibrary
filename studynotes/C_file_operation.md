# C语言中文件的相关读写操作

```c
#include<stdio.h>
struct Student
{
    int num;
    char name[10];
    int age;
    char school[15];
};
int main()
{
    FILE *fp1=fopen("C:\\Users\\28020\\Desktop\\新建文本文档.txt","r");//读取文件
    FILE *fp2=fopen("C:\\Users\\28020\\Desktop\\text.txt","r");//读取文件
    FILE *fp3=fopen("C:\\Users\\28020\\Desktop\\text2.txt","w");//写入文件
    FILE *fp4=fopen("C:\\Users\\28020\\Desktop\\text3.txt","r");
    //打开文件，文件路径必须用双斜线(转义)
    /*if(fp2==NULL)    //判断文件打开成功与否，空指针说明失败
    {
        printf("打开文件失败！\n\n");
        exit(0);
    }
    printf("打开文件成功！\n\n");*/

    //字符方式读取文件数据并输出到屏幕
    /*puts("文件fp1里面的内容是：");
    char ch;
    while(!feof(fp1))//feof(fp1)为0时文件未结束
    {
        ch=fgetc(fp1);
        putchar(ch);
    }
    puts("\n");*/

    //格式化读取并保存到数组中
    int a[100],i,j;

    //读取整型数据并存到一维数组中:
    //puts("将fp1文件中的数据读取后保存在一维数组中,数组中各元素值为：");
    //第一种形式:
    /*for(i=0;fscanf(fp1,"%d",&a[i])!=EOF;i++)
        printf("%d ",a[i]);
    puts("\n");*/
    //第二种形式:
    /*i=0;
    while(!feof(fp1))
    {
        fscanf(fp1,"%d",&a[i]);
        printf("%d ",a[i++]);
    }
    puts("\n");*/

    //读取整型数据并存到二维数组中:
    int b[30][30];
    for(i=0;i<3;i++)
        for(j=0;j<6;j++)
            fscanf(fp2,"%d",&b[i][j]);
    puts("将fp2文件中的数据读取后保存在二维数组中,数组中各元素值为：");
    for(i=0;i<3;i++)
    {
        for(j=0;j<6;j++)
            printf("%d\t",b[i][j]);
        printf("\n");
    }
    puts("\n");

    //将一维数组里面的数据写入到文件fp3中
    int c[5]={1,2,3,4,5};
    fprintf(fp3,"一维数组:\n");
    for(i=0;i<5;i++)
        fprintf(fp3,"%d  ",c[i]);
    fprintf(fp3,"\n\n");

    //将二维数组里面的数据写入到文件fp3中
    fprintf(fp3,"二维数组:\n");
    for(i=0;i<3;i++)
    {
        for(j=0;j<6;j++)
            fprintf(fp3,"%d ",b[i][j]);
        fprintf(fp3,"\n");
    }

    /*int m=fclose(fp2);//判断文件关闭成功与否，fclose()返回值为0时关闭成功
    if(m)
    {
        printf("关闭文件失败！\n\n");
        exit(0);
    }
    printf("关闭文件成功！\n\n");*/

    //将文件里面的内容读取并存到结构体数组中
    struct Student stu[10];
    puts("文件text3.txt里面的内容是:");
    puts("number\tname");
    //第一种形式:
    /*for(int i=0;fscanf(fp4,"%d%s\n",&stu[i].num,&stu[i].name)!=EOF;i++)
        printf("%d\t%s\n",stu[i].num,stu[i].name);*/
    //第二种形式:
    int p=0;
    while(!feof(fp4))
    {
        fscanf(fp4,"%d%s\n",&stu[i].num,&stu[i].name);
        printf("%d\t%s\n",stu[i].num,stu[i].name);
        p++;
    }
    puts("\n");

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    return 0;
}
```