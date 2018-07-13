#ifndef _ICU_H_
#define _ICU_H_
#include "types.h"
#define	BASE_ICU_PTR	\
		((HW_ICU*)0x00800000)

#define	PID_CEVA			0
//[0]: CEVA中断使能
#define	PID_GPIO			1
//[1]: GPIO中断使能
#define	PID_BK24			2
//[2]: BK24_BB中断使能
#define	PID_PWM				3
//[3]: PWM中断使能
#define	PID_UART			4
//[4]: UART中断使能
#define	PID_RTC				5
//[5]: RTC中断使能
#define	PID_ADC				6
//[6]: ADC中断使能
#define	PID_SPI				7
//[7]: SPI中断使能
#define	PID_I2C0			8
//[8]: I2C0中断使能
#define	PID_3DS				9
//[9]: 3DS中断使能
#define	PID_EXT_TIME		10
//[10]: EXT_TIME中断使能
#define	PID_I2C1			11
//[11]: I2C1中断使能
#define	PID_TIMER			12
//[12]: 16bit TIMER中断使能

#pragma anon_unions
typedef struct HW_ICU{
	union{
		uint32 REG_0x0;
		struct{
			uint32 CLK_SRC_SEL:2;
			//时钟源(clk_src)选择：;00: 32KHz ;01: 16MHz Crystal. Reset value.;10: Reserved;11: PLL clock. 96MHz in BK3231S.
#define ICU_CLKSRC_32K \
    0

#define ICU_CLKSRC_16M \
    1

#define ICU_CLKSRC_PLL \
    3
			uint32 :30;
		};
	};
	union{
		uint32 REG_0x1;
		uint32 core;
		struct{
			uint32 CORE_PWD:1;
			//ARM9 Core时钟关闭信号：;0：工作时钟打开;1：工作时钟关闭;【说明】：时钟源为clk_src
			uint32 CORE_DIV:2;
			//ARM9 Core时钟分频信号：;Fclk_core = Fclk_src / core_div
#define ICU_MAKE_CoreClk(srcfr,fr) \
    ((srcfr)/(fr))
			uint32 :5;
			uint32 :24;
		};
	};
	union{
		uint32 REG_0x2;
		uint32 adc;
		struct{
			uint32 ADC_PWD:1;
			//ADC时钟关闭信号：;0：工作时钟打开;1：工作时钟关闭;【说明】：时钟源为clk_16m
			uint32 ADC_DIV:7;
			//ADC时钟分频信号：;Fclk_adc = Fclk_16m/ (adc_div + 1)
			uint32 :24;
		};
	};
	union{
		uint32 REG_0x3;
		uint32 uart;
		struct{
			uint32 UART_PWD:1;
			//UART时钟关闭信号：;0：工作时钟打开;1：工作时钟关闭;【说明】：时钟源为16MHz
			uint32 :31;
		};
	};
	union{
		uint32 REG_0x4;
		uint32 i2c;
		struct{
			uint32 I2C0_PWD:1;
			//I2C0工作时钟关闭信号：;0：工作时钟打开;1：工作时钟关闭;【说明】：时钟源为16MHz
			uint32 :15;
			uint32 I2C1_PWD:1;
			//I2C1工作时钟关闭信号：;0：工作时钟打开;1：工作时钟关闭;【说明】：时钟源为16MHz
			uint32 :15;
		};
	};
	union{
		uint32 REG_0x5;
		uint32 spi;
		struct{
			uint32 SPI_PWD:1;
			//SPI工作时钟关闭信号：;0：工作时钟打开;1：工作时钟关闭;【说明】：时钟源为16MHz
			uint32 :31;
		};
	};
	union{
		uint32 REG_0x6;
		uint32 ceva;
		struct{
			uint32 CEVA_PWD:1;
			//CEVA BTDM工作时钟关闭信号：;0：工作时钟打开;1：工作时钟关闭;【说明】：时钟源为16MHz
			uint32 :31;
		};
	};
	union{
		uint32 REG_0x7;
		uint32 wdt;
		struct{
			uint32 WDT_PWD:1;
			//BK24工作时钟关闭信号：;0：工作时钟打开;1：工作时钟关闭;【说明】：时钟源为16MHz
			uint32 :31;
		};
	};
	union{
		uint32 REG_0x8;
		uint32 bk24;
		struct{
			uint32 BK24_PWD:1;
			//WDT工作时钟关闭信号：;0：工作时钟打开;1：工作时钟关闭;【说明】：时钟源为32KHz（ROSC）
			uint32 :31;
		};
	};
	union{
		uint32 REG_0x9;
		uint32 lpo;
		struct{
			uint32 LPO_PWD:1;
			//Ceva IP Low Power工作时钟关闭信号：;0：工作时钟打开;1：工作时钟关闭;【说明】：时钟源为作时钟关闭信号：;0：工作时钟打开;1：工作时钟关闭;【说明】：时钟源为Ceva IP Low Power工作时钟关闭信号：;0：工作时钟打开;1：工作时钟关闭;【说明】：时钟源为作时钟关闭信号：;0：工作时钟打开;1：工作时钟关闭;【说明】：时钟源为32KHz
			uint32 LPO_GEN:1;
			//Use 32.768k Hz  to Generate 32k Hz;0: 32KHz From ROSC or 16MHz division;1: 32KHz Generate by Xtal 32.768KHz clock
#define LPO_GEN_FROM_DIV		0
			//32K从内部分频器产生的32768Hz生成
#define LPO_GEN_FROM_XTAL		1
			//32K从外接32768晶振生成
			uint32 :30;
		};
	};
	union{
		uint32 REG_0xa;
		uint32 rtc;
		struct{
			uint32 RTC_PWD:1;
			//RTC工作时钟关闭信号：;0：工作时钟打开;1：工作时钟关闭;【说明】：时钟源为32KHz
			uint32 :31;
		};
	};
	union{
		uint32 pwm_clk;
		struct{
			uint32 pwd:1;
			//PWM工作时钟关闭信号：;0：工作时钟打开;1：工作时钟关闭
			uint32 sel:2;
			//PWM工作时钟选择信号：;0：工作时钟为32KHz;1：工作时钟为16MHz
			//uint32 :30;
		};
	}pwm[5];// 特别注意:pwm5与pwm4共用1个寄存器，pwm4使用位0-3，pwm5使用位4-7
	union{
		uint32 REG_0x10;
		uint32 INT_EN;
		struct{
			uint32 ceva_int_en:1;
			//[0]: CEVA中断使能
			uint32 gpio_int_en:1;
			//[1]: GPIO中断使能
			uint32 bk24_int_en:1;
			//[2]: BK24_BB中断使能
			uint32 pwm_int_en:1;
			//[3]: PWM中断使能
			uint32 uart_int_en:1;
			//[4]: UART中断使能
			uint32 rtc_int_en:1;
			//[5]: RTC中断使能
			uint32 adc_int_en:1;
			//[6]: ADC中断使能
			uint32 spi_int_en:1;
			//[7]: SPI中断使能
			uint32 i2c0_int_en:1;
			//[8]: I2C0中断使能
			uint32 _3ds_int_en:1;
			//[9]: 3DS中断使能
			uint32 ext_time_en:1;
			//[10]: EXT_TIME中断使能
			uint32 i2c1_int_en:1;
			//[11]: I2C1中断使能
			uint32 timer_int_en:1;
			//[12]: 16bit TIMER中断使能
			uint32 :1;
			uint32 :1;
			uint32 :1;
			uint32 ceva_wakeup_en:1;
			//[16]: CEVA中断唤醒使能
			uint32 gpio_wakeup_en:1;
			//[17]: GPIO中断唤醒使能
			uint32 bk24_wakeup_en:1;
			//[18]: BK24_BB中断唤醒使能
			uint32 pwm_wakeup_en:1;
			//[19]: PWM中断唤醒使能
			uint32 uart_wakeup_en:1;
			//[20]: UART中断唤醒使能
			uint32 rtc_wakeup_en:1;
			//[21]: RTC中断唤醒使能
			uint32 adc_wakeup_en:1;
			//[22]: ADC中断唤醒使能
			uint32 spi_wakeup_en:1;
			//[23]: SPI中断唤醒使能
			uint32 i2c0_wakeup_en:1;
			//[24]: I2C0中断唤醒使能
			uint32 _3ds_wakeup_en:1;
			//[25]: 3DS中断唤醒使能
			uint32 ext_time_wakeup_en:1;
			//[26]: EXT_TIME中断唤醒使能
			uint32 i2c1_wakeup_en:1;
			//[27]: I2C1中断唤醒使能
			uint32 timer_wakeup_en:1;
			//[28]: 16bit TIMER中断唤醒使能
			uint32 :1;
			uint32 :1;
			uint32 :1;
		};
	};
	union{
		uint32 REG_0x11;
		struct{
			uint32 IRQ_EN:1;
			//IRQ中断使能
			uint32 FIQ_EN:1;
			//FIQ中断使能
			uint32 :30;
		};
	};
	union{
		uint32 REG_0x12;
		uint32 INT_FLAG;
		struct{
			uint32 ceva_if:1;
			//[0]: CEVA中断标志
			uint32 gpio_if:1;
			//[1]: GPIO中断标志
			uint32 bk24_if:1;
			//[2]: BK24_BB中断标志
			uint32 pwm_if:1;
			//[3]: PWM中断标志
			uint32 uart_if:1;
			//[4]: UART中断标志
			uint32 rtc_if:1;
			//[5]: RTC中断标志
			uint32 adc_if:1;
			//[6]: ADC中断标志
			uint32 spi_if:1;
			//[7]: SPI中断标志
			uint32 i2c0_if:1;
			//[8]: I2C0中断标志
			uint32 _3ds_if:1;
			//[9]: 3DS中断标志
			uint32 ext_time_if:1;
			//[10]: EXT_TIME中断标志
			uint32 i2c1_if:1;
			//[11]: I2C1中断标志
			uint32 timer_if:1;
			//[12]: 16bit TIMER中断标志
			uint32 :1;
			uint32 :1;
			uint32 :1;
			//中断状态标志位（屏蔽前）;写清寄存器，写1清0;Bit位定义同INT_EN描述
			uint32 :16;
		};
	};
	union{
		uint32 REG_0x13;
		struct{
			uint32 peri_2nd_en:32;
			//GPIO secondary peripheral function enable.;Bit0 ~ Bit31 for GPIO-A/B/C/D.;
			// 0: Test Pin disable to output via GPIO;1: Test Pin enable  to output via GPIO
		};
	};
	union{
		uint32 REG_0x14;
		uint32 analog_test_enable;
		struct{
			//0-3
			uint32 pwdMCUldoLP1V_en:1;
			//Enable Test Mode of pwdMCUldoLP1V
			uint32 pwdMCUldoHP1V_en:1;
			//Enable Test Mode of pwdMCUldoHP1V
			uint32 pwdSpildoHP1V_en:1;
			//Enable Test Mode of pwdSpildoHP1V
			uint32 pwdCB_Ref1V_en:1;
			//Enable Test Mode of pwdCB_Ref1V

			//4-7
			uint32 pwdCB_Bias1V_en:1;
			//Enable Test Mode of pwdCB_Bias1V
			uint32 pwd16MXtal1V_en:1;
			//Enable Test Mode of pwd16MXtal1V
			uint32 pwdPAldo1V_en:1;
			//Enable Test Mode of pwdPAldo1V
			uint32 pwdPAbufldo1V_en:1;
			//Enable Test Mode of pwdPAbufldo1V
			
			//8-11
			uint32 pwdTrxIFldo1V_en:1;
			//Enable Test Mode of pwdTrxIFldo1V
			uint32 pwdTxLOldo1V_en:1;
			//Enable Test Mode of pwdTxLOldo1V
			uint32 pwdVCOldo1V_en:1;
			//Enable Test Mode of pwdVCOldo1V
			uint32 pwdanaLoopldo1V_en:1;
			//Enable Test Mode of pwdanaLoopldo1V
			
			//12-15
			uint32 pwddigLoopldo1V_en:1;
			//Enable Test Mode of pwddigLoopldo1V
			uint32 pwdLNAldo1V_en:1;
			//Enable Test Mode of pwdLNAldo1V
			uint32 pwdMIXldo1V_en:1;
			//Enable Test Mode of pwdMIXldo1V
			uint32 pwdRxLOldo1V_en:1;
			//Enable Test Mode of pwdRxLOldo1V
			
			//16-19
			uint32 pwdIFADCldo1V_en:1;
			//Enable Test Mode of pwdIFADCldo1V
			uint32 pwdTestldo1V_en:1;
			//Enable Test Mode of pwdTestldo1V
			uint32 pwdSARADCldo1V_en:1;
			//Enable Test Mode of pwdSARADCldo1V
			uint32 pwdSARADC1V_en:1;
			//Enable Test Mode of pwdSARADC1V
			
			//20-23
			uint32 pwdTempSensor1V_en:1;
			//Enable Test Mode of pwdTempSensor1V
			uint32 pwd48MPLL1V_en:1;
			//Enable Test Mode of pwd48MPLL1V
			uint32 pwd32K1V_en:1;
			//Enable Test Mode of pwd32K1V
			uint32 pwdTestBuf1V_en:1;
			//Enable Test Mode of pwdTestBuf1V
			
			//24-27
			uint32 pwdPA1V_en:1;
			//Enable Test Mode of pwdPA1V
			uint32 pwdPAbuf1V_en:1;
			//Enable Test Mode of pwdPAbuf1V
			uint32 pwdTxIF1V_en:1;
			//Enable Test Mode of pwdTxIF1V
			uint32 pwdLNA1V_en:1;
			//Enable Test Mode of pwdLNA1V
			
			//28-31
			uint32 pwdMIX1V_en:1;
			//Enable Test Mode of pwdMIX1V
			uint32 pwdRxIF1V_en:1;
			//Enable Test Mode of pwdRxIF1V
			uint32 pwdIFADC1V_en:1;
			//Enable Test Mode of pwdIFADC1V
			uint32 pwdTestEn:1;
			//analogn_control模块power-down信号测试模式使能：;0: 正常工作模式，该模式下所有模拟单元的Power Down由硬件逻辑控制;1：测试模式，该模式下所有模拟单元的Power Down由寄存器0x15~0x16的pwd信号控制;;Enable Analog Test Mode of pwdRSSI1V
		};
	};
	union{
		uint32 REG_0x15;
		struct{
			uint32 pwdMCUldoLP1V:1;
			//Analog test control of pwdMCUldoLP1V
			uint32 pwdMCUldoHP1V:1;
			//Analog test control of pwdMCUldoHP1V
			uint32 pwdSpildoHP1V:1;
			//Analog test control of pwdSpildoHP1V
			uint32 pwdCB_Ref1V:1;
			//Analog test control of pwdCB_Ref1V

			uint32 pwdCB_Bias1V:1;
			//Analog test control of pwdCB_Bias1V
			uint32 pwd16MXtal1V:1;
			//Analog test control of pwd16MXtal1V
			uint32 pwdPAldo1V:1;
			//Analog test control of pwdPAldo1V
			uint32 pwdPAbufldo1V:1;
			//Analog test control of pwdPAbufldo1V
			
			uint32 pwdTrxIFldo1V:1;
			//Analog test control of pwdTrxIFldo1V
			uint32 pwdTxLOldo1V:1;
			//Analog test control of pwdTxLOldo1V
			uint32 pwdVCOldo1V:1;
			//Analog test control of pwdVCOldo1V
			uint32 pwdanaLoopldo1V:1;
			//Analog test control of pwdanaLoopldo1V
			
			uint32 pwddigLoopldo1V:1;
			//Analog test control of pwddigLoopldo1V
			uint32 pwdLNAldo1V:1;
			//Analog test control of pwdLNAldo1V
			uint32 pwdMIXldo1V:1;
			//Analog test control of pwdMIXldo1V
			uint32 pwdRxLOldo1V:1;
			
			//Analog test control of pwdRxLOldo1V
			uint32 pwdIFADCldo1V:1;
			//Analog test control of pwdIFADCldo1V
			uint32 pwdTestldo1V:1;
			//Analog test control of pwdTestldo1V
			uint32 pwdSARADCldo1V:1;
			//Analog test control of pwdSARADCldo1V
			uint32 pwdSARADC1V:1;
			//Analog test control of pwdSARADC1V
			
			uint32 pwdTempSensor1V:1;
			//Analog test control of pwdTempSensor1V
			uint32 pwd48MPLL1V:1;
			//Analog test control of pwd48MPLL1V
			uint32 pwd32K1V:1;
			//Analog test control of pwd32K1V
			uint32 pwdTestBuf1V:1;
			//Analog test control of pwdTestBuf1V
			
			uint32 pwdPA1V:1;
			//Analog test control of pwdPA1V
			uint32 pwdPAbuf1V:1;
			//Analog test control of pwdPAbuf1V
			uint32 pwdTxIF1V:1;
			//Analog test control of pwdTxIF1V
			uint32 pwdLNA1V:1;
			//Analog test control of pwdLNA1V
			
			uint32 pwdMIX1V:1;
			//Analog test control of pwdMIX1V
			uint32 pwdRxIF1V:1;
			//Analog test control of pwdRxIF1V
			uint32 pwdIFADC1V:1;
			//Analog test control of pwdIFADC1V
			uint32 pwdRSSI1V:1;
			//Analog test control of pwdRSSI1V
		};
	};
	union{
		uint32 REG_0x16;
		struct{
			uint32 gcken_ana:1;
			//Analog test control of gcken_ana
			uint32 errdet_en_tx:1;
			//Analog test control of errdet_en_tx
			uint32 errdet_en_rx:1;
			//Analog test control of errdet_en_rx
			uint32 rxvcoon:1;
			//Analog test control of rxvcoon
			uint32 rx_pll_en:1;
			//Analog test control of rx_pll_en
			uint32 txvcoon:1;
			//Analog test control of txvcoon
			uint32 tx_pll_en:1;
			//Analog test control of tx_pll_en
			uint32 TxCwEn:1;
			//Analog test control of TxCwEn
			uint32 pwdBoost:1;
			//Analog test control of pwdBoost
			uint32 pwd16Mclk1V:1;
			//Analog test control of pwd16Mclk1V
			uint32 pwdIFRSSI1V:1;
			//Analog test control of pwdIFRSSI1V
			uint32 :5;
		};
	};
	union{
		uint32 REG_0x17;
		uint32 digital_pwd;
		struct{
			uint32 clk16m_pwd:1;
			//16MHz Crystal power-down controled by SW;0: Open 16MHz Xtal;1: Close 16MHz Xtal
			uint32 clkpll_pwd:1;
			//PLL clock power-down  controled by SW;0：PLL clock Power on;1：PLL clock Power off
			uint32 cb_bias_pwd:1;
			//Analog pwdCB_Bias1V power-down controled by SW;0: Power on;1: Power off
			uint32 hp_ldo_pwd:1;
			//Analog High Power LDO power-down controled by SW;0: Power on;1: Power off
			uint32 ref1v_pwd:1;
			//REF1V  power-down controled by SW;0: Power on;1: Power off
			uint32 :27;
		};
	};
	union{
		uint32 REG_0x18;
		struct{
			uint32 GPIOA_DEEP_WAKEN:8;
			//DeepSleep GPIO-A唤醒使能信号：0-不使能， 1-使能
			uint32 GPIOB_DEEP_WAKEN:8;
			//DeepSleep GPIO-B[6]唤醒使能信号：0-不使能， 1-使能
			uint32 GPIOC_DEEP_WAKEN:8;
			//DeepSleep GPIO-C[6]唤醒使能信号：0-不使能， 1-使能
			uint32 GPIOD_DEEP_WAKEN:8;
			//DeepSleep GPIO-D[6]唤醒使能信号：0-不使能， 1-使能
		};
	};
	union{
		uint32 REG_0x19;
		struct{
			uint32 GPIOE_DEEP_WAKEN:8;
			//DeepSleep GPIO-E[7]唤醒使能信号：0-不使能， 1-使能
			uint32 :8;
			uint32 deep_sleep_latch:16;
			//深睡眠控制字， 写入0x3231使能芯片进入深睡眠
		};
	};
	union{
		uint32 REG_0x1A;
		struct{
			uint32 spi_trig:1;
			//32KHz Calibration模块触发信号;0: Calibration模块保持复位状态;1：Calibration模块工作
			uint32 cali_mode:1;
			//Calibration模式指示信号,切换cali_mode要用spi_trig先置0再置1触发一次;0：31.25KHz;1：32KHz
			uint32 manu_en:1;
			//手动Calibration使能信号;0: 数字自动输出校准系数f_calo，c_calo;1：f_calo=manu_fin, c_calo=manu_cin
			uint32 manu_cin:5;
			//粗调系数，每LSB约为1KHz
			uint32 manu_fin:9;
			//细调系数，每LSB约为10Hz
			uint32 :15;
		};
	};
	union{
		uint32 REG_0x1B;
		struct{
			uint32 lpo_sleep_time:24;
			//Low power clock (32KHz) sleep time. (Unit: 31.25us/32us);当芯片16MHz时钟power down时，用32KHz时钟运行该寄存器指定的cycle后，会wake-up 16MHz时钟进行32KHz Calibration。;;当该寄存器配置为0时，该功能无效。且配置值应大于48，确保有48*31.25=1.5ms的settler time;;Default=0x140 (Dec320)，目的是当32KHz jitter为100ppm时，32KHz时钟运行10ms会有1us的误差，需进行一次Calibration
			uint32 :8;
		};
	};
	union{
		uint32 REG_0x1C;
		struct{
			uint32 boost_ready_dly:16;
			//Delay Boost power-down for Flash operation.;Delay time unit: core-clock period.
			uint32 :16;
		};
	};
	union{
		uint32 REG_0x1D;
		struct{
			uint32 rstnreg_sw:1;
			//Analog rstnreg indication register.
			uint32 :31;
		};
	};
	union{
		uint32 REG_0x1E;
		struct{
			uint32 ext_timer_to:24;
			//Time-to register of external low-power timer in analog-control module.
			uint32 ext_timer_en:1;
			//Enable of external low-power timer in analog-control module.;0: disable external low-power timer.;1: enable external low-power timer
			uint32 clk32k_pwd:1;
			//32kHz clock power-down controlled by SW.;0: not power-down 32kHz clock in sub-deep-sleep;1: power-down 32kHz clock when sub-deep-sleep starst
			uint32 :6;
		};
	};
	union{
		uint32 REG_0x1F;
		uint32 fiq_irq;
		struct{
			uint32 fiq_priority:16;
			//决定中断响应使用FIQ还是IRQ使能;1：FIQ;0：IRQ;对应中断位同INT_EN描述
			uint32 :16;
		};
	};
	union{
		uint32 REG_0x20;
		struct{
			uint32 dco16m_pwd:1;
			//DCO 16MHz clock power-down controlled by SW.
			uint32 :31;
		};
	};
	union{
		uint32 REG_0x21;
		struct{
			uint32 otp_pwd:1;
			//OTP power-down controlled by SW.
			uint32 :31;
		};
	};
	union{
		uint32 REG_0x22;
		struct{
			uint32 cstm_cfg0:32;
			//No description
		};
	};
	union{
		uint32 REG_0x23;
		struct{
			uint32 cstm_cfg1:32;
			//No description
		};
	};
	union{
		uint32 REG_0x24;
		struct{
			uint32 cstm_cfg2:32;
			//No description
		};
	};
	union{
		uint32 REG_0x25;
		struct{
			uint32 cstm_cfg3:32;
			//No description
		};
	};
	union{
		uint32 REG_0x26;
		struct{
			uint32 jtag_mode:1;
			//JTAG Mode enable;0: Normal mode for JTAG interface;1: JTAG mode for JTAG interface. Reset value.
			uint32 :31;
		};
	};
}HW_ICU;
// #ifdef __cplusplus  
// extern "C" {  
// #endif  

void ICU_SetSysclk16M(void);
void ICU_SetSysclk96M(int div);
int ICU_GetSystemClk(void);
int ICU_CheckSystem96M(void);
int ICU_CheckSystem48M(void);
void ICU_EnableIRQ(HW_ICU*icu);
void ICU_EnableFIQ(HW_ICU*icu);
void ICU_DisableIRQ(HW_ICU*icu);
void ICU_DisableFIQ(HW_ICU*icu);
void ICU_Initial(void);

// #ifdef __cplusplus  
// }
// #endif  

#endif
