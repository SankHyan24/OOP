cmake -G "MinGW Makefiles" .. 
这个project用CMake构建。（实际上我是用MINGW，效果和linux应该一样

文件结构：
build目录，放的是几个在windows下构造好的exe，以及对应的shell脚本
code目录，放的是一个程序对应的cpp文件。都是几行，因为都是对后面lib库里的简单调用也没必要加注释了
lib目录放的是这几个程序共用的一个库。因为涉及到文件读写，要按照一个格式协议进行存储和读取，所以我觉得最好共享一个标准。
lib库里面放着几个类，大体结构就是database类最大，包含许多diary，而diary类里面包含date类，设置date类是因为程序里面涉及到日期比较大小比较多。声明都在pd.hpp里面，另外几个cpp都是其具体实现。注释都在那个hpp里面，给出了每个方法的功能介绍。

使用方法：
向下兼容pta的要求。
pdadd.exe不加任何参数，默认构建一个名字叫做pd.txt的新日记
pdadd.exe + filename 是打开这个日记并进行写入
pdlist + filename + （可选：初始年月日+截至年月日） 效果和pta一样
pdremove +filename +日期
pdshow +filename +日期

另外build目录下的test.sh是测试的shell脚本，输出会存在output的文档里


