/* ###################################################################
**     Filename    : main.c
**     Project     : Assignment 2
**     Processor   : MK20DX128VLH5
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-10-17, 12:01, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "AD1.h"
#include "AdcLdd1.h"
#include "Term1.h"
#include "Inhr1.h"
#include "ASerialLdd1.h"
#include "Motor.h"
#include "PwmLdd1.h"
#include "TU1.h"
#include "Servo1.h"
#include "PwmLdd2.h"
#include "TU2.h"
#include "Servo2.h"
#include "PwmLdd3.h"
#include "EMControl.h"
#include "BitIoLdd1.h"
#include "LSwitch.h"
#include "BitIoLdd2.h"
#include "RSwitch.h"
#include "BitIoLdd3.h"
#include "Hall_out_B.h"
#include "BitIoLdd4.h"
#include "Hall_out_A.h"
#include "BitIoLdd5.h"
#include "Direction.h"
#include "BitIoLdd6.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
#include <string.h>
#include <stdio.h>

int baseval = 0;
int basevaltot = 0;
int baseadj = 0;
int baseadjtot = 0;

int boomval = 0;
int boomvaltot = 0;
int boomadj = 0;
int boomadjtot = 0;

int windupval = 0;
int winduptot = 0;
int winddownval = 0;
int winddownvaltot = 0;

volatile char buffer [100];
volatile int msgRec;
/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */
	int *analog[4];
	#define LENGTH 40
	char message [LENGTH];

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */
  for(;;){
	  if (manual=1){



			  for(int i=0;i<1000000;i++){

			  }
			  while(!ERR_OK==AD1_Measure(TRUE)){}
			  AD1_GetValue16(&analog);


			  for(int i=0;i<4;i++){
				  snprintf(message, LENGTH, "joystick %i %i\n\r",i, analog[i]);
				  Term1_SendStr(message);
			  }

	  }



// This is the automatic control section, read the characters and
//	executes to the necessary functions
//don't forget to initialize all the values!!! Has not been done yet
	  else {		// so while the manual contorl is not doing anything, wait for the interupt
		  while (msgrec=0){


		  }

			  if (sscanf (buffer, "base %num", baseval) >0){		//checks for base value
				  basevalue(baseval);
			  }
			  if (sscanf (buffer, "base adjust %num", baseadj) >0){		//checks for base adjutsment
				  baseadjust(baseadj);
			  }
			  if (sscanf (buffer, "boom %num", boomval) >0){		//checks for boom value
				  boomvalue(baseval);
			  }
			  if (sscanf (buffer, "boom adjust %num", boomadj) >0){		//checks for boom adjustment
				  boomadjust(baseval);
			  }
			  if (strcmp (buffer, "EM On")==0){		//checks for EM switch, no function needed
				  EMControl_PutVal(1);
			  }
			  else if (strcmp (buffer, "EM Off") ==0){
				  EMControl_PutVal(0);
			  }
			  	  else{
				 	EMControl_PutVal(0);			//EM should always be off until deactivated
			  }
			  if (sscanf (buffer, "windup %num", windupval) >0){		//checks for the windup and down value
				  windup(windupval);
			  }
			  if (sscanf (buffer, "winddown %num", windupval) >0){
				  windup(windupval);
			  }
	  }

//----------------------This is the function section-------*unfinished*---------
// -------------Base movement--------------------------
	  void basevalue(baseval) {
		  if (baseval >= 0){
			  Direction_PutVal(1);		//turn the motor on
			  //implement PWM contorl here
			  // set to specified position and update the total value of the base
		  }
	  }

	  void baseadjust(baseadj) {
		  if (baseadj >= 0){
			  Direction_PutVal(1);
			  //check that the adjusment value is not greater than the max and min angle
			  //increase by whatever specified and then update base tot value
		  }
	  }
//-----------------Boom movement-----------------------
	  void boomvalue(boomval) {		//boom movement works off duty cycle
		  if (boomval >=0 && <= 90){				//value must be between 0-90 degrees
				  Servo1_SetDutyMS(boomval/10);		//needs to be calibrated
				  boomvaltot = boomval;				//incrememnt needs to be used to smoothen it out
				  	  	  	  	  	  	  	  	  	 // devide by the amout it needs to go by how many steps
		  }
	  }
	  void boomadjust(boomadj) {
		  if (boomvaltot + boomadj > 90){ 			//if its greater than 90 juts set it to ninety
			  Servo1_SetDutyMS(9);
			  boomvaltot = 90;						//update total value
		  }
		  else if (boomvaltot + boomadj < 0){		// if the adjusent is lower than 0, set it to 0
			  Servo1_SetDutyMS(0);
			  boomvaltot = 0;
		  }
		  else{
			  Servo1_SetDutyMS((boomvaltot + boomadj)/10);		//if it is fine then adjust and set total value.
		  boomvaltot = boomvaltot+boomadj;
		  }
	  }
// ------------winch control--------------------------
	  void windup(windupval) {		//works off duty cycle
		  if (windupval >= 0){		//take 20ms to check if the motor is on
			  Servo2_SetRatio16(windupval);  			//this is on a constant rotation motor, pwm defgines speed
			  	  	  	  	  	  	  	  	  	  	  	  // must be experimented
		  }
	  }
	  void windown(windownval) {
		  if (winddownval1 <= 0){
			  Direction_PutVal(1);
		  }
	  }

		  }
  /*
//initializeing the gui thing
	  void initialise(){
	  Term1_SendStr('------ Automatic Control------ /n/r');
	  Term1_SendStr('         - Commands - /n/r');
	  Term1_SendStr('+To rotate base use - base "value" /n/r');
	  Term1_SendStr('+To adjust base use - base adjust "value" /n/r');
	  Term1_SendStr('-----------------------------------------/n/r');
	  Term1_SendStr('+To move boom angle use - boom "value" /n/r');
	  Term1_SendStr('+To adjust boom angle use - boom adjust "value" /n/r');
	  Term1_SendStr('-----------------------------------------/n/r');
	  Term1_SendStr('+To windup use - windup "value"/n/r');
	  Term1_SendStr('+To winddown use - winddown "value"/n/r');
	  Term1_SendStr('-----------------------------------------/n/r');
	  Term1_SendStr('+To enable electromagnet use - EM On "value"/n/r');
	  Term1_SendStr('+To disable electromagnet use - EM Off "value"/n/r');
	  Term1_SendStr('-----------------------------------------/n/r');
	  }
	  }*/
