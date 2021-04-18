# 可行性报告

[TOC]



## 项目介绍

本项目以微内核seL4为基础，使用Rust语言对seL4进行重写，并参考Inferno平台上的Dis虚拟机和Android平台上的Dalvik虚拟机制作seL4的寄存器式虚拟机，以实现seL4在跨平台能力上的提升。此外，针对seL4对于分布式系统支持较弱的问题，本项目将通过虚拟机方式实现基于seL4的分布式系统。



## 理论依据

### **seL4**                                                                                      ![logo](https://sel4.systems/images/logo-text-white.svg)

seL4是一款操作系统微内核，是当前第二代微内核中最为出色的一款，其主要优势在于拥有经过了形式化验证的极高安全性，同时并没有为此损失性能，其性能不仅不落后于已有的微内核，还实现了性能的极大提升，使之成为目前最安全、性能最高的微内核，并且开源，有着较好的参考价值。

#### seL4 IPC机制[^1]

在seL4诞生之前，微内核界的曾经有过两代微内核，分别以Mach和L4为代表。

Mach采取了进程间通信理论上最为高效的通信方式——共享内存，同步访问。Mach的共享内存机制是在虚拟内存技术的支持下实现的，只有需要对内存进行写入时才进行复制。这么一处理比每次都复制一遍内存节省了内存使用同时又加快了IPC机制的处理时间，这种对共享内存的改进称为“写时复制”，在如今的通用操作系统如Linux中常常用到。它的效率较当时流行的UNIX版本低了25%，并且代码规模超过了UNIX，因此没有得到广泛应用。

L4仍然使用共享内存的IPC方式，但是对于IPC功能进行了精简，只是单纯地传递信息，诸如安全权限检查这类的代码都省略掉，省略掉的功能全部由用户进程自己处理，使得其IPC功能代码执行时间大大缩短。并且使用寄存器而不是内存来传递消息，同时限制信息的长度，省去了对内存的访问时间。L4的IPC速度最终达到了Mach的20倍，实现了高性能的突破。

seL4是在第二代内核L4的基础上发展而来的，它不仅继承了L4内核家族的高性能特性，而且在IPC机制上做了进一步改良。seL4在共享内存的基础上采用了同步和异步端口通信，同步IPC拥有更好的编程抽象，但会阻塞进程指导通信操作完成，在面对大量并发时效率欠佳；异步IPC只要发起一次操作即可返回而不需要等待其完成，拥有更高的效率。seL4将多种IPC方式综合起来应用于不同的场景从而实现了极高的效率。

##### 能力空间

seL4的IPC机制最大的特点是使用了能力空间的概念，进程持有不可伪造的令牌来表示拥有请求某种服务的能力。令牌可以被复制，可以被转移，还可以通过IPC进行传输。令牌其实是一个指向存在于内核空间内核对象的指针，所以普通进程并不能修改自身以及其他进程的权限分配，但是内核可以对令牌指定的权限进行控制，从而保证了用户态不能绕过能力空间这个机制对系统服务造成滥用。

##### seL4基于共享内存和端点（Endpoint）消息传递的IPC机制[^2]

端点消息传递只用于不超过几十个字节的短消息传递，更长的消息采取共享内存的方式进行通信。

共享内存的通信方式可以通过“通知”进行同步，分为以下3种：

	1. 根据信任关系，可以在一组线程之间直接共享缓冲区，不发送者发送者缓冲区同线程可以拥有不同的读写权限；
	2. 将缓冲区封装在共享服务器中；
	3. 给受信任的服务器授予对发送者缓冲区的读权限，并开放接收者缓冲区的写权限，然后将消息从发送者缓冲区拷贝到接收者缓冲区。

端点消息传递的通信方式是同步进行的，只有在发送方和接收方都准备就绪时消息交换才能发生，否则先就绪的一方需要阻塞直到另一方调用了IPC操作。消息操作通过“端点对象”进行。简单来说，端点可视为邮箱，发送方和接收方在达成一致后通过该邮箱交换消息。拥有发送权限的所有进程都可以通过端点发送消息，而拥有接收权限的所有进程都可以通过端点接收消息，这意味着每个端点可以有任意数量的发送方和接收方。但是无论有多少进程尝试从某个发送端点接收消息，发送端点可以指定一些消息仅被队列中的第一个进程接收。

值得一提的是，由于进程间通信具有严格的权限限制，当一个进程执行“仅发送消息”操作时，它的权限仅限于发送消息而不允许接收消息，因此它并不能收到接收方的反馈信息。

##### 通知：二进制信号量

与一般的信号量通信机制类似，也是通过“Signal()”和“Wait()“两种操作进行，对互斥的资源进行管理。

