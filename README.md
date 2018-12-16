# sudoku
软件工程基础个人项目：实现一个能够生成数独终局并且能求解数独的控制台程序。（C++实现）

一、生成终局
（1）在命令行中使用'-c'参数加数字N(1<=N<=1 000 000)控制生成数独终局的数量.
（2）将生成的数独终局用一个文本文件保存（sudoku.txt）.
（3）在生成数独矩阵时,左上角的第一个数为：(学号后两位）%9+1.（(2+2)%9+1=5）

二、求解数独
（1）在命令行中使用'-s'参数加文件名的形式来求解数独，并将结果输出至文件(solve.txt).
（2）数独题目格式,0代表空格,题目与题目之间空一行,行末无空格,最后一个数独题目后无空行.
（3）数独题目个数N(1<=N<=1 000 000),保证文件中数独格式正确.