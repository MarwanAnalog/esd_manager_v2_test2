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






/*MAIN PROGRAM*/


int main ()
{







while(1)
{
	//wait for a scan
	while(i==0)  // Loop that keep reading from stdin until a barcode is scanned!
	{
		//LCD screen : Wait for Scan
		gets(barcode);
		i = strlen(barcode);
		if (i>0)
                {i=1;}
	}
	
	//extract the employee ID
	P1 = strtok(barcode," - ");
    P2 = strtok(NULL," - "); // the employee ID number will be saved here!
    P3 = strtok(NULL," - ");
	
	//Verify the ID number in the employee Database
		
		//Open a connection
		
	





}


}







/*FUNCTION'S SOURCES*/

