# xuexi_test
//测试上传

创建工程遇到的难题

第一个问题是：没有正确的进行文件的创建

出现了这个情况，导致我以为自己的电脑没有装stm32 的芯片支持包。  

<img width="1026" height="756" alt="Image" src="https://github.com/user-attachments/assets/3e9b83e3-5d6b-4002-a9c3-ba5afb7affcb" />

关闭这个界面，然后重新创建一个工程，就不会出现这个问题。

第二个问题就是关于启动文件的选择：根据资料不同的芯片型号选择不同的启动文件。
STM32 标准库把 F1 系列分为 LD(低密度)、MD(中密度)、HD(高密度)、XL 等，而 F103ZE 这类 512KB Flash 的芯片归类为高密度 HD。


对应关系里给出的规则是：256K–512K Flash 选用 HD，因此 F103ZET6 应使用 startup_stm32f10x_hd.s 这个启动文件。

第三个问题就是创建启动文件后，编译出现这个错误(截取部分)：

```
Rebuild started: Project: led01
*** Using Compiler 'V6.19', folder: 'D:\arm_KeilMDK\ARM\ARMCLANG\Bin'
Rebuild target 'Target 1'
Start/core_cm3.c(445): error: non-ASM statement in naked function is not supported
uint32_t result=0;
^
Start/core_cm3.c(442): note: attribute is here
uint32_t __get_PSP(void) __attribute__( ( naked ) );
void
./Start/core_cm3.h(1217): error: unknown type name 'inline'
static __INLINE void __CLREX() { __ASM volatile ("clrex"); }
^
./Start/core_cm3.h(751): note: expanded from macro '__INLINE'
#define __INLINE inline /*!< inline keyword for GNU Compiler */
^
./Start/core_cm3.h(1217): warning: a function declaration without a prototype is deprecated in all versions of C [-Wstrict-prototypes]
static __INLINE void __CLREX() { __ASM volatile ("clrex"); }
^
void
./Start/core_cm3.h(1468): error: unknown type name 'inline'
static __INLINE void NVIC_SetPriorityGrouping(uint32_t PriorityGroup)
^
./Start/core_cm3.h(751): note: expanded from macro '__INLINE'
#define __INLINE inline /*!< inline keyword for GNU Compiler */
^
./Start/core_cm3.h(1489): error: unknown type name 'inline'
static __INLINE uint32_t NVIC_GetPriorityGrouping(void)
^
./Start/core_cm3.h(751): note: expanded from macro '__INLINE'
#define __INLINE inline /*!< inline keyword for GNU Compiler */
^
./Start/core_cm3.h(1489): error: expected ';' after top level declarator
static __INLINE uint32_t NVIC_GetPriorityGrouping(void)
^
;
./Start/core_cm3.h(1756): error: unknown type name 'inline'
static __INLINE uint32_t ITM_SendChar (uint32_t ch)
^
./Start/core_cm3.h(751): note: expanded from macro '__INLINE'
#define __INLINE inline /*!< inline keyword for GNU Compiler */
^
./Start/core_cm3.h(1756): error: expected ';' after top level declarator
static __INLINE uint32_t ITM_SendChar (uint32_t ch)
^
;
Start/system_stm32f10x.c(162): warning: no previous extern declaration for non-static variable 'SystemCoreClock' [-Wmissing-variable-declarations]
uint32_t SystemCoreClock = SYSCLK_FREQ_72MHz; /*!< System Clock Frequency (Core Clock) */
^
Start/system_stm32f10x.c(162): note: declare 'static' if the variable is not intended to be used outside of this translation unit
uint32_t SystemCoreClock = SYSCLK_FREQ_72MHz; /*!< System Clock Frequency (Core Clock) */
^
Start/system_stm32f10x.c(167): warning: no previous extern declaration for non-static variable 'AHBPrescTable' [-Wmissing-variable-declarations]
__I uint8_t AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};
^
Start/system_stm32f10x.c(167): note: declare 'static' if the variable is not intended to be used outside of this translation unit
__I uint8_t AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};
^
17 warnings and 17 errors generated.
compiling system_stm32f10x.c...
assembling startup_stm32f10x_hd.s...
".\Objects\led01.axf" - 38 Error(s), 53 Warning(s).
Target not created.
Build Time Elapsed: 00:00:11
```

主要原因还是
你用的是 Arm Compiler 6（clang 内核），但 core_cm3.c / core_cm3.h 和 startup_stm32f10x_*.s 这些文件是给 旧版 AC5（armcc） 和老 CMSIS 写的，语法和关键字与 AC6 不兼容，所以出现 “naked function 不允许非汇编语句 / inline 未知类型” 之类错误。按照这个办法解决：打开 “魔法棒” → 选项里的 Target 或 C/C++ 选项卡，把 “Using Compiler V6.x” 改成 Use default Compiler Version 5 或直接选择 Arm Compiler 5。
<img width="626" height="470" alt="Image" src="https://github.com/user-attachments/assets/feac2d0b-60fd-48e4-8ce0-6ec66d2c6d4b" />

新建的这个工程文件夹中放的文件是：
1、User 文件夹：暂时只有一个文件主函数，程序入口，包含主要应用逻辑。以后会放一些业务层逻辑。

2、Library 文件夹：是我从官方提供的文件中拷贝的STM32标准外设库， STM32标准外设库包含所有外设驱动程序和头文件。如GPIO、RCC（时钟管理）、EXTI（外部中断）等。

3、Start 文件夹： 芯片初始化和启动代码也是从官方的文件中拷贝的。

4、DebugConfig 文件夹: Keil MDK调试器配置文件 ,配置STM32F103ZE芯片在调试模式下的行为，特别是当CPU被暂停/断点暂停时，各个外设和计时器如何运作.

5、Objects 文件夹: 编译生成文件（中间/输出文件),这是Keil MDK编译生成的中间文件和输出文件夹，包含编译、链接后的产物。(Objects文件夹可以完全删除，重新编译时会自动生成。这是临时编译文件，不需要版本控制。)

6、Listings 文件夹 - 编译列表文件。()





2026年1月3日2026年1月2号

浏览了野火stm32初级教程前三章的内容：

第一章 介绍配套开发板的使用，keil的一些相关的功能和j-link下载。

第二章 主要说的是jlink、keil的安装和芯片的安装包，以及创建一个新的工程和里面的相关文件是干啥的。

第三章 进行新工程的创建，我需要重点看一下keil的仿真调试，因为我很少调试过这些，并将自己写的模板工程点亮一个led小灯进行了一个调试，进去看了一些可以进去看到一些相关的函数。发现一个问题就是在函数跳转到初始化的时候，会卡死。原因是：自己对于仿真调试的三个按键不够了解，首先先了解这三个按键

Step (Step Into) ： 逐语句每一行都要进去执行，当你怀疑某个具体函数（比如自己写的 LED_On()）内部逻辑有问题，想进去一行一行检查细节时。

Step Over ：逐个函数执行，比如你调用了自己定义的某个函数，你确信这个库函数没问题，不想浪费时间进去看它怎么置位寄存器，就点这个按钮直接“跨”过去。

Step Out ：跳出某个函数，你不小心用“Step Into”进了一个很长的库函数（比如 printf 实现），发现里面有几百行代码，不想一行一行按了，就点这个按钮直接跳出来。

今天遇到的这个情况是：在 main 函数的主循环里点这个。因为 main 函数通常是死循环，永远不会“Return”，点这个等于全速运行，会导致调试器看起来“卡死”。



