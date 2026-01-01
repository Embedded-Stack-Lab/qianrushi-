# xuexi_test
//测试上传

创建工程遇到的难题

第一个问题是：没有正确的进行文件的创建

出现了这个情况，导致我以为自己的电脑没有装stm32 的芯片支持包。 ![image.jpg](https://ppl-ai-file-upload.s3.amazonaws.com/web/direct-files/attachments/images/155685023/ddb70557-bcb4-4f4f-a7a6-2fa2506566ba/image.jpg?AWSAccessKeyId=ASIA2F3EMEYEYT62ROSI&Signature=5fIbIjD88LP8ZkCPctu6SNHeACo%3D&x-amz-security-token=IQoJb3JpZ2luX2VjEB4aCXVzLWVhc3QtMSJHMEUCIQCe2mMNLFWplAFFRC%2BF84JijU0ceKvYzV4wvs%2F8NRk3GAIgDswwreuFM8%2BQ6IuHAqLy84Zn8ZKYxm%2FPxTd2bwB0Xj0q%2FAQI5%2F%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FARABGgw2OTk3NTMzMDk3MDUiDHpyI1HqD8phBbWxlirQBH5h4KF8KcRscbTNIQvtsiuAbJQofzs%2B6GLUM%2FpR3fts6T185IlKhWkPn%2BFfyCUyipf32DAooXgJl8QEGcJy3Jkvv1jhecfEXMBvcN4rFbJNbWkp%2FbalsTCBZiVtxJ1QIwZ9EivuI8KUI4GYboYr8i7k%2BrOWACzKc6S1OxYwLIsv0b5bvtnCssgyFW3%2BTXqObTrRXLtInQYqNRuWUeYzqkVtS%2B6FurDyPAPLnNKW9XKKk1QxzdLs9l%2Bqr4qoR96DNdNl2t2E2KFSk9LuqYd0fH8ykKIgseP8GBG%2BdGXShdGqRSHkB%2BZQi2%2B8Je5jJXOdNLaPTIS4M4yNZ78tG5nHjB4d1bExL5as1CKxKqiaWQsJ1%2BjtLWevLTdr%2B%2BdOiHUs%2F1tHStUSgDqPsxwhhEwfAFIa5GKALjTLeXHLoRQ8RgI3EjGDXCzfMSqmmumduaoThDpXgJjKwyqXqwN0lezVxKDBdSGCd2xKiB9kXbGqMw1OnZDALRH0BPB45n0MXMoLyd%2BZ1tmAHVAV3NzzBY16WHEpJKs%2FlFMsw%2Ffblg%2BCbbTVe8wSWPWu1zrU5U026B8w2teswMt9rB0DKNVNtRDZZArcWiHp%2BLXnOrSkpBDQcPLVy35qQwHOzpyuaXhWvEYRurtrbf6Uw826%2BnQtVy6EDdF7hTgjuxoNtBpLKcfPGt%2BsRWV9GjyPLtrBPDCAJ57MhpQ0B6tWwP9eZ%2BSvNmQY4PX0Q4Oo%2F8iY2EpkAiK1br%2FWLDAHf%2BkRZd0s1Mbb1gy%2BPx5nXnOGjOkb1ZsnTVTcczgwnu7ZygY6mAFhgvXxXF4GY2q3WNp17QHPL508inIv3UE5ZEURsPUGluNWB2wbPl5n8ctcBvRfyj8T9uquPalMqAAVtDJglwCMwlqEOxVZuLMUDXlw%2F7m2oCXrjrkNLFItdZEqA%2Bv4KAFvO7bB5dqg9PtLb91mG1UoXeyIIPLS8OvJBK4MfUn8BkdahZlef5D3fnLQUyg9gWBbRPXqVAk%2BCw%3D%3D&Expires=1767275972) 

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
