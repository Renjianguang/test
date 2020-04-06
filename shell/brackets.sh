#!/bin/bash

#小括号用法:
#1.单小括号:将括号内的命令在子shell中运行
(ls -l;echo hahah;pwd)
#2.初始化数组
array=(a b c d)
for i in ${array[@]}
do
    echo $i
done

#双小括号用法:
#1.算数运算
echo $((1+2))
if (($1+$2)); then
    echo "ok"
else
    echo "no"
fi
for ((i=0;i<5;i++))
do
    echo $i
done

#中括号用法：
#1.用于逻辑表达式
#注意:中括号内部的内容要和中括号之间有一个空格
#整数比较要用专门的关键字
if [ "abc" == "abc" ]; then
    echo "yes"
fi

if [ $1 -lt $2 ]; then
    echo "good"
fi
#2.匹配字符范围
cat mm.txt | grep [a-j]
#3.引用单个数组元素
arr=(12 32 33 22)
echo $((arr[2]+arr[3]))

#双中括号用法:
#1.用于逻辑表达式，比[]更通用，可以适配正常的逻辑运算符
if [[ $1 != $2 ]]; then
    echo "nace"
fi

#大括号用法:
#1.对文件描述的扩展
cat {a,b}.txt #表示cat a.txt b.txt
cat {a..d}.txt
#2.截取字符串
var=hellowordrehnjghappyhellobeijin
echo ${var%h*y} #注意：需以指定字符串结尾
echo ${var##*h} #注意：需以制定字符串开始

echo ${var:5}      #正数从头开始
echo ${var:(-3)}    #负数从末尾开始
echo ${var:10/2}
echo ${var:5:4}
#3.替换字符串
echo ${var/word/world}
echo ${var//hello/hi}
