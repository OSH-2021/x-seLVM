# 结题报告：x-seLVM项目

## 项目介绍

x-seLVM项目旨在利用Lua虚拟机，使seL4内核对平台的依赖转化为Lua虚拟机对平台的依赖，从而扩大seL4微内核的平台适用范围。主要的技术为将内核的部分接口进行改写，并将其注册到Lua程序中，实现运行在Lua虚拟机上的seL4内核。

##  小组成员

| 身份  | 姓名   | 邮箱                        |
| ----- | ------ | --------------------------- |
| 组长  | 张一方 | zyf001028@mail.ustc.edu.cn  |
| 组员  | 陶思成 | tsc2001@mail.ustc.edu.cn    |
| 组员  | 林晨阳 | lcy2333@mail.ustc.edu.cn    |
| 组员  | 吴晨源 | wuchenyuan@mail.ustc.edu.cn |
| 组员* | 刘佳如 | liujiaru@mail.ustc.edu.cn   |

*：刘佳如同学参与了调研报告和中期报告的制作，但在期中报告之后由于个人原因退出本组。

## 项目背景

### seL4微内核[^1]![logo](https://sel4.systems/images/logo-text-white.svg)

#### 特性概述

seL4是一款操作系统微内核，是第二代微内核中最为出色的一款，其主要优势在于拥有经过了形式化验证的极高安全性，同时并没有为此损失性能，其性能不仅不落后于已有的微内核，还实现了性能的极大提升，使之成为目前最安全、性能最高的微内核，并且开源，有着较好的参考价值。

#### IPC

在seL4诞生之前，微内核界的曾经有过两代微内核，分别以Mach和L4为代表。

Mach采取了进程间通信理论上最为高效的通信方式——共享内存，同步访问。Mach的共享内存机制是在虚拟内存技术的支持下实现的，只有需要对内存进行写入时才进行复制。这么一处理比每次都复制一遍内存节省了内存使用同时又加快了IPC机制的处理时间，这种对共享内存的改进称为“写时复制”，在如今的通用操作系统如Linux中常常用到。它的效率较当时流行的UNIX版本低了25%，并且代码规模超过了UNIX，因此没有得到广泛应用。

L4仍然使用共享内存的IPC方式，但是对于IPC功能进行了精简，只是单纯地传递信息，诸如安全权限检查这类的代码都省略掉，省略掉的功能全部由用户进程自己处理，使得其IPC功能代码执行时间大大缩短。并且使用寄存器而不是内存来传递消息，同时限制信息的长度，省去了对内存的访问时间。L4的IPC速度最终达到了Mach的20倍，实现了高性能的突破。

seL4是在第二代内核L4的基础上发展而来的，它不仅继承了L4内核家族的高性能特性，而且在IPC机制上做了进一步改良。seL4在共享内存的基础上采用了同步和异步端口通信，同步IPC拥有更好的编程抽象，但会阻塞进程指导通信操作完成，在面对大量并发时效率欠佳；异步IPC只要发起一次操作即可返回而不需要等待其完成，拥有更高的效率。seL4将多种IPC方式综合起来应用于不同的场景从而实现了极高的效率。

#### 能力空间

seL4的IPC机制最大的特点是使用了能力空间的概念，进程持有不可伪造的令牌来表示拥有请求某种服务的能力。令牌可以被复制，可以被转移，还可以通过IPC进行传输。令牌其实是一个指向存在于内核空间内核对象的指针，所以普通进程并不能修改自身以及其他进程的权限分配，但是内核可以对令牌指定的权限进行控制，从而保证了用户态不能绕过能力空间这个机制对系统服务造成滥用。

#### API

seL的API定义于libsel4库中，分为5个部分：System Calls，Architecture-Independent Object Methods，x86-Specific Object Methods，ARM-Specific Object Methods，RISCV-Specific Object Methods。前两个部分与系统架构无关，后3个部分分别专用于x86、ARM和RISC-V架构。本项目修改的API主要是System Calls和Architecture-Independent Object Methods两个与系统架构无关的部分。

#### 安全性

seL4是世界上第一个且是迄今为止唯一一个经过安全性形式验证的操作系统。seL4的安全性表现为在它为系统中运行的应用程序之间的隔离提供了最高的保证 ，这意味着可以遏制系统某一部分的妥协，并防止损害该系统其他可能更关键的部分。

### Rust语言<img src="https://www.runoob.com/wp-content/uploads/2020/04/rusticon.png" alt="Rust logo" style="zoom:67%;" />