| 按钮     | 名称      | 执行动作       | 进入函数       | 相关的场景                           |
| -------- | --------- | -------------- | -------------- | ------------------------------------ |
| F11      | step into | 向下或进入内部 | 进入函数内部   | 底层细节以及自己写的函数             |
| F10      | step over | 向下           | 直接运行完函数 | 查看主逻辑流程以及跳过已知正确的函数 |
| Ctrl+F11 | step out  | 向外           | 立即做完并返回 | 进入一个长函数向退出                 |

最后写了一个流水灯，我才了解到标准库没有延时含糊需要用Systick系统滴答定时器来写。还未进行分层，以及了解gpio引脚的输入输出模式。



2026年1月3号：

1.介绍库函数的作用，是配置最底层的寄存器，有利于快速的开发，易于阅读，维护成本低。是与寄存器介于驱动层与用户之间的代码，向下处理寄存器直接相关的配置，向上为用户提供配置寄存器接口。

2.库函数开发方式与寄存器开发方式：

库函数开发方式：从驱动层====》库函数层，调用相关的库接口；库函数层===》特殊寄存器层，通过函数、宏封装配置寄存器的操作来做的。

直接配置寄存器的方式：驱动层====》特殊寄存器层，是直接配置寄存器来实现的。

3.cmsis标准：ARM 与芯片厂商建立了 CMSIS 标准(Cortex MicroController Software Interface  Standard)。

<img width="700" height="416" alt="Image" src="https://github.com/user-attachments/assets/35f130d1-387b-475a-ad59-b61258d972e0" />

<img width="756" height="626" alt="Image" src="https://github.com/user-attachments/assets/d938b3e8-b7c8-4f7a-a08d-875c9dd35c6c" />

内核层的函数：包括访问寄存器的名称、地址定义，主要是有ARM公司提供。

设备外设访问层：提供了片上的核外外设的地址和中断的定义，主要由芯片的厂商提供。

4.了解安装包中库文件夹中相关文件的作用：

- core_cm3.c 跟启动文件一样都是底层文件，都是由 ARM 公司提供的，遵 守 CMSIS 标准，即所有 CM3 芯片的库都带有这个文件，这样软件在不同的 CM3 芯片的移植工作就得以简化。
- 在 DeviceSupport 文件夹下的是启动文件、外设寄存器定义&中断向量 定义层 的一些文件，这是由 ST 公司提供的。system_stm32f10x.c 在实现系统时钟的时候要用到 PLL（锁相环），这 就需要操作寄存器，寄存器都是以存储器映射的方式来访问的，所以该文件中 包含了stm32f10x.h 这个头文件。
- stm32f10x.h这个文件，是一个底层文件。所有处理器厂商都会将对内存的操作封装成一个宏，即我们通常说的寄存 器，并且把这些实现封装成一个系统文件，包含在相应的开发环境中。

5.启动文件：Libraries\CMSIS\Core\CM3\startup\arm 文件夹下是由汇编编写的 系统启动文件，不同的文件对应不同的芯片型号，在使用时要注意。一些英文缩写的意义如下：

cl：互联型产品，stm32f105/107 系列 

vl：超值型产品，stm32f100 系列 

xl：超高密度（容量）产品，stm32f101/103 系列 

ld：低密度产品，FLASH 小于 64K 

md：中等密度产品，FLASH=64 or 128 

hd：高密度产品，FLASH 大于 128

6.重点：启动文件的作用：

- 初始化堆栈指针SP。
- 初始化程序计数器指针PC‘；
- 设置堆栈的大小；
- 设置异常向量表的入口地址。
- 设置外部SRAM作为数据存储器（这个有用户配置，一般的开发板可没有外部SRAM）。
- 设置C库的分支入口__main(最终用来调用main函数)。
- 在3.5版的启动文件还调用了在system_stm32f10x.c文件中的systemIni()函数配置系统时钟，在旧版本工程中要用户进入main函数自己调用systemIni()函数。

7.Libraries\STM32F10x_StdPeriph_Driver 文件夹下有 inc（include 的 缩写）跟 src（source 的简写）这两个文件夹，这都属于 CMSIS 的设备外设函 数部分。src 里面是每个设备外设的驱动程序，这些外设是芯片制造商在 Cortex-M3 核外加进去的。

8.还需要添加这三个文件：在库目录的\Project\STM32F10x_StdPeriph_Template 目录下，存放 了官方的一个库工程模板，我们在用库建立一个完整的工程时，还需要添加这 个目录下的 stm32f10x_it.c、stm32f10x_it.h、stm32f10x_conf.h 这三 个文件。下面是这三个文件的作用：

- stm32f10x_it.c，是专门用来编写中断服务函数的，在我们修改前，这个 文件已经定义了一些系统异常的接口，其它普通中断服务函数由我们自己添 加。
- stm32f10x_conf.h，这个文件被包含进 stm32f10x.h 文件。是用来配 置使用了什么外设的头文件，用这个头文件我们可以很方便地增加或删除上面 driver 目录下的外设驱动函数库。
- stm32f10x_conf.h 这个文件还可配置是否使用“断言”编译选项，在开 发时使用断言可由编译器检查库函数传入的参数是否正确，软件编写成功后， 去掉“断言”编译选项可使程序全速运行。可通过定义 USE_FULL_ASSERT 或取消定义来配置是否使用断言。

8.库函数的关系：
<img width="665" height="802" alt="Image" src="https://github.com/user-attachments/assets/97b38aad-bdee-4bad-ae52-c0f2e5812f05" />

2026年1月4日与1月3日

第五章：

1.存储器映射图：

<img width="751" height="574" alt="Image" src="https://github.com/user-attachments/assets/5f4c8252-ce8f-4e8b-b61f-85a9efae1b4f" />

寄存器的最终地址(绝对地址)=外设基地址+总线基地址+寄存器组基地址

外设基地址：
-   每个外设(比如GPIOA、USART、TIME)所属的总线占据一小段的连续寻址范围，这段范围起始地址叫做外设基地址 。
- 这个就是某个具体外设在内存里的起点，所有的外设寄存器都在这一区域内按偏移排列。
-  例如：首先看到 PERIPH_BASE 这个宏，宏展开为 0x4000 0000,并把它强制
转换为 uint32_t 的 32 位类型数据，这是因为地 STM32 的地址是 32 位的，Cortex-M3 核分配给片 上外设的从 0x4000 0000 至 0x5FFF FFFF 的 512MB 寻址空间中 的第一个地 址，我们把 0x4000 0000 称为外设基地址。


总线基地址：
- 在MCU中，片上外设挂载在不同总线上(比如AHB、APB1、APB2)。
- 每条总线在整个存储器映射中有一段连续的地址，这段区域的第一个地址叫“总线基地址”，也是这条总线上第一个外设的起始地址。
- 例如：接下来是宏 APB2PERIPH_BASE，宏展开为 PERIPH_BASE（外设基地
址）加上偏移地址 0x1 0000，即指向的地址为 0x4001 0000。STM32 不同的外设是挂载在不同的总
线上的，见图 5-8。有 AHB 总线、APB2 总线、APB1 总线，挂载在这些总线上
的外设有特定的地址范围。


寄存器组基地址：
- 针对“单个外设”（如GPIOA、USART1），这个外设控制/状态寄存器是一整组连续地址。这组寄存器最前面的那个地址，就是这个外设的寄存器组地址，也被称为“这个外设的基地址”。
- 最后到了宏 GPIOC_BASE，宏展开为 APB2PERIPH_BASE (APB2 总线
外设的基地址)加上相对 APB2 总线基地址的偏移量 0x1000 得到了 GPIOC 端
口的寄存器组的基地址。


