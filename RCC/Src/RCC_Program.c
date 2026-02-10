/**
 ******************************************************************************
 * @file           : RCC_Program.c
 * @author         : Amany_Elsedawy
 * @version        : 0.0
 * @date           : 31-10-2025
 * @brief          : PROGRAM file for RCC driver
 * @note           : Built for STM32NUCLEO F446xx
 ******************************************************************************
 */
#include<stdint.h>

/*library layer*/
#include"STM32F446xxLIB.h"
#include"ErrorType.h"

/*RCC files*/

#include"RCC_Interface.h"
#include"RCC_Private.h"



/**
 ******************************************************************************
 * @fn RCC_SetClk
 * @brief Enables or disables a specific clock source (HSI, HSE, PLL,PLLI2S or PLLSAI)
 * @param[in] ClkSrc     : Clock source to configure
 * @param[in] ClkStatus  : Desired status (ENABLE or DISABLE)
 * @retval ErrorStatus   : Returns status indicating success or failure
 ******************************************************************************
 */
uint8_t RCC_SetClk(RCC_ClkSrc_t ClkSrc, RCC_Status_t ClkStatus){


	/*create error status variable*/
	uint8_t LocalErrorStatus = STD_OK;
	uint32_t counter=0;
	/*check CLK on or off*/
	if(ClkStatus==Enable){
		/*switch which type of RCC Source select*/

		switch(ClkSrc){

		case SRC_HSI:
			/*set pin 0 in CR to enable HSI*/
			RCC->CR|=(1U<<HSION_Mask);
			/*wait for HSI flag*/
			while(!(RCC->CR&(1U<<HSI_RDY_PIN))){
				counter++;
				if(counter>TIMEOUT_HSI){
					LocalErrorStatus = STD_NOK;
					break;
				}
			}

			break;
		case SRC_HSE:

			/*set pin 16 &18 in CR to enable HSE to receive clock from ST link*/
			RCC->CR |=(1U<<HSEPYP_Mask);
			RCC->CR |=(1U<<HSEON_Mask);
			while(!(RCC->CR&(1<<HSE_RDY_PIN))){
				counter++;
				if(counter>TIMEOUT_HSE){
					LocalErrorStatus = STD_NOK;
					break;
				}
			}

			break;
		case SRC_PLL:


			RCC->CR |=(1U<<MPLLON_Mask);
			while(!(RCC->CR&(1U<<MPLL_RDY_PIN))){
				counter++;
				if(counter>TIMEOUT_PLL){
					LocalErrorStatus = STD_NOK;
					break;
				}
			}
			break;
		case  SRC_PLLI2S:

			RCC->CR |=(1U<<PLLI2SON_Mask);
			while(!(RCC->CR&(1U<<PLLI2SON_RDY_PIN))){
				counter++;
				if(counter>TIMEOUT_PLL){
					LocalErrorStatus = STD_NOK;
					break;
				}
			}
			break;
		case  SRC_PLLSAI:

			RCC->CR |=(1U<<PLLSAION_Mask);
			while(!(RCC->CR&(1U<<PLLSAION_RDY_PIN))){
				counter++;
				if(counter>TIMEOUT_PLL){
					LocalErrorStatus = STD_NOK;
					break;
				}
			}
			break;


		default:
			LocalErrorStatus=STD_NOK;
			break;
		}

	}else if(ClkStatus==Disable){
		switch(ClkSrc){

		case SRC_HSI:
			/*CLEAR pin 0 in CR to disable HSI*/
			RCC->CR &=~(1U<<HSION_Mask);


			break;
		case SRC_HSE:
			/*CLEAR pin 16 & 18in CR to disable HSE*/
			RCC->CR &=~(1U<<HSEON_Mask);
			RCC->CR &=~(1U<<HSEPYP_Mask);
			break;

		case SRC_PLL:
			/*CLEAR pin 24 in CR to disable PLL*/
			RCC->CR &=~(1U<<MPLLON_Mask);

			break;
		case SRC_PLLI2S:
			/*CLEAR pin 26 in CR to disable PLL*/
			RCC->CR &=~(1U<<PLLI2SON_Mask);

			break;
       case SRC_PLLSAI:
	        /*CLEAR pin 28 in CR to disable PLL*/
	         RCC->CR &=~(1U<<PLLSAION_Mask);

	break;
default:
	LocalErrorStatus=STD_NOK;
	break;

		}
	}

	return  LocalErrorStatus;

}


