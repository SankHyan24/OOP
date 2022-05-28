





<br/><br/><br/><br/><br/><br/><br/><br/>

# <center>Final Project Report<center>


## <center>author：<center>
### <center>孙川<center>
### **<center>3200105788</center>**
[TOC]


<div STYLE="page-break-after: always;"></div>

## 1. 介绍
### 1.1 完成情况

| 要求                                                         | 完成情况                                 | 说明                                                         |
| :----------------------------------------------------------- | :--------------------------------------- | ------------------------------------------------------------ |
| **1.**实现对二进制序列化的支持                               | **[<font color="green">已实现</font>]**  | 代码参见目录2.1                                              |
| **2.**对TinyXML封装，实现对XML序列化的支持                   | **[<font color="green">已实现</font>] ** | 代码参见目录2.2                                              |
| **3.**每个模块要有自己的命名空间                             | **[<font color="green">已实现</font>] ** | 二进制序列化使用`BinSerial`命名空间，XML序列化使用`XMLSerial`命名空间。 |
| **4.**每个模块至少支持算术类型、C++字符串以及STL容器：`set map list vector pair` | **[<font color="green">已实现</font>] ** | 支持容器嵌套，以及tuple类型和tuple与其他支持类型的嵌套       |
| **5.**每个模块至少提供一种方便的机制来实现用户定义类型的序列化 | **[<font color="green">已实现</font>] ** | 使用类似reflection的功能（C++不支持）实现用户类型序列化与反序列化。本质是自定义类型与tuple类型的互相转换。 |
| **6.**在测试中，需要覆盖所有要求的类型和选项                 | **[<font color="green">已实现</font>] ** | 代码参见CMakeList.txt中Test部分，分别使用两个函数对进行二进制和XML的两种模式序列化/反序列化测试。 |
| **7.[<font color="red">Bonus</font>]**支持对智能指针的序列化 | **[<font color="green">已实现</font>] ** | 实现除用户定义类型外，对以上所有支持类型的unique_ptr指针的序列化与反序列化（如`unique_ptr<vector<int>>`，但不支持形如`vector<unique_ptr>`类型的序列化） |

### 1.2 适用环境

| 测试环境                       | 结果                                  |
| ------------------------------ | ------------------------------------- |
| MinGW32 v9.2.0                 | **[<font color="green">PASS</font>]** |
| Ubuntu 20.04 LTS GCC=9.4.0/WSL | **[<font color="green">PASS</font>]** |

基本上**除了<font color="red">MSVC</font>以外**的Tool Kit都可以，因为MSVC貌似没有cxxabi这个东西。

另外需要编译器支持C++17标准。都在cmake里写了。

### 1.3 构建方法

用CMakeList根目录下CMAKE:

```shell
mkdir build
cd build
cmake ..
make
```

### 1.3 文件结构

```shell
│					# 根目录，README以及配置文件
├───code 			# - Project主体所在文件夹
│   └───include 	#   - hpp文件，包括项目主要代码，以及相关macro和utility
├───lib 			# - Tiny XML 所在文件夹
└───test 			# - CTest代码主体所在文件夹
    ├───include 	#   - 测试必要的头文件
    └───src 		#   - 测试代码，一个cpp文件测试一个module
```

## 2. 使用和实现说明

**在test部分的cpp文件中已经给出了序列化和反序列化函数的使用的方法。**

**如想自定义测试请在原test文件基础上进行修改。**

**如果遇到问题可以参考下面。**

### 2.1 二进制序列化

#### 2.1.1 如何使用

1. 首先include相关必须文件（`binserial.hpp bindeser.hpp`）
2. `using namespace BinSerial;`
3. 之后`serialize(你的变量，输出的二进制文件地址)`或者`deserialize(你的变量，输入的二进制文件地址)`
4. **如果你的变量是用户自定义变量**，使用宏定义的函数：`serialize_user(你的变量，输出的二进制文件地址)`或者`deserialize_user(你的变量，输入的二进制文件地址)`。更多使用方法详见`macro.hpp`

#### 2.1.2 如何实现

本质上是基于一定协议的二进制读写文件，具体协议依赖于特定的类型。也就是说如果如果两个变量的类型相同，且属于本程序所支持的类型，就可以将其中一个序列化为特定格式，并由第二个反序列化出来。总的来说，序列化和反序列化的函数结构都是类似的，两者也必须遵守相同的协议。

序列化具体实现，是由一个入口函数`serialize`开始，打开相关文件，并执行子函数`serialize_`进行文件的写入。总体执行过程类似于中序遍历一个由vector/set等容器嵌套组成的变量树。

如遇到`vector<T>`，则程序将其分解为多个`T`类型变量，逐一进行`serialize`。其他STL容器如`set, map, list, string`本质与之相同，是先转为vector再执行序列化的。反序列化类似。

tuple类型的序列化与vector类似，但是具体实现上，是对tuple的成员进行一个个拆解，一层层进行序列化的。反序列化类似。

用户自定义函数的序列化，本质上是将类型转化为内部成员对外可见的tuple后，再进行序列化的。反序列化类似。详细内容在第三部分。

### 2.2 XML序列化

#### 2.2.1 如何使用

