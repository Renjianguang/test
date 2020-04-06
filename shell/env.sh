#!/bin/bash

#$1~9代表传入shell的参数
for i in $@
do
    echo $i
done
#$#表示参数的数量
    echo $#
#$?代表最近执行的命令或shell输出的状态码 
    echo $?
#$$表示当前shell的进程id
    echo $$
#$@表示所有的参数
    echo $@
#OLDPWD 表示之前的路径
    echo $OLDPWD
#PPID表示父进程的PID
    echo $PPID
#RANDOM 表示一个随机数
    echo $RANDOM
#SECONDS表示脚本运行的时间
    echo $SECONDS

#PATH
    echo $PATH
#HOME
    echo $HOME
#HISTSIZE
    echo $HISTSIZE
#LOGNAME
    echo $LOGNAME
#SHELL
    echo $SHELL
#LANG
    echo $LANG
#MAIL
    echo $MAIL
#PS1
    echo $PS1
#USER
    echo $USER
#UID
    echo $UID
