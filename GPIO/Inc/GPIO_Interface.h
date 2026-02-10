
/**
 ******************************************************************************
 * @file           : GPIO_Interface.h
 * @author         : Amany_Elsedawy
 * @version        : 0.0
 * @date           : 24-10-2025
 * @brief          : Interface file for GPIO driver
 * @note           : Built for STM32NUCLEO F446xx
 ******************************************************************************
 */


#ifndef  GPIO_INTERFACE_H
#define  GPIO_INTERFACE_H



#include<stdint.h>


typedef enum{


	PORTA=0,
	PORTB,
	PORTC,
	PORTD,
	PORTE,
	PORTF,
	PORTG,
	PORTH


}GPIO_Port_t;

typedef enum{
	
	
	
	PIN0=0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7,
	PIN8,
	PIN9,
	PIN10,
	PIN11,
	PIN12,
	PIN13,
	PIN14,
	PIN15
	
}GPIO_Pin_t;




typedef enum{
	
	
	PIN_LOW=0,
	PIN_HIGH
	
}GPIO_PinVal_t;
typedef enum{
	
	INPUT=0,
	OUTPUT,
	ALTERNATIVE_FUNCTION,
	ANALOG
}GPIO_Mode_t;
 
 
 typedef enum{
	 
	 
	LOW=0,
    MEDIUM,
    FAST, 
    HIGH
}GPIO_OutputSpeed_t;


typedef enum{
	
	PUSH_PULL=0,
	OPEN_DRAIN,
	
}GPIO_OutputType_t;

typedef  enum{
	
	NOPULL=0,
	PULLUP,
	PULLDOWN
	
}GPIO_PullUpDown_t;


typedef enum{
	
   AF0=0,
   AF1,
   AF2,
   AF3,
   AF4,
   AF5,
   AF6,
   AF7,
   AF8,
   AF9,
   AF10,
   AF11,
   AF12,
   AF13,
   AF14,
   AF15
	
	
}GPIO_AltFunc_t;


typedef  struct{
	GPIO_Port_t Port;//2line for clear and or 
	GPIO_Pin_t  PinNum;
	GPIO_Mode_t Mode;
	GPIO_OutputSpeed_t  Speed;
	GPIO_OutputType_t   OutPutType;
	GPIO_PullUpDown_t  PullType;
	GPIO_AltFunc_t   AltFunc;
	
	
}GPIO_pinConfig_t;



uint8_t  GPIO_u8PinInit( const GPIO_pinConfig_t* PinConfig );

uint8_t   GPIO_u8SetPinValue(GPIO_Port_t Port, GPIO_Pin_t PinNum,GPIO_PinVal_t Pin_Val);

uint8_t   GPIO_u8TogglePinValue(GPIO_Port_t Port, GPIO_Pin_t PinNum);

uint8_t   GPIO_u8ReadPinValue(GPIO_Port_t Port, GPIO_Pin_t PinNum,GPIO_PinVal_t* Pin_Val);



#endif