1. 首先include相关必须文件（`xmlserial.hpp xmldeser.hpp`）
2. `using namespace XMLSerial;`
3. 之后`serialize(你的变量，输出的二进制文件地址)`或者`deserialize(你的变量，输入的二进制文件地址)`
4. **如果你的变量是用户自定义变量**，使用宏定义的函数：`serialize_user(你的变量，输出的二进制文件地址)`或者`deserialize_user(你的变量，输入的二进制文件地址)`。也可以将最外层的element重命名为你想要的名字：`serialize_user_n(你的变量，输出的二进制文件地址，名字)`或者`deserialize_user_n(你的变量，输入的二进制文件地址,名字)`。

#### 2.2.2 如何实现

具体思路和二进制的序列化反序列化一，不同的一点在于XML序列化反序列化中序遍历的程序树，同时被映射为了TinyXML2中的XMLDocument类的文档树（DOM），每个节点对应变量信息的节点。

总体上实现和二进制一样，多的是对XML库的调用。读读代码就会用了。

这里有一个难点，如何让程序知道我序列化的变量到底是什么变量？C标准库里有Typeinfo，但是读取出来的类型标识并不是人类能读取出来的（比如说const char*被编译出的类型名是PKc）。

C++本身是不具有这种特性的，这里我参考stackoverflow使用了一种预先标识的办法，定义了`TypeParseTraits`方法，并通过宏`REGISTER_PARSE_TYPE(X)`在`xmlserial.hpp`中，预先告诉编译器这个类型对应的类型名是什么。**<font color="red">注意：</font>如果你的类型不是其中之一，就过不了编译。如果想过编译，要自己手动在这里添加变量名。**

**例子：**下面是对一个随机生成的`vector<tuple<int, double, string>>`变量序列化为XML的结果：

```xml
<?xml version="1.0" encoding="UTF-8" standalone="no"?>
<serialization>
    <vector size="4">
        <tuple size="3">
            <int value="55"/>
            <double value="68.905651"/>
            <string length="10">L^C"$XrwWr</string>
        </tuple>
        <tuple size="3">
            <int value="39"/>
            <double value="90.979543"/>
            <string length="10">Y90&gt;UG%+&amp;f</string>
        </tuple>
        <tuple size="3">
            <int value="82"/>
            <double value="67.795700"/>
            <string length="10">"#xO\joo[3</string>
        </tuple>
        <tuple size="3">
            <int value="25"/>
            <double value="59.337824"/>
            <string length="10">)5&amp;hK4kN%/</string>
        </tuple>
    </vector>
</serialization>
```

### 2.3 关于用户定义变量

用户定义变量，如果成员都是int bool double等等类型，则可以直接将变量整体二进制读取写入。

但是如果成员变量中含有vector这种东西就不好办了。所以要用另一种方法。

第一步是想办法将对外界隐蔽成员的struct类型转变为tuple类型，也就是逐一把struct的成员先提取出来。C++不具有Reflectoin，这里我使用struct binding，参考BOOST里面的宏定义的花式使用，将不同情况下的struct（class）的成员强转出来。具体实现见`macro.hpp`，这部分参考了StackOverflow中给出的方法。

由于我是不同情况都提前写好了，如果class的成员都是public，且成员数量不超过6个，就都能跑过。如果非要多于六个，需要在`auto struct_to_tuple(T &&object) noexcept`添加该情况。下面是六个变量的情况示例：

```cpp
if constexpr (is_braces_constructible<type, any_type, any_type, any_type, any_type, any_type, any_type>{})
{
    auto &&[p1, p2, p3, p4, p5, p6] = object;
    return std::make_tuple(p1, p2, p3, p4, p5, p6);
}
```



第二步就是构建相应的tuple，这一步比较简单。构建好之后就可以使用tuple的对应方法了

但是由于相关方法都是编译器预操作，做不到将其整合到serialize函数中，于是我定义了相应macro，如serialize_user，将相应的转化部分添加在serialization之前。如此便完成了用户变量的序列化与反序列化。

## 3. 关于测试

### 3.1 使用方法：

使用CTEST。

测试的时候直接跑cmake下面的Test就可以了。

自定义测试的话，如果是二进制测试，就在`binarytest.cpp`里更改，XML测试就在`xmltest`里更改。

### 3.2 说明：

测试过程实际是测验序列化和反序列化的两个量是不是一样，这里我用的是自定义宏函数ASSERT_EQ。

如果ASSERT函数中的两个参数不相等，则程序会中断。

因此如果程序的结果是这样的：

![image-20220528171947315](https://cdn.jsdelivr.net/gh/SankHyan24/image1/img/image-20220528171947315.png)

或者使用的VScode或者CLion集成了CTest的环境，出现：

![image-20220528172214345](https://cdn.jsdelivr.net/gh/SankHyan24/image1/img/image-20220528172214345.png)

就说明测试通过了。

## 4. 参考与声明

- [leethomason/tinyxml2: TinyXML2 is a simple, small, efficient, C++ XML parser that can be easily integrated into other programs. (github.com)](https://github.com/leethomason/tinyxml2)

- [C++ Get name of type in template - Stack Overflow](https://stackoverflow.com/questions/1055452/c-get-name-of-type-in-template)
- [c++ - struct to/from std::tuple conversion - Stack Overflow](https://stackoverflow.com/questions/38561242/struct-to-from-stdtuple-conversion)

声明：除了上面说的，其余代码都是我自己敲的
