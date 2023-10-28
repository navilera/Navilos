#include "stdbool.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"

#include "stm32f1xx_hal.h"

#include "HalGpio.h"
#include "HalUart.h"

#include "Kernel.h"
#include "MemoryMap.h"

#define SYSTEM_US_TICKS (SystemCoreClock / 1000000) // cycles per microsecond

/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);

#ifdef LOADER
static bool CheckBootMode(void)
{
    // get HW (0,0) key pressed during keyboard power-up time.
    // while user presses HW (0,0) key, FW enters a keymap download mode or FW update mode.
	// no matter what key code mapped into the (0,0). It just check matrix (0,0).
    return KeyHw_IsPressed(0, 0);
}

static void Jump(uint32_t address)
{
    typedef void (*pFunction)(void);

    pFunction Jump_To_Application;

    // variable that will be loaded with the start address of the application
    uint32_t* JumpAddress;
    const uint32_t* ApplicationAddress = (uint32_t *)address;

    // get jump address from application vector table
    JumpAddress = (uint32_t *)ApplicationAddress[1];

    // load this address into function pointer
    Jump_To_Application = (pFunction)JumpAddress;

    // Disable all interrupts
    for (int i = 0; i < 8; i++) {
        NVIC->ICER[i] = NVIC->IABR[i];
    }

    // Set interrupt vector table
    SCB->VTOR = address; /* Vector Table Relocation in Internal FLASH. */

    // Set stack pointer as in application's vector table
    __set_MSP((uint32_t)(ApplicationAddress[0]));

    // Go
    Jump_To_Application();
}

#else

static void Kernel_Init(void)
{
/*
	extern void Polling_task();
	extern void Host_comm_task();
	extern void Debug_cli_task();
	extern void Keymap_dnldr_task();

    uint32_t taskId;

    Kernel_task_init();

    taskId = Kernel_task_create(Polling_task);
    if (NOT_ENOUGH_TASK_NUM == taskId)
    {
        debug_printf("Polling_task creation fail\n");
    }

    taskId = Kernel_task_create(Host_comm_task);
    if (NOT_ENOUGH_TASK_NUM == taskId)
    {
        debug_printf("Host_comm_task creation fail\n");
    }

    taskId = Kernel_task_create(Debug_cli_task);
    if (NOT_ENOUGH_TASK_NUM == taskId)
    {
        debug_printf("Debug_cli_task creation fail\n");
    }

    Kernel_start();
*/
}
#endif

int main(void)
{
    HAL_Init();
    SystemClock_Config();

    Hal_gpio_init();
    Hal_uart_init();

#ifdef LOADER
    if (CheckBootMode())
    {
    	debug_printf("BootLoader..\n");
    	//App_msc_Init();
    }
    else
    {
    	debug_printf("Jump to the MainFW..\n");
    	Jump(MAIN_FW_BADDR);
    }
#else
    	//App_hid_Init();

		while (USBD_HID_Is_Configured() != true)
		{
			debug_printf("Waiting for USBHID configuration\n");
			//USBD_Delay(1000);
		}

        debug_printf("Navilos Start..\n");
	    Kernel_Init();
#endif

    while (1) { }
}

/** System Clock Configuration
*/
static void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct;
    RCC_ClkInitTypeDef RCC_ClkInitStruct;
    RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Initializes the CPU, AHB and APB busses clocks 
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
      {
        halt(__FILE__, __LINE__);
      }

    /**Initializes the CPU, AHB and APB busses clocks 
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
      |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
      {
        halt(__FILE__, __LINE__);
      }

    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
    PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
      {
        halt(__FILE__, __LINE__);
      }

    /**Configure the Systick interrupt time 
     */
    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
     */
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

    /* SysTick_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