2.C语言关键字volatile：
volatile：告诉编译器“这个变量随时可能变，每次读写都算有副作用”。

作用：禁止对它的读写做省略、合并等优化，保证每次都真正访问内存/寄存器。

典型用途：外设寄存器、中断/多线程共享标志、延时空循环。

不能做的事：不能保证原子性，不能解决所有并发问题。
3.stm32对于库函数的封装：
在 stm32f10x.h 文件中，有以下代码：

```c
代码一
#define GPIOA               ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB               ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC               ((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD               ((GPIO_TypeDef *) GPIOD_BASE)
#define GPIOE               ((GPIO_TypeDef *) GPIOE_BASE)
#define GPIOF               ((GPIO_TypeDef *) GPIOF_BASE)
```

有了这些宏，我们就可以定位到具体的寄存器地址，在这里发现了一个陌 生的类型 GPIO_TypeDef ，追踪它的定义，可以在 stm32f10x.h 文件中找 到如下代码：图1

<img width="721" height="359" alt="Image" src="https://github.com/user-attachments/assets/38b5538c-6d60-4ad8-83a1-aad5d340dc34" />

其中 __IO 也是一个 ST 库定义的宏，宏定义如下：图二
<img width="920" height="470" alt="Image" src="https://github.com/user-attachments/assets/f9340f53-94a7-4d36-939d-f57e8b08e431" />

只要匹配结构体 的首地址，就可以确定各寄存器的具体地址了。图三
<img width="617" height="621" alt="Image" src="https://github.com/user-attachments/assets/46eab5b8-9064-464e-ba38-63b4b12017de" />
分析代码一：GPIOA_BASE 在上一小节已解析，是一个代表 GPIOA 组寄存器的基地址。(GPIO_TypeDef *) 在这里的作用则是把 GPIOA_BASE 地址转换为GPIO_TypeDef 结构体指针类型。

4.STM32的时钟系统

为了实现低功耗，STM32设计了一套功能完善的但却非常复杂的时钟系统。普通的MCU，在配置好GPIO的寄存器后就可以使用，，但是STM32，还需开启外设时钟。

总结：今天晚上修改了隐藏文件，因为昨天晚上在.gitignore隐藏一些不必要的文件，没有自习观察，把所有的文件全部隐藏进去了。还有寄存器的地址是如何来的，stm32有外设四个总线，APB1,2,AHB1,2。了解stm32的时钟系统的一小部分。

2026年1月5号

补充1.4c语言关键字volatile内容和 “只读 / 读写” 这两个概念是可以组合使用的：

- “只读/读写” 是通过 const（是否允许程序修改）来定义的。volatile 只表示“值可能随时变化，禁止优化”，不决定能不能写 。

- 看是否有const关键字，如果有则只允许读，如果没有则允许读写。

- ```
  volatile int *p;        // 指向 volatile int 的普通指针（对象是 volatile）
  int * volatile q;       // 自身是 volatile 的指针，指向普通 int
  const volatile int *r;  // 指向 const volatile int（对象只读且 volatile）
  
  ```

   “对象是否只读/读写”：看对象类型里有没有 const。
  “对象是否 volatile”：看对象类型里有没有 volatile。
   指针本身是否 volatile，只影响指针值是否会被优化缓存，不影响指向对象的读写属性  。


1.时钟的分类:

| 分类方式 | 种类                   | 功能                                                         |
| -------- | ---------------------- | ------------------------------------------------------------ |
| 频率     | 高速时钟和低速时钟     | 高速时钟是提供给芯片主体的主时钟；<br />低速时钟只是提供给芯片中的RTC(实时时钟)及独立看门狗使用 |
| 时钟源   | 内部时钟源与外部时钟源 | 内部时钟是在芯片内部RC振荡器产生的，起震快，在芯片刚刚上电的时候，默认使用是内部高速时钟。<br />而外部时钟信号是由外部晶振输入的，在精度与稳定性上有很大优势，因此上电后通过软件配置，转而采用外部时钟信号。 |
|          |                        |                                                              |

2.如上表所示stm32有4种时钟源：

- 高速外部时钟（HSE）:以外部晶振作为时钟源，晶振频率可取范围为4~16Mhz,我们一般采用8MHZ。

- 高速内部时钟（HSI）：有内部RC震荡器产生，频率为8MHz,但是不稳定。

- 低速外部时钟（LSE）：以外部晶振为时钟源，主要是提供给实时时钟模块提供，一般是32.768KHz。

- 低速内部时钟（LSI）：有内部的RC振荡器产生，也是主要给实时时钟模块供电，一般是40kHz。

  

3.<img width="725" height="794" alt="Image" src="https://github.com/user-attachments/assets/889edcd3-4f24-4795-8c0e-fe4f86a5d940" />

 从 STM32 的 OSC 引脚接外部晶振得到 8MHz 的 HSE 时钟，先经过 PLLXTPRE 分频器（这里选不分频，保持 8MHz），再通过 PLLSRC 开关选 HSE 作为 PLL 的输入，用 PLLMUL 设 9 倍频得到 72MHz 的 PLLCLK；接着经 SW 开关选 PLLCLK 作为系统时钟 SYSCLK（72MHz）；SYSCLK 经 AHB 预分频器（不分频）输出 72MHz 的 HCLK，再通过 APB2 预分频器（不分频），最终让挂载在 APB2 上的 GPIO 外设时钟也达到 72MHz。 

总结：复习昨天看的内容，看了关于volatile与const的读写组合，今天晚上有初步了解8M的外部时钟是如何倍频到72Mhz的。

2026年1月6日

代码点灯，为什么使能时钟的时候是APB2XXX?这个的来源是啥，所有的外设都是这样的吗，如果不是请举例子？
答：问题一:在STM32中不同的外设挂载在不同的总线上，比如APB1、AHB和APB2等，每条总线外设都对应不同的时钟，根据原理图，LED灯连接在GPIOA这个引脚上，根据芯片手册知道，GPIO挂在APB2总线上。因此需在RCC中使能APB2的时钟，逻辑电路才会工作，输出高低电平来点亮LED灯。
问题二：不是，根据所要使用芯片的不同功能选择不同打开不同的时钟总线。比如通用定时器TIM2、3、4在ABP1上面挂在这。

问题总结：根据功能需求先看参考手册里“某个外设挂在哪条总线”，再在 RCC 里打开那条总线对应的外设时钟。



1.HCLK、FCLK、PCLK1、PCLK2了解
2、对于STM32的点灯配置工程配置文件的了解重点是里面的结构体函数

总结：为提前保存导致没有上传上去，明天把这部分的笔记补回来，今天晚上将stm32的系统时钟给看完了，led的结构体没有整理笔记。

昨天晚上未将这部分上传：

| 名称  | 来源                                               | 作用对象                                          | 最大频率              |
| ----- | -------------------------------------------------- | ------------------------------------------------- | --------------------- |
| HCLK  | SYSCLK经过AHB预分频                                | AHB总线、内核、SRAM、FLASH接口、DMA等，CPU主频    | 72MZH                 |
| FCLK  | 与HCLK同源且同步，由由内核作为“自由运行时钟”使用。 | Cortex-M3内核内部逻辑、休眠唤醒与调试跟踪相关机制 | 与HCLKT同步或同步工作 |
| PCLK1 | 由HCLK经APB1预分频器得到。                         | APB1总线外设：TIM2\3\4\5、USART2\3等。            | 36MHZ                 |
| PCLK2 | 由HCLK经APB2预分频得到。                           | APB2总线外设：GPIOA~G、AFIO、ADC1\2等。           | 72MHZ                 |

