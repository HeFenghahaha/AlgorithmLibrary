# Java中Vector(向量类)的一些常用方法

```java
package test5;

import java.util.Enumeration;
import java.util.Iterator;
import java.util.Vector;
class Practice 
{
    void creatVector()
    {
        Vector<Integer> myvector=new Vector<Integer>();
        myvector.add(1);
        myvector.add(2);
        myvector.add(3);
        myvector.add(4);
        myvector.add(5);
        myvector.add(6);
        myvector.addElement(7);
        myvector.addElement(new Integer(8));
        myvector.add(4,9);//在下标4的位置添加元素9，其他元素依次顺延
        printVector(myvector);
        queryElement(myvector);
        deleteElement(myvector);
    }
    void queryElement(Vector<Integer> myvector)
    {
        System.out.println("元素值为3的下标是："+myvector.indexOf(3));//返回值为3的元素的下标(没有找到返回-1)
        System.out.println("元素值为3的下标是："+myvector.indexOf(3,1));//从下标为1的元素开始查找值为3的元素并返回其下标
        System.out.println("元素值为3的下标是："+myvector.lastIndexOf(3));//从向量尾部开始逆向搜索值为3的元素并返回其下标
        System.out.println("元素值为3的下标是："+myvector.lastIndexOf(3, 1));//从下标1处由尾至头逆向搜索值为3的元素并返回其下标 
        System.out.println("第一个元素的值："+myvector.firstElement());//向量的第一个元素
        System.out.println("最后一个元素的值："+myvector.lastElement());//向量的最后一个元素
        System.out.println("当前向量中元素的个数："+myvector.size());//向量中元素的个数
    }
    void deleteElement(Vector<Integer> myvector)
    {
        myvector.removeElement(1);//删除值为1的元素
        printVector(myvector);
        System.out.println("删除值为1的元素后，元素个数："+myvector.size());
        myvector.remove(0);//删除下标为0的元素
        printVector(myvector);
        System.out.println("删除下标为0的元素后，元素个数："+myvector.size());
        myvector.removeElementAt(3);//删除下标为3的元素
        printVector(myvector);
        System.out.println("删除下标为3的元素后，元素个数："+myvector.size());
        myvector.removeAllElements();//删除所有元素
        System.out.println("删除所有元素后，元素个数："+myvector.size());
    }
    void printVector(Vector<Integer> mv)
    {
        //遍历向量的第一种方法:此方法将向量对象对应到一个枚举类型
        /*Enumeration<Integer> elements=mv.elements();
        while(elements.hasMoreElements())//判断集合中是否还有元素
            System.out.printf("%d,",elements.nextElement());//获取下一个元素
        System.out.println();*/

        //遍历向量的第二种方法:此方法将向量对象对应到一个迭代器
        Iterator<Integer> iterator=mv.iterator();
        while(iterator.hasNext())//判断是否还有元素
            System.out.printf("%d,",iterator.next());//获取下一个元素
        System.out.println();
    }
}

public class MyVector
{
    public static void main(String[] args)
    {
        Practice practice=new Practice();
        practice.creatVector();
    }
}
```