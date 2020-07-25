	.INCLUDE "M128DEF.INC"


	.ORG 00
	LDI R30,1			;R30 = 0
	LDI R31,4			;R31 = 4
	LDI R16,9			;R16 = 9
L1: ADD R30,R31
	DEC R16				;R16 = R16 - 1
	BRNE L1				;if Z = 0
L2: RJMP L2				;Wait here forever