seL4的主体采用C语言编写，并辅以少量汇编语言用于提升其效率。C语言本身的效率在高级语言中较为出色，但是存在一定的安全性问题。虽然seL4系统的安全性已经经过了形式化验证，但是为了从语言层面进一步提高安全性和稳健性，我们计划采用Rust语言对seL4源码进行重写。选择Rust语言的原因如下：

1. Rust语言有着类似C++语言的语法，易于上手，便于学习和尽快开展项目；
2. Rust语言拥有高效率的内存访问，可以为性能要求较高的应用提供支持，能够为项目的性能提供更好的保障；
3. Rust的类型系统和所有权模型保证了内存安全性和线程安全性，使得很多不安全错误在编译时就能被发现，进一步提高项目安全性。

### Lua语言与Lua虚拟机<img src="https://bkimg.cdn.bcebos.com/pic/a686c9177f3e67090ae08a613bc79f3df9dc5548?x-bce-process=image/resize,m_lfit,w_268,limit_1/format,f_jpg" alt="Lua logo" style="zoom:50%;" />

#### Lua语言特性概述[^2]

Lua是一个小巧的脚本语言，其设计目的是为了通过灵活嵌入应用程序中从而为应用程序提供灵活的扩展和定制功能。一个完整的Lua解释器不过200k，在所有脚本引擎中，Lua的速度是最快的。这一切都决定了Lua是作为嵌入式脚本的最佳选择。Lua由标准C编写而成，几乎在所有操作系统和平台上都可以编译，运行。Lua的目标是成为一个很容易嵌入其它语言中使用的语言，它也确实成为了一门易于扩展的语言。

很多知名游戏都使用了Lua作为自己的嵌入式脚本语言，比如：魔兽世界、愤怒的小鸟等。

#### Lua语言与C集成[^3]

Lua语言提供了非常易于使用的扩展接口和机制：Lua脚本可以很容易的被C和C++代码调用，也可以反过来调用C和C++函数来扩展Lua标准库中没有包含的功能。Lua和C进行数据交流是通过栈进行的：调用C函数时，Lua程序将C函数需要的参数入栈，C函数从栈中弹出参数并按照需要解释为不同的类型；C函数执行结束后，将返回值压入栈中，Lua程序从栈中弹出返回值。

由于seL4源码是C语言编写的，项目中主要利用的是Lua对C的调用。要完成对C函数的调用，需要将C函数进行改写，使之满足Lua语言的要求。使用的三个Lua标准库为：lua.h，lualib.h，lauxlib.h。具体要求如下：

1. C函数属性必须定义为static；
2. C函数的返回值类型必须为int；
3. C函数的参数必须有且只有lua_State* L，该参数为Lua与C进行数据交流使用的栈指针；
4. 由栈中弹出的数据并不具有类型属性，需要使用lua标准库中的一些方法转换为相应的C基本类型，C中的结构体需要拆解为基本类型分别赋值；
5. 由于Lua函数允许多个返回值，被调C函数的int型返回值为Lua需要的返回值个数，返回值本身压入栈中；
6. 在C程序中需要定义一个函数注册表，指定可以被Lua调用的C函数在Lua中的名称；
7. 使用lua_newlib()方法将函数注册表中的函数完成注册。

典型的可以被Lua调用的C函数如下：

```C
static int l_sin(lua_State *L){
  	const char* num1 = lua_tostring(L,1);
  	const char* num2 = lua_tostring(L,2);
  	lua_pushnumber(L,strlen(num1));
  	lua_pushnumber(L,sin(num1[0]));
  	lua_pushstring(L,num2);
  	return 3;
}
```

典型的C函数注册表如下：

```C
static const luaL_Reg mylib[] = {
	{"dir",l_dir},
	{"sin",l_sin},
	{"TP",l_getTotolPrice},
	{NULL, NULL}
};
```

将注册表中的函数完成注册如下：

```C
extern int luaopen_seL4_lib(lua_State* L)
{
    luaL_newlib(L, mylib);
    return 1;
}
```

#### Lua虚拟机实现机制

Lua脚本的执行都是通过Lua虚拟机进行的，Lua虚拟机拥有一套RISC指令集，一切Lua脚本经过解释之后得到Lua指令集的二进制程序，由Lua虚拟机执行Lua指令集程序。

## 设计思路

本项目的目标是要提高seL4的平台适应能力，而Lua虚拟机几乎可以在所有的平台上运行，并且提供了对C语言的简单接口，因此计划将seL4的API进行部分改写，将API方法注册到Lua程序中，通过Lua程序在虚拟机上的执行来实现跑在Lua虚拟机上的seL4内核，从而实现可以跑在各个平台上的seL4内核。

