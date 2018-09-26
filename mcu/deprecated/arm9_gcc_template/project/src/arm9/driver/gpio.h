#ifndef _GPIO_H_
#define _GPIO_H_
#include "types.h"

#define	BASE_GPIO_PTR	\
		((HW_GPIO*)0x00f00500)

#define NUM_GPIO_PORT	\
		5

#define GPIOA					0
#define GPIOB					1
#define GPIOC					2
#define GPIOD					3
#define GPIOE					4
#define GPIO0					0
#define GPIO1					1
#define GPIO2					2
#define GPIO3					3
#define GPIO4					4
#pragma anon_unions

typedef struct HW_GPIOU{
	union{
		uint32 REG_0x0;
		struct{
			uint32 normal:8;
			//function selection, 0:2nd Function, 1:GPIO
			uint32 oe_n:8;
			//Output Enable, 0:Output, 1:Not Output
			uint32 pu:8;
			//Pull up enable, 0:no pull up, 1:pull up
			uint32 pd:8;
			//Pull down eanble, 0:no pull down, 1:pull down
		};
	};
	union{
		uint32 REG_0x1;
		struct{
			uint32 od:8;
			//GPIOA[7:0] Output data
			uint32 id:8;
			//GPIOA[7:0] Input daa
			uint32 ie:8;
			//Input enable, 0:not Input, 1:Input
			uint32 :8;
		};
	};
}HW_GPIOU;

#pragma anon_unions
typedef struct HW_GPIO{
	HW_GPIOU gpio[5];
	union{
		uint32 REG_0xA[2];
		struct{
			uint8 wu_type[5];
			//GPIO wake up type, 1:rising edge, 0:falling edge
			uint32 :24;
		};
	};
	union{
		uint32 REG_0xC[2];
		struct{
			uint8 wu_en[5];
			//GPIO wake up enable, 1:Enable, 0:Disable
			uint32 :24;
		};
	};
	union{
		uint32 REG_0xE;
		struct{
			uint8 wu_stat[5];
			//GPIO Interrupt status, 1:interrupt, 0:no interrupt, write 1 to clear
			uint32 :24;
		};
	};
}HW_GPIO;

#define GPIO_Output(pn)	\
	/*Func:Setting Specify Port output value */\
	/*pn:port index*/\
	BASE_GPIO_PTR->gpio[pn].od

#define GPIO_OutputLow(pn,pl)	\
	/*Func: Specify GPIO output low */\
	/*pn:Port index;pl:PIN index*/\
	GPIO_Output(pn)&=(~(pl))

#define GPIO_OutputHigh(pn,pl)	\
	/*Func: Specify GPIO output high */\
	/*pn:Port index;pl:PIN index*/\
	GPIO_Output(pn)|=((pl))

#define GPIO_OutputNeg(pn,pl)	\
	/*Func: Toggle Specify GPIO output*/\
	/*pn:Port index;pl:PIN index*/\
	GPIO_Output(pn)^=((pl))

#define GPIO_Input(pn)	\
	/*Func: Read Specify GPIO input data */\
	/*pn:Port index*/\
	BASE_GPIO_PTR->gpio[pn].id

#define GPIO_SetSF(pn,sfl)	\
	/*Func:Setting Specify GPIO 2nd function */\
	/*pn:Port index;pl:PIN index*/\
	{\
	BASE_GPIO_PTR->gpio[pn].normal &= (~(sfl));\
	BASE_GPIO_PTR->gpio[pn].pu &= (~(sfl));\
	BASE_GPIO_PTR->gpio[pn].pd &= (~(sfl));\
	}

#define GPIO_InputSetup(pn,i,pullup,pulldw) \
	/*Func: Setting Specify GPIO input */\
	/*pn:Port index;i,pullup,pulldw:PIN index*/\
	{\
	BASE_GPIO_PTR->gpio[pn].normal |= (i);\
	BASE_GPIO_PTR->gpio[pn].ie |= ((i));\
	BASE_GPIO_PTR->gpio[pn].oe_n |= ((i));\
	if(pullup){BASE_GPIO_PTR->gpio[pn].pu |= ((pullup));}\
	if(pulldw){BASE_GPIO_PTR->gpio[pn].pd |= ((pulldw));}\
	}

#define GPIO_DiablePU(pn,pul) \
	{\
	/*Func:Disable Specify GPIO Pullup */\
	/*pn:Port index;pul:PIN index*/\
	if(pul){BASE_GPIO_PTR->gpio[pn].pu &= (~(pul));}\
	}

#define GPIO_DiablePD(pn,pdl) \
	{\
	/*Func:Disable Specify GPIO Pulldown */\
	/*pn:Port index;pdl:PIN index*/\
	if(pdl)BASE_GPIO_PTR->gpio[pn].pd  &= (~(pdl));\
	}


#define GPIO_OutputSetup(pn,oe) \
	/*Func: Setting Specify GPIO output */\
	/*pn:Port index;oe:Output PIN*/\
	{\
	BASE_GPIO_PTR->gpio[pn].normal |= (oe);\
	BASE_GPIO_PTR->gpio[pn].ie &= (~(oe));\
	BASE_GPIO_PTR->gpio[pn].oe_n &= (~(oe));\
	}

#define GPIO_WakeupSetup(pn,enl,modl,modh) \
	/*功能:对指定端口进行唤醒功能设定*/\
	/*pn:端口号;enl、modl、modh:将要设为能够唤醒、低电平唤醒、高电平唤醒的管脚列表*/\
	{\
	if(enl)BASE_GPIO_PTR->wu_en[pn] |= ((enl));\
	if(modh)BASE_GPIO_PTR->wu_type[pn] |= ((modh));\
	if(modl)BASE_GPIO_PTR->wu_type[pn] &= (~(modl));\
	}

#endif
