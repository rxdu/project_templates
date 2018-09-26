/*
*********************************************************************************************************
*                         wysdhl2005/Debug Communication     With Circle TX AND RX Buffer
*
*                           (c) Copyright 2011; wysdhl2005, NCEPU; BaoDing , hebei
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/
/*--ע�⣺����ostart,oend,istart,iend,sendfull,sendactive���ж��и�ֵ������������������������������Ϊvolatile����������(2013��1��18��0:14:53)---*/
#include "debug_with_usart.h"

/*���������ó���������*/
#define OLEN 128                                            //���з��ͻ�������С
volatile unsigned short ostart = 0;             //���ͻ�������ʼ����
volatile unsigned short oend = 0;           //���ͻ�������������
char  outbuf[OLEN];                                             //���ͻ������洢����

#define ILEN 16                                             //���н��ջ�������С
volatile unsigned char istart = 0;              //���ջ�������ʼ����
volatile unsigned char iend = 0;                //���ջ�������������
char  inbuf[ILEN];                                              //���ջ����洢����

volatile unsigned char  sendfull = 0;     //���ͻ���������־
volatile unsigned char  sendactive = 0;   //������Ч��־

void (*USART_SendByte)(unsigned char);
/*************************************************************************
** ��������: void putbuf(char c)
** ��������:  д�ַ���SBUF�����ͻ�����
** �䡡��:      c-->д��buffer������
** ����  :
** ȫ�ֱ���: ��
** ����ģ��:
** ˵����
** ע�⣺
**************************************************************************/
void putbuf(char c)
{
        while(sendfull);                                        //�ȴ����ͻ������գ����������������ͷ���
    {
      UsartTxIRQDisable;                                //��ʱ���пڹر��ж�
      if(!sendactive)                                       //�������ڿ��У�ֱ�ӴӴ��ڷ�������
      {
          sendactive = 1;                           //���ô���æ��־
                    UsartSendByte((char) c);        //д��SBUF����������
      }
      else                                                              //�������ڲ����У������ݷ�������������
      {
        outbuf[oend++&(OLEN-1)] = c;        //�����ͻ����������ַ�
        if(((oend^ostart)&(OLEN-1)) == 0)
         {
                        sendfull=1;                                     //���û���������־
                 }
      }
      UsartTxIRQEnable;                                     //�򿪴��п��ж�
    }
}
/*************************************************************************
** ��������:    void  DebugPutChar (char c)
** ��������:  д�ַ���SBUF�����ͻ�����
** �䡡��:      c-->д��������
** ����  :
** ȫ�ֱ���: ��
** ����ģ��:
** ˵����
** ע�⣺
**************************************************************************/
//putchar:�жϿ���putchar����
//�滻��׼�⺯��putchar����
//printf����ʹ��putchar����һ���ַ�
void  DebugPutChar (char c)
{
  if (c=='\n')           //�����µ���
  {
    putbuf(0x0D);      //��������LFǰ����CR
  }
  putbuf(c);
}
/*************************************************************************
** ��������:    char DebugGetChar(void)
** ��������:  �ӽ��ջ�������ȡһ����
** �䡡��:      none
** ����  :    ���ؽ��յ�����
** ȫ�ֱ���: ��
** ����ģ��:
** ˵����
** ע�⣺
**************************************************************************/
//_getkey:�жϿ���_getkey����
//�滻��׼�⺯��_getkey����
//getchar��gets����ʹ��_getkey
char DebugGetChar(void)
{
    char c;
  if(iend==istart)return ((char)(-1));//�жϽ��ջ�������ʼ�����Ƿ����ڽ��ջ�������������,�������������ַ�����0xFF(-1)��
  UsartRxIRQDisable;
  c=inbuf[istart++ & (ILEN - 1)];
  UsartRxIRQEnable;
  return(c);
}

/*************************************************************************
** ��������: void Func_UsartIRQ(void)
** ��������: �����жϺ�����ͨ���궨������
** �䡡��:
** ����  :
** ȫ�ֱ���: ��
** ����ģ��:
** ˵����
** ע�⣺
**************************************************************************/

