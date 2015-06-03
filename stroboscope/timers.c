/*
  The SAM3X8E CPU has 3 Timer Counters (TC) they are called TC0, TC1, TC2.
  Every Timer Counter contains 3 Channels numbered 0, 1 and 2.
  Every Channel has its own counter and interrupt handler that are
    independent from other Channels.

  See chapter 37 of datasheet, page 869.

  TC  Chan  NVIC "irq"  IRQ handler function   PMC id    Due pins
  ---------------------------------------------------------------
  TC0   0    TC0_IRQn     TC0_Handler          ID_TC0     2, 13
  TC0   1    TC1_IRQn     TC1_Handler          ID_TC1     60, 61
  TC0   2    TC2_IRQn     TC2_Handler          ID_TC2     58
  TC1   0    TC3_IRQn     TC3_Handler          ID_TC3     none
  TC1   1    TC4_IRQn     TC4_Handler          ID_TC4     none
  TC1   2    TC5_IRQn     TC5_Handler          ID_TC5     none
  TC2   0    TC6_IRQn     TC6_Handler          ID_TC6     4, 5
  TC2   1    TC7_IRQn     TC7_Handler          ID_TC7     3, 10
  TC2   2    TC8_IRQn     TC8_Handler          ID_TC8     11, 12

  Really useful forum discussion about this at:
    http://forum.arduino.cc/index.php?topic=130423.0
*/

#include <Arduino.h>



/** Descr: Initialize and start the timer TC1 on a given channel.
    Params:
     - count: init count value before firing.
     - channel: channel of the timer TC1 to be used.
    Ret: none.
*/
void start_timer_TC1 (uint32_t count, uint32_t channel)
{
  /* Turn on the timer clock in the power management controller which are
     off by default for power saving:
     1) Disable write protection for pmc registers.
     2) Enable the specified peripheral clock. */
  pmc_set_writeprotect (false) ;

  /* Enable peripheral clock (PMC id column in the table above). Depending
     on the channel used, we enable the corresponding clock. */
  switch (channel) {
  case 0: pmc_enable_periph_clk (ID_TC3) ; break ;
  case 1: pmc_enable_periph_clk (ID_TC4) ; break ;
  case 2: pmc_enable_periph_clk (ID_TC5) ; break ;
  }

  /* Configuration of the timer itself. */
  TC_Configure
    (TC1,                    /* Clock to use. */
     channel,                /* Channel of the clock to use. */
     TC_CMR_WAVE             /* Waveform mode. */
     | TC_CMR_WAVSEL_UP_RC   /* The counter runs up, and resets when it equals
                                RC. */
     | TC_CMR_TCCLKS_TIMER_CLOCK4) ;  /* Run the clock at MCU / 128. */

  TC_SetRC (TC1, channel, count) ;   /* Initialise count value. */
  TC_Start (TC1, channel) ;          /* Really start the timer. */

  /* Enable timer interrupts:
     1) IER = interrupt enable register.
     2) IDR = interrupt disable register. */
  TC1->TC_CHANNEL[channel].TC_IER = TC_IER_CPCS ;
  TC1->TC_CHANNEL[channel].TC_IDR = ~TC_IER_CPCS ;

  /* Enable the interrupt in the nested vector interrupt controller
     (NVIC "irq" column in the table above). Depending on the channel used, we
     enable the corresponding interrupt. */
  switch (channel) {
  case 0: NVIC_EnableIRQ (TC3_IRQn) ; break ;
  case 1: NVIC_EnableIRQ (TC4_IRQn) ; break ;
  case 2: NVIC_EnableIRQ (TC5_IRQn) ; break ;
  }
}



/** Descr: Stop the timer TC1 on a given channel.
    Params:
     - channel: channel of the timer TC1 used.
    Ret: none.
*/
void stop_timer_TC1 (uint32_t channel)
{
  /* Disable the interrupt in the nested vector interrupt controller
     (NVIC "irq" column in the table above). Depending on the channel used, we
     enable the corresponding interrupt. */
  switch (channel) {
  case 0: NVIC_DisableIRQ (TC3_IRQn) ; break ;
  case 1: NVIC_DisableIRQ (TC4_IRQn) ; break ;
  case 2: NVIC_DisableIRQ (TC5_IRQn) ; break ;
  }
  TC_Stop (TC1, channel) ;
}