分频是分频是因为 STM32 既有高速外设又有低速外设，各种外设的工作频率不尽相同，如同 pc 机上的南北桥，
把高速的和低速的设备分开来管理。最后，每个外设都配备了外设时钟的开关，当我们不使用某个外设时，可以把这个外设时钟关闭，从而降低 STM32的整体功耗。





2026年1月7日

LED具体代码分析：

1.先看原理图上LED的连到那个引脚了：PA0、PA1、PA8
<img width="1276" height="789" alt="Image" src="https://github.com/user-attachments/assets/856f24b6-1e6a-4fa4-b1c6-1b08c411f8c4" />

2.要用到那些库文件，stm32f10x_rcc.c、start_stm32f10x_hd.c、core_cm3.c等
3.我编写的文件是USER/main.c

4.配置工程文件与编写用户文件：

- 根据我们这个实验要用到GPIO和RCC这两个片上外设

- 找到配置文件打开stm32f10x_conf.h打开这两文件的注释，让这两个文件生效

- 在user文件中的main.c引入相关的头文件stmf103x_it.c

  <img width="896" height="345" alt="Image" src="https://github.com/user-attachments/assets/a94096a7-69d9-4104-837b-e6d7e1bb6c28" />

  总结今天将昨天后面那部分给看完了，知道这些结构体里面都写的是那些内容。



2026年1月8日

1.在这个初始化代码中：函数初始化中GPIO_InitTypeDef， GPIO_InitStructure;利用库，定义一个名为GPIO_InitStructuref的结构体，结构体的类型为GPIO_InitTypeDef。结构体就是库文件利用关键字typedef封装的新类型。用到stm32f10x_gpio.h这个库中 如图示：
<img width="990" height="395" alt="Image" src="https://github.com/user-attachments/assets/b3ef212f-fb8f-45a6-9102-fee7fdce6ede" />
这个结构体内有三个成员：GPIO_Pin,GPIO_Speed,GPIO_Mode

uint16_t类型的GPIO_Pin为我们将选择配置的引脚，这些stm32f10x_gpio.h文件中有如下定义：
<img width="820" height="445" alt="Image" src="https://github.com/user-attachments/assets/c480c796-59cc-4426-84e4-c65837f6ec0b" />
这些宏的值，就是允许我们给结构体成员 GPIO_Pin 赋的值，如我们给GPIO_Pin 赋值为宏 GPIO_Pin_0，表示我们选择了 GPIO 端口的第 0 个引脚，在后面会通过一个函数把这些宏的值进行处理，设置相应的寄存器，实现我们
对 GPIO 端口的配置。意义为我们将要选择 GPIO的 Pin0、Pin1、Pin8 引脚进行配置。

GPIOSpeed_TypeDef 和 GPIOMode_TypeDef 又是两个库定义的新类型，GPIOSpeed_TypeDef 原型如下：

<img width="251" height="170" alt="Image" src="https://github.com/user-attachments/assets/7b59a668-8882-46ec-ad95-444f8790c292" />

GPIO_Speed_10MHz=1，GPIO_Speed_2MHz=2，GPIO_Speed_50MHz=3。这些常量可用于标识 GPIO 引脚可以配置成的各个最高速度。所以我们在为结构体中的 GPIO_Speed 赋值的时候，就可以直接用这些含义清晰的枚举标识符了。如 led.c 代码中的第 38 行，给GPIO_Speed 赋值为 3，意义为使其最高频率可达到 50MHz。

GPIOMode_TypeDef 也是一个枚举类型定义符，原型如下：

<img width="970" height="470" alt="Image" src="https://github.com/user-attachments/assets/5f9ba0a7-8a53-4a5a-bc0b-f5a3fe69f40b" />
这个枚举类型也定义了很多含义清晰的枚举常量，是用来帮助配置 GPIO引脚的模式的，如 GPIO_Mode_AIN 意义为模拟输入、GPIO_Mode_IN_FLOATING 为浮空输入模式。
我们可以总结 GPIO_InitTypeDef 类型结构体的作用，整个结构体包含 GPIO_Pin 、GPIO_Speed、GPIO_Mode 三个成员，我们对这三个成员赋予不同的数值可以对 GPIO 端口进行不同的配置，而这些可配置的数值，已
经由 ST 的库文件封装成见名知义的枚举常量。

2.初始化库函数——GPIO_Init()

- 在这个函数的内部，实现了把输入的这些参数按照一定的规则转化，进而写入寄存器，实现了配置 GPIO 端口的功能。

- 在我们应用库函数的时候，只需要知道它的功能及输入什么类型的参数，允许的参数值就足够了，这些我们都可以能通过查找库帮助文档获得，或者从官方提供的demo中寻找。

3.开启外设时钟，启动文件及SystemInit()解析

在 startup_stm32f10x_hd.s 启动文件中

```
;Reset_Handler 子程序开始
2. Reset_Handler PROC
3.
4. ;输出子程序 Reset_Handler 到外部文件
5. EXPORT Reset_Handler [WEAK]
6.
7. ;从外部文件中引入 main 函数
8. IMPORT __main 
9.
10. ;从外部文件引入 SystemInit 函数
11. IMPORT SystemInit
12.
13. ;把 SystemInit 函数调用地址加载到通用寄存器 r0
14. LDR R0, =SystemInit
15.
16. ;跳转到 r0 中保存的地址执行程序（调用 SystemInit 函数）
17. BLX R0
18.
19. ;把 main 函数调用地址加载到通用寄存器 r0
20. LDR R0, =__main
21.
22. ;跳转到 r0 中保存的地址执行程序（调用 main 函数）
23. BX R0 
24.
25. ;Reset_Handler 子程序结束
26. ENDP
```

注意啊，这里面有个启动文件还未搞懂，注意
当芯片被复位(包括上电复位)的时候，将开始运行这一段代码，运行过程为先调用了 SystemInit()函数，再进入 c 语言中的 main 函数执行。

这个函数的定义在 system_stm32f10x.c 文件之中。它的作用是设置系统时钟 SYSCLK。函数的执行流程是先将与配置时钟相关的寄存器都复位为默认值，复位寄存器后，调用了另外一个函数 SetSysClock()，SetSysClock()代码如下：

<img width="602" height="364" alt="Image" src="https://github.com/user-attachments/assets/6e3e3bd2-cb14-4ce1-bce6-974cb044ef3e" />

从 SetSysClock()代码可以知道，它是根据我们设置的条件编译宏来进行不同的时钟配置的。

在 system_stm32f10x.c 文件的开头，已经默认有了如下的条件编译定义：
<img width="445" height="685" alt="Image" src="https://github.com/user-attachments/assets/01ae752e-9467-4183-9099-27791649e428" />

SYSCLK_FREQ_72MHz 条件编译的标识符，所以在SetSysClock()函数中将调用 SetSysClockTo72()函数把芯片的系统时钟SYSCLK 设置为 72MHz 当然，前提是输入的外部时钟源 HSE 的振荡频率要为8MHz。

总结：首先复习了一下昨天所看的，并补充了一下笔记，今天看着部分未做，因为再回过头整理时，发现里面的部分代码未点击去了解，gpio初始化中比较重要的部分是，对于寄存器的某一位进行一个操作，将某一位置零，需将1位移到对应的位置，然后取反进行一个与操作。置一的话只需将1位移对应的位置进行一个或操作。



2026年1月6日
1.在我这个代码中，调用这个函数RCC_APB2PeriphClockCmd()，调用的时候需要向它输入两个参数，一个参数为将要控制的，挂载在 APB2总线上的外设时钟，第二个参数为选择要开启还是关闭该时钟。

