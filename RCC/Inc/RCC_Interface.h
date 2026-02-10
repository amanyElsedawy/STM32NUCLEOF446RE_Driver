/**
 ******************************************************************************
 * @file           : RCC_Interface.h
 * @author         : Amany_Elsedawy
 * @version        : 0.0
 * @date           : 28-10-2025
 * @brief          : Interface file for RCC driver
 * @note           : Built for STM32NucleoF446re
 ******************************************************************************
 */

#ifndef RCC_Interface_H
#define RCC_Interface_H


#include<stdint.h>


/*Enum have options of switch of clock*/

typedef  enum{


	SW_HSI=0,      /* High Speed Internal*/
	SW_HSE,
	SW_PLL_P,     /* PLL main output P*/
	SW_PLL_R      /* PLL main output R*/

}RCC_ClkSW_t;

/*Enum have options of source of clock*/
typedef  enum{


	SRC_HSI=0,      // High Speed Internal
	SRC_HSE,
	SRC_PLL,// High Speed External
    SRC_PLLI2S,
	SRC_PLLSAI

}RCC_ClkSrc_t;



typedef enum{

	Enable,
	Disable

}RCC_Status_t;

typedef  enum{

	HSI=0,
	HSE,



}RCC_PllClkSrc_t;

/****  SET configuration for M :Division factor for the main PLL  *****/

typedef enum
{
	PLLM_DIV2 = 2,
	PLLM_DIV3,
	PLLM_DIV4,
	PLLM_DIV5,
	PLLM_DIV6,
	PLLM_DIV7,
	PLLM_DIV8,
	PLLM_DIV9,
	PLLM_DIV10,
	PLLM_DIV11,
	PLLM_DIV12,
	PLLM_DIV13,
	PLLM_DIV14,
	PLLM_DIV15,
	PLLM_DIV16,
	PLLM_DIV17,
	PLLM_DIV18,
	PLLM_DIV19,
	PLLM_DIV20,
	PLLM_DIV21,
	PLLM_DIV22,
	PLLM_DIV23,
	PLLM_DIV24,
	PLLM_DIV25,
	PLLM_DIV26,
	PLLM_DIV27,
	PLLM_DIV28,
	PLLM_DIV29,
	PLLM_DIV30,
	PLLM_DIV31,
	PLLM_DIV32,
	PLLM_DIV33,
	PLLM_DIV34,
	PLLM_DIV35,
	PLLM_DIV36,
	PLLM_DIV37,
	PLLM_DIV38,
	PLLM_DIV39,
	PLLM_DIV40,
	PLLM_DIV41,
	PLLM_DIV42,
	PLLM_DIV43,
	PLLM_DIV44,
	PLLM_DIV45,
	PLLM_DIV46,
	PLLM_DIV47,
	PLLM_DIV48,
	PLLM_DIV49,
	PLLM_DIV50,
	PLLM_DIV51,
	PLLM_DIV52,
	PLLM_DIV53,
	PLLM_DIV54,
	PLLM_DIV55,
	PLLM_DIV56,
	PLLM_DIV57,
	PLLM_DIV58,
	PLLM_DIV59,
	PLLM_DIV60,
	PLLM_DIV61,
	PLLM_DIV62,
	PLLM_DIV63

} RCC_PLLM_Div_t;


/****  Set configuration for N: Main PLL (PLL) multiplication factor for VCO   ****/
#define PLLN_MIN  50
#define PLLN_MAX  432


/****  SET R :PLL division factor for I2Ss, SAIs, SYSTEM and SPDIF-Rx clocks *****/
typedef enum{

	PLLR_DIV2=2,
	PLLR_DIV3=3,
	PLLR_DIV4=4,
	PLLR_DIV5=5,
	PLLR_DIV6=6,
	PLLR_DIV7=7

}RCC_PLLR_DIV_t;

