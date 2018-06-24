/*
 * AFE44x0.c
 *
 * Provides AFE44x0 API
 *
 * Copyright (C) 2016 Texas Instruments Incorporated - http://www.ti.com/ 
 * ALL RIGHTS RESERVED  
 *
*/

#include "AFE4400.h"
#include <msp430x14x.h>

/**************************************************************************************************************************************************
*	        Prototypes									                                                  										  *
**************************************************************************************************************************************************/

/**************************************************************************************************************************************************
*	        Global Variables										                                  											  *
**************************************************************************************************************************************************/
#define DELAY_COUNT 2

unsigned long AFE44xx_Current_Register_Settings[36] = {
  CONTROL0_VAL,           //Reg0:CONTROL0: CONTROL REGISTER 0
  LED2STC_VAL,            //Reg1:REDSTARTCOUNT: SAMPLE RED START COUNT
  LED2ENDC_VAL,           //Reg2:REDENDCOUNT: SAMPLE RED END COUNT
  LED2LEDSTC_VAL,         //Reg3:REDLEDSTARTCOUNT: RED LED START COUNT
  LED2LEDENDC_VAL,        //Reg4:REDLEDENDCOUNT: RED LED END COUNT
  ALED2STC_VAL,           //Reg5:AMBREDSTARTCOUNT: SAMPLE AMBIENT RED START COUNT
  ALED2ENDC_VAL,          //Reg6:AMBREDENDCOUNT: SAMPLE AMBIENT RED END COUNT
  LED1STC_VAL,            //Reg7:IRSTARTCOUNT: SAMPLE IR START COUNT
  LED1ENDC_VAL,           //Reg8:IRENDCOUNT: SAMPLE IR END COUNT
  LED1LEDSTC_VAL,         //Reg9:IRLEDSTARTCOUNT: IR LED START COUNT
  LED1LEDENDC_VAL,        //Reg10:IRLEDENDCOUNT: IR LED END COUNT
  ALED1STC_VAL,           //Reg11:AMBIRSTARTCOUNT: SAMPLE AMBIENT IR START COUNT
  ALED1ENDC_VAL,          //Reg12:AMBIRENDCOUNT: SAMPLE AMBIENT IR END COUNT
  LED2CONVST_VAL,         //Reg13:REDCONVSTART: REDCONVST
  LED2CONVEND_VAL,        //Reg14:REDCONVEND: RED CONVERT END COUNT
  ALED2CONVST_VAL,        //Reg15:AMBREDCONVSTART: RED AMBIENT CONVERT START COUNT
  ALED2CONVEND_VAL,       //Reg16:AMBREDCONVEND: RED AMBIENT CONVERT END COUNT
  LED1CONVST_VAL,         //Reg17:IRCONVSTART: IR CONVERT START COUNT
  LED1CONVEND_VAL,        //Reg18:IRCONVEND: IR CONVERT END COUNT
  ALED1CONVST_VAL,        //Reg19:AMBIRCONVSTART: IR AMBIENT CONVERT START COUNT
  ALED1CONVEND_VAL,       //Reg20:AMBIRCONVEND: IR AMBIENT CONVERT END COUNT
  ADCRSTSTCT0_VAL,        //Reg21:ADCRESETSTCOUNT0: ADC RESET 0 START COUNT
  ADCRSTENDCT0_VAL,       //Reg22:ADCRESETENDCOUNT0: ADC RESET 0 END COUNT
  ADCRSTSTCT1_VAL,        //Reg23:ADCRESETSTCOUNT1: ADC RESET 1 START COUNT
  ADCRSTENDCT1_VAL,       //Reg24:ADCRESETENDCOUNT1: ADC RESET 1 END COUNT
  ADCRSTSTCT2_VAL,        //Reg25:ADCRESETENDCOUNT2: ADC RESET 2 START COUNT
  ADCRSTENDCT2_VAL,       //Reg26:ADCRESETENDCOUNT2: ADC RESET 2 END COUNT
  ADCRSTSTCT3_VAL,        //Reg27:ADCRESETENDCOUNT3: ADC RESET 3 START COUNT
  ADCRSTENDCT3_VAL,       //Reg28:ADCRESETENDCOUNT3: ADC RESET 3 END COUNT
  PRP,                    //Reg29:PRPCOUNT: PULSE REPETITION PERIOD COUNT
  CONTROL1_VAL,           //Reg30:CONTROL1: CONTROL REGISTER 1 //timer enabled, averages=3, RED and IR LED pulse ON PD_ALM AND LED_ALM pins
  0x00000,                //Reg31:?: ??          
  (ENSEPGAIN + STAGE2EN_LED1 + STG2GAIN_LED1_0DB + CF_LED1_5P + RF_LED1_1M),                      //Reg32:TIAGAIN: TRANS IMPEDANCE AMPLIFIER GAIN SETTING REGISTER
  (AMBDAC_0uA + FLTRCNRSEL_500HZ + STAGE2EN_LED2 + STG2GAIN_LED2_0DB + CF_LED2_5P + RF_LED2_1M),  //Reg33:TIA_AMB_GAIN: TRANS IMPEDANCE AAMPLIFIER AND AMBIENT CANELLATION STAGE GAIN
  (LEDCNTRL_VAL),                                                                                 //Reg34:LEDCNTRL: LED CONTROL REGISTER
  (TX_REF_1 + RST_CLK_ON_PD_ALM_PIN_DISABLE + ADC_BYP_DISABLE + TXBRGMOD_H_BRIDGE + DIGOUT_TRISTATE_DISABLE + XTAL_ENABLE + EN_FAST_DIAG + PDN_TX_OFF + PDN_RX_OFF + PDN_AFE_OFF)                 //Reg35:CONTROL2: CONTROL REGISTER 2 //bit 9
};

