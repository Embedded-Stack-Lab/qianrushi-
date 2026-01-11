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

