/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "_rand.h"
#include "_delay.h"
#include "defPrincipais.h"
#include "NOKIA5110_fb.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

osThreadId Space_shipHandle;
osSemaphoreId Draw_semaphoreHandle;
/* USER CODE BEGIN PV */
uint32_t prop = 1, ADC_buffer[2], Valor_ADC[2];

osThreadId LCD_print_handle;
osThreadId Move_space_ship_handle;

struct pontos_t Space_ship_points, pt[4], Asteroid_points[4];
struct sig_pontos_t Space_ship_reference, pt_ref[3], Asteroid_reference[4];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_ADC1_Init(void);
void Space_ship_task(void const * argument);

/* USER CODE BEGIN PFP */
void LCD_print_task(void const * argument);
void Move_space_ship_task(void const * argument);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  unsigned int uSeed = 1;
  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  HAL_ADC_MspInit(&hadc1);
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */
  HAL_ADC_Start_DMA(&hadc1, ADC_buffer, 2);
  HAL_ADC_Start_IT(&hadc1);
  // LCD 5110 initialization
  inic_LCD();
  limpa_LCD();

  // Screen initialization
  goto_XY(0, 0);
  string_LCD("Start");
  imprime_LCD();

  while(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_15))
  {
    uSeed++;
  }

  vSrand(uSeed);

  limpa_LCD();
  imprime_LCD();

  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of Draw_semaphore */
  osSemaphoreDef(Draw_semaphore);
  Draw_semaphoreHandle = osSemaphoreCreate(osSemaphore(Draw_semaphore), 1);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of Space_ship */
  osThreadDef(Space_ship, Space_ship_task, osPriorityNormal, 0, 100);
  Space_shipHandle = osThreadCreate(osThread(Space_ship), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  osThreadDef(LCD_print, LCD_print_task, osPriorityNormal, 0, 100);
  LCD_print_handle = osThreadCreate(osThread(LCD_print), NULL);
  
  osThreadDef(Move_space_ship, Move_space_ship_task, osPriorityNormal, 0, 100);
  Move_space_ship_handle = osThreadCreate(osThread(Move_space_ship), NULL);

  /* USER CODE END RTOS_THREADS */

  /* Start scheduler */
  osKernelStart();
  
  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */
  /** Common config 
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 2;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel 
  */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel 
  */
  sConfig.Channel = ADC_CHANNEL_2;
  sConfig.Rank = ADC_REGULAR_RANK_2;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/** 
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void) 
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6 
                          |GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PC15 */
  GPIO_InitStruct.Pin = GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA3 PA4 PA5 PA6 
                           PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6 
                          |GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE BEGIN Header_LCD_print_task */
/**
  * @brief  Function implementing the LCD_print thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_LCD_print_task */
void LCD_print_task(void const * argument)
{
  /* Infinite loop */
  for(;;)
  {
    imprime_LCD();
    osDelay(17);
  } 
}

/* USER CODE BEGIN Header_Move_space_ship_task */
/**
  * @brief  Function implementing the Move_space_ship thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_Move_space_ship_task */
void Move_space_ship_task(void const * argument)
{
  uint32_t i = 0;
  int32_t angle = 0;

  pt[2].x1 = 50;
  pt[2].x2 = 50;
  pt[2].y1 = 28;
  pt[2].y2 = 4;
  pt[3].x1 = 50;
  pt[3].x2 = 50;
  pt[3].y1 = 28;
  pt[3].y2 = 4;
  pt_ref[2].x1 = 50; pt_ref[2].x2 = 50;
  pt_ref[2].y1 = 40; pt_ref[2].y2 = -8;
  auto_map_XY((struct pontos_t *) &pt[3], (struct sig_pontos_t *)&pt_ref[2]);

  Space_ship_points.x1 = 39;
  Space_ship_points.y1 = 21;
  Space_ship_points.x2 = 41;
  Space_ship_points.y2 = 25;
  Space_ship_points.x3 = 43;
  Space_ship_points.y3 = 21;
  Space_ship_reference.x1 = 41;
  Space_ship_reference.y1 = 22;
  Space_ship_reference.x2 = 41;
  Space_ship_reference.y2 = 22;
  Space_ship_reference.x3 = 41;
  Space_ship_reference.y3 = 22;

  Asteroid_points[0].x1 = 69;
  Asteroid_points[0].y1 = 13;
  Asteroid_points[0].x2 = 65;
  Asteroid_points[0].y2 = 7;
  Asteroid_points[0].x3 = 69;
  Asteroid_points[0].y3 = 1;
  Asteroid_points[1].x1 = 77;
  Asteroid_points[1].y1 = 1;
  Asteroid_points[1].x2 = 81;
  Asteroid_points[1].y2 = 7;
  Asteroid_points[1].x3 = 77;
  Asteroid_points[1].y3 = 13;

  Asteroid_reference[0].x1 = 73;
  Asteroid_reference[0].x2 = 73;
  Asteroid_reference[0].x3 = 73;
  Asteroid_reference[0].y1 = 7;
  Asteroid_reference[0].y2 = 7;
  Asteroid_reference[0].y3 = 7;
  Asteroid_reference[1].x1 = 73;
  Asteroid_reference[1].x2 = 73;
  Asteroid_reference[1].x3 = 73;
  Asteroid_reference[1].y1 = 7;
  Asteroid_reference[1].y2 = 7;
  Asteroid_reference[1].y3 = 7;

  Asteroid_points[2].x1 = 6;
  Asteroid_points[2].y1 = 46;
  Asteroid_points[2].x2 = 2;
  Asteroid_points[2].y2 = 40;
  Asteroid_points[2].x3 = 6;
  Asteroid_points[2].y3 = 34;
  Asteroid_points[3].x1 = 14;
  Asteroid_points[3].y1 = 34;
  Asteroid_points[3].x2 = 18;
  Asteroid_points[3].y2 = 40;
  Asteroid_points[3].x3 = 14;
  Asteroid_points[3].y3 = 46;

  Asteroid_reference[2].x1 = 10;
  Asteroid_reference[2].x2 = 10;
  Asteroid_reference[2].x3 = 10;
  Asteroid_reference[2].y1 = 40;
  Asteroid_reference[2].y2 = 40;
  Asteroid_reference[2].y3 = 40;
  Asteroid_reference[3].x1 = 10;
  Asteroid_reference[3].x2 = 10;
  Asteroid_reference[3].x3 = 10;
  Asteroid_reference[3].y1 = 40;
  Asteroid_reference[3].y2 = 40;
  Asteroid_reference[3].y3 = 40;
  /* Infinite loop */
  for(;;)
  {
    osSemaphoreWait(Draw_semaphoreHandle, osWaitForever);

    if(i < 360)
    {
      girar_hexagono_horario(Asteroid_points, Asteroid_reference);
      girar_hexagono_antihorario((struct pontos_t *) &Asteroid_points[2], (struct sig_pontos_t *) &Asteroid_reference[2]);
      i += 30;

      if(i == 180)
      {
        Asteroid_points[0].x3++;
        Asteroid_points[1].x1--;
      }else if(i == 360)
      {
        Asteroid_points[0].x1--;
        Asteroid_points[1].x3++;
        i = 0;
      }
    }

    osThreadYield();

    if(Valor_ADC[1] > 3000)
    {
      if(angle == 0)
        move_XY(0, 1, &Space_ship_points, &Space_ship_reference);
      else if(angle == 45 || angle == -315)
        move_XY(1, 1, &Space_ship_points, &Space_ship_reference);
      else if(angle == 90 || angle == -270)
        move_XY(1, 0, &Space_ship_points, &Space_ship_reference);
      else if(angle == 135 || angle == -225)
        move_XY(1, -1, &Space_ship_points, &Space_ship_reference);
      else if(angle == 180 || angle == -180)
        move_XY(0, -1, &Space_ship_points, &Space_ship_reference);
      else if(angle == 225 || angle == -135)
        move_XY(-1, -1, &Space_ship_points, &Space_ship_reference);
      else if(angle == 270 || angle == -90)
        move_XY(-1, 0, &Space_ship_points, &Space_ship_reference);
      else if(angle == 315 || angle == -45)
        move_XY(-1, 1, &Space_ship_points, &Space_ship_reference);
    

      pt[0].x1 = Space_ship_points.x1; pt[0].y1 = Space_ship_points.y1;
      pt[0].x2 = Space_ship_points.x2; pt[0].y2 = Space_ship_points.y2;
      pt_ref[0].x1 = Space_ship_reference.x1; pt_ref[0].y1 = Space_ship_reference.y1;
      pt_ref[0].x2 = Space_ship_reference.x2; pt_ref[0].y2 = Space_ship_reference.y2;
      pt[1].x1 = pt[2].x1; pt[1].y1 = pt[2].y1;
      pt[1].x2 = pt[2].x2; pt[1].y2 = pt[2].y2;
      pt_ref[1].x1 = pt_ref[2].x1; pt_ref[1].y1 = pt_ref[2].y1;
      pt_ref[1].x2 = pt_ref[2].x2; pt_ref[1].y2 = pt_ref[2].y2;
      prop = !colisao_linha((struct pontos_t *) &pt, (struct sig_pontos_t *) &pt_ref);
    }

    osThreadYield();

    if(Valor_ADC[0] < 1000)
    {
      girar_triangulo_antihorario(&Space_ship_points, &Space_ship_reference);
      angle += 45;
      if(angle == 360)
        angle = 0;
    }else if(Valor_ADC[0] > 3000)
    {
      girar_triangulo_horario(&Space_ship_points, &Space_ship_reference);
      angle -= 45;
      if(angle == -360)
        angle = 0;
    }

    osSemaphoreRelease(Draw_semaphoreHandle);
    osThreadYield();
  }
}

/* USER CODE END 4 */

/* USER CODE BEGIN Header_Space_ship_task */
/**
  * @brief  Function implementing the Space_ship thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_Space_ship_task */
void Space_ship_task(void const * argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
    osSemaphoreWait(Draw_semaphoreHandle, osWaitForever);

    escreve_Nr_Peq(10,29, Valor_ADC[0], 10);
		escreve_Nr_Peq(10,39, Valor_ADC[1], 10);
    desenha_triangulo(&Space_ship_points, &Space_ship_reference, (uint32_t) 1);
    desenha_hexagono(Asteroid_points, Asteroid_reference, 1);
    desenha_hexagono((struct pontos_t *) &Asteroid_points[2], (struct sig_pontos_t *) &Asteroid_reference[2], 1);
    desenha_linha(&pt[3], prop);
    osDelay(120);
    
    desenha_triangulo(&Space_ship_points, &Space_ship_reference, (uint32_t) 0);
    desenha_hexagono(Asteroid_points, Asteroid_reference, 0);
    desenha_hexagono((struct pontos_t *) &Asteroid_points[2], (struct sig_pontos_t *) &Asteroid_reference[2], 0);

    osSemaphoreRelease(Draw_semaphoreHandle);
  
    osThreadYield();
  }
  /* USER CODE END 5 */ 
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM4 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM4) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
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
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