/****  SET P: division factor for  (system Clock) configuration*****/
typedef enum{
	PLLP_DIV2=0,
	PLLP_DIV4,
	PLLP_DIV6,
	PLLP_DIV8

}RCC_PLLP_DIV_t;
/****  SET Q: division factor for (USB)configuration*****/
typedef enum {
	PLLQ_DIV2 = 2,
	PLLQ_DIV3,
	PLLQ_DIV4,
	PLLQ_DIV5,
	PLLQ_DIV6,
	PLLQ_DIV7,
	PLLQ_DIV8,
	PLLQ_DIV9,
	PLLQ_DIV10,
	PLLQ_DIV11,
	PLLQ_DIV12,
	PLLQ_DIV13,
	PLLQ_DIV14,
	PLLQ_DIV15
} RCC_PLLQ_DIV_t;

typedef enum{
	PLLSRC_HSI =0,
	PLLSRC_HSE

}RCC_PLLSRC;
/****  SET R (I2S or system Clock) configuration*****/

typedef  struct{
	RCC_PLLSRC    PLLSRC;
	RCC_PLLM_Div_t  M_Div;
	uint32_t        N_Mult;
	RCC_PLLP_DIV_t  SysClk_Factor;
	RCC_PLLQ_DIV_t  USB_Factor;
	RCC_PLLR_DIV_t  I2S_Factor;


}RCC_PllConfig_t;

/***enum for AHB1 Reset peripheral  ***/




typedef enum{
	GPIOARST=0,
	GPIOBRST=1,
	GPIOCRST=2,
	GPIODRST=3,
	GPIOERT=4,
	GPIOFRST=5,
	GPIOGRST=6,
	GPIOHRST=7,
	CRCRST=12,
	DMA1=21,
	DMA2=22,
	OTGHSRST=29

}RCC_AHB1RST_Periph_t;


/*** enum for AHB2 Reset peripheral ***/


typedef  enum{


	DCMIRST =0,
	OTGFSRST=7

}RCC_AHB2RST_Periph_t;


/*** enum for AHB3  Reset peripheral ***/


typedef  enum{


	FMCRST=0,
	QSPIRST=1

}RCC_AHB3RST_Periph_t;

/*** enum for APB1 Reset peripheral ***/


typedef  enum{

	TIM2RST=0,
	TIM3RST=1,
	TIM4RST=2,
	TIM5RST=3,
	TIM6RST=4,
	TIM7RST=5,
	TIM12RST=6,
	TIM13RST=7,
	TIM14RST=8,

	WWDGRST=11,
	SPI2RST=14,
	SPI3RST=15,
	SPDIFRXRST=16,
	UART2RST=17,
	UART3RST=18,
	UART4RST=19,
	UART5RST=20,


	I2C1RST=21,
	I2C2RST=22,
	I2C3RST=23,
	FMPI2C1RST=24,
	CAN1RST=25,
	CAN2RST=26,
	CECRST=27,
	PWRRST=28,
	DACRST=29

}RCC_APB1RST_Periph_t;


/*** enum for APB2 Reset peripheral ***/


typedef  enum{

	TIM1RST=0,
	TIM8RST=1,
	USART1RST=4,
	USART6RST=5,
	ADCRST=8,
	SDIORST=11,
	SPI1RST=12,
	SPI4RST=13,
	SYSCFGRST=14,
	TIM9RST=16,
	TIM10RST=17,
	TIM11RST=18,
	SAI1RST=22,
	SAI2RST=23


}RCC_APB2RST_Periph_t;



/*** enum for AHB1 enable ***/