##### seL4快速通道（seL4 fastpath）

seL4快速通道是使seL4的IPC性能远远超过了其他微内核的主要原因，是seL4内核做出的重要优化。

Fastpath是在微内核上的附加前端，用于快速处理一些简单而常用的操作。用户可以选择关闭这一快速通道，虽然这不会对seL4微内核的行为造成大的影响，但其性能将大大损失。[^2]

seL4 fastpath的应用场景主要是Call和ReplyWait的系统调用，在fastpath下，IPC消息通过寄存器进行传递，能力不被传递。消息经过fastpath被即时传递，并不经过非常耗时的调度逻辑。[^3]

使用seL4 fastpath需要满足以下5个条件[^4]：

	1. 必须使用seL4_Call或seL4_ReplyRecv的系统调用；
	2. 消息中的数据必须适应seL4_FastMessageRegisters寄存器的要求，这些寄存器是fastpath的专用寄存器；
	3. 使用fastpath的进程必须拥有有效的地址空间；
	4. 不得传递进程标志（caps）；
	5. 优先级高于 被IPC解除阻塞的进程 的进程不得被运行。

##### 总结

seL4拥有多种多样的IPC机制来适应不同的应用场景，并且为常用的IPC系统调用做了硬件上的适配，使之IPC效率得到了巨大的提升，因此seL4可以作为一个高性能的改良参考，使得我们做出的微内核从根源上拥有较高的效率优势。



#### API[^5]

seL4使用的API是libsel4，分为5个部分：System Calls，Architecture-Independent Object Methods，x86-Specific Object Methods，ARM-Specific Object Methods，RISCV-Specific Object Methods。前两个部分与系统架构无关，后3个部分都专用于某一特定架构。

本项目将继承seL4的API不做大的修改，在虚拟机部分API中的调用和方法将被转化为相应环境中的调用和方法，转化功能将作为系统服务模块开发，并不作为微内核的一部分。



#### 安全性

seL4是世界上第一个且是迄今为止唯一一个经过安全性形式验证的操作系统。seL4的安全性表现为在它为系统中运行的应用程序之间的隔离提供了最高的保证 ，这意味着可以遏制系统某一部分的妥协，并防止损害该系统其他可能更关键的部分。

由于seL4已经拥有了极高的安全性，因此有关安全性内容不在本项目的改进计划之内。本项目将不会对seL4的安全性框架进行显著的改动，并尽可能地将其安全性沿用到项目成果中。



### **Rust语言**                                                                         

seL4的主体采用C语言编写，并辅以少量汇编语言用于提升其效率。C语言本身的效率在高级语言中较为出色，但是存在一定的安全性问题。虽然seL4系统的安全性已经经过了形式化验证，但是为了从语言层面进一步提高安全性和稳健性，我们计划采用Rust语言对seL4源码进行重写。选择Rust语言的原因如下：

1. Rust语言有着类似C++语言的语法，易于上手，便于学习和尽快开展项目；
2. Rust语言拥有高效率的内存访问，可以为性能要求较高的应用提供支持，能够为项目的性能提供更好的保障；
3. Rust的类型系统和所有权模型保证了内存安全性和线程安全性，使得很多不安全错误在编译时就能被发现，进一步提高项目安全性。



### **seL4上实现寄存器式架构虚拟机**

#### 基于虚拟机实现方式分析栈式架构虚拟机的不足

在解释器执行虚拟机指令中造成时间消耗的主要来自以下三个部分[1]

1. 指令调度
2. 取操作数
3. 执行计算

我们分别对这三个部分进行分析

一、 指令调度

对于操作栈来说，所有的操作数都是隐式的，这就意味着指令不需要显式地指明操作数的地址，从而大大地减少了指令的字节数。

我们以加法为例：

```assembly
iload_1
iload_2
iadd
istore_3
```

1. **每条指令都是”零地址指令“，并没有任何参数。**上面的iload_1、iload_2两条指令，分别向一个叫做“求值栈”的地方压入整型常量1、2。iadd指令则从求值栈顶弹出2个值，将值相加，然后把结果压回到栈顶。istore_3指令从求值栈顶弹出一个值，并将值保存到局部变量区的第一个位置(slot0)，从而实现加法。

   零地址指令的好处是每条指令都很短，节省储存空间，但是缺点同样也很明显：**要完成同样一个任务，使用零地址指令需要更多的指令数。**还是以加法为例，我们要用三地址指令实现加法指令，只需要``ADD rst,rsc1,rsc2``一条指令就能完成目的，而这样的一条指令和寄存器虚拟机的结构是配适的，**所以我们说采取寄存器虚拟机架构能显著的减少虚拟机指令数目**

