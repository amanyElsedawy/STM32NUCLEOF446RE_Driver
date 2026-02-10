#ifndef  STM32F446xxLIB_H
#define  STM32F446xxLIB_H





/******           Various Memories Base Addresses       ******/


#define FLASH_BASE_ADDRESS        0x08000000UL
#define SRAM_BASE_ADDRESS         0x20000000UL
#define  ROM_BASE_ADDRESS         0x1FFF0000UL









/******     AHB1   Peripheral    Base    Address     ******/

#define GPIOA_BASE_ADDRESS       0x40020000U
#define GPIOB_BASE_ADDRESS       0x40020400U
#define GPIOC_BASE_ADDRESS       0x40020800U
#define GPIOD_BASE_ADDRESS       0x40020C00U
#define GPIOE_BASE_ADDRESS       0x40021000U
#define GPIOF_BASE_ADDRESS       0x40021400U 
#define GPIOG_BASE_ADDRESS       0x40021800U
#define GPIOH_BASE_ADDRESS       0x40021C00U

#define RCC_BASE_ADDRESS         0x40023800U

/******     AHB2   Peripheral    Base    Address     ******/



/******     AHB3   Peripheral    Base    Address     ******/



/******     APB1   Peripheral    Base    Address     ******/

/******     APB2   Peripheral    Base    Address     ******/

/******     APB3   Peripheral    Base    Address     ******/



/******     GPIO  Register Definition Structure     ******/




typedef  struct{

	volatile uint32_t   MODER;     /*GPIO  PORT MODR Register */
	volatile uint32_t	OTYPER;    /*GPIO  PORT Output Type Register */
	volatile uint32_t	OSPEEDR;   /*GPIO  PORT Output Speed Register */
	volatile uint32_t	PUPDR;     /*GPIO  PORT Pull up/down Register */
	volatile uint32_t	IDR;       /*GPIO  PORT Input Data Register */
	volatile uint32_t	ODR;       /*GPIO  PORT Output Data Register */
	volatile uint32_t	BSRR;      /*GPIO  PORT Bit Set/Reset Register */
	volatile uint32_t	LCKR;      /*GPIO  PORT LOCK  Register */
	volatile uint32_t	AFR[2];    /*GPIO  PORT Alternative function Register */


}GPIO_RegDef_t;



/******     RCC Rrgister Definition  Structre     ******/
typedef struct
{
	volatile uint32_t CR;            /*!< RCC clock control register,                                  Address offset: 0x00 */
	volatile uint32_t PLLCFGR;       /*!< RCC PLL configuration register,                              Address offset: 0x04 */
	volatile uint32_t CFGR;          /*!< RCC clock configuration register,                            Address offset: 0x08 */
	volatile uint32_t CIR;           /*!< RCC clock interrupt register,                                Address offset: 0x0C */
	volatile uint32_t AHB1RSTR;      /*!< RCC AHB1 peripheral reset register,                          Address offset: 0x10 */
	volatile uint32_t AHB2RSTR;      /*!< RCC AHB2 peripheral reset register,                          Address offset: 0x14 */
	volatile uint32_t AHB3RSTR;      /*!< RCC AHB3 peripheral reset register,                          Address offset: 0x18 */
	uint32_t          RESERVED0;     /*!< Reserved, 0x1C */
	volatile uint32_t APB1RSTR;      /*!< RCC APB1 peripheral reset register,                          Address offset: 0x20 */
	volatile uint32_t APB2RSTR;      /*!< RCC APB2 peripheral reset register,                          Address offset: 0x24 */
	uint32_t          RESERVED1[2];  /*!< Reserved, 0x28–0x2C */
	volatile uint32_t AHB1ENR;       /*!< RCC AHB1 peripheral clock enable register,                   Address offset: 0x30 */
	volatile uint32_t AHB2ENR;       /*!< RCC AHB2 peripheral clock enable register,                   Address offset: 0x34 */
	volatile uint32_t AHB3ENR;       /*!< RCC AHB3 peripheral clock enable register,                   Address offset: 0x38 */
	uint32_t          RESERVED2;     /*!< Reserved, 0x3C */
	volatile uint32_t APB1ENR;       /*!< RCC APB1 peripheral clock enable register,                   Address offset: 0x40 */
	volatile uint32_t APB2ENR;       /*!< RCC APB2 peripheral clock enable register,                   Address offset: 0x44 */
	uint32_t          RESERVED3[2];  /*!< Reserved, 0x48–0x4C */
	volatile uint32_t AHB1LPENR;     /*!< RCC AHB1 peripheral clock enable in low power mode register, Address offset: 0x50 */
	volatile uint32_t AHB2LPENR;     /*!< RCC AHB2 peripheral clock enable in low power mode register, Address offset: 0x54 */
	volatile uint32_t AHB3LPENR;     /*!< RCC AHB3 peripheral clock enable in low power mode register, Address offset: 0x58 */
	uint32_t          RESERVED4;     /*!< Reserved, 0x5C */
	volatile uint32_t APB1LPENR;     /*!< RCC APB1 peripheral clock enable in low power mode register, Address offset: 0x60 */
	volatile uint32_t APB2LPENR;     /*!< RCC APB2 peripheral clock enable in low power mode register, Address offset: 0x64 */
	uint32_t          RESERVED5[2];  /*!< Reserved, 0x68–0x6C */
	volatile uint32_t BDCR;          /*!< RCC Backup domain control register,                          Address offset: 0x70 */
	volatile uint32_t CSR;           /*!< RCC clock control & status register,                         Address offset: 0x74 */
	uint32_t          RESERVED6[2];  /*!< Reserved, 0x78–0x7C */
	volatile uint32_t SSCGR;         /*!< RCC spread spectrum clock generation register,               Address offset: 0x80 */
	volatile uint32_t PLLI2SCFGR;    /*!< RCC PLLI2S configuration register,                           Address offset: 0x84 */
	volatile uint32_t PLLSAICFGR;    /*!< RCC PLLSAI configuration register,                           Address offset: 0x88 */
	volatile uint32_t DCKCFGR;       /*!< RCC Dedicated Clocks configuration register,                 Address offset: 0x8C */
	volatile uint32_t CKGATENR;      /*!< RCC Clocks Gated Enable Register,                            Address offset: 0x90 */
	volatile uint32_t DCKCFGR2;      /*!< RCC Dedicated Clocks configuration register 2,               Address offset: 0x94 */
} RCC_RegDef_t;
/*****  RCC    pointer to structure  *****/
#define  RCC         ((RCC_RegDef_t*)RCC_BASE_ADDRESS)



/******     GPIO  peripheral Definition     ******/




#define  GPIOA         ((GPIO_RegDef_t*)GPIOA_BASE_ADDRESS)
#define  GPIOB         ((GPIO_RegDef_t*)GPIOB_BASE_ADDRESS)
#define  GPIOC         ((GPIO_RegDef_t*)GPIOC_BASE_ADDRESS)
#define  GPIOD         ((GPIO_RegDef_t*)GPIOD_BASE_ADDRESS)
#define  GPIOE         ((GPIO_RegDef_t*)GPIOE_BASE_ADDRESS)
#define  GPIOF         ((GPIO_RegDef_t*)GPIOF_BASE_ADDRESS)
#define  GPIOG         ((GPIO_RegDef_t*)GPIOG_BASE_ADDRESS)
#define  GPIOH         ((GPIO_RegDef_t*)GPIOH_BASE_ADDRESS)



#endif
