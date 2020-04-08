/***************************************************************************************
 *	File Name				:	imput.h	
 *	CopyRight				:	
 *	ModuleName				:	
 *
 *	CPU						:
 *	RTOS					:
 *
 *	Create Data				:	2020/4/8
 *	Author/Corportation		:	Hz
 *
 *	Abstract Description	:	this will be used for input funtion
 *
 *--------------------------------Revision History--------------------------------------
 *	No	version		Data			Revised By			Item			Description
 *	
 *
 ***************************************************************************************/


/**************************************************************
*	Multi-Include-Prevent Section
**************************************************************/
#ifndef __CONTROL_H
#define __CONTROL_H
/**************************************************************
*	Prototype Declare Section
**************************************************************/
char getch(char from,char to);//return the character range(from,to) 
int get_data(int *e);//return the correct input

/**************************************************************
*	End-Multi-Include-Prevent Section
**************************************************************/
#endif
