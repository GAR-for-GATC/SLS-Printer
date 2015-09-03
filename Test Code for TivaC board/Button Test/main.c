#include "lm4f120h5qr.h"


//Test code to make on board LED blink when button is pressed.
//There are 43 programmable GPIO pins
void wait(void);

int main(){
	
	//  The RCGCGPIO 32 bit register is used to enable and disable GPIO modules in "run mode".
	// This turns on bit 5 in the register on and activates the clock for port f.
	// This also activates port f.
	SYSCTL_RCGCGPIO_R |= 0x20U;
	
	//  Writing 0x4C4f434BU to GPIOLOCK enables write access to the GPIOCR register.
	// Writing anything else to GPIOLOCK locks the GPIOCR register.  Reading from 
	// GPIOLOCK also re-enables the lock state.  Read datasheet for more info.
	//   In this example, pin PF0 is connected to switch 2 and is configured to GPIO by default and
	// can only be reconfigured by clearing the LOCK register and then setting the RC register.	
	GPIO_PORTF_LOCK_R = 0x4C4f434BU;
	
	//  The GPIOCR register determines the values of the GPIOAFSEL, GPIOPUR, GPIOPDR, and GPIODEN
	// registers.  If a bit is GPIOCR is set, then the bits in GPIOAFSEL, GPIOPUR, GPIOPDR, and GPIODEN
	// can be written to.
	GPIO_PORTF_CR_R = 0xFF; //all bits can be written.
	
	//  The GPIOAMSEL register controls isolation circuits to the analogue side of  a unified I/O pad.
	// When a bit in this register is set to one, the analogue function of the pin is enabled, isolation 
	// disabled and the pin can use analogue functions.  
	//  When the bit is disabled, isolation is enabled and the pin is capable of digital functions.
	GPIO_PORTF_AMSEL_R = 0x00U;  // All portF is digital pins.
	
	//  The GPIOPCTL register is used to choose the peripheral signal when in alternate mode.  When a bit is 
	// set in GPIOAFSEL, that pin is controlled by an associated peripheral.  GPIOPCTL is used to select a 
	// peripheral function for signal definition.  The reset value is 0x00000000.
	GPIO_PORTF_PCTL_R = 0x00000000U;
	
	//  The GPIODIR register is used to configure each individual pin as either input or output.  When a bit in
	// the register is 0, the pin is an input.  When the bit is one, the pin is an output.
	GPIO_PORTF_DIR_R = 0x0EU;  // Sets pins 0x0E, or 0b01110, to make pins PF0 and PF4 inputs and to make 
														 // PF1, PF2 and PF3 outputs.
	
	//  The GPIOAFSEL register is the mode control select register.  If the bit is 0, then that pin is used as 
	// GPIO.  If set, then the GPIO is controlled by an associated peripheral.
	// DO NOT reset pins PC[3:0] which are used for the JTAG programmer.
	GPIO_PORTF_AFSEL_R = 0x00U;
	
	// GPIOPUR controls pullups.  Setting a bit in this register enables a weak pullup resistor and clears
	// the corresponding bit in GPIOPDR, which is lets you set pulldown resisors.
	GPIO_PORTF_PUR_R = 0x11U; //00010001
	
	//  GPIODEN is the digital enable register.  The pins are tristated (except for specific pins) by default
	// and can be used as input or output when a bit in this register is set.
	GPIO_PORTF_DEN_R = 0xFFU;  //all pins on.
	
	
	
	while(1){
		/*
		GPIO_PORTF_DATA_R &= ~0x0E; //turn off all 3 leds 00001110
		wait();
		GPIO_PORTF_DATA_R |= 0x02; //turn on an LED
		wait();
		GPIO_PORTF_DATA_R &= ~0x02;
		wait();
		GPIO_PORTF_DATA_R |= 0x04; //0100
		wait();
		GPIO_PORTF_DATA_R &= ~0x04;
		wait();
		GPIO_PORTF_DATA_R |= 0x08; //1000
		wait();
		GPIO_PORTF_DATA_R &= ~0x08;
		wait();
		*/
		  //This code turns on a certain LED if a button on the bottom of the board is pushed.
		GPIO_PORTF_DATA_R &= ~0x0E; //Turn off the 3 LEDs.  Turns 00001110 to 1111001, pins PF1, PF2 and PF3.
		
		//When a button is pressed, the bit in GPIO_PORTF_DATA_R (PF0 and PF4) is cleared.
		switch(GPIO_PORTF_DATA_R & 0x11U){ //0x00010001
			
			case 0x00: //both switches are pressed
				GPIO_PORTF_DATA_R |= 0x02; //turn on red LED
				break;
			case 0x01: //switch one is pressed, two isnt pressed
				GPIO_PORTF_DATA_R |= 0x04; //turn on blue
				break;
			case 0x10: //switch 2 is pressed, one isnt.
				GPIO_PORTF_DATA_R |= 0x08; //turn on green
				break;
			default: //no switch is pressed.
				break;
		}
		
		
	}
	return 0;
	
	
	
}

void wait(void){
	for(int i=0; i<1000000;i++);
}

