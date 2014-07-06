//============================================================================
// Name        : ESD_Manager_V2_algorithm_V1.c
// Author      : Marouen BESSROUR
// Version     :
// Copyright   : Copyright TIS Circuits 2014
// Description : ESD_Manager_V2 
//============================================================================



/*INCLUDES*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlext.h>
#include <sql.h>
#include "BeagleBone_gpio.h"
#include "BeagleBone_hd44780.h"



/*FUNCTIONS PROTOTYPES*/





/*VARIABLES*/
char barcode[100] 		//to get the barcode in a array of char
char *P1; 				// tools to decompose the barcode and extract the ID number from
char *P2;				//same
char *P3;				//same
int i=0;				// to verify a barcode was entered or not
int j;
struct gpioID LED1,BUTTON1;





/*MAIN PROGRAM*/


int main ()
{

	pinMode(&LED1,P8_3,"out");
	pinMode(&BUTTON1,P9_12,"in");





while(1)
{
	//wait for a scan
	while(i==0)  // Loop that keep reading from stdin until a barcode is scanned!
	{
		//LCD screen : Wait for Scan
		gets(barcode);
		printf("%s\n",barcode);
		i = strlen(barcode);
		if (i>0)
                {i=1;}
	}
	
	//extract the employee ID
	P1 = strtok(barcode," - ");
    P2 = strtok(NULL," - "); // the employee ID number will be saved here!
    P3 = strtok(NULL," - ");
	printf("%s\n",P2);
	
	// Authorize the ESD Test (activate a LED)
	digitalWrite(LED1,1);
	
	//Authorize Access (By a Button)
	for (j=0;j<100;j++)
	{
		if (digitalRead(BUTTON1)==1)
			printf("ACCESS GRANTED \n");
		else
			printf("ACCESS DENIED \n");	
		delayms(500);
	}
		cleanup(LED1);
		cleanup(BUTTON1);
		i = 0;

}


}







/*FUNCTION'S SOURCES*/

