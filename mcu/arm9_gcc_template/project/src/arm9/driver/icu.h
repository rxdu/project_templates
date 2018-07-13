#ifndef _ICU_H_
#define _ICU_H_
#include "types.h"
#define	BASE_ICU_PTR	\
		((HW_ICU*)0x00800000)

#define	PID_CEVA			0
//[0]: CEVA�ж�ʹ��
#define	PID_GPIO			1
//[1]: GPIO�ж�ʹ��
#define	PID_BK24			2
//[2]: BK24_BB�ж�ʹ��
#define	PID_PWM				3
//[3]: PWM�ж�ʹ��
#define	PID_UART			4
//[4]: UART�ж�ʹ��
#define	PID_RTC				5
//[5]: RTC�ж�ʹ��
#define	PID_ADC				6
//[6]: ADC�ж�ʹ��
#define	PID_SPI				7
//[7]: SPI�ж�ʹ��
#define	PID_I2C0			8
//[8]: I2C0�ж�ʹ��
#define	PID_3DS				9
//[9]: 3DS�ж�ʹ��
#define	PID_EXT_TIME		10
//[10]: EXT_TIME�ж�ʹ��
#define	PID_I2C1			11
//[11]: I2C1�ж�ʹ��
#define	PID_TIMER			12
//[12]: 16bit TIMER�ж�ʹ��

