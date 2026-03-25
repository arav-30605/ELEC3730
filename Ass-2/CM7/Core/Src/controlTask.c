// Code written by: Aravind Gowrinathan
#include "myMain.h"

static DMA2D_HandleTypeDef hdma2d;


static uint32_t LCD_X_Size = 0;
uint32_t change =0;
uint32_t GrindTimeLeft;

volatile SystemState_t current_state;

// DAC setup
int data[100];
#define SAMPLES 100

void StartControlTask(void *argument)
{
// Queue Setup
// All queues are first defined in the ioc file
// Queues and tasks are under Middlewares and sotware packs
// Set the queues and tasks under the freertos mode
	// Receive ButtonPress Queue
	uint16_t StateChangeReceivedValue;
	osStatus_t Statestatus;

	// Send Timer Queue
	uint16_t StartTimerFlag= 0;

	// Send Display Queue
	uint16_t dispvalue= 0;
	osStatus_t Displaystatus;

	// DAC array
	for (uint16_t i=0; i< SAMPLES; i++){
		data[i] = (uint32_t) 50.0 * (sin(2*3.14159*i/SAMPLES)+1);
	}
	// Start Timer
	HAL_TIM_Base_Start(&htim2);

	for(;;)
	{
		// Receive Message from Queue
		Statestatus = osMessageQueueGet(ButtonQueueHandle, &StateChangeReceivedValue, NULL, osWaitForever);

		if (Statestatus == osOK) {
			switch (StateChangeReceivedValue) {
				case 1:
					// Update State
					current_state = STATE_ON;

					// Update display
					dispvalue = 1;
			    	Displaystatus = osMessageQueuePut(ScreenQueueHandle, &dispvalue, 0, osWaitForever);

			    	// Start DAC and DMA
					// Clear D:cache before DMA
			    	// Watch the lectures
					SCB_CleanDCache_by_Addr((uint32_t*)data, sizeof(data));
					// Start sound using DAC + DMA
					// From Assignment 1B code
					HAL_DAC_Start_DMA(&hdac1, DAC_CHANNEL_1, data, SAMPLES, DAC_ALIGN_12B_R);

					// Send Queue to start grindTimer
					StartTimerFlag = 1;
					osMessageQueuePut(GrindQueueHandle, &StartTimerFlag, 0, osWaitForever);
					break;

				case 2:
					// Update State
					current_state = STATE_PAUSED;

					//Stop DAC DMA
					HAL_DAC_Stop_DMA(&hdac1, DAC_CHANNEL_1);

					// Reset the pause-time elapsed counter
					PauseTimeCount = 0;

					// Update display
					dispvalue = 4;
			    	Displaystatus = osMessageQueuePut(ScreenQueueHandle, &dispvalue, 0, osWaitForever);
					break;

				case 3:
					// Update State
					current_state = STATE_OFF;

					//Stop DAC DMA
					HAL_DAC_Stop_DMA(&hdac1, DAC_CHANNEL_1);

					// Update display
					dispvalue = 3;
			    	Displaystatus = osMessageQueuePut(ScreenQueueHandle, &dispvalue, 0, osWaitForever);
					break;
			}
		}
		osDelay(1);
	}
}







static void CopyBuffer(uint32_t *pSrc, uint32_t *pDst, uint16_t x, uint16_t y, uint16_t xsize, uint16_t ysize)
{

  uint32_t destination = (uint32_t)pDst + (y * LCD_X_Size + x) * 4;
  uint32_t source      = (uint32_t)pSrc;

  /*##-1- Configure the DMA2D Mode, Color Mode and output offset #############*/
  hdma2d.Init.Mode         = DMA2D_M2M;
  hdma2d.Init.ColorMode    = DMA2D_OUTPUT_ARGB8888;
  hdma2d.Init.OutputOffset = LCD_X_Size - xsize;
  hdma2d.Init.AlphaInverted = DMA2D_REGULAR_ALPHA;  /* No Output Alpha Inversion*/
  hdma2d.Init.RedBlueSwap   = DMA2D_RB_REGULAR;     /* No Output Red & Blue swap */

  /*##-2- DMA2D Callbacks Configuration ######################################*/
  hdma2d.XferCpltCallback  = NULL;

  /*##-3- Foreground Configuration ###########################################*/
  hdma2d.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
  hdma2d.LayerCfg[1].InputAlpha = 0xFF;
  hdma2d.LayerCfg[1].InputColorMode = DMA2D_INPUT_ARGB8888;
  hdma2d.LayerCfg[1].InputOffset = 0;
  hdma2d.LayerCfg[1].RedBlueSwap = DMA2D_RB_REGULAR; /* No ForeGround Red/Blue swap */
  hdma2d.LayerCfg[1].AlphaInverted = DMA2D_REGULAR_ALPHA; /* No ForeGround Alpha inversion */

  hdma2d.Instance          = DMA2D;

  /* DMA2D Initialization */
  if(HAL_DMA2D_Init(&hdma2d) == HAL_OK)
  {
    if(HAL_DMA2D_ConfigLayer(&hdma2d, 1) == HAL_OK)
    {
      if (HAL_DMA2D_Start(&hdma2d, source, destination, xsize, ysize) == HAL_OK)
      {
        /* Polling For DMA transfer */
        HAL_DMA2D_PollForTransfer(&hdma2d, 100);
      }
    }
  }
}

static void CPU_CACHE_Enable(void)
{
  /* Enable I-Cache */
  SCB_EnableICache();

  /* Enable D-Cache */
  SCB_EnableDCache();
}

/**
  * @brief  Configure the MPU attributes as Write Through for External SDRAM.
  * @note   The Base Address is 0xD0000000 .
  *         The Configured Region Size is 32MB because same as SDRAM size.
  * @param  None
  * @retval None
  */
static void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct;

  /* Disable the MPU */
  HAL_MPU_Disable();

  /* Configure the MPU as Strongly ordered for not defined regions */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.BaseAddress = 0x00;
  MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
  MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.SubRegionDisable = 0x87;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /* Configure the MPU attributes as WT for SDRAM */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.BaseAddress = SDRAM_DEVICE_ADDR;
  MPU_InitStruct.Size = MPU_REGION_SIZE_32MB;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER1;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.SubRegionDisable = 0x00;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /* Enable the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}