typedef enum
{
	GPIOA_EN      = 0,   // Bit 0  : IO port A clock enable
	GPIOB_EN      = 1,   // Bit 1  : IO port B clock enable
	GPIOC_EN      = 2,   // Bit 2  : IO port C clock enable
	GPIOD_EN      = 3,   // Bit 3  : IO port D clock enable
	GPIOE_EN      = 4,   // Bit 4  : IO port E clock enable
	GPIOF_EN      = 5,   // Bit 5  : IO port F clock enable
	GPIOG_EN      = 6,   // Bit 6  : IO port G clock enable
	GPIOH_EN      = 7,   // Bit 7  : IO port H clock enable
	CRC_EN        = 12,  // Bit 12 : CRC clock enable
	BKPSRAM_EN    = 18,  // Bit 18 : Backup SRAM interface clock enable
	DMA1_EN       = 21,  // Bit 21 : DMA1 clock enable
	DMA2_EN       = 22,  // Bit 22 : DMA2 clock enable
	OTGHS_EN      = 29,  // Bit 29 : USB OTG HS clock enable
	OTGHSULPI_EN  = 30   // Bit 30 : USB OTG HS ULPI clock enable
} RCC_AHB1EN_Periph_t;

/****   enum for AHB2 Peripheral enable   ****/

typedef enum{


	DCMI_EN=0,
	/*BITS 0:6  Reserved*/
	OTGFS_EN=7,
	/*BITS 8:31  Reserved*/

}RCC_AHB2EN_Periph_t;

/****   enum for AHB3 Peripheral enable   ****/

typedef enum{


	 FMC_EN=0,
	 QSPI_EN=1,
	/*BITS 2:31  Reserved*/

}RCC_AHB3EN_Periph_t;

/****   Enum for APB1 Peripheral Clock Enable Bits   ****/
typedef enum
{
    TIM2_EN        = 0,
    TIM3_EN        = 1,
    TIM4_EN        = 2,
    TIM5_EN        = 3,
    TIM6_EN        = 4,
    TIM7_EN        = 5,
    TIM12_EN       = 6,
    TIM13_EN       = 7,
    TIM14_EN       = 8,
    WWDG_EN        = 11,
    SPI2_EN        = 14,
    SPI3_EN        = 15,
    SPDIFRX_EN     = 16,
    USART2_EN      = 17,
    USART3_EN      = 18,
    UART4_EN       = 19,
    UART5_EN       = 20,
    I2C1_EN        = 21,
    I2C2_EN        = 22,
    I2C3_EN        = 23,
    FMPI2C1_EN     = 24,
    CAN1_EN        = 25,
    CAN2_EN        = 26,
    CEC_EN         = 27,
    PWR_EN         = 28,
    DAC_EN         = 29
    /* Bits 30–31 Reserved*/
} RCC_APB1EN_Periph_t;

/****   Enum for APB2 Peripheral Clock Enable Bits   ****/

typedef enum
{
    TIM1_EN        = 0,
    TIM8_EN        = 1,
    /* Bits 2–3 Reserved*/
    USART1_EN      = 4,
    USART6_EN      = 5,
    /* Bits 6–7 Reserved*/
    ADC1_EN        = 8,
    ADC2_EN        = 9,
    ADC3_EN        = 10,
    SDIO_EN        = 11,
    SPI1_EN        = 12,
    SPI4_EN        = 13,
    SYSCFG_EN      = 14,
    /* Bit 15 Reserved*/
    TIM9_EN        = 16,
    TIM10_EN       = 17,
    TIM11_EN       = 18,
    /* Bits 19–21 Reserved*/
    SAI1_EN        = 22,
    SAI2_EN        = 23
    /* Bits 24–31 Reserved*/
} RCC_APB2EN_Periph_t;

/****  Enum for AHB1 Peripheral Clock Enable in Low Power Mode (RCC_AHB1LPENR)  ****/

typedef enum
{
    GPIOA_LPEN   = 0,
    GPIOB_LPEN   = 1,
    GPIOC_LPEN   = 2,
    GPIOD_LPEN   = 3,
    GPIOE_LPEN   = 4,
    GPIOF_LPEN   = 5,
    GPIOG_LPEN   = 6,
    GPIOH_LPEN   = 7,

    CRCLPEN      = 12,
    FLITFLPEN    = 15,
    SRAM1LPEN    = 16,
    SRAM2LPEN    = 17,
    BKPSRAMLPEN  = 18,
    DMA1LPEN     = 21,
    DMA2LPEN     = 22,
    OTGHSLPEN    = 29,
    OTGHSULPILPEN= 30

} RCC_AHB1LPEN_Periph_t;