/***********************************************************************************************************
*	        Variables for the SPI Interaction                                                          	   *
***********************************************************************************************************/


/**********************************************************************************************************
*	External Variables																			          *
**********************************************************************************************************/

/**********************************************************************************************************
* Init_AFE44xx_DRDY_Interrupt												                                          *
**********************************************************************************************************/
void Init_AFE44xx_DRDY_Interrupt (void)
{
  P2DIR &= ~AFE_ADC_DRDY;
  P2REN |= AFE_ADC_DRDY;                              // Enable P2.3 internal resistance
  P2OUT |= AFE_ADC_DRDY;                            	// Set P2.3 as pull-Up resistance
  P2IES |= AFE_ADC_DRDY;                              // P2.3 Hi/Lo edge
  P2IFG &= ~AFE_ADC_DRDY;                           	// P2.3 IFG cleared
  P2IE &= ~AFE_ADC_DRDY;                             	// P2.3 interrupt disabled
}

/**********************************************************************************************************
* Enable_AFE44xx_DRDY_Interrupt												                                          *
**********************************************************************************************************/
void Enable_AFE44xx_DRDY_Interrupt (void)
{
  P2IFG &= ~AFE_ADC_DRDY;                           	// P2.3 IFG cleared
  P2IE |= AFE_ADC_DRDY;                             	// P2.3 interrupt enabled
}

/**********************************************************************************************************
* Disable_AFE44xx_DRDY_Interrupt												                                          *
**********************************************************************************************************/
void Disable_AFE44xx_DRDY_Interrupt (void)
{
  P2IFG &= ~AFE_ADC_DRDY;                           	// P2.3 IFG cleared
  P2IE &= ~AFE_ADC_DRDY;                             	// P2.3 interrupt disabled
}