2.注意在使用这些函数的时候，开启时钟注意看挂在那个时钟线上，开启对应的时钟。

3.通过控制GPIO的引脚电平的高低，只要控制住GPIOX__BSRR寄存器即可。用GPIO_SetBits()输出高电平，和GPIO_ResetBits()控制低电平。

4.C语言知识点“\”是须行符，用来连接上下行的代码；

- ​	 将 char 型变量 a 的第七位(bit6)清 0，其它位不变。

```
 a &= ~(1<<6); //括号内 1 左移 6 位，得二进制数：0100 0000 
 //按位取反，得 1011 1111 ，所得的数与 a 作”位与&”运算，
 // a 的第 7 位（bit6）被置零，而其它位不变。
```

-   同理，将变量 a 的第七位(bit6)置 1，其它位不变的方法如下。

```
 a |= (1<<6); //把第七位（bit6）置 1，其它为不变
```

-  将变量 a 的第七位(bit6)取反，其它位不变。

```
a ^=(1<<6); //把第七位（bit6）取反，其它位不变
```



总结：今天看了systick滴答定时器工作分析这一部分，了解到里面有四个位，使能位，异常 触发位，时钟选择为，以及计数标志位。知道是如何进行一个精准的延时，这部分的内容。以及前一部分的总结。



2026年1月10日

1.GPIO初始化，定义局部变量==》用断言进行一个合法性的检查==》GPIO模式的配置==》 对于GPIO_CRL寄存器的低8位进行一个配置，对于GPIO_CRH进行一个配置==》并将其更新到寄存器中。

<img width="1604" height="2895" alt="Image" src="https://github.com/user-attachments/assets/d47639de-8eec-454c-a604-696c6cbf0ff5" />

2.了解到库函数开发与寄存器开发优缺点对比：

| 开发方式 | 优点                                                         | 缺点                                                         |
| -------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| 寄存器   | 直接控制寄存器，运行效率高。<br />精确控制每个寄存器，灵活。 | 1.开发难度大，开发周期长<br />2.代码阅读性较差，可移植差<br />3.后期维护成本高 |
| 库函数   | 开发速度快，易上手。<br />可读性好，可移植性强。             | 相对于寄存器开发，运行效率略低。                             |



3.操作系统和有所有使用了时基的系统，都必须要一个硬件定时器来产生需要的“滴答”中断，作为整个系统的时基。滴答中断对操作系统尤其重要。

