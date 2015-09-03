#include "lm4f120h5qr.h"
#include "tm4c_cmsis.h"
#include "core_cm4.h"

//  The system clock is defined by the crystal on the board,
// which is 16MHz
#define SYS_CLOCK_HZ 16000000U
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts

void SysTick_Handler(void);

int main(){
	//Take the base number from the datasheet and add the offset for register
	//RCGCGPIO.  This allows clock access to GPIO blockF, activating it.
	*((unsigned int *) 0x400FE608u) = 0x20u; 
	
	//then GPIOAFSEL is cleared to use pins as GPIO
	*((unsigned int *) 0x40025420u) = 0x00u;
	
	// Then set the GPIODIR register to set the direction of the GPIO pin 
	//as input or output.  Set 3 registers to output.
	*((unsigned int *) 0x40025400u) = 0x0Eu;
	
	//Enable GPIO registers by turning on the GPIODEN register bits.
	*((unsigned int *) 0x4002551Cu) = 0x0Eu;
	
	//The SysTick timer is initialized using the next 3 lines:
	//The STRELOAD register is set
	//The STCURRENT register is cleared by writing any value to it.
	//The STCTRL register is configured.
	//	To check that the range of the clock isn't overloaded, which is 
	// 24 bits.  16 million is equal to 0x7A11FF, so it fits into 3 bytes.
	
	SysTick->LOAD = (SYS_CLOCK_HZ/2u) - 1u; //minus one because it counts through 0.
																					//checks every 1/2 second.
	SysTick->VAL  = 0;
	SysTick->CTRL = (1u << 2) | (1u << 1) | 1u;
		
	EnableInterrupts();	
	
		
	while(1){
		/*
		//Turn on GPIO pin 2 using the GPIO F data register
		*((unsigned int *) 0x400253FCu) ^= 0x02u;
		int counter = 0;
		while(counter < 100000){
			counter++;
		}
		
		*((unsigned int *) 0x400253FCu) = 0x00u;
		counter = 0;
		while(counter < 1000000){
			counter++;
		}
		*/
	}
	
}


void SysTick_Handler(void){	
	*((unsigned int *) 0x400253FCu) ^= 0x02u;
}