void Func_UsartIRQ(void)
{
       //-------------���������ж�--------------
  char c;
  if(IsUsartRxIRQFlag)               //�����ж�
  {
        UsartReceiveByte(c);        //���ַ�
            ClearUsartRxIRQFlag;        //�������ж�������־
    //ʹ�ã�istart+ILEN)^iend�� ((INT8U)(istart+ILEN)!=iend)�ȽϷ�����
        if((istart+ILEN)^iend)
    //if((INT8U)(istart+ILEN)!=iend)
    {
       inbuf[iend++ & (ILEN - 1)]=c;   //��������������
    }
  }
  //-------------���������ж�--------------
  if(IsUsartTxIRQFlag)
  {
    ClearUsartTxIRQFlag;            //�巢���жϱ�־
    if(ostart != oend)
    {
       UsartSendByte((char)outbuf[ostart++ & (OLEN - 1)]);//�����ͻ����������ַ�
       sendfull = 0;              //��������������־λ
     }
     else
     {
        sendactive = 0;         //���ô��ڿ���
        UsartTxIRQDisable;      //��ʱ���пڹر��ж�
     }
   }
}
/*********************************************************************************
*��������: DebugBufferStatus CheckDebugBufferIsNull(void)
*����������  �� 0 ��������
*����������  �� 0��������
*����ֵ��    NULL--->DebugBuffer is empty;
                         NotNULL---->DebugBuffer is Not Empty.
*�财���Ĳ�����
*���ܽ��ܣ�  ����DBUG�������Ƿ�Ϊ��
*�޸���־��  �޸�����ʱ�䣺2013��1��6��9:46:10
*********************************************************************************/
DebugBufferStatus CheckDebugBufferIsNull(void)                                                                                  /* ����DBUG�������Ƿ�Ϊ�� */
{
    if(ostart == oend)
        return Null;
    else
        return NotNull;
}
/*********************************************************************************
*��������:   void DebugUsartInit(void)
*����������  �� 0 ��������
*����������  �� 0��������
*����ֵ��    ��
*�财���Ĳ�����
*���ܽ��ܣ�  ��ʼ��Debug���ڲ���
*�޸���־��  �޸�����ʱ�䣺2013��1��6��9:44:31
*********************************************************************************/
void DebugUsartInit(void)
{
  istart=0;
  iend=0;
  ostart=0;
  oend=0;
  sendactive=0;
  sendfull=0;
    xdev_out(DebugPutChar);
  xdev_in(DebugGetChar);
}
/*********************************************************************************
*��������: void USART_SendString(unsigned char *str)
*����������  �� 1 ��������
*����������  �� 0��������
*����ֵ��    ��
*�财���Ĳ�����
*���ܽ��ܣ�  ͨ��ѡ�����ڷ���һ���ַ���
*�޸���־��  �޸�����ʱ�䣺2011��2��28��14:21:58
*********************************************************************************/
/*����һ���ַ���*/
void USART_SendString(unsigned char *str)
{
 while(*str)
   if(USART_SendByte)USART_SendByte(*str++);
}

/*********************************************************************************
*��������: void USART_SendHex(unsigned char bSentData)
*����������  �� 1 ��������
*����������  �� 0��������
*����ֵ��    ��
*�财���Ĳ�����
*���ܽ��ܣ�  ͨ��ѡ�����ڽ�ʮ�������� ���� ASCII����ʽ���ͳ�ȥ
*            ���磺0x1a -> '1' 'a'.
*�޸���־��  �޸�����ʱ�䣺2011��2��28��14:21:58
*********************************************************************************/
/*ͨ������һ���� ʮ������ת��ΪASCII ������*/
void USART_SendHex(unsigned char bSentData)
{
  unsigned char bTmp;

  bTmp =((unsigned char)(bSentData>>4)&0x0f) + (unsigned char)'0';

  if(bTmp > '9') bTmp += 7;
    if(USART_SendByte)USART_SendByte(bTmp);

  bTmp =(unsigned char)(bSentData & 0x0f) + (unsigned char)'0';

  if(bTmp > '9') bTmp += 7;
    if(USART_SendByte)USART_SendByte(bTmp);
}

/*********************************************************************************
*��������: void PrintBuffer(unsigned char *bpPrintBuffer, u8 bLength)
*����������  �� 2 ��������
*����������  �� 0��������
*����ֵ��    ��
*�财���Ĳ�����
*���ܽ��ܣ�  ͨ��ѡ�����ڽ��������������� ���� ASCII����ʽ���ͳ�ȥ
*            ���磺0x1a -> '1' 'a'.
*�޸���־��  �޸�����ʱ�䣺2011��2��28��14:21:58
*********************************************************************************/
void PrintBuffer(unsigned char *bpPrintBuffer, u8 bLength)
{
  unsigned char bCount;
  for(bCount = 0; bCount < bLength; bCount++)
  {
  USART_SendHex(bpPrintBuffer[bCount]);
  if(USART_SendByte)USART_SendByte(' ');
  }
  USART_SendString("(LEN:");//��ӡ���ݳ���
  USART_SendHex(bLength);
  if(USART_SendByte)
    {
        USART_SendByte(')');
      USART_SendByte(0x0d);   // ��ӡ�س�
      USART_SendByte(0x0a);  // ��ӡ����
    }
}
/*********************************************************************************
*��������: void USART_Send32Dec(long  lLong)
*����������  �� 1 ��������
*����������  �� 0��������
*����ֵ��    ��
*�财���Ĳ�����
*���ܽ��ܣ�  ͨ��ѡ�����ڽ��������������� ���� ASCII����ʽ���ͳ�ȥ
*            ���磺-123456 -> '-' '1' '2' '3 '4' '5' '6'.
*�޸���־��  �޸�����ʱ�䣺2011��2��28��14:31:54
*********************************************************************************/
/*���������ݰ��ַ��ͷ��ͳ�ȥ*/
void USART_Send32Dec(long  lLong)
{
  unsigned char bCount, bPrinted;
  long lTmp,lDigit;
  bPrinted = 0;
  if(lLong < 0)
  {
  lLong = -lLong;
  if(USART_SendByte)USART_SendByte('-');//������������
  }
  lDigit = 1000000000L;
  for(bCount = 0; bCount < 9; bCount++)
  {
  lTmp = (unsigned char)(lLong/lDigit);//�ֱ���ȡÿһλ
  if(lTmp)
  {
    if(USART_SendByte)USART_SendByte(((unsigned char)lTmp)+'0');
    bPrinted = 1;
  }
  else if(bPrinted)
    if(USART_SendByte)USART_SendByte(((unsigned char)lTmp)+'0');
  lLong -= ((long)lTmp)*lDigit;//��ʣ��λ
  lDigit = lDigit/10;
  }
  lTmp = (u8)(lLong/lDigit);
  /*if(lTmp)*/ if(USART_SendByte)USART_SendByte(((unsigned char)lTmp)+'0');
}
