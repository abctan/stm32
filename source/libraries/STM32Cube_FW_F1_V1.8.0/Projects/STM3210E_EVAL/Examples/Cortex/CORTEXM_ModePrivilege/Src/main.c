/**
  ******************************************************************************
  * @file    Cortex/CORTEXM_ModePrivilege/Src/main.c
  * @author  MCD Application Team
  * @brief   Description of the Cortex-M3 Mode Privilege example.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup STM32F1xx_HAL_Examples
  * @{
  */

/** @addtogroup CORTEXM_ModePrivilege
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define SP_PROCESS_SIZE             0x200  /* Process stack size */
#define SP_PROCESS                  0x02   /* Process stack */
#define SP_MAIN                     0x00   /* Main stack */
#define THREAD_MODE_PRIVILEGED      0x00   /* Thread mode has privileged access */
#define THREAD_MODE_UNPRIVILEGED    0x01   /* Thread mode has unprivileged access */

/* Private function prototypes -----------------------------------------------*/
static __INLINE  void __SVC(void);

/* Private macro -------------------------------------------------------------*/
#if defined ( __CC_ARM   )
__ASM void __SVC(void)
{
  SVC 0x01
  BX R14
}
#elif defined ( __ICCARM__ )
static __INLINE  void __SVC()
{
  __ASM("svc 0x01");
}
#elif defined   (  __GNUC__  )
static __INLINE void __SVC()
{
  __ASM volatile("svc 0x01");
}
#endif

/* Private variables ---------------------------------------------------------*/
__IO uint8_t PSPMemAlloc[SP_PROCESS_SIZE];
__IO uint32_t Index = 0, PSPValue = 0, CurrentStack = 0, ThreadMode = 0;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  /* STM32F103xG HAL library initialization:
       - Configure the Flash prefetch
       - Systick timer is configured by default as source of time base, but user 
         can eventually implement his proper time base source (a general purpose 
         timer for example or other time source), keeping in mind that Time base 
         duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and 
         handled in milliseconds basis.
       - Set NVIC Group Priority to 4
       - Low Level Initialization
     */
  HAL_Init();

  /* Configure the system clock to 72 MHz */
  SystemClock_Config();

  /* Configure LED3*/
  BSP_LED_Init(LED3);

  /* Switch Thread mode Stack from Main to Process -----------------------------*/
  /* Initialize memory reserved for Process Stack */
  for(Index = 0; Index < SP_PROCESS_SIZE; Index++)
  {
    PSPMemAlloc[Index] = 0x00;
  }

  /* Set Process stack value */
  __set_PSP((uint32_t)PSPMemAlloc + SP_PROCESS_SIZE);

  /* Select Process Stack as Thread mode Stack */
  __set_CONTROL(SP_PROCESS);

  /* Execute ISB instruction to flush pipeline as recommended by Arm */
  __ISB(); 

  /* Get the Thread mode stack used */
  if((__get_CONTROL() & 0x02) == SP_MAIN)
  {
    /* Main stack is used as the current stack */
    CurrentStack = SP_MAIN;
  }
  else
  {
    /* Process stack is used as the current stack */
    CurrentStack = SP_PROCESS;

    /* Get process stack pointer value */
    PSPValue = __get_PSP();
  }

  /* Switch Thread mode from privileged to unprivileged ------------------------*/
  /* Thread mode has unprivileged access */
  __set_CONTROL(THREAD_MODE_UNPRIVILEGED | SP_PROCESS);
  
  /* Execute ISB instruction to flush pipeline as recommended by Arm */
  __ISB(); 

  /* Unprivileged access mainly affect ability to:
      - Use or not use certain instructions such as MSR fields
      - Access System Control Space (SCS) registers such as NVIC and SysTick */

  /* Check Thread mode privilege status */
  if((__get_CONTROL() & 0x01) == THREAD_MODE_PRIVILEGED)
  {
    /* Thread mode has privileged access  */
    ThreadMode = THREAD_MODE_PRIVILEGED;
  }
  else
  {
    /* Thread mode has unprivileged access*/
    ThreadMode = THREAD_MODE_UNPRIVILEGED;
  }

  /* Switch back Thread mode from unprivileged to privileged -------------------*/
  /* Try to switch back Thread mode to privileged (Not possible, this can be
     done only in Handler mode) */
  __set_CONTROL(THREAD_MODE_PRIVILEGED | SP_PROCESS);

  /* Execute ISB instruction to flush pipeline as recommended by Arm */
  __ISB(); 

  /* Generate a system call exception, and in the ISR switch back Thread mode
    to privileged */
  __SVC();

  /* Check Thread mode privilege status */
  if((__get_CONTROL() & 0x01) == THREAD_MODE_PRIVILEGED)
  {
    /* Thread mode has privileged access  */
    ThreadMode = THREAD_MODE_PRIVILEGED;
  }
  else
  {
    /* Thread mode has unprivileged access*/
    ThreadMode = THREAD_MODE_UNPRIVILEGED;
  }

  /* Infinite loop */
  while (1)
  {
  }
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 72000000
  *            HCLK(Hz)                       = 72000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 2
  *            APB2 Prescaler                 = 1
  *            HSE Frequency(Hz)              = 8000000
  *            HSE PREDIV1                    = 1
  *            PLLMUL                         = 9
  *            Flash Latency(WS)              = 2
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef clkinitstruct = {0};
  RCC_OscInitTypeDef oscinitstruct = {0};
  
  /* Enable HSE Oscillator and activate PLL with HSE as source */
  oscinitstruct.OscillatorType  = RCC_OSCILLATORTYPE_HSE;
  oscinitstruct.HSEState        = RCC_HSE_ON;
  oscinitstruct.HSEPredivValue  = RCC_HSE_PREDIV_DIV1;
  oscinitstruct.PLL.PLLState    = RCC_PLL_ON;
  oscinitstruct.PLL.PLLSource   = RCC_PLLSOURCE_HSE;
  oscinitstruct.PLL.PLLMUL      = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&oscinitstruct)!= HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  clkinitstruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  clkinitstruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  clkinitstruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  clkinitstruct.APB2CLKDivider = RCC_HCLK_DIV1;
  clkinitstruct.APB1CLKDivider = RCC_HCLK_DIV2;  
  if (HAL_RCC_ClockConfig(&clkinitstruct, FLASH_LATENCY_2)!= HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }
}



#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
