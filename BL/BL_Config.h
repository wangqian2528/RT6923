#ifndef __BL_CONFIG_H__
#define __BL_CONFIG_H__

//#include "integer.h"
#include "em_cmu.h"
#include "em_usart.h"
#include "em_gpio.h"
//#include "HAL.h"
#include "Timer.h"

#define BL_UART       UART0
#define BL_LOC        UART_ROUTE_LOCATION_LOC0
#define BL_CMUCLOCK   cmuClock_UART0
#define BL_GPIOPORT   gpioPortA
#define RIFD_INTPIN     2
#define BL_TXPIN      3
#define BL_RXPIN      4

#define BL_INT_PORT   gpioPortA

#endif