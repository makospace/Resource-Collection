# Resource-Collection
>不生产知识，只是知识的搬运工，收集全网优质学习资源 & 引流工程

[编程语言](##编程语言)

## 编程语言
## C++
> C++是用C语言实现的，在C语言的基础上进行改进和扩展的
- [C++面向对象程序设计](https://blog.csdn.net/weixin_44368437/article/details/117563488?spm=1001.2014.3001.5506)
- 
### 应用方向：
1. 嵌入式
2. 编译器
3. 图形学
   
## Go
> Go 语言在1.5版本前主要由汇编和C语言写的，C语言占比85%以上，另外有少量的周边模块如文档等，带了些 html shell perl 代码，可以忽略不计。1.5版本及之后，Go 完成了语言自举， 由 89.9% 的Go，4.6%的汇编语言，0.2%的C语言，5.3%其他胶水语言（html shell perl）编写而成！
> 
> 学习Go的协程可以加深对线程的认识，区别协程与线程，认识到协程的本质就是用户级线程
> Go语言的自举（self-hosting）是通过编写一个Go语言编译器来实现的。这个编译器可以用其他编程语言（如C或C++）编写，然后使用它来编译Go语言的源代码，生成一个新的Go语言编译器。新的编译器可以使用来编译更多的Go语言代码，以此类推，实现了自举。

>自举的过程如下：
>1. 使用C或C++编写一个最小的Go语言编译器，可以编译一个非常简单的Go语言程序。
>2. 使用这个最小的编译器编译更复杂的Go语言程序，生成一个更完整的Go语言编译器。
>3. 使用新生成的编译器编译更复杂的Go语言程序，生成一个更完整的Go语言编译器。
>4. 重复步骤3，直到生成一个完整的Go语言编译器。
>通过这个过程，Go语言的自举就完成了。现在，Go语言的开发者们可以使用这个自举的编译器来编译更多的Go语言代码，并将它们打包成可执行文件或库。
## Java
> 国企开发岗标准语言，封装完备，对标逻辑严密的大型业务
### Java基础
>JavaSE是Java Standard Edition的缩写，是Java平台的标准版，也是Java开发中最常用的版本。JavaSE提供了Java语言的核心API和JVM（Java虚拟机），包括基础类库、输入输出、网络通信、安全性、图形用户界面、多线程等功能，是Java开发的基础。JavaSE可以运行在各种操作系统上，包括Windows、Linux、Mac OS等。
   - [JavaSE总结](https://blog.csdn.net/Bb15070047748/article/details/119572236?spm=1001.2014.3001.5506)
   - [Java基础知识总结](https://blog.csdn.net/Pandafz1997/article/details/120865759?spm=1001.2014.3001.5506)
   - 
---
## 数学
### 概率
- [习题](./notes/Probability_Theory.md)
## 基础知识
### 操作系统
[CS-Notes](https://github.com/CyC2018/CS-Notes)

[内存分配](https://www.cnblogs.com/Li-F/p/11971571.html)

[文件系统.1](https://zhuanlan.zhihu.com/p/183238194)
[文件系统.2](http://ruanyifeng.com/blog/2011/12/inode.html)

---
### 数据结构
#### 树
  - [红黑树](https://blog.csdn.net/u014028063/article/details/84318349?spm=1001.2014.3001.5506)

[习题](./notes/shujvjiegou.md)
  
---
### 数据库
#### 模型
  - [依赖关系与范式](https://www.cnblogs.com/wsyjlly/p/10387413.html#:~:text=%E9%9D%9E%E5%B9%B3%E5%87%A1%E7%9A%84%E5%A4%9A%E5%80%BC%E4%BE%9D%E8%B5%96%EF%BC%9A%E8%8B%A5X%E2%80%94%3E%E2%80%94%3EY%EF%BC%8C,%E5%B9%B6%E4%B8%94X%EF%BC%8CY%EF%BC%8CZ%E6%98%AFU%E7%9A%84%E5%AD%90%E9%9B%86%EF%BC%8CZ%3DU-X-Y%EF%BC%8C%E8%8B%A5Z%E4%B8%8D%E4%B8%BA%E7%A9%BA%EF%BC%8C%E5%88%99%E7%A7%B0X%E2%80%94%3E%E2%80%94%3EY%E4%B8%BA%E9%9D%9E%E5%B9%B3%E5%87%A1%E7%9A%84%E5%A4%9A%E5%80%BC%E4%BE%9D%E8%B5%96%E3%80%82)

#### 索引
  - [底层实现](https://blog.csdn.net/wangfeijiu/article/details/113409719)

---
## 学业
### 学校排名
  1. 国企对学校的排名参照泰晤士
### 基本路线
  - [大学学习路线](https://blog.csdn.net/mengchuan6666/article/details/119062708)
- 
---
## 工具
### Docker
  - [菜鸟教程](https://www.runoob.com/docker/docker-tutorial.html)
   
### Redis
  - [菜鸟教程](https://www.runoob.com/redis/redis-tutorial.html) 
   
---
## 人工智能
### NLP

## 网络安全
### 学习路线
  - [网络安全学习路线](https://blog.csdn.net/mrbone9/article/details/123057077?spm=1001.2014.3001.5506)
  - [知识清单](https://blog.csdn.net/Internet_xx/article/details/119953419?spm=1001.2014.3001.5506)
- 
---
## 算法
#### 线段树
  1. 应用范围：区间查询，单点查询，区间修改，单点修改
  - [洛谷题单](https://www.luogu.com.cn/training/206#problems)

#### 树状数组
  1. 功能被包含于线段树，只能进行单点修改和区间查询，但是代码更简洁
  - [图解](https://blog.csdn.net/bestsort/article/details/80796531?spm=1001.2014.3001.5506)
- 
#### 网络流
  1. [Dinic算法](https://blog.csdn.net/stjp20080714/article/details/118398290?spm=1001.2014.3001.5506)

#### 动态规划
  - [习题](./notes/dp_Exercise.md)

### 算法设计

---
## 优秀博客
  - [阮一峰](http://www.ruanyifeng.com/blog/computer/)

  - [武宁子](https://www.wolai.com/wuning/8m9F2QuBJbAM51RNbiBqyq)

  - [Li-Yongjun](https://liyongjun.blog.csdn.net/?type=blog)

---
## 面试
### 企业面试
  - [2016互联网面试总结](https://blog.csdn.net/zhoufenqin/article/details/50911161?spm=1001.2014.3001.5506)

---
## 实用
### API
  1. [API文档汇总](https://blog.csdn.net/freeking101/article/details/115191217?spm=1001.2014.3001.5506)

---
## 杂谈
  - 计算机系统研究内核用三个词概括：计算 通信 存储

---
## 未来规划
  - 去国外互联网