/**********************************************************************************************************
* Set_GPIO														                                          *
**********************************************************************************************************/
void Set_GPIO(void)
{
  //port set..
  //Port 1.1 - AFE_RESETZ, P1.2 - AFE_PDNZ, P2.3 - ADC_RDY, P2.4- PD_ALM, P2.5 - LED_ALM,
  //P5.7 - DIAG_END
  
  P1SEL |= BIT0;
  P1DIR |= BIT0;
  P1OUT |= BIT0;
  
  P1DIR |= (AFE_RESETZ + AFE_PDNZ);
  P1OUT |= (AFE_RESETZ + AFE_PDNZ);
  P2DIR &= ~(AFE_ADC_DRDY + AFE_PD_ALM + AFE_LED_ALM);
  P5DIR &= ~AFE_DIAG_END;
  
  P2SEL = 0x00;
  P2DIR &= BIT0;
  P2OUT |= (BIT1 + BIT2 + BIT7);
  P2DIR |= (BIT1 | BIT2 | BIT7);
}

/**********************************************************************************************************
* Set_UCB1_SPI													                                          *
**********************************************************************************************************/
void Set_UCB1_SPI(void)
{ 
  P4SEL |= BIT1+BIT2+BIT3;  			// Set SPI peripheral bits
  P4DIR |= BIT0+BIT1+BIT3;			// STE, SCLK, and DOUT as output
  P4DIR &= ~BIT2;                         	// Din as input
  P4OUT |=BIT0;				// Set STE high
  UCB1CTL1 |= UCSWRST;               		// Enable SW reset
  UCB1CTL0 |= UCMSB+UCCKPH+UCMST+UCSYNC;	// [b0]   1 -  Synchronous mode
  // [b2-1] 00-  3-pin SPI
  // [b3]   1 -  Master mode
  // [b4]   0 - 8-bit data
  // [b5]   1 - MSB first
  // [b6]   0 - Clock polarity high.
  // [b7]   1 - Clock phase - Data is captured on the first UCLK edge and changed on the following edge.
  
  UCB1CTL1 |= UCSSEL_2;               	// SMCLK
  UCB1BR0 = 0x01;                             // 16 MHz
  UCB1BR1 = 0;                                //
  UCB1CTL1 &= ~UCSWRST;              		// Clear SW reset, resume operation
  UCB1IE =0x0;
  
  //P4OUT &= ~BIT0;				// Set STE low
}

/**********************************************************************************************************
* Init_AFE44xx_Resource						                                          *
**********************************************************************************************************/

void Init_AFE44xx_Resource(void)
{
  Set_GPIO();										// Initializes AFE44xx's input control lines
  Set_UCB1_SPI();									// Initialize SPI regs.    
}

/**********************************************************************************************************
*	        AFE44xx default Initialization          				                  					  *
**********************************************************************************************************/