// -----------------------------GUI settings
void SendString( char* StrToSend, int NewLine){ //send str to terminal
	Term1_SendStr(StrToSend);
		if (NewLine ==1){
			Term1_SendStr("\r\n");
		}
}

void SendBlankStr ( int spacesToSend){
	for (int j = 1; j <= spacesToSend; j++) {
		Term1_SendStr("");
	}
}
void PrintBorder(int X1, int Y1, int X2, int Y2) { // Prints a yellow border
	Term1_MoveTo(X1, Y1);	// Move to top left corner
	// Set the border colour
	Term1_SetColor(clBlack, clYellow);
	SendBlankStr(X2 - X1 + 1); // Send the top row
	for (int j = Y1 + 1; j < Y2; j++) { // For each of the inner 'rows'
		Term1_MoveTo(X1, j);
		SendBlankStr(1);
		Term1_MoveTo(X2, j);
		SendBlankStr(1);
	}
	Term1_MoveTo(X1, Y2); // Send the bottom row
	SendBlankStr(X2 - X1 + 1);
}
void BorderTitle(char* title, int X1, int Y1) { // Sets the border title

	Term1_SetColor(clBlack, clYellow);
	Term1_MoveTo(X1, Y1);
	SendString(title, 0);
}
void PrintHowToInstructions() { // Prints the how-to instructions
	Term1_SetColor(clWhite, clBlack);

	Term1_MoveTo(26, 5);
	SendString("Type the following commands:", 0);
	Term1_MoveTo(26, 6);
	SendString("> base n     		Set base to n", 0);
	Term1_MoveTo(26, 7);
	SendString("> base adjust n   	adjust base rotation by n", 0);
	Term1_MoveTo(26, 8);
	SendString("> boom n    		Set boom value to n", 0);
	Term1_MoveTo(26, 9);
	SendString("> boom adjust       adjusts boom value by n", 0);
	Term1_MoveTo(26, 10);
	SendString("> windup n      	winds the winch up by n", 0);
	Term1_MoveTo(26, 11);
	SendString("> winddown n      	winds the winch down by n", 0);
	Term1_MoveTo(26, 12);
	SendString("> EM On      		turns the electromagnet on", 0);
	Term1_MoveTo(26, 13);
	SendString("> EM On      		turns the electromagnet on", 0);
	Term1_MoveTo(26, 14);
	SendString("> clc       		Clear the console", 0);
}
void InitializeGUI() {
	Term1_Cls();
	Term1_MoveTo(1, 1);
	Term1_SetColor(clYellow, clBlack);
	SendString("CC2511 Lab 8", 1);
	PrintBorder(1, 3, 22, 12); // PWM status border
	BorderTitle("+---[ PWM Status ]---+", 1, 3); // PWM Title
	PrintBorder(24, 3, 69, 12); // How to use border
	BorderTitle("+---------------[ How to use ]---------------+", 24, 3); // PWM Title
	updatePWMStatus(RLEDPWM, GLEDPWM, BLEDPWM);
	PrintHowToInstructions();
	lineUpTo = 0;
}

  }
  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
