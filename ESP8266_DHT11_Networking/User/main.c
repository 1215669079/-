/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-01-xx
  * @brief   WF-ESP8266 WiFiģ�����
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� iSO STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
 
#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_SysTick.h"
#include "bsp_esp8266.h"
#include "bsp_esp8266_test.h"
#include "bsp_dht11.h"
#include "bsp_led.h"  
#include "./beep/bsp_beep.h"   
#include "./dwt_delay/core_delay.h"
#include "./lcd/bsp_ili9341_lcd.h"
extern int hum_data,tem_data;

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main ( void )
{
	/* ��ʼ�� */
  USART_Config ();                                                      //��ʼ������1
  CPU_TS_TmrInit();                                                     //��ʼ��DWT��������������ʱ����
  LED_GPIO_Config();                                                    //��ʼ��RGB�ʵ�
	ESP8266_Init ();                                                      //��ʼ��WiFiģ��ʹ�õĽӿں�����
	DHT11_Init ();                                                        //��ʼ��DHT11
	BEEP_GPIO_Config();                                                   //��ʼ��������
	
	//LCD ��ʼ��
	ILI9341_Init (); 
	//����0��3��5��6 ģʽ�ʺϴ���������ʾ���֣�
	//���Ƽ�ʹ������ģʽ��ʾ����	����ģʽ��ʾ���ֻ��о���Ч��			
	//���� 6 ģʽΪ�󲿷�Һ�����̵�Ĭ����ʾ����  
	ILI9341_GramScan ( 6 );

  ILI9341_Clear(0,0,LCD_X_LENGTH,LCD_Y_LENGTH);	/* ��������ʾȫ�� */
	
	printf ( "\r\nҰ�� WF-ESP8266 WiFiģ���������\r\n" );                 //��ӡ����������ʾ��Ϣ

  ESP8266_StaTcpClient_Unvarnish_ConfigTest();                          //��ESP8266��������
  
  
	SysTick_Init ();                                                      //���� SysTick Ϊ 10ms �ж�һ�Σ����ж����ȡ����������
  
  while ( 1 )
  {
    
    if( read_dht11_finish ) // read_dht11_finish == 1 or read_dht11_finish == -1
    {
      
      ESP8266_SendDHT11DataTest(); // ESP8266 ����һ����ʪ������
//      printf("read_dht11_finish=%d\r\n", read_dht11_finish);    //Debug
      read_dht11_finish = 0;       // �����־λ
      
			LCD_DisplayDHT11DataTest();  //��ʾDHT11��ʪ������
			BEEP_CheckDHT11DataTest();   //�����ʪ���ж��Ƿ�Ԥ��
      LED2_TOGGLE;                  //�̵���
    }
		if( read_dht11_finish == -1) // read_dht11_finish == 1 or read_dht11_finish == -1
    {
      
			LCD_DisplayDHT11ReadErrorTest();  //��ʾDHT11��ȡ��ʪ��ʧ����Ϣ
    }
    ESP8266_CheckRecvDataTest();  // ESP8266 ���һ���Ƿ���յ�������
  }
	
	
}


/*********************************************END OF FILE**********************/