/**
 ******************************************************************************
 * @fn RCC_SetSystemClock
 * @brief Selects the system clock source (HSI / HSE / PLLP / PLLR)
 * @param[in] ClkSrc     : Desired system clock source
 * @retval ErrorStatus   : Returns status indicating if selection was successful
 ******************************************************************************
 */
uint8_t RCC_SetSystemClock(RCC_ClkSW_t ClkSW){

	uint32_t counter=0;
	/*create error status variable*/
	uint8_t LocalErrorStatus = STD_OK;
	/*clear CFGR pins for switch */
	RCC->CFGR &=~(0b11<<0);
	/*set CFGR reg by SW clock*/
	RCC->CFGR |= (ClkSW << 0);
	/* Wait until switch happens or timeout expires*/
	while(((RCC->CFGR>>2)&0b11)!=ClkSW){
		counter++;
		if(counter>TIMEOUT_SW){
			LocalErrorStatus = STD_NOK;

		}


	}

	return LocalErrorStatus;

}


/**
 ******************************************************************************
 * @fn RCC_PLLConfig
 * @brief Configures PLL multiplication and division factors
 * @param[in] PllConfig  : Pointer to PLL configuration structure
 * @retval ErrorStatus   : Returns status indicating if PLL configuration succeeded
 ******************************************************************************
 */
uint8_t RCC_PLLConfig(const RCC_PllConfig_t *PllConfig){
	/*create error status variable*/
	uint8_t LocalErrorStatus = STD_OK;
	/*check for PLL is off before config*/
	if((RCC->CR>>24)&1){

		return STD_NOK;//PLL must disable first
	}
	/*clear old bit*/
	RCC->PLLCFGR &= ~((1<<22) | (0x3F<<0) | (0x1FF<<6) | (0b11<<16) | (0xF<<24) | (0x7<<28));


	/*set PLL source*/
	/* Bit 22 */
	RCC->PLLCFGR|=(PllConfig->PLLSRC<<22);

	/*ensure VCO_IN as VCO input frequency = PLL input clock frequency / PLLM with 2 ≤ PLLM ≤ 63 */
	/* Bits 5:0*/
	RCC->PLLCFGR|=(PllConfig->M_Div<<0);
	/*ensureVCO_OUT as VCO output frequency = VCO input frequency × PLLN with 50 ≤ PLLN ≤ 432*/

	/*make sure NFactor set in correct range */
	if((PllConfig->N_Mult>=PLLN_MIN) && (PllConfig->N_Mult<=PLLN_MAX) ){
		/*  Bits 14:6 */
		RCC->PLLCFGR|=(PllConfig->N_Mult<<6);


	}else{
		LocalErrorStatus = STD_NOK;

	}
	/*set PLL frequency as PLL output clock frequency = VCO frequency / PLLP with PLLP */
	/* Bits 17:16*/
	RCC->PLLCFGR|=(PllConfig->SysClk_Factor<<16);
	/* set USB frequency as USB OTG FS clock frequency = VCO frequency / PLLQ with 2 ≤ PLLQ ≤ 15 */
	/*  Bits 27:24*/
	RCC->PLLCFGR|=(PllConfig->USB_Factor<<24);
	/* set I2S frequency as Clock frequency = VCO frequency / PLLR with 2 ≤ PLLR ≤ 7*/
	/* Bits 30:28 */
	RCC->PLLCFGR|=(PllConfig->I2S_Factor<<28);

	return LocalErrorStatus;
}


/**
 ******************************************************************************
 * @fn RCC_EnablePeripheral
 * @brief Enables the clock for a specific peripheral on a given bus
 * @param[in] Bus         : The bus to which the peripheral belongs (AHB1, AHB2, APB1, APB2)
 * @param[in] peripheral  : The peripheral to enable
 * @retval None
 ******************************************************************************
 */
