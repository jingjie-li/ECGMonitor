//******************************************************************************
//   MSP-FET430P140 Demo - USART0, SPI 3-Wire Master
//
//   Description: SPI master talks to SPI slave using 3-wire mode. Incrementing
//   data is sent by the master starting at 0x00. Received data is expected to
//   decrement starting at 0xFF. USART0 RX ISR is used to handle communication
//   with the CPU normally in LPM0. The slave is initialized by the master
//   followed by a slave setup delay time in order to assure proper SPI
//   synchronization. P1.0 indicates proper data reception.
//   ACLK = n/a, MCLK = SMCLK = DCO ~ 800kHz
//
//                MSP430F149
//              -----------------
//          /|\|              XIN|-
//           | |                 |
//           --|RST          XOUT|-
//             |                 |
//       LED <-|P1.0         P3.1|-> Data Out (SIMO0)
//             |                 |
//     Scope <-|P3.4         P3.2|<- Data In (SOMI0)
//             |                 |
// Slave RST <-|P3.5         P3.3|-> Serial Clock Out (UCLK)
//
//  Z. Albus
//  Texas Instruments Inc.
//  Feb 2005
//  Built with IAR Embedded Workbench Version: 3.21A
//******************************************************************************

#include  <msp430x14x.h>

char MST_Data = 0x00, SLV_Data = 0xFF;

void main(void)
{
  unsigned int i;

  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1OUT = 0x000;                            // Setup P1.0 for LED output
  P1DIR |= 0x001;
  P3SEL = 0x00E;                            // Setup P3 for SPI mode
  P3OUT = 0x020;                            // Setup P3.4 for Scope trigger and
  P3DIR |= 0x030;                           // P3.5 for slave initialization
  
  U0CTL = CHAR + SYNC + MM + SWRST;         // 8-bit, SPI, Master
  U0TCTL = CKPL + SSEL1 + STC;              // Polarity, SMCLK, 3-wire
  U0BR0 = 0x002;                            // SPICLK = SMCLK/2
  U0BR1 = 0x000;
  U0MCTL = 0x000;
  
  ME1 = USPIE0;                             // Module enable
  U0CTL &= ~SWRST;                          // SPI enable
  IE1 |= URXIE0;                            // Recieve interrupt enable
  _EINT();                                  // Enable interrupts

  P3OUT &= ~0x020;                          // Toggle P3.5: slave reset
  P3OUT |= 0x020;
  i = 50000;                                // Delay
  do (i--);
  while (i != 0);

  while (1)
  {
    TXBUF0 = MST_Data;                      // Transmit first character
    LPM0;                                   // CPU off
  }
} // End Main

#pragma vector=USART0RX_VECTOR
__interrupt void SPI0_rx (void)
{
  P3OUT ^= 0x010;                           // XOR P3.4 for scope trigger
  while ((IFG1 & UTXIFG0) == 0);            // USART0 TX buffer ready?
  if (U0RXBUF == SLV_Data)                  // Test for correct character RX'd
  {
    SLV_Data = SLV_Data -1;                 // Decrement incoming data mask
    MST_Data = MST_Data +1;                 // Increment out-going data
    TXBUF0 = MST_Data;
    P1OUT |= 0x001;                         // Pulse P1.0 indicating valid data
    P1OUT &= ~0x001;
  }
  else
  {
    TXBUF0 = MST_Data;
    P1OUT |= 0x001;                         // Set P1.0 indicating data error
  }
}