void AFE44xx_Default_Reg_Init(void)
{
  Disable_AFE44x0_SPI_Read();
  
  AFE44x0_Reg_Write((unsigned char)PRPCOUNT, (unsigned long)PRP);
  AFE44x0_Reg_Write((unsigned char)LED2STC, (unsigned long)LED2STC_VAL);
  AFE44x0_Reg_Write((unsigned char)LED2ENDC, (unsigned long)LED2ENDC_VAL);
  AFE44x0_Reg_Write((unsigned char)LED2LEDSTC, (unsigned long)LED2LEDSTC_VAL);
  AFE44x0_Reg_Write((unsigned char)LED2LEDENDC, (unsigned long)LED2LEDENDC_VAL);
  AFE44x0_Reg_Write((unsigned char)ALED2STC, (unsigned long)ALED2STC_VAL);
  AFE44x0_Reg_Write((unsigned char)ALED2ENDC, (unsigned long)ALED2ENDC_VAL);
  AFE44x0_Reg_Write((unsigned char)LED1STC, (unsigned long)LED1STC_VAL);
  AFE44x0_Reg_Write((unsigned char)LED1ENDC, (unsigned long)LED1ENDC_VAL);
  AFE44x0_Reg_Write((unsigned char)LED1LEDSTC, (unsigned long)LED1LEDSTC_VAL);
  AFE44x0_Reg_Write((unsigned char)LED1LEDENDC, (unsigned long)LED1LEDENDC_VAL);
  AFE44x0_Reg_Write((unsigned char)ALED1STC, (unsigned long)ALED1STC_VAL);
  AFE44x0_Reg_Write((unsigned char)ALED1ENDC, (unsigned long)ALED1ENDC_VAL);
  AFE44x0_Reg_Write((unsigned char)LED2CONVST, (unsigned long)LED2CONVST_VAL);
  AFE44x0_Reg_Write((unsigned char)LED2CONVEND, (unsigned long)LED2CONVEND_VAL);
  AFE44x0_Reg_Write((unsigned char)ALED2CONVST, (unsigned long)ALED2CONVST_VAL);
  AFE44x0_Reg_Write((unsigned char)ALED2CONVEND, (unsigned long)ALED2CONVEND_VAL);
  AFE44x0_Reg_Write((unsigned char)LED1CONVST, (unsigned long)LED1CONVST_VAL);
  AFE44x0_Reg_Write((unsigned char)LED1CONVEND, (unsigned long)LED1CONVEND_VAL);
  AFE44x0_Reg_Write((unsigned char)ALED1CONVST, (unsigned long)ALED1CONVST_VAL);
  AFE44x0_Reg_Write((unsigned char)ALED1CONVEND, (unsigned long)ALED1CONVEND_VAL);
  AFE44x0_Reg_Write((unsigned char)ADCRSTSTCT0, (unsigned long)ADCRSTSTCT0_VAL);
  AFE44x0_Reg_Write((unsigned char)ADCRSTENDCT0, (unsigned long)ADCRSTENDCT0_VAL);
  AFE44x0_Reg_Write((unsigned char)ADCRSTSTCT1, (unsigned long)ADCRSTSTCT1_VAL);
  AFE44x0_Reg_Write((unsigned char)ADCRSTENDCT1, (unsigned long)ADCRSTENDCT1_VAL);
  AFE44x0_Reg_Write((unsigned char)ADCRSTSTCT2, (unsigned long)ADCRSTSTCT2_VAL);
  AFE44x0_Reg_Write((unsigned char)ADCRSTENDCT2, (unsigned long)ADCRSTENDCT2_VAL);
  AFE44x0_Reg_Write((unsigned char)ADCRSTSTCT3, (unsigned long)ADCRSTSTCT3_VAL);
  AFE44x0_Reg_Write((unsigned char)ADCRSTENDCT3, (unsigned long)ADCRSTENDCT3_VAL);
  
  AFE44x0_Reg_Write((unsigned char)CONTROL0, AFE44xx_Current_Register_Settings[0]);            //0x00
  AFE44x0_Reg_Write((unsigned char)CONTROL2, AFE44xx_Current_Register_Settings[35]);           //0x23
  AFE44x0_Reg_Write((unsigned char)TIAGAIN, AFE44xx_Current_Register_Settings[32]);            //0x20
  AFE44x0_Reg_Write((unsigned char)TIA_AMB_GAIN, AFE44xx_Current_Register_Settings[33]);       //0x21
  AFE44x0_Reg_Write((unsigned char)LEDCNTRL, AFE44xx_Current_Register_Settings[34]);           //0x22
  AFE44x0_Reg_Write((unsigned char)CONTROL1, AFE44xx_Current_Register_Settings[30]);           //0x1E
  
  Enable_AFE44x0_SPI_Read();
}

/**********************************************************************************************************
*	        AFE44xx_Read_All_Regs          				                  					  *
**********************************************************************************************************/

