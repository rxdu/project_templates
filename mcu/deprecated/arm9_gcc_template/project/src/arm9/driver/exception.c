#include "gpio.h"
#include "icu.h"

extern void Uart_isr(void);

/*extern "C" */void FAST_CALL FIQ_Exception(void)
{
	unsigned int IntStat;
	HW_ICU *icu=BASE_ICU_PTR;
	IntStat = icu->INT_FLAG;
	if(IntStat&BIT(4))          //Uart1 Int Assert
	{
		icu->INT_FLAG=BIT(4);
//		Uart_isr();
		return;
	}
	icu->INT_FLAG = IntStat;
}

/*extern "C" */void FAST_CALL IRQ_Exception(void)
{
	unsigned int IntStat;
	HW_ICU *icu=BASE_ICU_PTR;
	IntStat = icu->INT_FLAG;

	if(IntStat&BIT(12)){		//timer int
		icu->INT_FLAG=BIT(12);
//		timer_isr();
		return;
	}
	if(IntStat&BIT(2)){			//bk2401 int
//		Bk2401_isr();
	}
	if(IntStat&BIT(8)){			//I2C0 int
//		I2C0_ExcetpionHandle();
	}
	icu->INT_FLAG = IntStat;
}

/*Do not change the function*/
__irq void FAST_ENTRY1 SYSirq_FIQ_Handler(void)
{
	__asm volatile
	{
		#pragma arm
		bl FIQ_Exception
	};
}

/*Do not change the function*/
__irq void FAST_ENTRY2 SYSirq_IRQ_Handler(void)
{
	__asm volatile
	{
		#pragma arm
		bl IRQ_Exception
	};
}