#pragma anon_unions
typedef struct HW_ICU{
	union{
		uint32 REG_0x0;
		struct{
			uint32 CLK_SRC_SEL:2;
			//ʱ��Դ(clk_src)ѡ��;00: 32KHz ;01: 16MHz Crystal. Reset value.;10: Reserved;11: PLL clock. 96MHz in BK3231S.
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
			//ARM9 Coreʱ�ӹر��źţ�;0������ʱ�Ӵ�;1������ʱ�ӹر�;��˵������ʱ��ԴΪclk_src
			uint32 CORE_DIV:2;
			//ARM9 Coreʱ�ӷ�Ƶ�źţ�;Fclk_core = Fclk_src / core_div
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
			//ADCʱ�ӹر��źţ�;0������ʱ�Ӵ�;1������ʱ�ӹر�;��˵������ʱ��ԴΪclk_16m
			uint32 ADC_DIV:7;
			//ADCʱ�ӷ�Ƶ�źţ�;Fclk_adc = Fclk_16m/ (adc_div + 1)
			uint32 :24;
		};
	};
	union{
		uint32 REG_0x3;
		uint32 uart;
		struct{
			uint32 UART_PWD:1;
			//UARTʱ�ӹر��źţ�;0������ʱ�Ӵ�;1������ʱ�ӹر�;��˵������ʱ��ԴΪ16MHz
			uint32 :31;
		};
	};
	union{
		uint32 REG_0x4;
		uint32 i2c;
		struct{
			uint32 I2C0_PWD:1;
			//I2C0����ʱ�ӹر��źţ�;0������ʱ�Ӵ�;1������ʱ�ӹر�;��˵������ʱ��ԴΪ16MHz
			uint32 :15;
			uint32 I2C1_PWD:1;
			//I2C1����ʱ�ӹر��źţ�;0������ʱ�Ӵ�;1������ʱ�ӹر�;��˵������ʱ��ԴΪ16MHz
			uint32 :15;
		};
	};
	union{
		uint32 REG_0x5;
		uint32 spi;
		struct{
			uint32 SPI_PWD:1;
			//SPI����ʱ�ӹر��źţ�;0������ʱ�Ӵ�;1������ʱ�ӹر�;��˵������ʱ��ԴΪ16MHz
			uint32 :31;
		};
	};
	union{
		uint32 REG_0x6;
		uint32 ceva;
		struct{
			uint32 CEVA_PWD:1;
			//CEVA BTDM����ʱ�ӹر��źţ�;0������ʱ�Ӵ�;1������ʱ�ӹر�;��˵������ʱ��ԴΪ16MHz
			uint32 :31;
		};
	};
	union{
		uint32 REG_0x7;
		uint32 wdt;
		struct{
			uint32 WDT_PWD:1;
			//BK24����ʱ�ӹر��źţ�;0������ʱ�Ӵ�;1������ʱ�ӹر�;��˵������ʱ��ԴΪ16MHz
			uint32 :31;
		};
	};
	union{
		uint32 REG_0x8;
		uint32 bk24;
		struct{
			uint32 BK24_PWD:1;
			//WDT����ʱ�ӹر��źţ�;0������ʱ�Ӵ�;1������ʱ�ӹر�;��˵������ʱ��ԴΪ32KHz��ROSC��
			uint32 :31;
		};
	};
	union{
		uint32 REG_0x9;
		uint32 lpo;
		struct{
			uint32 LPO_PWD:1;
			//Ceva IP Low Power����ʱ�ӹر��źţ�;0������ʱ�Ӵ�;1������ʱ�ӹر�;��˵������ʱ��ԴΪ��ʱ�ӹر��źţ�;0������ʱ�Ӵ�;1������ʱ�ӹر�;��˵������ʱ��ԴΪCeva IP Low Power����ʱ�ӹر��źţ�;0������ʱ�Ӵ�;1������ʱ�ӹر�;��˵������ʱ��ԴΪ��ʱ�ӹر��źţ�;0������ʱ�Ӵ�;1������ʱ�ӹر�;��˵������ʱ��ԴΪ32KHz
			uint32 LPO_GEN:1;
			//Use 32.768k Hz  to Generate 32k Hz;0: 32KHz From ROSC or 16MHz division;1: 32KHz Generate by Xtal 32.768KHz clock
#define LPO_GEN_FROM_DIV		0
			//32K���ڲ���Ƶ��������32768Hz����
#define LPO_GEN_FROM_XTAL		1
			//32K�����32768��������
			uint32 :30;
		};
	};
	union{
		uint32 REG_0xa;
		uint32 rtc;
		struct{
			uint32 RTC_PWD:1;
			//RTC����ʱ�ӹر��źţ�;0������ʱ�Ӵ�;1������ʱ�ӹر�;��˵������ʱ��ԴΪ32KHz
			uint32 :31;
		};
	};
	union{
		uint32 pwm_clk;
		struct{
			uint32 pwd:1;
			//PWM����ʱ�ӹر��źţ�;0������ʱ�Ӵ�;1������ʱ�ӹر�
			uint32 sel:2;
			//PWM����ʱ��ѡ���źţ�;0������ʱ��Ϊ32KHz;1������ʱ��Ϊ16MHz
			//uint32 :30;
		};
	}pwm[5];// �ر�ע��:pwm5��pwm4����1���Ĵ�����pwm4ʹ��λ0-3��pwm5ʹ��λ4-7
	union{
		uint32 REG_0x10;
		uint32 INT_EN;
		struct{
			uint32 ceva_int_en:1;
			//[0]: CEVA�ж�ʹ��
			uint32 gpio_int_en:1;
			//[1]: GPIO�ж�ʹ��
			uint32 bk24_int_en:1;
			//[2]: BK24_BB�ж�ʹ��
			uint32 pwm_int_en:1;
			//[3]: PWM�ж�ʹ��
			uint32 uart_int_en:1;
			//[4]: UART�ж�ʹ��
			uint32 rtc_int_en:1;
			//[5]: RTC�ж�ʹ��
			uint32 adc_int_en:1;
			//[6]: ADC�ж�ʹ��
			uint32 spi_int_en:1;
			//[7]: SPI�ж�ʹ��
			uint32 i2c0_int_en:1;
			//[8]: I2C0�ж�ʹ��
			uint32 _3ds_int_en:1;
			//[9]: 3DS�ж�ʹ��
			uint32 ext_time_en:1;
			//[10]: EXT_TIME�ж�ʹ��
			uint32 i2c1_int_en:1;
			//[11]: I2C1�ж�ʹ��
			uint32 timer_int_en:1;
			//[12]: 16bit TIMER�ж�ʹ��
			uint32 :1;
			uint32 :1;
			uint32 :1;
			uint32 ceva_wakeup_en:1;
			//[16]: CEVA�жϻ���ʹ��
			uint32 gpio_wakeup_en:1;
			//[17]: GPIO�жϻ���ʹ��
			uint32 bk24_wakeup_en:1;
			//[18]: BK24_BB�жϻ���ʹ��
			uint32 pwm_wakeup_en:1;
			//[19]: PWM�жϻ���ʹ��
			uint32 uart_wakeup_en:1;
			//[20]: UART�жϻ���ʹ��
			uint32 rtc_wakeup_en:1;
			//[21]: RTC�жϻ���ʹ��
			uint32 adc_wakeup_en:1;
			//[22]: ADC�жϻ���ʹ��
			uint32 spi_wakeup_en:1;
			//[23]: SPI�жϻ���ʹ��
			uint32 i2c0_wakeup_en:1;
			//[24]: I2C0�жϻ���ʹ��
			uint32 _3ds_wakeup_en:1;
			//[25]: 3DS�жϻ���ʹ��
			uint32 ext_time_wakeup_en:1;
			//[26]: EXT_TIME�жϻ���ʹ��
			uint32 i2c1_wakeup_en:1;
			//[27]: I2C1�жϻ���ʹ��
			uint32 timer_wakeup_en:1;
			//[28]: 16bit TIMER�жϻ���ʹ��
			uint32 :1;
			uint32 :1;
			uint32 :1;
		};
	};
	union{
		uint32 REG_0x11;
		struct{
			uint32 IRQ_EN:1;
			//IRQ�ж�ʹ��
			uint32 FIQ_EN:1;
			//FIQ�ж�ʹ��
			uint32 :30;
		};
	};
	union{
		uint32 REG_0x12;
		uint32 INT_FLAG;
		struct{
			uint32 ceva_if:1;
			//[0]: CEVA�жϱ�־
			uint32 gpio_if:1;
			//[1]: GPIO�жϱ�־
			uint32 bk24_if:1;
			//[2]: BK24_BB�жϱ�־
			uint32 pwm_if:1;
			//[3]: PWM�жϱ�־
			uint32 uart_if:1;
			//[4]: UART�жϱ�־
			uint32 rtc_if:1;
			//[5]: RTC�жϱ�־
			uint32 adc_if:1;
			//[6]: ADC�жϱ�־
			uint32 spi_if:1;
			//[7]: SPI�жϱ�־
			uint32 i2c0_if:1;
			//[8]: I2C0�жϱ�־
			uint32 _3ds_if:1;
			//[9]: 3DS�жϱ�־
			uint32 ext_time_if:1;
			//[10]: EXT_TIME�жϱ�־
			uint32 i2c1_if:1;
			//[11]: I2C1�жϱ�־
			uint32 timer_if:1;
			//[12]: 16bit TIMER�жϱ�־
			uint32 :1;
			uint32 :1;
			uint32 :1;
			//�ж�״̬��־λ������ǰ��;д��Ĵ�����д1��0;Bitλ����ͬINT_EN����
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
			//analogn_controlģ��power-down�źŲ���ģʽʹ�ܣ�;0: ��������ģʽ����ģʽ������ģ�ⵥԪ��Power Down��Ӳ���߼�����;1������ģʽ����ģʽ������ģ�ⵥԪ��Power Down�ɼĴ���0x15~0x16��pwd�źſ���;;Enable Analog Test Mode of pwdRSSI1V
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
			//PLL clock power-down  controled by SW;0��PLL clock Power on;1��PLL clock Power off
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
			//DeepSleep GPIO-A����ʹ���źţ�0-��ʹ�ܣ� 1-ʹ��
			uint32 GPIOB_DEEP_WAKEN:8;
			//DeepSleep GPIO-B[6]����ʹ���źţ�0-��ʹ�ܣ� 1-ʹ��
			uint32 GPIOC_DEEP_WAKEN:8;
			//DeepSleep GPIO-C[6]����ʹ���źţ�0-��ʹ�ܣ� 1-ʹ��
			uint32 GPIOD_DEEP_WAKEN:8;
			//DeepSleep GPIO-D[6]����ʹ���źţ�0-��ʹ�ܣ� 1-ʹ��
		};
	};
	union{
		uint32 REG_0x19;
		struct{
			uint32 GPIOE_DEEP_WAKEN:8;
			//DeepSleep GPIO-E[7]����ʹ���źţ�0-��ʹ�ܣ� 1-ʹ��
			uint32 :8;
			uint32 deep_sleep_latch:16;
			//��˯�߿����֣� д��0x3231ʹ��оƬ������˯��
		};
	};
	union{
		uint32 REG_0x1A;
		struct{
			uint32 spi_trig:1;
			//32KHz Calibrationģ�鴥���ź�;0: Calibrationģ�鱣�ָ�λ״̬;1��Calibrationģ�鹤��
			uint32 cali_mode:1;
			//Calibrationģʽָʾ�ź�,�л�cali_modeҪ��spi_trig����0����1����һ��;0��31.25KHz;1��32KHz
			uint32 manu_en:1;
			//�ֶ�Calibrationʹ���ź�;0: �����Զ����У׼ϵ��f_calo��c_calo;1��f_calo=manu_fin, c_calo=manu_cin
			uint32 manu_cin:5;
			//�ֵ�ϵ����ÿLSBԼΪ1KHz
			uint32 manu_fin:9;
			//ϸ��ϵ����ÿLSBԼΪ10Hz
			uint32 :15;
		};
	};
	union{
		uint32 REG_0x1B;
		struct{
			uint32 lpo_sleep_time:24;
			//Low power clock (32KHz) sleep time. (Unit: 31.25us/32us);��оƬ16MHzʱ��power downʱ����32KHzʱ�����иüĴ���ָ����cycle�󣬻�wake-up 16MHzʱ�ӽ���32KHz Calibration��;;���üĴ�������Ϊ0ʱ���ù�����Ч��������ֵӦ����48��ȷ����48*31.25=1.5ms��settler time;;Default=0x140 (Dec320)��Ŀ���ǵ�32KHz jitterΪ100ppmʱ��32KHzʱ������10ms����1us���������һ��Calibration
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
			//�����ж���Ӧʹ��FIQ����IRQʹ��;1��FIQ;0��IRQ;��Ӧ�ж�λͬINT_EN����
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
