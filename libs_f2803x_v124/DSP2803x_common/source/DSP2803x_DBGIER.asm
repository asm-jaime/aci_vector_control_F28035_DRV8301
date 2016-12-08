;// TI File $Revision: /main/1 $
;// Checkin $Date: December 5, 2008   18:00:49 $
;//###########################################################################
;//
;// FILE:  DSP2803x_DBGIER.asm
;//
;// TITLE: Set the DBGIER register
;//
;// DESCRIPTION:
;//  
;//  Function to set the DBGIER register (for realtime emulation).
;//  Function Prototype: void SetDBGIER(Uint16)
;//  Useage: SetDBGIER(value);
;//  Input Parameters: Uint16 value = value to put in DBGIER register. 
;//  Return Value: none          
;//
;//###########################################################################
;// $TI Release: 2803x C/C++ Header Files and Peripheral Examples V1.24 $
;// $Release Date: January 11, 2011 $
;//###########################################################################	
		.global _SetDBGIER
		.text
		
_SetDBGIER:
		MOV 	*SP++,AL
		POP 	DBGIER
		LRETR
		
