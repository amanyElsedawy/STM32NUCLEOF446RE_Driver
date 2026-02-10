
/**
 ******************************************************************************
 * @file           : GPIO_Program.c
 * @author         : Amany_Elsedawy
 * @version        : 0.0
 * @date           : 24-10-2025
 * @brief          : PROGRAM file for GPIO driver
 * @note           : Built for STM32NUCLEO F446xx
 ******************************************************************************
 */
#include<stdint.h>
/*Stm32F446xx Library*/
#include"STM32F446xxLIB.h"
#include"ErrorType.h"
/*GPIO_FILES*/
#include"GPIO_Interface.h"
#include"GPIO_Private.h"

/**
 ******************************************************************************
 *@fn GPIO_u8PimInit
 *@brief the function initializes the GPIO pin according to the input parameters
 *@parameter[in] PinConfig :the initialization values of the pin
 *@retval ErrorStatus
 ******************************************************************************
 */
/*create array of pointer to structure that have GPIO_PORTS as pointer to REG Structure*/
static GPIO_RegDef_t* const GPIO_PORTS[GPIO_Peripheral_Num]={ GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH};
/*implement INIT Function*/
uint8_t  GPIO_u8PinInit( const GPIO_pinConfig_t* PinConfig ){

	/*define Local ERROR Status*/
	uint8_t LocalErrorStatus=STD_OK;
	if(PinConfig !=NULL){

		if(((PinConfig->Port) <=PORTH) && ((PinConfig->PinNum)<=PIN15)){
			/*init port of the pin*/
			GPIO_RegDef_t* GPIOx=	GPIO_PORTS[PinConfig->Port];
			/*clear moder register*/
			GPIOx->MODER&=~(MODER_MASK<< ((PinConfig->PinNum)* MODER_PIN_ACCESS ));//this line make stuck in code
			/*set moder reg by pin mode*/
			GPIOx->MODER|=((PinConfig->Mode)<< ((PinConfig->PinNum)* MODER_PIN_ACCESS ));
			/*set pull up and pull down if analog-Hardware will ignore configuration*/
			/*clear bits for  Pull up Down type*/
			GPIOx->PUPDR&=~(PUPDR_MASK<< ((PinConfig->PinNum)* PUPDR_PIN_ACCESS));
			/*set Pull up Down type*/
			GPIOx->PUPDR|=((PinConfig->PullType)<< ((PinConfig->PinNum)*  PUPDR_PIN_ACCESS  ));

			/*Select  speed and Output type in case output mode or alternative */
			if (( PinConfig->Mode == OUTPUT )|| (PinConfig->Mode == ALTERNATIVE_FUNCTION) ){
				/*clear bits for Output type*/
				GPIOx->OTYPER&=~( OTYPER_MASK << (PinConfig->PinNum));
				/*Select output type(pushpull or open drain)*/
				GPIOx->OTYPER|=((PinConfig->OutPutType ) <<(PinConfig->PinNum));
				/*clear bits for speed*/
				GPIOx->OSPEEDR&=~(OSPEEDR_MASK<<((PinConfig->PinNum)* OSPEEDR_PIN_ACCESS ));
				/*set output Speed:low, High, Fast*/
				GPIOx->OSPEEDR|=((PinConfig->Speed)  <<((PinConfig->PinNum)*  OSPEEDR_PIN_ACCESS ));


				if(PinConfig->Mode == ALTERNATIVE_FUNCTION) {


                    uint8_t Local_u8RegNum=(PinConfig->PinNum)/ 8u;
					uint8_t Local_u8BitNum=(PinConfig->PinNum) % 8;
					/*CLEAR & set alternative config*/
                    (GPIOx->AFR[Local_u8RegNum]) &=~(AFR_MASK<<(Local_u8BitNum*AFR_PIN_ACCESS ));
                    (GPIOx->AFR[Local_u8RegNum]) |= ((PinConfig->AltFunc)<<(Local_u8BitNum*AFR_PIN_ACCESS ));


				}

			}

		}


		else{
			LocalErrorStatus=STD_NOK;
		}

	}else{
		LocalErrorStatus=NULL_PTR_ERR;
	}

	return LocalErrorStatus;


}





/**
 ******************************************************************************
 *@fn GPIO_u8SetPinValue
 *@brief the function output certain value on an output pin
 *@parameter[in] Port:the port number, get options @Port_t enum
 *@parameter[in] PinNum:the Pin number, get options @Pin_t enum
 *@parameter[in] PinVal:the output value, get options @PinVal_t enum
 *@retval ErrorStatus
 ******************************************************************************
 */



uint8_t   GPIO_u8SetPinValue(GPIO_Port_t Port, GPIO_Pin_t PinNum,GPIO_PinVal_t Pin_Val){

	/*define Local ERROR Status*/
	uint8_t LocalErrorStatus=STD_OK;
	if (Port > PORTH || PinNum > PIN15 )
	{
		LocalErrorStatus = STD_NOK;
	}else{
		/*init port of the pin*/
		GPIO_RegDef_t* GPIOx=	GPIO_PORTS[Port];
		if(Pin_Val == PIN_LOW){
			/*clear bit value from BITS 16:31 in BSRR register*/
			GPIOx->BSRR=(1U<< (PinNum+16));

		}else if(Pin_Val ==PIN_HIGH ){
			/*set bit value from BITS 0:15 in BSRR register*/
			GPIOx->BSRR=(1<< PinNum);
		}
	}
	return LocalErrorStatus;



}


/**
 ******************************************************************************
 *@fn GPIO_u8TogglePinValue
 *@brief the function Toggle Output value
 *@parameter[in] Port:the port number, get options @Port_t enum
 *@parameter[in] PinNum:the Pin number, get options @Pin_t enum
 *@retval ErrorStatus
 ******************************************************************************
 */

uint8_t   GPIO_u8TogglePinValue(GPIO_Port_t Port, GPIO_Pin_t PinNum){
	/*define Local ERROR Status*/
	uint8_t LocalErrorStatus=STD_OK;

	if (Port>PORTH || PinNum>PIN15)
	{
		LocalErrorStatus = STD_NOK;
	}else{
		/*init port of the pin*/
		GPIO_RegDef_t* GPIOx=GPIO_PORTS[Port];
		GPIOx->ODR ^=(1U<< PinNum);

	}
	return LocalErrorStatus;

}

uint8_t   GPIO_u8ReadPinValue(GPIO_Port_t Port, GPIO_Pin_t PinNum,GPIO_PinVal_t* Pin_Val){
	/*define Local ERROR Status*/
	uint8_t LocalErrorStatus=STD_OK;

	if (Pin_Val == NULL || PinNum>PIN15)
	{
		LocalErrorStatus = STD_NOK;
	}else{


		GPIO_RegDef_t* GPIOx=	GPIO_PORTS[Port];

		*Pin_Val=(GPIO_PinVal_t)((GPIOx->IDR >> PinNum)&0x01);

	}
	return LocalErrorStatus;

}
