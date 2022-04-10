rm ./pd.txt

./pdadd.exe 

./pdadd.exe ./pd.txt <<< "2022/4/7
OOP很让人开心
我让我的class尽量涵盖多的功能
尽量联系课上学习到的知识
然而没用上继承和多态，确实觉得用不上啊！
就这样吧.
"

./pdadd.exe ./pd.txt <<< "2022 4 6
这只是昨天的日记罢了，没什么特殊的。
就这样.
"

./pdadd.exe ./pd.txt <<< "2022 4 8
今天是四月七日，但是我提前把四月八日的写完了
哈哈哈哈.
"

./pdlist.exe ./pd.txt >> output.log

./pdadd.exe ./pd.txt <<< "2022 4 7
本来是写完四月七日的，但是为了测试一下功能，所以重新写一份。问题不大.
"

./pdlist.exe ./pd.txt >> output.log
./pdlist.exe ./pd.txt 1999 12 12 2000 12 12 >> output.log
./pdlist.exe ./pd.txt 1922 12 12 2022 12 12 >> output.log
./pdremove ./pd.txt 2022 4 8 >> output.log
./pdlist.exe ./pd.txt >> output.log
./pdshow.exe ./pd.txt 2022 4 8 >> output.log
./pdshow.exe ./pd.txt 2022 4 6 >> output.log