/****  Enum for AHB2 Peripheral Clock Enable in Low Power Mode (RCC_AHB2LPENR)  ****/
typedef enum
{
    DCMI_LPEN   = 0,
    OTGFS_LPEN  = 7

} RCC_AHB2LPEN_Periph_t;

/****  Enum for AHB3 Peripheral Clock Enable in Low Power Mode (RCC_AHB3LPENR)  ****/
typedef enum
{
    FMCLPEN   = 0,
    QSPILPEN  = 1

} RCC_AHB3LPEN_Periph_t;
/****  Enum for APB1 Peripheral Clock Enable in Low Power Mode (RCC_APB1LPENR)  ****/
typedef enum
{
    TIM2_LPEN      = 0,
    TIM3_LPEN      = 1,
    TIM4_LPEN      = 2,
    TIM5_LPEN      = 3,
    TIM6_LPEN      = 4,
    TIM7_LPEN      = 5,
    TIM12_LPEN     = 6,
    TIM13_LPEN     = 7,
    TIM14_LPEN     = 8,
    WWDG_LPEN      = 11,
    SPI2_LPEN      = 14,
    SPI3_LPEN      = 15,
    SPDIFRX_LPEN   = 16,
    USART2_LPEN    = 17,
    USART3_LPEN    = 18,
    UART4_LPEN     = 19,
    UART5_LPEN     = 20,
    I2C1_LPEN      = 21,
    I2C2_LPEN      = 22,
    I2C3_LPEN      = 23,
    FMPI2C1_LPEN   = 24,
    CAN1_LPEN      = 25,
    CAN2_LPEN      = 26,
    CEC_LPEN       = 27,
    PWR_LPEN       = 28,
    DAC_LPEN       = 29

} RCC_APB1LPEN_Periph_t;

/****  Enum for APB2 Peripheral Clock Enable in Low Power Mode (RCC_APB2LPENR)  ****/
typedef enum
{
	TIM1_LPEN_APB2       = 0,
	TIM8_LPEN_APB2       = 1,
	USART1_LPEN_APB2     = 4,
	USART6_LPEN_APB2     = 5,
	ADC1_LPEN_APB2       = 8,
	ADC2_LPEN_APB2       = 9,
	ADC3_LPEN_APB2       = 10,
	SDIO_LPEN_APB2       = 11,
	SPI1_LPEN_APB2       = 12,
	SPI4_LPEN_APB2       = 13,
	SYSCFG_LPEN_APB2     = 14,
	TIM9_LPEN_APB2       = 16,
	TIM10_LPEN_APB2      = 17,
	TIM11_LPEN_APB2      = 18,
	SAI1_LPEN_APB2       = 22,
	SAI2_LPEN_APB2       = 23

} RCC_APB2LPEN_Periph_t;

/* enum for Bus */
typedef enum{

	AHB1,
	AHB2,
	AHB3,
	APB1,
	APB2




}RCC_BUS_t;


/*   functions prototype   */



/* function prototype to Enable/Disable CLK and set CLK source */

uint8_t RCC_SetClk(RCC_ClkSrc_t ClkSrc, RCC_Status_t ClkStatus);

/*function prototype to select system Clock(HSI / HSE / PLL)*/

uint8_t RCC_SetSystemClock(RCC_ClkSW_t ClkSW);

/*function prototype to set PLL configuration*/
uint8_t RCC_PLLConfig( const RCC_PllConfig_t *PllConfig);


void RCC_EnablePeripheral(RCC_BUS_t Bus, uint32_t peripheral);


void RCC_DisablePeripheral(RCC_BUS_t Bus, uint32_t peripheral);


void RCC_LPEnablePeripheral(RCC_BUS_t Bus, uint32_t peripheral);


void RCC_LPDisablePeripheral(RCC_BUS_t Bus, uint32_t peripheral);


void RCC_ResetPeripheral(RCC_BUS_t Bus, uint32_t peripheral);




#endif
