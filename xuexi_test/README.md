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
![1767279616168](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\1767279616168.png)

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