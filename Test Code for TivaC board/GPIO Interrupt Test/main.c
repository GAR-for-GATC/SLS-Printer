//	This code uses an interrupt that occurs when a button is pressed,
// toggling a light.

#include "lm4f120h5qr.h"
#include "tm4c_cmsis.h"
#include "core_cm4.h"

//  The system clock is defined by the crystal on the board,
// which is 16MHz
#define SYS_CLOCK_HZ 16000000U
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts

void SysTick_Handler(void);
void GPIOF_Handler(void);

//int counter = 0;

int main(){
	//Take the base number from the datasheet and add the offset for register
	//RCGCGPIO.  This allows clock access to GPIO blockF, activating it.
	*((unsigned int *) 0x400FE608u) = 0x20u; 
	
	//then GPIOAFSEL is cleared to use pins as GPIO
	*((unsigned int *) 0x40025420u) = 0x00u;
	
	// Then set the GPIODIR register to set the direction of the GPIO pin 
	//as input or output.  Set 3 registers to output.
	*((unsigned int *) 0x40025400u) = 0x0Eu; //0000.1110;
	
	//set pulldown resistors for PF4.
	GPIO_PORTF_PUR_R = 0x10U;
	
	//Enable GPIO registers by turning on the GPIODEN register bits.
	*((unsigned int *) 0x4002551Cu) = 0x1Eu; //all LEDs activated and PF4 button activated.

	//The GPIOIS register is the interrupt sense register.
	GPIO_PORTF_IS_R &= ~0x10;
	//Setting to 0 allows GPIOIEV to control the register.
	GPIO_PORTF_IBE_R &= ~0x10;
	//Set to 0 to detect falling edges
	GPIO_PORTF_IEV_R &= ~0x10;
	//clear PF4 interrupt flag
	GPIO_PORTF_ICR_R = 0x10;
	//set interrupt from GPIO pin to generate interrupts.
	GPIO_PORTF_IM_R |= 0x10;
	//Set priority to 5, PR17 has offset of 0x444.
	// I have no idea how to work this.
	NVIC_PRI7_R = (NVIC_PRI7_R&0xFF00FFFF)|0x00A00000;
	//Enable nterrupt 30 in NVIC
	NVIC_EN0_R = 0x40000000; 
	
	
	
	
	EnableInterrupts();	
	
		
	while(1){

	}
	
}


void SysTick_Handler(void){	
	*((unsigned int *) 0x400253FCu) ^= 0x02u;
}




void GPIOF_Handler(void){
	GPIO_PORTF_ICR_R = 0x10; 
	*((unsigned int *) 0x400253FCu) ^= 0x02u;

}