void AFE44xx_Read_All_Regs(unsigned long AFE44xxeg_buf[])
{
  unsigned char Regs_i;
  for ( Regs_i = 0; Regs_i < 50; Regs_i++)
  {
    AFE44xxeg_buf[Regs_i] = AFE44xx_Reg_Read(Regs_i);
  }
}
/*********************************************************************************************************/
/**********************************************************************************************************
*	        AFE44xx_PowerOn_Init          				                  					  			  *
***********************************************************************************************************/
void AFE44xx_PowerOn_Init(void)
{
  volatile unsigned short Init_i, j;
  Init_AFE44xx_Resource();
  for (j = 0; j < DELAY_COUNT; j++)
  {
    for ( Init_i =0; Init_i < 20000; Init_i++);
    for ( Init_i =0; Init_i < 20000; Init_i++);
    for ( Init_i =0; Init_i < 20000; Init_i++);
  }
  Init_AFE44xx_DRDY_Interrupt();
  AFE44xx_Default_Reg_Init();
}

/**********************************************************************************************************
*	        AFE44x0_Reg_Write           					  			  *
***********************************************************************************************************/
void AFE44x0_Reg_Write (unsigned char reg_address, unsigned long data)
{
  unsigned char dummy_rx;
  
  P4OUT&= ~0x01;   //  SEN LOW FOR TRANSMISSION.
  // Loop unrolling for machine cycle optimization
  UCB1TXBUF = reg_address;                    // Send the first byte to the TX Buffer: Address of register
  while ( (UCB1STAT & UCBUSY) );		// USCI_B1 TX buffer ready?
  dummy_rx = UCB1RXBUF;			// Dummy Read Rx buf
  UCB1TXBUF = (unsigned char)(data >>16);     // Send the second byte to the TX Buffer: Data[23:16]
  while ( (UCB1STAT & UCBUSY) );		// USCI_B1 TX buffer ready?
  dummy_rx = UCB1RXBUF;			// Dummy Read Rx buf
  UCB1TXBUF = (unsigned char)(((data & 0x00FFFF) >>8));       // Send the third byte to the TX Buffer: Data[15:8]
  while ( (UCB1STAT & UCBUSY) );		                // USCI_B1 TX buffer ready?
  dummy_rx = UCB1RXBUF;			                // Dummy Read Rx buf
  UCB1TXBUF = (unsigned char)(((data & 0x0000FF)));           // Send the first byte to the TX Buffer: Data[7:0]
  while ( (UCB1STAT & UCBUSY) );		                // USCI_B1 TX buffer ready?
  dummy_rx = UCB1RXBUF;			                // Dummy Read Rx buf
  P4OUT|=0x01;  // SEN HIGH
}

/**********************************************************************************************************
*	        AFE44x0_Reg_Read           					  			  *
***********************************************************************************************************/
unsigned long AFE44x0_Reg_Read(unsigned char Reg_address)
{
  unsigned char SPI_Rx_buf[4];
  unsigned long retVal;
  retVal = 0;
  P4OUT&= ~0x01;   //  SEN LOW FOR TRANSMISSION.
  // Loop unrolling for machine cycle optimization
  UCB1TXBUF = Reg_address;                    // Send the first byte to the TX Buffer: Address of register
  while ( (UCB1STAT & UCBUSY) );		// USCI_B1 TX buffer ready?
  SPI_Rx_buf[0] = UCB1RXBUF;			// Read Rx buf
  UCB1TXBUF = 0;                              // Send the second byte to the TX Buffer: dummy data
  while ( (UCB1STAT & UCBUSY) );		// USCI_B1 TX buffer ready?
  SPI_Rx_buf[1] = UCB1RXBUF;			// Read Rx buf: Data[23:16]
  UCB1TXBUF = 0;                              // Send the third byte to the TX Buffer: dummy data
  while ( (UCB1STAT & UCBUSY) );		// USCI_B1 TX buffer ready?
  SPI_Rx_buf[2] = UCB1RXBUF;			// Read Rx buf: Data[15:8]
  UCB1TXBUF = 0;                              // Send the first byte to the TX Buffer: dummy data
  while ( (UCB1STAT & UCBUSY) );		// USCI_B1 TX buffer ready?
  SPI_Rx_buf[3] = UCB1RXBUF;			// Read Rx buf: Data[7:0]
  P4OUT|=0x01;  // set HIGH at end of transmission
  retVal = SPI_Rx_buf[1];
  retVal = (retVal << 8) | SPI_Rx_buf[2];
  retVal = (retVal << 8) | SPI_Rx_buf[3];
  //retVal = (SPI_Rx_buf[1]<<16)|(SPI_Rx_buf[2]<<8)|(SPI_Rx_buf[3]);
  return 	retVal;
}

