# Java中String类的一些函数的用法

## 1.1 String类对象的声明及创建

```java
String s1=new String("we are students")；

String s2 = "we are students";

String s3 = new String(s1);

String s4 = new String(char a[]);

String s5 = new String(char a[],int startIndex,int count)
```

## 1.2 字符串的常用方法

```java
--public int length()
```

length()方法可以获取一个字符串的长度 ,如：String tom= "我们是学生";   tom.length()的值5。

```java
--public boolean equals(String s)
```

字符串对象调用String类中的equals方法，比较当前字符串对象的内容是否与参数指定的字符串s的内容相同。如：
```java
String tom=new String( "we are students");

String boy=new String( "We are students");

String jerry= new String("we are students");

```

tom.equals(boy)的值是false

tom.equals(jerry)的值是true

注意:  == 与 equals之间的区别：equals判断两个字符串的内容是否相同，而==是判断两个字符串变量的值(引用值)是否相同。 

```java
--public boolean startsWith(String s)
```

字符串对象调用startsWith(String s)方法，判断当前字符串对象的前缀是否是参数指定的字符串s。

```java
--public boolean endsWith(String s)
```

字符串对象调用endsWith(String s) 方法，判断当前字符串的后缀是否是字符串s。

```java
--public boolean regionMatches(int firstStart,String other,int otherStart,int length)
```

从当前字符串参数firstStart指定的位置开始处，取长度为length的一个子串，从other字符串参数othertStart指定的位置开始，取长度为length的另一个子串，如果两个子串相同返回true，否则返回false。

```java
--public int compareTo（String s）
```

字符串对象可以使用String类中的compareTo（String s）方法，按字典序与参数s指定的字符串比较大小。如果当前字符串与s相同，该方法返回值0；如果当前字符串对象大于s，该方法返回正值；如果小于s，该方法返回负值。 

```java
--public int indexOf (String s)
```

字符串调用该方法从当前字符串的头开始检索字符串s，并返回首次出现s的位置。

```java
--public int indexOf(String s ,int startpoint)
```

字符串调用该方法从当前字符串的startpoint位置处开始检索字符串s，并返回首次出现s的位置。

```java
--public int lastIndexOf (String s)
```

字符串调用lastIndexOf (String s)方法从当前字符串的头开始检索字符串s，并返回最后出现s的位置。
注意：如果没有检索到字符串s,返回值为-1。

```java
--public String substring(int start)
```

字符串对象调用该方法获得一个当前字符串的子串，该子串是从当前字符串的start处截取到字符串的末尾所得到的字符串。字符串对象调用substring(int start ,int end)方法获得一个当前字符串的子串，该子串是从当前字符串的start处截取到end处所得到的字符串(start~end-1)，但不包括end处所对应的字符。

```java
--public String  replaceAll(String oldString ,String newString)
```

字符串对象s调用该方法可以获得一个串对象，这个串对象是通过用参数newString指定的字符串替换s中由oldString指定的所有字符串而得到的字符串。

```java
--public String trim()
```

一个字符串s通过调用方法trim()得到一个字符串对象，该字符串对象是s去掉前后空格后的字符串。

## 1.3 字符串与基本数据的相互转化 


使用java.lang包中的Byte、Short、Integer 、 Long、Float、Double类调相应的类方法，可以将“数字”格式的字符串，转化为相应的基本数据类型。 相对应的方法如下：

```java
--public static  byte  parseByte(String  s) throws NumberFormatException
--public static  short  parseShort(String  s) throws NumberFormatException
--public static  int  parseInt(String  s) throws NumberFormatException
--public static  long  parseLong(String  s) throws NumberFormatException
--public static  float  parseFloat(String  s) throws NumberFormatException
--public static  double  parseDouble(String  s) throws NumberFormatException 
```

## 1.4 对象的字符串表示 

在子类的讲述中我们讲过，所有的类都默认是java.lang包中Object类的子类或间接子类。Object类有一个public 方法toString()，一个对象通过调用该方法可以获得该对象的字符串表示。

## 1.5 StringTokenizer类

当我们分析一个字符串并将字符串分解成可被独立使用的单词时，可以使用java.util中的StringTokenizer类.
  
参数dilim中的字符被作为分隔符.
我们把一个StringTokenizer对象称作一个字符串分析器.

```java
--public String nextToken()
```

一个分析器可以使用该方法逐个获取字符串中的语言符号（单词），每当调用nextToken()时，都将在字符串中获得下一个语言符号。

```java
### --public boolean hasMoreTokens()
```

一个分析器可以使用该方法来判断是否还可以获取语言符号。

## 1.6 字符串与字符、字节数组

```java
--public void getChars(int start,int end,char c[],int offset )  
```

字符串调用getChars方法将当前字符串中的一部分字符拷贝到参数c指定的数组中。将字符串中从位置start到end-1位置上的字符拷贝的数组c中，并从数组c的offset处开始存放这些字符。
注意：必须保证数组c能容纳下要被拷贝的字符。

```java
--public byte[]  getBytes() 使用平台默认的字符编码，将当前字符串转化为一个字节数组。
--public char[] toCharArray()  
```

字符串对象调用该方法可以初始化一个字符数组，该数组的长度与字符串的长度相等，并将字符串对象的全部字符拷贝到该数组中。

## 1.7 StringBuffer类

String类创建的字符串对象是不可修改的，也就是说，String字符串不能修改、删除或替换字符串中的某个字符，即String对象一旦创建，那么实体是不可以再发生变化的。
StringBuffer类能创建可修改的字符串序列，也就是说，该类的对象的实体的内存空间可以自动的改变大小，便于存放一个可变的字符序列。  

## 1.8 正则表达式

一个正则表达式是含有一些具有特殊意义字符的字符串，这些特殊字符称作正则表达式中的元字符。比如，“\\dhello”中的\\d就是有特殊意义的元字符，代表0到9中的任何一个。字符串“9hello”和“1hello”都是和正则表达式：“\\dhello”匹配的字符串之一。
字符串对象调用public boolean matches(String regex)
方法可以判断当前字符串对象是否和参数regex指的正则表达式匹配。