void RCC_EnablePeripheral(RCC_BUS_t Bus, uint32_t peripheral){
	switch(Bus){

	case AHB1:
		RCC->AHB1ENR |=(1U<<peripheral);


		break;
	case AHB2:

		RCC->AHB2ENR|=(1U<<peripheral);

		break;
	case AHB3:
		RCC->AHB3ENR|=(1U<<peripheral);


		break;
	case APB1:
		RCC->APB1ENR|=(1U<<peripheral);

		break;
	case APB2:

		RCC->APB2ENR|=(1U<<peripheral);
		break;



	}


}


/**
 ******************************************************************************
 * @fn RCC_DisablePeripheral
 * @brief Disables the clock for a specific peripheral on a given bus
 * @param[in] Bus         : The bus to which the peripheral belongs
 * @param[in] peripheral  : The peripheral to disable
 * @retval None
 ******************************************************************************
 */
void RCC_DisablePeripheral(RCC_BUS_t Bus, uint32_t peripheral){
	switch(Bus){

	case AHB1:
		RCC->AHB1ENR &=~(1U<<peripheral);


		break;
	case AHB2:

		RCC->AHB2ENR&=~(1U<<peripheral);

		break;
	case AHB3:
		RCC->AHB3ENR&=~(1U<<peripheral);


		break;
	case APB1:
		RCC->APB1ENR&=~(1U<<peripheral);

		break;
	case APB2:

		RCC->APB2ENR&=~(1U<<peripheral);
		break;
	}
}


/**
 ******************************************************************************
 * @fn RCC_LPEnablePeripheral
 * @brief Enables peripheral clock during Low Power mode
 * @param[in] Bus         : The bus of the peripheral (AHB1, AHB2, APB1, APB2)
 * @param[in] peripheral  : The peripheral to enable in low-power mode
 * @retval None
 ******************************************************************************
 */
void RCC_LPEnablePeripheral(RCC_BUS_t Bus, uint32_t peripheral){

	switch(Bus){

	case AHB1:
		RCC->AHB1LPENR|=(1U<<peripheral);


		break;
	case AHB2:

		RCC->AHB2LPENR|=(1U<<peripheral);

		break;
	case AHB3:
		RCC->AHB3LPENR|=(1U<<peripheral);


		break;
	case APB1:
		RCC->APB1LPENR|=(1U<<peripheral);

		break;
	case APB2:

		RCC->APB2LPENR|=(1U<<peripheral);
		break;



	}





}


/**
 ******************************************************************************
 * @fn RCC_LPDisablePeripheral
 * @brief Disables peripheral clock during Low Power mode
 * @param[in] Bus         : The bus of the peripheral (AHB1, AHB2, APB1, APB2)
 * @param[in] peripheral  : The peripheral to disable in low-power mode
 * @retval None
 ******************************************************************************
 */
void RCC_LPDisablePeripheral(RCC_BUS_t Bus, uint32_t peripheral){

	switch(Bus){

	case AHB1:
		RCC->AHB1LPENR &=~(1U<<peripheral);


		break;
	case AHB2:

		RCC->AHB2LPENR&=~(1U<<peripheral);

		break;
	case AHB3:
		RCC->AHB3LPENR&=~(1U<<peripheral);


		break;
	case APB1:
		RCC->APB1LPENR&=~(1U<<peripheral);

		break;
	case APB2:

		RCC->APB2LPENR&=~(1U<<peripheral);
		break;
	}
}


/**
 ******************************************************************************
 * @fn RCC_ResetPeripheral
 * @brief Resets a specific peripheral by toggling its reset bit
 * @param[in] Bus         : The bus where the peripheral is located
 * @param[in] peripheral  : The peripheral to reset
 * @retval None
 ******************************************************************************
 */
void RCC_ResetPeripheral(RCC_BUS_t Bus, uint32_t peripheral){


	switch(Bus){

	case AHB1:
		RCC->AHB1RSTR|=(1U<<peripheral);


		break;
	case AHB2:

		RCC->AHB2RSTR|=(1U<<peripheral);

		break;
	case AHB3:
		RCC->AHB3RSTR|=(1U<<peripheral);


		break;
	case APB1:
		RCC->APB1RSTR|=(1U<<peripheral);

		break;
	case APB2:

		RCC->APB2RSTR|=(1U<<peripheral);
		break;



	}


}







