
#include "gpio.h"
#include "icu.h"
#include "XVR_3231S.h"

void Delay(int dly)
{
	while(dly--);
}

void ICU_SetSysclk16M(void)
{
	HW_ICU*icu=BASE_ICU_PTR;
	icu->CLK_SRC_SEL=ICU_CLKSRC_16M;
	icu->core = 0;
	Delay(2);
	icu->pwdSARADC1V = 1;
	icu->pwd48MPLL1V = 1;
}

void ICU_SetSysclk96M(int div)
{
	HW_XVR_3231S*xvr=BASE_XVR_3231S_PTR;
	HW_ICU*icu=BASE_ICU_PTR;
	icu->REG_0x17 = 0;
	xvr->REG_0x9 = 0x19407d80;
	icu->pwdSARADC1V =0;
	icu->pwd48MPLL1V = 0;
	Delay(5);
	xvr->REG_0x9 = 0x19407d00;
	Delay(20);
	icu->CORE_DIV = div;
	icu->CORE_PWD = 0;
	icu->CLK_SRC_SEL = ICU_CLKSRC_PLL ;
}

int ICU_GetSystemClk(void)
{
	HW_ICU*icu=BASE_ICU_PTR;
	int freq=96000000;
	if(icu->CLK_SRC_SEL==ICU_CLKSRC_16M)		freq=16000000;	
	if(icu->CLK_SRC_SEL==ICU_CLKSRC_32K)		freq=32000;	
	return(freq/(icu->CORE_DIV+1));
}

int ICU_CheckSystem96M(void){
	HW_ICU*icu=BASE_ICU_PTR;
	if((icu->CLK_SRC_SEL==ICU_CLKSRC_PLL)&&(icu->CORE_DIV==0))return(1);
	return(0);
}

int ICU_CheckSystem48M(void)
{
	HW_ICU*icu=BASE_ICU_PTR;
	if((icu->CLK_SRC_SEL==ICU_CLKSRC_PLL)&&(icu->CORE_DIV==1))return(1);
	return(0);
}

void ICU_EnableIRQ(HW_ICU*icu)
{
	icu->IRQ_EN = 1;
}

void ICU_EnableFIQ(HW_ICU*icu)
{
	icu->FIQ_EN = 1;
}

void ICU_DisableIRQ(HW_ICU*icu)
{
	icu->IRQ_EN = 0;
}

void ICU_DisableFIQ(HW_ICU*icu)
{
	icu->FIQ_EN = 0;
}

void ICU_Initial(void)
{
	HW_ICU*icu=BASE_ICU_PTR;
	icu->jtag_mode = 0;
	icu->digital_pwd = 0;
	icu->dco16m_pwd =1;
	icu->boost_ready_dly = 0x500;
#ifdef LPO_GEN_IS_16M_TO_32K
	icu->LPO_GEN = LPO_GEN_FROM_DIV;
#else
	icu->LPO_GEN = LPO_GEN_FROM_XTAL;
#endif

	icu->ceva = 0;
	icu->fiq_irq = (BIT(PID_CEVA)|BIT(PID_UART));/*解决超过20B接收时丢信息的bug*/\
	BASE_XVR_3231S_PTR->REG_0x9 =0x19407D80;
	icu->pwdSARADCldo1V_en = 1;
	Delay(10);
	icu->pwd48MPLL1V_en = 1;
	Delay(2);
	BASE_XVR_3231S_PTR->REG_0x9 =0x19407D00;
	Delay(20);

	ICU_EnableFIQ(icu);
	ICU_EnableIRQ(icu);
}
