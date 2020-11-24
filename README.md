# easyCommandLine
操作系统大作业之简单命令行解析器

1. 在Linux环境下模拟实现简单命令解释器。
(1)要求实现的基本命令包括： 
pwd                  //显示当前所在目录的路径名
list  <目录名>          //列出指定目录名中的所有目录及文件
cd  <目录名或路径>   //改变当前工作目录
mkdir  <目录名>     //新建目录
rmdir  <目录名>      //删除目录
exit                 //退出命令解释程序
(2)可选做的扩展命令包括：
   rename <旧文件名> <新文件名>  //重命名一个文件或目录
   copy <已存在的文件名> <副本文件名或路径>  //复制一个已存在的文件（或者扩展成复制文件夹）
   find <目录> -name <待查找的文件名> //在指定的目录及其子目录中查找指定的文件，
并输出查找到的文件的绝对路径。
   注意：扩展命令可以根据自己的理解进行一些合理的变动。
