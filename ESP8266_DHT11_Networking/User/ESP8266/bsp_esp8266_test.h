#ifndef  __ESP8266_TEST_H
#define	 __ESP8266_TEST_H



#include "stm32f10x.h"
#include "stdlib.h"


/********************************** �û���Ҫ���õĲ���**********************************/
#define      macUser_ESP8266_ApSsid                       "cyx"                //Ҫ���ӵ��ȵ������
#define      macUser_ESP8266_ApPwd                        "0316cyx440"           //Ҫ���ӵ��ȵ����Կ
//#define      macUser_ESP8266_ApSsid                       "zyj"                //Ҫ���ӵ��ȵ������
//#define      macUser_ESP8266_ApPwd                        "12345678"           //Ҫ���ӵ��ȵ����Կ

#define      macUser_ESP8266_TcpServer_IP                 "192.168.43.148"      //Ҫ���ӵķ������� IP
#define      macUser_ESP8266_TcpServer_Port               "12345"               //Ҫ���ӵķ������Ķ˿�
//#define      macUser_ESP8266_TcpServer_IP                 "192.168.212.36"      //Ҫ���ӵķ������� IP
//#define      macUser_ESP8266_TcpServer_Port               "12345"               //Ҫ���ӵķ������Ķ˿�



/********************************** �ⲿȫ�ֱ��� ***************************************/
extern volatile uint8_t ucTcpClosedFlag;
extern int read_dht11_finish;



/********************************** ���Ժ������� ***************************************/
void ESP8266_StaTcpClient_Unvarnish_ConfigTest(void);
void ESP8266_SendDHT11DataTest(void);
void ESP8266_CheckRecvDataTest(void);

#endif