/**********************************************************************************************************
*	        Enable_AFE44x0_SPI_Read        	                  					  *
**********************************************************************************************************/
void Enable_AFE44x0_SPI_Read (void)
{
  unsigned char dummy_rx;
  //Set Control0 - Enable SPI Read bit
  P4OUT&= ~0x01;                        // CS LOW for start of transmission.   
  // Loop unrolling for machine cycle optimization
  UCB1TXBUF = 0;                        // Send the first byte to the TX Buffer: Address of register
  while ( (UCB1STAT & UCBUSY) );	// USCI_B1 TX buffer ready?
  dummy_rx = UCB1RXBUF;			// Dummy Read Rx buf   
  UCB1TXBUF = 0;                        // Send the second byte to the TX Buffer: Data[23:16]
  while ( (UCB1STAT & UCBUSY) );	// USCI_B1 TX buffer ready?
  dummy_rx = UCB1RXBUF;			// Dummy Read Rx buf
  UCB1TXBUF = 0;                        // Send the third byte to the TX Buffer: Data[15:8]
  while ( (UCB1STAT & UCBUSY) );	// USCI_B1 TX buffer ready?
  dummy_rx = UCB1RXBUF;			// Dummy Read Rx buf
  UCB1TXBUF = 1;                        // Send the first byte to the TX Buffer: Data[7:0]
  while ( (UCB1STAT & UCBUSY) );	// USCI_B1 TX buffer ready?
  dummy_rx = UCB1RXBUF;			// Dummy Read Rx buf 
  P4OUT|=0x01;                          // CS High for end of transmission
}

/**********************************************************************************************************
*	        Disable_AFE44x0_SPI_Read       	                  					  *
**********************************************************************************************************/
void Disable_AFE44x0_SPI_Read (void)
{
  unsigned char dummy_rx;
  //Set Control0 - Disable SPI Read bit
  P4OUT&= ~0x01;                        // CS LOW for start of transmission.
  // Loop unrolling for machine cycle optimization
  UCB1TXBUF = 0;                        // Send the first byte to the TX Buffer: Address of register
  while ( (UCB1STAT & UCBUSY) );	// USCI_B1 TX buffer ready?
  dummy_rx = UCB1RXBUF;			// Dummy Read Rx buf
  UCB1TXBUF = 0;                        // Send the second byte to the TX Buffer: Data[23:16]
  while ( (UCB1STAT & UCBUSY) );	// USCI_B1 TX buffer ready?
  dummy_rx = UCB1RXBUF;			// Dummy Read Rx buf
  UCB1TXBUF = 0;                        // Send the third byte to the TX Buffer: Data[15:8]
  while ( (UCB1STAT & UCBUSY) );	// USCI_B1 TX buffer ready?
  dummy_rx = UCB1RXBUF;			// Dummy Read Rx buf
  UCB1TXBUF = 0;                        // Send the first byte to the TX Buffer: Data[7:0]
  while ( (UCB1STAT & UCBUSY) );	// USCI_B1 TX buffer ready?
  dummy_rx = UCB1RXBUF;			// Dummy Read Rx buf
  P4OUT|=0x01;                          // CS High for end of transmission
}

/*********************************************************************************************************/

/**********************************************************************************************************/
// Echo character
#pragma vector=USCI_B1_VECTOR
__interrupt void USCI_B1_ISR(void)
{
  switch(UCB1IV)
  {
  case 0:break;                             // Vector 0 - no interrupt
  case 2:break;                             // Vector 2 - RXIFG
  case 4:break;                             // Vector 4 - TXIFG
  default: break;
  }
}
// End of file