2. 在C语言中，指令分派通常是使用一个switch分支进行实现的，而这样的一种分支预测方式是十分不准确的。在现在的计算机架构上绝大多数编译器对间接跳转指令的预测未命中率高达大约95%[^9]，即使是采用线程调度这样的分支办法，也只能带来45%的间接跳转指令的预测命中率[^9]

![SBD实现方式](https://github.com/OSH-2021/x-seLVM/blob/main/pictures/SBD%E5%AE%9E%E7%8E%B0%E6%96%B9%E5%BC%8F.jpg)

而现在的计算机架构多为多级流水实现，这就意味着，一但分支指派错误，就需要清空全部流水线并回滚至分支，这就造成了性能的浪费。**更多的指令数就意味着更多的分支指派错误，带来更多的性能浪费[^7]。**采用寄存器虚拟机的多地址指令，会减少指令的数目，从而减少分支预测带来性能损失。**所以我们说采取寄存器虚拟机架构能显著地减少分支预测带来的性能损失**

二、 取操作数

如一中所述，栈架构代码中取操作数只需要使用栈指针(stack pointer)即可实现，寄存器架构代码中需要指令指定操作数地址。因此寄存器架构的代码将会比栈架构代码更长。正因如此，小代码量，小内存读取的栈架构实现受到VM实现的青睐。但这仅仅是在实现比较简单的任务时的比较，一旦任务规模大，实现复杂，栈架构需要更多的指令数的缺点也逐渐显现，这会逐渐缩小两种实现方式的代码字节大小，**使用寄存器架构的虚拟机导致代码变长的缺陷被逐渐削减**。

三、执行计算

绝大多数虚拟机指令最后都是由物理硬件执行简单的计算，不论使用了什么样的中介和表示方式，故单从执行计算的角度进行分析，两者的差别并不大。**但对于寄存器架构的虚拟机，更易于编译器通过消除常量变量和重复表达式进行代码优化,如消除对相同常量的重复装载，前后复写传播，提取常量指令[3]，从而进一步提高虚拟机性能**。

四、栈式与寄存器式虚拟机性能比较

1. 学术界对寄存器架构的虚拟机性能分析主要是将栈虚拟机代码翻译成寄存器虚拟机代码，再进行性能比较。[^6]
2. 当我们采用寄存器架构的虚拟机实现时，较于操作栈架构的实现，虚拟机指令数目会有47%的下降，同时代码大小也会有25%的增加[^8]。

3. 从时间性能来看，采用C分支指派时，寄存器架构可以较栈架构减少32.3%的时间；如果使用更加有效的分支指派，如线程调度，寄存器架构还是可以较栈架构减少26.5%的时间[^8]。



### **CAP理论**[^15]

​	CAP理论观点是，在分布式计算机系统（根据网络分享数据的）中不可能同时提供以下全部三个保证

####  一致性（Consistency）:

所有节点同一时间看到的是相同的数据。

#### 可用性（Availability）:

不管是否成功，确保每一个请求都能接收到响应。

#### 分区容错性（Partition tolerance）:

系统任意分区时，在网络故障时，仍能操作。

#### CAP 理论3 of  2的一定误导性：[^16]

Eric Brewer 指出在CAP里面“三选二”的做法存在一定误导性。

主要体现在：

1）由于分区很少发生，那么在系统不存在分区的情况下没理由牺牲C或A；

2）C与A之间的取舍可以在同一系统内一非常小的粒度反复发生，而每一次的决策可能因为具体的操作，乃至因为牵涉特定的数据或用户而有所不同；

3）这三种性质可以在一定程度上衡量。

系统设计者可以用一定的方法（version vector 算法，CRDT...），通过分区过程中不变量的仔细管理实现C和A的优化。



### 跨平台技术

#### 基本概念

跨平台泛指程序语言、软件或硬件设备可以在多种作业系统或不同硬件架构的电脑上运作。

广义而言，一般的计算语言都可做到跨平台，开发商只需要提供各种平台下的Runtime/中间件环境即可。严格而言是指用某种计算机语言编制的程序只需要做小量的修改，编译之后即可在另外一种平台下运行，此时并不提供Runtime/中间件环境。



#### JAVA实现跨平台[^19]

Java对于跨平台的支持，就像对安全性和网络移动性的支持一样，是分布在整个Java体系结构中的。其中扮演者重要的角色的有 **Java语言规范、Class文件、Java虚拟机（JVM）**等。

首先，在Java语言规范中，规定了Java语言中基本数据类型的取值范围和行为。其次，所有Java文件要编译成统一的Class文件。最后，通过Java虚拟机将Class文件转成对应平台的二进制文件。

想把Java文件，编译成二进制文件文件，需要经过两步编译，**前端编译**和**后端编译**。

![前后端编译示意图](https://camo.githubusercontent.com/a2e2815a2d9ad21076fb0801e276a9cea93dfc2b/68747470733a2f2f7777772e686f6c6c6973636875616e672e636f6d2f77702d636f6e74656e742f75706c6f6164732f323031392f30332f31353533393239313533333137352e6a7067)

前端编译主要是指与源语言有关但与目标机无关的部分。Java中，我们知道的 javac 的编译就是前端编译。除了这种以外，我们使用的很多IDE如eclipse，idea等，都是内置了前端编译器，主要功能就是.java文件转换为.class文件。

后端编译主要是将中间代码再翻译成机器语言。Java中，这一步骤就是后端编译（jvm来执行）。

#####  Java语言规范

Java语言在跨平台方面做了一些努力，这些努力被定义在Java语言规范中。遵从规范格式，才能够被jvm编译以及解释运行。比如，Java中基本数据类型的值域和行为都是由其自己定义的。而C/C++中，基本数据类型是由它的占位宽度决定的，占位宽度则是由所在平台决定的。所以，在不同的平台中，对于同一个C++程序的编译结果会出现不同的行为。 

*注：举一个简单的例子，对于int类型，在Java中，int占4个字节，这是固定的。 但是在C++中却不是固定的了。在16位计算机上，int类型的长度可能为两字节；在32位计算机上，可能为4字节；当64位计算机流行起来后，int类型的长度可能会达到8字节。*

##### Class字节码

各种不同的平台的虚拟机都使用统一的程序存储格式——字节码（ByteCode），这是构成平台无关性的另一个基石。Java虚拟机只与由字节码组成的Class文件进行交互。 我们说Java语言可以Write Once ,Run Anywhere。这里的Write其实指的就是生成Class文件的过程。 因为Java Class文件可以在任何平台创建，也可以被任何平台的Java虚拟机装载并执行，所以才有了Java的平台无关性。Class 是16进制的文件流，最终会被jvm转成二进制的机械码。

##### JAVA虚拟机

Java的平台无关性是建立在Java虚拟机的平台有关性基础之上的，是因为Java虚拟机屏蔽了底层操作系统和硬件的差异。

跨平台是由jvm来完成的，jvm会根据不同的操作系统和硬件设备，提供不同jvm。想要做到跨平台，最重要的就是根据对应的硬件和操作系统生成Class文件对应的二进制指令。

*HotSpot虚拟机中，主要有解释执行和即时编译两种形式：*

*1. 解释执行：逐条将字节码翻译成机器码并执行*

*2. 即时编译（Just-in-time ，JIT）：将一个方法中包含的所有字节码编译成机器码后再执行。*

*HotSpot 默认采用混合模式，综合了解释执行和即时编译两者的优点。它会先解释执行字节码，而后将其中反复执行的热点代码（热点检测），以方法为单位进行即时编译。*



#### Android实现跨平台

<img src="https://gimg2.baidu.com/image_search/src=http%3A%2F%2Fcollection.sinaimg.cn%2Fcqyw%2F20121016%2FU5566P1081T2D88572F7DT20121016095448.gif&refer=http%3A%2F%2Fcollection.sinaimg.cn&app=2002&size=f9999,10000&q=a80&n=0&g=0n&fmt=jpeg?sec=1620637454&t=19d4c61edfb40c097ee2a942b55ab73e" width="30%">



Android也是基于Java语言的，Android源代码转换成机器码这一过程随着版本有不少的优化：

* Android 1.0（2008 年）：采用一个名为 Dalvik 的虚拟机，并且集成了一个解释器。当 App 运行时，就会调用这个解释器，对代码进行逐句解释，速度很慢。

* Android 2.2（2010 年）：引入 JIT（Just In Time）即时编译机制，当 App 运行时，会将用户经常使用的功能编译为机器能直接执行的 010101 机器码，不用一句一句地去翻译。当出现不常用的功能时，再调用解释器来翻译；这样速度加快，但每次启动 App 都要重新编译一次，不能一劳永逸。

* Android 5.0（2014 年 10 月）：将虚拟机 Dalvik 换成 ART（Android Run Time），将 JIT 的编译器替换成 AOT（Ahead of Time）。如此，App 在下载后安装到手机上时同时把能编译的代码先编译成机器听得懂的 101010；剩下不太好翻译的代码，就在用户使用时再叫醒解释器来翻译。如此，不用每次打开 App 都需要编译，但安装 App 的时间有点长，而且占用手机空间。

* Android 7.0（2016 年）：采用混合编译机制，安装时先不编译中间代码，而是在用户空闲时将能够编译成机器码的那部分代码，通过 AOT 编译器先静态编译了。如果 AOT 还没来得及编译或者不能编译，再调用 JIT+ 解释器。这种机制，相当于用时间换空间，既缩短了用户安装 APP 的等待时间，又将虚拟机里编译器和解释器能做的优化提升到最大效率了。

* Android 8.0 上改进了解释器，解释模式执行效率大幅提升。

* Android 10.0 上提供了预先放置热点代码的方式，应用在安装的时候就能知道常用代码会被提前编译。

  当前的 Android 采用的是解释执行 + JIT + AOT 的综合模式，在 空间占用+安装速度+运行速度 上已经达到了一个很好的平衡。但应用在被打包成 APK 的时候，采用的还是 Java 代码。换句话说，在 APK 变成用户可应用的过程中，还经历了一个在 Android 系统内部的编译过程。

  



## 技术依据

### **基于Dalvik与seL4的适配性进行分析**

2.1 Dalvik良好的模块设计

松耦合的设计理念使得 Dalvik的各个模块均可以拆分、替换，并且Dalvik在代码中设计了大量的预处理机制来实现模块的加载控制，这对本文控制整个移植流程提供了极大的帮助。[^10]

2.２ 内存管理模块的实现[^10]

Dalvik 内存管理 模 块 主 要 移 植 部 分 是 dlmalloc。 Dlmalloc采用所谓的边界标记法将内存划分成很多块，从而对内存的分配与回收进行管理。考虑为为dlmalloc的实现源码定义了

两种结构体 malloc_chunk和 malloc_tree_chunk来 描 述 这 些块，小于２５６字节的chunk块由结构体malloc_chunk来描述,大于２５６字 节 的chunk块 由 结 构 体 malloc_tree_chunk来 管理。

结构体 malloc_chunk和 malloc_tree_chunk的定义如下：

```c
struct  malloc_chunk{
    size_t prev_foot;
    size_t head;
    struct malloc_chunk * fd;
    struct malloc_chunk * bk;
}
typedef struct malloc_chunk mchunk
typedef struct malloc_chunk * mchunkptr
typedef struct malloc_chunk * sbinptr

struct malloc_tree_chunk{
    with malloc_chunk
    size_t prev_chunk;
    size_t head;
    struct malloc_tree_chunk *fd;
    struct malloc_tree_chunk *bfk;
    struct malloc_tree_chunk *child;
    struct malloc_tree_chunk *parent;
    bindex_t index;   
}
```

![image-20210418024138409](https://github.com/OSH-2021/x-seLVM/blob/main/pictures/%E6%A0%88%E7%A9%BA%E9%97%B4.png)





### **Socket**

![](https://images.cnblogs.com/cnblogs_com/goodcandle/socket3.jpg)

Socket（套接字）是调用操作系统通信服务的一种机制，应用于网络进程间的通信。因此，在实现分布式虚拟机系统间的通信时，适宜使用Socket机制。上图展现了Socket通信的原理。Socket 是一种“打开→读/写→关闭”模式的实现，服务器和客户端各自维护一个“文件”，在建立连接打开后，可以向文件写入内容供对方读取或者读取对方内容，通讯结束时关闭文件。[^11]

Socket 就像一个电话插座，负责连通两端的电话，进行点对点通信，让电话可以进行通信，端口就像插座上的孔，端口不能同时被其他进程占用。而我们建立连接就像把插头插在这个插座上，创建一个 Socket 实例开始监听后，这个电话插座就时刻监听着消息的传入，谁拨通我这个“IP 地址和端口”，我就接通谁。[^11]

Socket起源于Unix系统，它将Socket看作是一种特殊的文件，可以用“ 打开open→读写write/read→关闭close ”模式来操作。Socket通信的一般步骤[^12]如下：

```
1.创建ServerSocket和Socket
2.打开连接到的Socket的I/O流
3.按照协议对Socket进行读/写操作
4.关闭I/O流，关闭Socket
```

既然Socket是“open—write/read—close”模式的一种实现，那么socket就提供了这些操作对应的函数接口。下列为socket程序编写中，基本的socket函数：

#### socket()函数

socket函数对应于普通文件的打开操作。普通文件的打开操作返回一个文件描述字，而socket()用于创建一个socket描述符（socket descriptor），它唯一标识一个socket。

```c
int socket(int domain, int type, int protocol);
//参数domain
//即协议域，又称为协议族（family）。常用的协议族有，AF_INET、AF_INET6、AF_LOCAL（或称AF_UNIX，Unix域socket）、AF_ROUTE等等。协议族决定了socket的地址类型，在通信中必须采用对应的地址。

//参数type
//指定socket类型。常用的socket类型有SOCK_STREAM、SOCK_DGRAM、SOCK_RAW、SOCK_PACKET、SOCK_SEQPACKET等。

//参数protocol
//指定socket使用的协议。常用的协议有IPPROTO_TCP、IPPTOTO_UDP、IPPROTO_SCTP、IPPROTO_TIPC等。
```

#### bind()函数

调用socket()创建一个socket时，返回的socket描述字存在于协议族中，但没有一个具体的地址。此时调用bind()函数，把一个地址族中的特定地址赋给socket。

```c
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
//参数sockfd	
//即socket描述字，socket()函数创建的，具有唯一标识一个socket。bind()函数就是将给这个描述字绑定一个名字。

//参数addr	
//一个const struct sockaddr *指针，指向要绑定给sockfd的协议地址。创建socket时的地址协议族（ipv4/ipv6/Unix域）不同，这个地址结构也不同。

//参数addrlen	
//该协议地址的长度。
```

#### listen(),connect()函数

作为服务端，在调用socket()、bind()之后就会调用listen()来监听这个创建的socket，如果客户端这时调用connect()发出连接请求，服务端就会接收到这个请求。

```c
int listen(int sockfd, int backlog);
//参数sockfd	要监听的socket描述字

//参数backlog	相应socket可以排队的最大连接个数
```

```c
int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
//参数addr	服务器的socket地址

//参数addrlen	该socket地址长度
```

#### accept()函数

TCP服务端依次调用socket()、bind()、listen()之后，就会监听指定的socket地址了。TCP客户端依次调用socket()、connect()之后，就向服务端发送了一个连接请求。服务端监听到这个请求之后，就会调用accept()函数取接收请求，这样连接就建立好了。此后就可以开始网络I/O操作的进行。

```c
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
//参数sockfd
//服务器的socket描述字,是服务器开始调用socket()函数生成的，称为监听socket描述字

//参数addr
//指向struct sockaddr *的指针，用于返回客户端的协议地址

//参数addrlen
//协议地址的长度

//返回值
//如果accpet成功，那么其返回值是由内核自动生成的一个已连接的socket，代表与返回客户的TCP连接
```

#### read(),write()函数

至此，服务器与客户已经建立好连接了，能够实现了网咯中不同进程之间的通信。要调用网络I/O进行读写操作，可以有选择地使用几组网络I/O操作的读写函数：

```c
#include 

ssize_t read(int fd, void *buf, size_t count);
ssize_t write(int fd, const void *buf, size_t count);

ssize_t send(int sockfd, const void *buf, size_t len, int flags);
ssize_t recv(int sockfd, void *buf, size_t len, int flags);

ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,const struct sockaddr *dest_addr, socklen_t addrlen);
ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,struct sockaddr *src_addr, socklen_t *addrlen);

ssize_t sendmsg(int sockfd, const struct msghdr *msg, int flags);
ssize_t recvmsg(int sockfd, struct msghdr *msg, int flags);
```

#### close()函数

完成了读写操作，就要关闭相应的socket描述字。调用close()函数，把该socket标记为以关闭，使相应socket描述字的引用计数减1，然后立即返回到调用进程。此后，该socket不能再由调用进程使用。

```c
int close(int fd);
```

### **共享内存**

![1](https://ss2.bdstatic.com/70cFvnSh_Q1YnxGkpoWK1HF6hhy/it/u=3860786216,1007367958&fm=15&gp=0.jpg)

Shared Memory（共享内存）机制，即是允许两个要进行通信的进程访问同一个逻辑内存。不同进程之间共享的内存，通常为同一段物理内存。如果某个进程向共享内存写入数据，所做的改动将立即影响到可以访问同一段共享内存的任何其他进程。因此，本地进程间通信，或者拥有共享物理存储的分布式系统间通信，均可利用共享内存机制实现IPC、提高通信效率。[^13]

然而，共享内存并未提供同步机制。在第一个进程结束对共享内存的写操作之前，并无自动机制可以阻止第二个进程开始对它进行读取。所以，通常需要其他IPC机制来同步对共享内存的访问，例如信号量、互斥锁。

信号量( semophore ) 是一个计数器，可以用来控制多个进程对共享资源的访问。它常作为一种锁机制，防止某进程正在访问共享资源时，其他进程也访问该资源。因此，信号量主要作为进程间以及同一进程内不同线程之间的同步手段。

共享内存的一般步骤如下：[^14]

```
1.获得共享内存对象的ID
2.将共享内存映射至本进程虚拟内存空间的某个区域
3.当不适用时，解除映射关系
4.当所有进程都不用共享内存之时，删除共享内存
```

上述四个步骤，分别通过下列API函数实现：

#### shmget(),ftok()函数

第一步，创建或打开一个共享内存，获取该段共享内存的ID。

```c
int shmget(key_t key, size_t size, int shmflg);
//参数key
//这块共享内存的唯一IPC标识符。若为父子关系的进程间通信，则使用IPC_PRIVATE。若为无亲缘关系间的进程，则由ftok()生成key。

//参数size
//需要申请共享内存的大小。最小单位为页，一页是4KB。一般申请的内存大小为页的整数倍。

//参数shmflg
//表征该块内存的模式、权限。如果要创建新的共享内存，参数应为IPC_CREAT，IPC_EXCL；如果是已经存在的，可以使用IPC_CREAT或直接传0。

//返回值
//成功则返回一个新建或已经存在的共享内存标识符，取决于shmflg的参数。失败返回-1，并设置错误码。
```

```c
key_t ftok(const char *pathname, int proj_id);
//参数pathname
//在系统中存在,并且进程能够访问的路径名

//proj_id
//ID名，为1-255的一个整型数，一般取为一个ASCII值
```

#### shmat()函数

第二步，映射共享内存，即把指定的共享内存映射到进程的地址空间用于访问。

```c
void *shmat( int shmid , char *shmaddr , int shmflag);
//参数shmid
//该块共享内存的ID，即标识符。

//参数shmaddr
//共享内存映射的起始地址, 一般不指定，即传入NULL。此时，由内核自动分配一个空闲的地址，与存储段连接。

//参数shmflag
//本进程对该内存的操作模式。若为SHM_RDONLY的话，为只读模式。否则，若该参数为0，为读写模式

//返回值
//成功时，返回共享内存的起始地址。失败时返回-1。
```

#### shmdt()函数

第三步，当一个进程不需要共享内存的时候，就应撤销shmat()的映射。该函数并不删除所指定的共享内存区，只是将之前用shmat()函数连接好的共享内存区脱离目前的进程。

```c
int shmdt(const void *shmaddr);
//参数shmaddr	 共享内存的首地址。

//返回值		成功返回0，并将shmid_ds结构体中的shm_nattch计数器减1；出错返回-1
```

#### shmctl()函数

第四步，等所有进程都用shmdt()脱离共享内存映射，该块共享内存不再使用，就应将之销毁。

```c
int shmctl(int shmid, int cmd, struct shmid_ds *buf);
//参数shmid	
//共享内存的ID。

//参数cmd		
//表征要执行操作。若为IPC_STAT，则读取共享内存的状态；若为IPC_SET，则改变共享内存的状态；要销毁共享内存，应将该参数设为IPC_RMID，表示将之删除。

//参数buf		
//属性信息结构体指针，可以保存/设置属性。IPC_STAT操作时，取得的状态放在这个结构体中。若要改变共享内存的状态，用这个结构体指定。销毁共享内存时，设置为NULL即可。

//返回值		
//成功返回0，失败返回-1。
```



### **分布式系统CRDT（Conflict-Free Replicated Data Type）模型[^17][^18]**

CRDT（交换复制数据模型） 是一系列处理冲突的模型，主要分为CvRDT 和 CmRDT,他们的复制方式不同，CvRDT基于状态，这意味着用户将通过网络将整个CRDT状态发送给对方。相反，CmRDT通过将所有编辑（称为Op）分发到系统中的每个节点来进行复制。

#### CRDT例子

CRDT都是关于偏序的，要将结构转换成CRDT，必须首先在结构的状态空间上定义一种特殊的偏序。注意偏序还定义了合并的行为方式。例如，在两个插槽中存储多维数据集的2元组结构的状态空间，它的状态空间如下所示：

![png1](https://github.com/rust-crdt/rust-crdt/blob/master/art/crdt_statespace.png)

要将此结构转为CRDT，我们需要满足以下约束的状态空间上的偏序：

```
∀ s ⊆ S where S is your state space  # for any subset of the state space ...
∃ lub s and lub s ∈ S                # .. the least-upper-bound of the set is also in the state space
```

Lub指的是最小上界运算，它取状态空间的一个子集，并产生一个大于或等于该子集中所有状态的唯一状态。以下是满足约束的偏序：

![png2](https://github.com/rust-crdt/rust-crdt/blob/master/art/crdt_partial_order.png)

现在假设我们要合并这个结构的两个实例，我们可以由偏序得到最终合并的状态。

merge(a, b) = lub { a, b }

![png3](https://github.com/rust-crdt/rust-crdt/blob/master/art/crdt_merge.png)



## 技术路线

### 开发工具

* seL4 Source Code

* VSCode Rust IDE
* Benchmark

### Rust重写seL4微内核

使用Rust语言重写使用C语言的seL4微内核，在这一部分对seL4的整体结构不作修改，基本只是对已开源的代码进行语言改换。

### IPC机制调整

为了适应虚拟机的运行环境和提高虚拟机的运行效率，需要对seL4中的部分IPC机制进行调整（比如一部分seL4的高速IPC基于特定的硬件支持，在虚拟机环境中可能很难进行高保真的模拟）。

### seL4虚拟机解释器

seL4虚拟机的宿主系统暂定为Linux系统和浏览器。如果项目时间允许，可以尝试把Windows作为其宿主系统。

### 分布式虚拟机

各个虚拟机之间通过Socket网络接口进行进程间通信，实现分布式虚拟机，虚拟机数量较少时尝试通过共享内存的方式进行通信以提高通信效率。

### 项目目标

> 基本目标：
>
> > 完成seL4的Rust重写工作，能够在官方指定架构上正常运行；
> >
> > 完成seL4虚拟机向Linux系统和浏览器的解释器，让seL4虚拟机在Linux和浏览器上正常运行；
> >
> > 完成seL4虚拟机的分布式改造，实现包含至少3个seL4虚拟机的分布式操作系统。
>
> 高级目标：
>
> > 在完成了Rust的重写工作中，对其IPC机制作出一些调整使Rust语言版的seL4拥有更高的性能；
> >
> > 完成seL4虚拟机向Windows系统的解释器，让seL4虚拟机能够很好地控制图形界面；
> >
> > 实现分布式虚拟机之间的共享内存和其他资源，实现更大规模的分布式seL4虚拟机，并尽可能地提升分布式操作系统的效率。



## 参考资料

[^1]: 微内核发展史与Mach、L4、seL4微内核OS的比较 https://blog.csdn.net/xiasli123/article/details/105191368

[^2]: FAQ on seL4 https://docs.sel4.systems/projects/sel4/frequently-asked-questions.html
[^3]: SkyBridge通信机制 https://ipads.se.sjtu.edu.cn/zh/publications/MiEuroSys19.pdf
[^4]: seL4 IPC https://docs.sel4.systems/Tutorials/ipc.html
[^5]: seL4 API https://docs.sel4.systems/projects/sel4/api-doc.html

[^6]: B. Davis, A. Beatty, K. Casey, D. Gregg, and J. Waldron. The case for virtual register machines. In *Interpreters, Virtual Machines and Emulators* *(IVME ’03)*, pages 41–49, 2003
[^7]: P. Winterbottom and R. Pike. The design of the Inferno virtual machine. In *IEEE Compcon 97* *Proceedings*, pages 241–244, San Jose, California, 1997
[^8]:  Yunhe Shi et al. Virtual machine showdown[J]. ACM Transactions on Architecture and Code Optimization (TACO), 2008, 4(4) : 1-36.
[^9]: M. A. Ertl and D. Gregg. The behaviour of effiffifficient virtual machine interpreters on modern architectures. In *Euro-Par 2001*, pages 403–412. Springer LNCS 2150, 2001
[^10]: 高士翔,葛霄,潘磊,郑滔.Dalvik在iOS上的移植[J].计算机科学,2012,39(S1):375-379.
[^11]:[socket通信原理](https://www.cnblogs.com/wangcq/p/3520400.html)
[^12]:[socket通信原理分析总结](https://blog.csdn.net/Improve_life/article/details/109379790)
[^13]:[IPC之共享内存](https://blog.csdn.net/weixin_44522306/article/details/89598049?utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7EOPENSEARCH%7Edefault-1.control&dist_request_id=&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7EOPENSEARCH%7Edefault-1.control)
[^14]:[进程间通信——共享内存（Shared Memory）](https://blog.csdn.net/ypt523/article/details/79958188)
[^15]:E. Brewer, "Lessons from Giant-Scale Services," *IEEE Internet Computing*, July/Aug. 2001, pp. 46-55.
[^16]:[E. Brewer, "CAP twelve years later: How the "rules" have changed," in *Computer*, vol. 45, no. 2, pp. 23-29, Feb. 2012, doi: 10.1109/MC.2012.37.](https://ieeexplore.ieee.org/document/6133253/）
[^17]:https://github.com/rust-crdt/rust-crdt
[^18]:[A comprehensive study of CRDTs](https://hal.inria.fr/file/index/docid/555588/filename/techreport.pdf)
[^19]:[JAVA实现跨平台](https://www.cnblogs.com/lujiahua/p/11404611.html)
[^20]:A Design to Adapt Microkernel Inter-process Communication Mechanism[ICIIP '18: Proceedings of the 3rd International Conference on Intelligent Information Processing](https://dl.acm.org/doi/proceedings/10.1145/3232116)May 2018 Pages 190–193https://doi.org/10.1145/3232116.3232147