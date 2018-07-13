
//#include "uart.h"
#include "gpio.h"
#include "icu.h"


void Led_Init(void)
{
	BASE_GPIO_PTR->gpio[GPIO0].normal |= 1<<7;
	BASE_GPIO_PTR->gpio[GPIO0].ie &= (~(1<<7));
	BASE_GPIO_PTR->gpio[GPIO0].oe_n &= (~(1<<7));
}

void Led_ON(void)
{
	GPIO_Output(GPIO0)|=1<<7;
}

void Led_OFF(void)
{
	GPIO_Output(GPIO0)&=(~(1<<7));
}

int FAST_CALL entry0_main(void)
{
	static int led_flag = 0;
	static int led_cnt = 0;
	
	ICU_Initial();
//	Beken_UART_Initial(921600);
	Led_Init();
	
	while(1)
	{

		led_cnt++;
		if(led_cnt>30000)
		{
			led_cnt = 0;
			if(led_flag==0)
			{
				Led_OFF();
				led_flag =1;
			}
			else
			{
				Led_ON();
				led_flag =0;
			}

//			unsigned char aaa = 0x41;
//			uart_send( &aaa,1);
		}
	}

}

int FAST_ENTRY0 main(void)
{
	__asm volatile
	{
		#pragma arm
		bl entry0_main
	};
	return 0;
}

