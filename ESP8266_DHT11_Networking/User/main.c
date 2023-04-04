/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-01-xx
  * @brief   WF-ESP8266 WiFi模块测试
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 iSO STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
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
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main ( void )
{
	/* 初始化 */
  USART_Config ();                                                      //初始化串口1
  CPU_TS_TmrInit();                                                     //初始化DWT计数器，用于延时函数
  LED_GPIO_Config();                                                    //初始化RGB彩灯
	ESP8266_Init ();                                                      //初始化WiFi模块使用的接口和外设
	DHT11_Init ();                                                        //初始化DHT11
	BEEP_GPIO_Config();                                                   //初始化蜂鸣器
	
	//LCD 初始化
	ILI9341_Init (); 
	//其中0、3、5、6 模式适合从左至右显示文字，
	//不推荐使用其它模式显示文字	其它模式显示文字会有镜像效果			
	//其中 6 模式为大部分液晶例程的默认显示方向  
	ILI9341_GramScan ( 6 );

  ILI9341_Clear(0,0,LCD_X_LENGTH,LCD_Y_LENGTH);	/* 清屏，显示全黑 */
	
	printf ( "\r\n野火 WF-ESP8266 WiFi模块测试例程\r\n" );                 //打印测试例程提示信息

  ESP8266_StaTcpClient_Unvarnish_ConfigTest();                          //对ESP8266进行配置
  
  
	SysTick_Init ();                                                      //配置 SysTick 为 10ms 中断一次，在中断里读取传感器数据
  
  while ( 1 )
  {
    
    if( read_dht11_finish ) // read_dht11_finish == 1 or read_dht11_finish == -1
    {
      
      ESP8266_SendDHT11DataTest(); // ESP8266 发送一次温湿度数据
//      printf("read_dht11_finish=%d\r\n", read_dht11_finish);    //Debug
      read_dht11_finish = 0;       // 清零标志位
      
			LCD_DisplayDHT11DataTest();  //显示DHT11温湿度数据
			BEEP_CheckDHT11DataTest();   //检查温湿度判断是否预警
      LED2_TOGGLE;                  //绿灯亮
    }
		if( read_dht11_finish == -1) // read_dht11_finish == 1 or read_dht11_finish == -1
    {
      
			LCD_DisplayDHT11ReadErrorTest();  //显示DHT11获取温湿度失败信息
    }
    ESP8266_CheckRecvDataTest();  // ESP8266 检查一次是否接收到了数据
  }
	
	
}


/*********************************************END OF FILE**********************/