4.systick是一个24位的定时器，及一次最多计数2^24个时钟脉冲，脉冲计数值被保存到 当前计数值寄存器 STK_VAL (SysTick current value register）中。只能向下计数，当STK_VAL的值减少到0的时候，硬件自动把重装载寄存器的值STK_LOAD，（SysTick reload value register）中保存的数据加载到 STK_VAL，重新向下计数。当 STK_VAL 的值被计数至 0 时，触发异常，就可以在中断服务函数中处理定时事件了。

5.systick若进行工作必须进行寄存器的配置，三个控制位和一个标志位，都位于STK_CTRL寄存器中（SysTick control and status register ）

<img width="731" height="204" alt="Image" src="https://github.com/user-attachments/assets/d9898e35-3e99-433e-a430-b7e6d9209251" />
Bit0: ENABLE
为 SysTick timer 的使能位，此位为 1 的时候使能 SysTick timer，此位为 0
的时候关闭 SysTick timer。
Bit1：TICKINT
为异常触发使能位，此位为 1 的时候并且 STK_VAL 计数至 0 时会触发
SysTick 异常，此位被配置为 0 的时候不触发异常
Bit2：CLKSOURCE
为 SysTick 的时钟选择位，此位为 1 的时候 SysTick 的时钟为 AHB 时钟，
此位为 0 的时候 SysTick 时钟为 AHB/8（AHB 的八分频）。
Bit16：COUNTFLAG
为计数为 0 标志位，若 STK_VAL 计数至 0，此标志位会被置 1。

总结：今天看完了关于中断的函数的文档内容，在尝试写systick代码遇到困难不知道如何去写这个代码，只知道配置相关的寄存器，但是里面的简单逻辑自己却不知道如何写。重点编程，明天务必搞懂力扣的一到C语言题。

2026年1月11日

1.所有的GPIO引脚都可以用作外部中断源的输入，每个GPIO有16个引脚，所有的GPIO引脚都可以做为外部中断源的输入，一个有8种模式，不同的对应不同的复用功能。

下面这个图是GPIO的8种模式及其应用的场合

<img width="728" height="428" alt="Image" src="https://github.com/user-attachments/assets/43a4dc0d-5ecb-47a4-951a-1cad7ed50172" />

2.四种输入模式：

- 上下拉输入：与VDD相连的为上拉电阻，与Vss相连的是下拉电阻。在连接到施密特触发器，把电压信号转化为数字信号存储在输入数据寄存器中(IDR)。我们通过设置配置寄存器(CRL、CRH)，控制两个开关。于是就可以得到上下拉输入。
  GPIO配置为上拉输入模式，在默认状态下(GPIO引脚无输入)，读取的GPIO引脚数据为1，高电平。而下拉则相反，默认状态下其引脚的为0，低电平。

- stm32的浮空输入模式下，在他的芯片内部既没有上拉也没有下拉，经由施密特触发器输入，配置成这个模式，用电压表测量电压为1点多伏，电压值不确定。由于阻抗值较大，一般把这种模式用于标准的通信协议，如IIC和USART的接收端。

- 模拟输入模式(GPIO_Mode_AIN )则关闭了施密特触发器，不接上、下拉电阻，经由另一线路把电压信号传送到片上外设模块。如传送至给 ADC 模块，由ADC 采集电压信号。所以使用 ADC 外设的时候，必须设置为模拟输入模式。

3.四种输出模式：

补充P-MOS与N-MOS:

- N沟道和P沟道MOS管是MOSFET的主要两种类型，主要区别在于沟道载流子、导通条件和性能特点。

- N沟道MOS管的源极和漏极为N型半导体，载流子为电子，迁移率高。

- P沟道MOS管的源极和漏极为P型半导体，载流子为空穴，迁移率较低。

- 导通条件：

  | 特性     | N沟道MOS管      | P沟道MOS管      |
  | -------- | --------------- | --------------- |
  | 栅压特性 | Vgs>Vth(正电压) | Vgs<Vth(负电压) |
  | 电流方向 | D-->S（漏到源） | S-->D(源到漏)   |
  | 阈值电压 | 正值（2~5V）    | 负值(-2~5V)     |

- 性能对比:N沟道导通电阻低、开关速度快，适合高频高功率应用如电机驱动；P沟道成本较高但易实现高端驱动，常用于电源开关。

<img width="1223" height="814" alt="Image" src="https://github.com/user-attachments/assets/79515dd3-ad2f-4862-bb38-0ac3b6ecfc4e" />

符号关键的特证：

- N沟道符号的箭头从源极指向栅极，表示P型衬底指向N型沟道。

P沟道符号的箭头从栅极指向源极，反向表示N型衬底指向P型沟道。 

增强型和耗尽型MOS管的电路符号区别在于沟道线条：增强型用虚线表示需栅压诱导沟道，耗尽型用实线表示Vgs=0时已有沟道。

符号特证：增强型MOS管符号中，源漏间沟道为虚线，强调无栅压时截止。耗尽型MOS管沟道为实线，常带小箭头表示内置通道，可正负栅压导通。

| 类型   | 沟道表示 | N沟道箭头 | P沟道箭头 | 典型状态  |
| ------ | -------- | --------- | --------- | --------- |
| 增强型 | 虚线     | 向内      | 向外      | Vgs=0截止 |
| 耗尽型 | 实线     | 向内      | 向外      | Vgs=0导通 |

- 结构图的下半部分为输出模式：
- 为普通推挽输出(GPIO_Mode_Out_PP )、普通开漏输出 (GPIO_Mode_Out_OD)及复用推挽输出(GPIO_Mode_AF_PP )、复用开漏输出(GPIO_Mode_AF_OD )。

- 线路经过一个由P-MOS与N-MOS管组成的单元电路。在输出高电平时，P-MOS管导通，低电平N-MOS管导通。两个模式管轮流导通，一个负责灌电流，一个负责拉电流。使其负载能力和开关的速度比普通的方式有很大的提高。推挽输出的电平为低电平0，高电平为3.3v。
- 若控制输出为 1 (无法直接输出高电平)，则既不输出高电平，也不输出低电平，为高阻态。为正常使用时必须在外部接上一个上拉电阻。它具“线与”特性，即很多个开漏模式 引脚连接到一起时，只有当所有引脚都输出高阻态，才由上拉电阻提供高电平，此高电平的电压为外部上拉电阻所接的电源的电压。若其中一个引脚为低电平，那线路就相当于短路接地，使得整条线路都为低电平，0 伏。
- 普通推挽输出模式一般应用在输出电平为 0 和 3.3 伏的场合。而普通开漏输出一般应用在电平不匹配的场合，如需要输出 5 伏的高电平，就需要在外部接一个上拉电阻，电源为 5 伏，把 GPIO 设置为开漏模式，当输出高阻态时，由上拉电阻和电源向外输出 5 伏的电平。
- 对于相应的复用模式，则是根据 GPIO 的复用功能来选择的，如 GPIO 的引脚用作串口的输出，则使用复用推挽输出模式。如果用在 IC、SMBUS 这些需要线与功能的复用场合，就使用复用开漏模式。

注意：在使用任何一种开漏模式，都需要接上拉电阻。

按键的电路图：
<img width="1021" height="540" alt="Image" src="https://github.com/user-attachments/assets/3a7bf090-a927-45f7-8496-b1bfff0dbf3e" />



总结：下午复习了一下之前在力扣上所写的两数相加，第一步创建一个链表，第二步创建一个新的结点，然后初始化并进行一个赋值。第三步，创建一个虚拟的头结点，进行一个链表的遍历，并将这两个链表的相对应位置的数值进行一个相加；将数值进行一个处理，只保留个位数；在将这个数值赋值到，相对应的结点。最后将这个链表赋值给最终返回的那个，这个链表释放，并返回最终存储数据那个链表的结果。
然后复习了按键中断，和输入输出的8种模式，感觉需要进行编程才能记住，还学习了P与Nmos管。



2026年1月12日

看了按键点灯的实验写了代码，但是有问题需要更改。

2026年1月13日

加了一个电平反转的功能，但是代码还是有问题，没有解决；昨天的枚举定义的格式写错了，今天看了一部分中断的相关内容，按键点灯这个，由于准备按键1对应1号灯，按键2对应2号灯虽然实现但是效果不好，代码需要重新整理，思路还是不清晰。



2026年1月14日

今天晚上加了个打印函数来判断，按键是否按下，代码中未定义DEBUG的宏导致，无法打印。排查下来按键功能正常，对于串口的配置有了一个初步的了解，看了一小部分的中断笔记。



2026年1月15日

今天晚上发现在反转led灯时，我直接操控寄存器进行一个反转或者进行一个异或来处理。读取 PC3 的当前
输出电平，然后再用 1 减去读取得的电平数据状态，相当于获取一个也当前输出相反的状态，再把这个相反的状态利用 GPIO_WriteBit()函数写入到 PA1，从而实现了输出状态取反的功能。

```
	uint16_t odr = GPIOx->ODR;// 读取当前输出状态

	GPIOx->BSRR = (odr & GPIO_Pin) << 16 | (~odr & GPIO_Pin);// 利用BSRR寄存器翻转

	GPIOx->ODR ^= GPIO_Pin;// 直接异或翻转
```

而文档上则是读取当前的状态，然后写入返回值，还有在设置浮空输入是不用设置最大速度，gpio_init函数会自动忽略它的。然后看了中断和中断异常，了解中断向量表。



2026年1月15日

中断控制器 NVIC (Nested Vectored Interrupt Controller)。NVIC 是属于 Cortex 内核的器件，不可屏蔽中断 (NMI)和外部中断都由它来处理，而 SYSTICK 不是由 NVIC 来控制的。STM32 的中断向量具有两个属性，一个为抢占属性，另一个为响应属性，其属性编号越小，表明它的优先级别越高。
<img width="737" height="488" alt="Image" src="https://github.com/user-attachments/assets/0f83590a-9715-4ddb-b8c3-f9dbaf5e13f2" />*Modules->
STM32F10x_StdPeriph_Driver-* misc* 查找到一个 *NVIC_Init()* 函数，对 NVIC 初始化，首先要定义并填充一个 NVIC_InitTypeDef* 类型的结构体。
首先要用 NVIC_IRQChannel 参数来选择将要配置的中断向量，用 NVIC_IRQChannelCmd 参数来进行使能(ENABLE)或关闭（DISABLE）该中断。在 NVIC_IRQChannelPreemptionPriority 成员要配置。
中断向量的抢占优先级，在 NVIC_IRQChannelSubPriority 需要配置中断向量的响应优先级。

2026年1月16日

1.STM32 的中断向量具有两个属性，一个为抢占属性，另一个为响应属性，其属性编号越小，表明它的优先级别越高。

2.抢占，是指打断其它中断的属性，即因为具有这个属性，会出现嵌套中断(在执行中断服务函数 A 的过程中被中断 B 打断，执行完中断服务函数 B 再继续执行中断服务函数 A)，抢占属性由NVIC_IRQChannelPreemptionPriority 的参数配置。而响应属性则应用在抢占属性相同的情况下，当两个中断向量的抢占优先级相同时，如果两个中断同时到达，则先处理响应优先级高的中断，响应属性由 NVIC_IRQChannelSubPriority 的参数配置。

3.Cortex‑M3/M4 内核给每个中断分配 8 位优先级寄存器字段，但STM32 只实现了高 4 位，所以只有 16 个有效优先级等级（0–15）。这 4 个有效位可以再拆成两部分：一部分用于抢占优先（Preemption Priority），一部分用于 子 优先级（SubPriority）。

4.NVIC 中“数值越小优先级越高”，0 是最高优先级，15 是最低优先级。判断谁先响应该看：先比抢占优先级；如果相同，再比子优先级；如果还相同，再看中断向量号（通道号）谁小谁先。
5.配置中断通道用到了定时器2

```
NVIC_InitTypeDef NVIC_InitStructure;

NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;                 // 选择中断通道
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;       // 抢占优先级（0 最高）
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;              // 子优先级
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 // 使能
NVIC_Init(&NVIC_InitStructure);
```

6.设计优先级策略示例

- 抢占 0：最关键实时中断（如高精度定时、紧急故障处理）。

- 抢占 1：一般实时（如通信接收、主控定时）。


- 抢占 2：低实时性（如按键扫描、状态刷新）。

  

同一抢占级内部再用子优先级区分谁先服务。

看了外部中断，明天上传代码。



2026年1月18日
1.EXTI外部中断，STM32的所有GPIO 都引入到EXTI外部中断线上，使得所有的GPIO都能作为外部中断的输入源。

<img width="658" height="796" alt="Image" src="https://github.com/user-attachments/assets/141c0f80-6545-45e6-8b61-682fbe8124f8" />

PA0~PG0 连接到 EXTI0 、PA1~PG1 连接到EXTI1、 ……、 PA15~PG15 连接到 EXTI15。这里大家要注意的是：PAx~PGx端口的中断事件都连接到了 EXTIx，即同一时刻 EXTx 只能相应一个端口的事件触发，不能够同一时间响应所有 GPIO 端口的事件，但可以分时复用。配置为上升沿触发，下降沿触发或双边沿触发。EXTI 最普通的应用就是接上一个按键，设置为下降沿触发，用中断来检测按键。

2.在EXTI的实验代码中,开发板用到的是PF8，在EXTI8的外部中断线上。

3.总结发现用按键中断来电灯比之前用按键延时的效果要好。
延时方案 = CPU 一直盯着表等时间；中断方案 = 有事再叫 CPU，所以中断方式自然更灵敏、效果也更好。





2026年1月19日

1.下面是完成了一般配置一个 I/O 为 EXTI 中断的步骤，主要为功能：

1. 使能 EXTIx 线的时钟和第二功能 AFIO 时钟
2. 配置 EXTIx 线的中断优先级
3. 配置 EXTI 中断线 I/O
4. 选定要配置为 EXTI 的 I/O 口线和 I/O 口的工作模式
5. EXTI 中断线工作模式配置

```

    GPIO_InitTypeDef GPIO_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;

    // 使能 GPIOF 和 AFIO 时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF|RCC_APB2Periph_AFIO,ENABLE);

    // 配置 PF8 为上拉输入
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
    GPIO_Init(GPIOF,&GPIO_InitStructure);//初始化 GPIOF8
   
    // 连接 EXTI8 到 PF8
    NVIC_Configuration();

    /*
    * 配置 EXTI Line8
    *   选择 EXTI8
    *   中断模式
    *  下降沿触发
    *  使能 EXTI8
    *  GPIO_EXTILineConfig();
    *    
    *   
    */
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOF,GPIO_PinSource8);
    EXTI_InitStructure.EXTI_Line=EXTI_Line8;//选择 EXTI8
    EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;//中断模式
    EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;//下降沿触发
    EXTI_InitStructure.EXTI_LineCmd=ENABLE;//使能 EXTI8     
    EXTI_Init(&EXTI_InitStructure);//根据 EXTI_InitStructure 结构体初始化 EXTI8

static void NVIC_Configuration(void){
    NVIC_InitTypeDef NVIC_InitStructure;

    /* 配置 EXTI9_5 中断 */
    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//使能 EXTI9_5 中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0;//抢占优先级 0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0;//响应优先级 0
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能中断通道
    NVIC_Init(&NVIC_InitStructure);//根据 NVIC_InitStructure 结构体初始化 NVIC
    
}
```



2.调用 RCC_APB2PeriphClockCmd() 时还输入了参数 RCC_APB2Periph_AFIO，表示开启 AFIO 的时钟。
AFIO (alternate-function I/O)，指 GPIO 端口的复用功能，GPIO 除了用作普通的输入输出(主功能)，还可以作为片上外设的复用输入输出，如串口，ADC，这些就是复用功能。大多数 GPIO 都有一个默认复用功能，有的 GPIO 还有重映射功能， 重映射功能是指把原来属于 A 引脚的默认复用功能，转移到了B 引脚进行使用，前提是 B 引脚具有这个重映射功能当把 GPIO 用作 EXTI 外部中断 或使用重映射功能的时候，必须开启 AFIO时钟，而在使用默认复用功能的时候，就不必开启 AFIO 时钟了。

3.*NVIC_PriorityGroupConfig()*库函数，把 NVIC 中 断优先级分组设置为第 1 组。接下来将NVIC_IRQChannel=EXTI9_5_IRQn这个固定的参数，写入的参数在这stm32f10x.h 文件的 IRQn 类型定义中查找到。然后在配置抢占优先级和响应优先级即可完成，最后在NVIC_Init中调用该函数。

4.在这个 EXTI 设置中我们把 PF8 连接到内部的 EXTI5，GPIO 配置为上拉输入，工作在下降沿中断。在外围电路上我们将 PF8 接到了 key1 上。当按键没有按下时，PF8 始终为高，当按键按下时 PF8 变为低，从而 PF8 上产生一个下降沿跳变，EXTI5 会捕捉到这一跳变，并产生相应的中断，中断服务程序在stm32f10x_it.c 中实现。

5.中断服务函数的名 字必须要跟启动文件 *startup_stm32f10x_hd.s* 中的中断向量表定义一致。

在这个 EXTI 设置中我们把 PF8 连接到内部的 EXTI5，GPIO 配置为上拉输入，工作在下降沿中断。在外围电路上我们将 PF8 接到了 key1 上。当按键没有按下时，PF8 始终为高，当按键按下时 PF8 变为低，从而 PF8 上产生一个下降沿跳变，EXTI5 会捕捉到这一跳变，并产生相应的中断，中断服务程序在stm32f10x_it.c 中实现。

6.看了中级篇的usart串口打印，在之前已实现，主要了解一下串口的协议。



2026年1月20日

1.把 STM32 的 PA10 引脚(复用功能为 USART1 的 Rx)接到了 H2 接口的第 2 针脚，把 PA9 引脚(复用功能为 USART 的 Tx)连接到了 H2 接口的第 3 针脚。Tx（发送端）接第 3 针脚，Rx（接收端）接第 2 针脚。如图二
串口线主要分两种，直通线（平行线）和交叉线。它们的区别见图 3。假如 PC 与板子之间要实现全双工串口通讯，必然是 PC 的 Tx 针脚要连接到板子的 Rx 针脚，而 PC 的 Rx 针脚则要连接至板子的 Tx 针脚了。由于板子和 pc的串口接法是相同的，就要使用交叉线来连接了。如果有的开发板是 Tx 连接至H2 的第 2 针脚，而 Rx 连接至第 3 针脚，这与 PC 接法是相反的，这样的板子与 PC 通讯就需要使用直通线了。

<img width="1004" height="734" alt="Image" src="https://github.com/user-attachments/assets/158d4aa4-b9d2-4a5a-9353-9851c666f00d" />图一
<img width="297" height="182" alt="Image" src="https://github.com/user-attachments/assets/8c265663-5e88-4d09-8c56-62abf81914d4" />图二

<img width="622" height="757" alt="Image" src="https://github.com/user-attachments/assets/c6a90b21-6766-4dbc-a476-fd31ba1393b6" />图三
2.由三个部分组成，分别是波特率的控制部分、收发控制部分及数据存储转移部分。
发送数据的流程：PCLK 产生位时钟 → 波特率发生器 → 发送移位寄存器按位输出 → TDR 作为 CPU/DMA 和移位寄存器之间的缓存 → SR 标志配合 CR1/中断控制整个发送流程。

<img width="695" height="747" alt="Image" src="https://github.com/user-attachments/assets/d4ae4902-75ee-4ff3-ae56-6ce7a5ac03f1" />
3.围绕着发送器和接收器控制部分，有好多个寄存器：CR1、CR2、CR3、SR，即 USART 的三个控制寄存器(Control Register)及一个状态寄存器(Status Register)。通过向寄存器写入各种控制参数，来控制发送和接收，如奇偶校验位，停止位等，还包括对 USART 中断的控制；串口的状态在任何时候都可以从状态寄存器中查询得到。

4.当我们需要发送数据时，内核或 DMA 外设把数据从内存(变量)写入到发送数据寄存器 TDR 后，发送控制器将适时地自动把数据从 TDR 加载到发送移位寄存器，然后通过串口线 Tx，把数据一位一位地发送出去，在数据从 TDR 转移到移位寄存器时，会产生发送寄存器TDR 已空事件 TXE，当数据从移位寄存器全部发送出去时，会产生数据发送完成事件 TC，这些事件可以在状态寄存器中查询到。
而接收数据则是一个逆过程，数据从串口线 Rx 一位一位地输入到接收移位寄存器，然后自动地转移到接收数据寄存器 RDR，最后用内核指令或 DMA读取到内存(变量)中。

总结：今天晚上了解了理论知识，知道数据是如何从串口进行一个传输。



2026年1月21日 

1.编译器中设置一个选项 Use MicroLIB (使用微库)，的作用不单单是为了打印，是为了让工程用上 更小、更精简的 C 运行库，在 STM32 这类 Flash / RAM 比较有限的单片机上能明显减小程序体积。
<img width="626" height="470" alt="Image" src="https://github.com/user-attachments/assets/5d9435c1-96fb-4318-99d2-b7e470c8457d" />
2.课件中给的重定向代码看的不是很明白需要自己实现以下，与我自己所用的有不同的地方。
3.总结：明天把代码给弄明白，自己的c太差了。

2026年1月22日
1.串口打印的代码：函数框架
第一步：参数：value-要转换的数字，string-存储结果的字符数组，radix-进制，定义变量有字符串指针

第二步：十进制判断，其他进制返回值为空：值为0单独处理：进行非负检查，只处理正数。for循环是将数字进行一个拆分，按照位序进行一个输出。

2.USART1_printf：自制串口版 printf:
第一步：va_list ap; va_start(ap, Data);：为读取 ... 做准备，ap 是一个“指针”，指向 Data 后面的第一个参数。
第二步：.while循环只要当前字符不是 '\0'（结束符），就继续处理。
情况一：格式字符串里的 "\\r" 或 "\\n"（实际代码里写的是 "\r"、"\n"）就会变成真正的回车/换行字符发出去。
情况二：当前字符是 %，说明它后面紧跟一个类型标志（如 d 或 s）
情况三：普通字符无论是哪种情况，最后都会等 TC 置 1（发送完成）后再继续。



2026年1月24日

1.adc简介：ADC (Analog to Digital Converter)，模/数转换器。在模拟信号需要以数字形式处理、存储或传输时，模/数转换器几乎必不可少。通道的 A/D 转换可以单次、连续、扫描或间断模式执行。ADC 的结果可以左对齐或右对齐方式存储在 16 位数据寄存器中。模拟看门狗特性允许应用程序检测输入电压是否超出用户定义的高/低阀值。

2.分辨率是12位，不能直接测量负电压，所以没有符号位，即其最小量化单位。
$$
LSB = Vref+ / 212
$$
3.转换时间是可编程的。采样一次至少要用 14 个 ADC 时钟周期，而 ADC 的时钟频率最高为 14MHz，也就是说，它的采样时间最短为 1us。足以胜任中、低频数字示波器的采样工作。

4.转换时间是可编程的。采样一次至少要用 14 个 ADC 时钟周期，而 ADC 的时钟频率最高为 14MHz，也就是说，它的采样时间最短为 1us。足以胜任中、低频数字示波器的采样工作。

5.ADC 的类型决定了它性能的极限，STM32 的是逐次比较型 ADC。

6.它的参考电压负极是要接地的，即 Vref- = 0V。而参考电压正极的范围为 2.4V≦Vref+ ≦3.6V,所以 STM32 的 ADC 是不能直接测量负电压的，而且其输入的电压信号的范围为：VREF- ≦ VIN ≦ VREF+。当需要测量负电压或测量的电压信号超出范围时，要先经过运算电路进行平移或利用电阻分压。

2026年1月25日

今天复习了串口的相关知识，并练习了串口打印的代码，未能实现，编译无报错但是，打断点却卡主无法打印，问题未解决。在练习代码时，知道要设置那些参数，以及引脚设置的模式。明天解决这个问题。

1.STM32 的串口（USART/UART）本质就是用 TX/RX 两根线按一定格式把比特一个一个串行发出去，常用参数有波特率、数据位、校验位和停止位，最常见配置是 115200、8N1（8 位数据、无校验、1 位停止）。

2.硬件内部有发送/接收数据寄存器（TDR/RDR），还有状态位 TXE、TC、RXNE：写入 TDR 后数据被移位寄存器一位位发出，TDR 空时 TXE=1 表示可以写下一个字节，最后一位发完时 TC=1 表示整帧发送完成，而接收完一个字节放进 RDR 时 RXNE=1 提示软件来读。串口初始化的步骤基本固定：开 GPIO 和 USART 时钟、把 TX 配成复用推挽输出、RX 配成输入，然后设置波特率/数据位/停止位/校验，最后使能 USART，如需中断再打开 RXNE/TXE 中断并在 NVIC 里设置优先级。

3.软件层面可以用三种方式收发：轮询时不停检查 TXE/RXNE 后读写寄存器，简单但占用 CPU；中断方式在 RXNE/TXE 置位时自动进中断函数里处理，适合一般应用；DMA 方式把一大片数据交给 DMA 自动搬运，CPU 负担最小，适合高速或大批量数据。 对于打印调试信息，自己写一个简化版 printf（手动解析 %d/%s 再用 USART_SendData 发），也重写了fputc 。



2026年1月25日

1.gpio初始化的时候，初始化只初始化一次导致，Tx未进行推完输出的设置；第二个就是USART1_printf 函数里 %d 的处理分支忘了在循环中调用 USART_SendData，只在等待 TC 标志却从未真正发送整数对应的字符，同时 \n 还写成了 0xA0 而不是标准换行 0x0A，这些错误叠加起来就表现为“代码里写了 printf/USART1_printf，却在串口终端看不到或看不全想要的输出”。

2.模拟电压 → 通道选择 → 采样保持 → 12 位转换 → 数据寄存器（或 DMA/中断）

<img width="544" height="666" alt="Image" src="https://github.com/user-attachments/assets/aac43a77-bdb7-4e18-92d6-d9f0eccecff8" />

- 左侧有很多模拟源（外部通道 ADC_INx、内部温度传感器、内部参考电压等），通过模拟多路开关和 GPIO 连接到 ADC 前端，选择好要采样的那一路后送入“采样保持电路”。
- 中间部分是核心转换单元：采样保持电路在设定的采样时间内把通道电压“抓住”，随后 12 位逐次逼近 ADC（SAR）在 ADCCLK 驱动下完成转换，得到 12 位数字结果，并可通过模拟看门狗比较高低阈值产生中断。
- 左下和右下展示触发机制：规则组和注入组都可以由软件启动，也可以由定时器（TIMx_TRGO/CHx）、外部中断线（EXTI11、EXTI15 等）作为外部触发源，触发选择由 EXTSEL/JEXTSEL 与 EXTRIG 控制位决定，从而实现定时采样或事件驱动采样。

2026年1月26日

今天晚上重新将systick的代码写了一遍跟之前实现的方法不太一样，并且学习了adc不同的转换模式，按照次数分为单次转换和连续转换，再按“通道”来分，有非扫描模式和扫描模式。 非扫描就是只采一个通道，配置和使用最简单；扫描模式则是你在规则序列里排好多个通道，ADC 会按顺序一个个转换，可以是“单次扫描一遍就停”，也可以配合连续模式“扫完又从头开始循环”。