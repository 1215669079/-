#ifndef  __ESP8266_TEST_H
#define	 __ESP8266_TEST_H



#include "stm32f10x.h"
#include "stdlib.h"


/********************************** 用户需要设置的参数**********************************/
#define      macUser_ESP8266_ApSsid                       "cyx"                //要连接的热点的名称
#define      macUser_ESP8266_ApPwd                        "0316cyx440"           //要连接的热点的密钥
//#define      macUser_ESP8266_ApSsid                       "zyj"                //要连接的热点的名称
//#define      macUser_ESP8266_ApPwd                        "12345678"           //要连接的热点的密钥

#define      macUser_ESP8266_TcpServer_IP                 "192.168.43.148"      //要连接的服务器的 IP
#define      macUser_ESP8266_TcpServer_Port               "12345"               //要连接的服务器的端口
//#define      macUser_ESP8266_TcpServer_IP                 "192.168.212.36"      //要连接的服务器的 IP
//#define      macUser_ESP8266_TcpServer_Port               "12345"               //要连接的服务器的端口



/********************************** 外部全局变量 ***************************************/
extern volatile uint8_t ucTcpClosedFlag;
extern int read_dht11_finish;



/********************************** 测试函数声明 ***************************************/
void ESP8266_StaTcpClient_Unvarnish_ConfigTest(void);
void ESP8266_SendDHT11DataTest(void);
void ESP8266_CheckRecvDataTest(void);

#endif