## 技术路线

### seL4 API改写

seL4非平台依赖的System Calls包括Send、Recv、Call、Reply、Non-Blocking Send、Reply Recv等，处理这些系统调用的函数大部分位于api/syscall.c中，因此将这些内容进行了改写，使之能够被Lua调用。其他一些改写工作位于object和kernel文件夹中。

### seL4内核编译

seL4官网中给出了原版内核的独立编译流程，使用了cmake和ninja工具。

使用Rust改写过的seL4内核编译需要使用xargo库对Rust源码进行编译，再用gcc将C源码产生的目标文件和Rust源码产生的目标文件链接起来生成内核。

本项目基于x-qwq项目进行开发，因此选择第二种方式对内核进行编译和链接。使用xargo组织工具需要安装nightly版本的Rust编译器，并且需要配置与本机相关的浮点参数，具体配置方法可以参见使用xargo编译后的报错信息。

### seL4内核测试

seL4官网上给出了使用qemu进行模拟的内核功能测试方法和测试包。通过替换kernel.elf文件可以对各种内核进行功能测试。

## 项目成果

### seL4 API改写成果

改写的适用于Lua调用的seL4源码包括：src/api/syscall.c，src/kernel/boot.c，src/kernel/faulthandler.c，src/kernel/stack.c，src/kernel/thread.c，src/object/cnode.c，src/object/endpoint.c，src/object/interrupt.c，src/object/objecttype.c，src/object/tcb.c。

### seL4内核编译成果

成功使用cmake和ninja工具完成了C源码内核的编译。

成功使用xargo和gcc完成了含有Rust源码的内核的编译。

未能成功链接含有Lua改写的seL4内核。

### seL4内核测试成果

成功测试了C源码内核，内核表现正常，如下图所示：

![test result of C kernel](https://github.com/OSH-2021/x-seLVM/blob/main/pictures/C_kernel_test.png)

成功测试了含有Rust改写的内核，内核表现正常，如下图所示：

![test result of Rust kernel](https://github.com/OSH-2021/x-seLVM/blob/main/pictures/Rust_kernel_test.png)

由于含有Lua改写的内核未能成功链接，无法进行测试。

## 反思与展望

本次项目的经验有：

	1. 在改写和尝试链接的过程中，对seL4的项目结构有了更加深刻的认识；
 	2. 学习了Lua语言，以及Lua与C的集成方式，为未来使用Lua脚本进行开发奠定了基础；
 	3. 对编译、汇编和链接流程的认识更加丰富，积累了一套处理编译和链接错误的方法；
 	4. 对技术路线的设计要足够详细，这对调研工作提出了很高的要求；
 	5. 对于类似小组成员离职这样的突发事件要预案，开发计划要有一定的灵活性和抗干扰能力。

本次项目的遗憾有：

	1. 虽然掌握了改写C程序并在Lua中调用的方法，也验证了改写部分的正确性，但是未能成功链接成内核，没能达到预期的成果。

本次项目的展望有：

1. 本次项目没能做出最终成果，但是在链接过程中出现的各种未定义错误和定义冲突错误，显然能够在有限时间内解决，哪怕是进到头文件中挨个添加、修改、删除定义也一定能够在有限时间内完成，未来有时间可以继续进行开发；同时也欢迎有兴趣的同学跟进完成。目前对报错的认识为：

   > 大量的报错类型为：undeclared function，undeclared type，conflicting definition。
   >
   > 目前所见的大部分报错出现在stdio.h，stddef.h，string.h等标准库中。
   >
   > 怀疑报错原因：在部分seL4源码中存在着与C标准库中重名的头文件，或者存在着对同名变量的不同定义。seL4源码并不引用任何C标准库，因此链接不存在错误。但是经过Lua改写后，由于引用了lua.h，lualib.h，lauxlib.h这三个头文件，间接引用了C标准库，从而出现了标准库和seL4源码内容冲突，触发了报错。

2. 对seL4进行了Lua改写后，通过外包一层Lua程序可以在Lua程序中使用seL4内核，可以继续利用Lua对各种语言的接口，实现使用各种语言调用seL4内核中的方法。

[^1]: https://github.com/OSH-2021/x-seLVM/blob/main/docs/feasibility.md
[^2]: https://baike.baidu.com/item/lua/7570719?fr=aladdin
[^3]: Programming in Lua, Roberto Ierusalimschy, Brazil, 2018.6

