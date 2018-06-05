/**************************************************************************/
/*!
    @file     board_pca10056.c
    @author   hathach

    @section LICENSE

    Software License Agreement (BSD License)

    Copyright (c) 2018, hathach (tinyusb.org)
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
    3. Neither the name of the copyright holders nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/**************************************************************************/

#include "bsp/board.h"
#include "board_pca10056.h"
#include "nrf_gpio.h"

#include "nrf_drv_power.h"

/*------------------------------------------------------------------*/
/* MACRO TYPEDEF CONSTANT ENUM
 *------------------------------------------------------------------*/
#define LED_1           13
#define LED_STATE_ON    0
#define LED_STATE_OFF   (1-LED_STATE_ON)


/*------------------------------------------------------------------*/
/* TUSB HAL MILLISECOND
 *------------------------------------------------------------------*/
volatile uint32_t system_ticks = 0;

void SysTick_Handler (void)
{
  system_ticks++;
}

uint32_t tusb_hal_millis(void)
{
  //#define tick2ms(tck)         ( ( ((uint64_t)(tck)) * 1000) / configTICK_RATE_HZ )
  //return tick2ms( app_timer_cnt_get() );

  return board_tick2ms(system_ticks);
}

/*------------------------------------------------------------------*/
/* BOARD API
 *------------------------------------------------------------------*/
void board_init(void)
{
  // Config clock source: XTAL or RC in sdk_config.h
  NRF_CLOCK->LFCLKSRC = (uint32_t)((CLOCK_CONFIG_LF_SRC << CLOCK_LFCLKSRC_SRC_Pos) & CLOCK_LFCLKSRC_SRC_Msk);
  NRF_CLOCK->TASKS_LFCLKSTART = 1UL;

  nrf_gpio_cfg_output(LED_1);

#ifdef SOFTDEVICE_PRESENT
  // TODO support Softdevice config
#else
  // Softdevice is not present, init power module and register tusb power event function
  // for vusb detect, ready, removed
  extern void tusb_hal_nrf_power_event(uint32_t event);

  nrf_drv_power_init(NULL);

  // USB Power detection
  const nrf_drv_power_usbevt_config_t config =
  {
      .handler = (nrf_drv_power_usb_event_handler_t) tusb_hal_nrf_power_event
  };
  TU_ASSERT( NRF_SUCCESS == nrf_drv_power_usbevt_init(&config) );
#endif

  // Tick init
  SysTick_Config(SystemCoreClock/1000);
  NVIC_EnableIRQ(SysTick_IRQn);
}

void board_led_control(uint32_t led_id, bool state)
{
  (void) led_id;
  nrf_gpio_pin_write(LED_1, state ? LED_STATE_ON : LED_STATE_OFF);
}

uint32_t board_buttons(void)
{
  return 0;
}

uint8_t  board_uart_getchar(void)
{
  return 0;
}

void board_uart_putchar(uint8_t c)
{

}
