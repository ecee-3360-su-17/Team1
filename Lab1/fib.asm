 ;
 ;		Filename: 	fib.asm (fib.s)
 ;
 ;		Creator:		Daniel K Langevin
 ;		Date:		2017
 ;


 .global fib

fib:
	push {lr}

base_case_one:
	cmp r0, #0
	bne base_case_two
	mov r0, #0
	pop {pc}

base_case_two:
	cmp r0, #1
	bne recurse
	mov r0, #1
	pop {pc}

recurse:
	push {r0}
	sub r0, r0, #1
	bl fib
	mov r1, r0
	pop {r0}
	push {r1}
	sub r0, r0, #2
	bl fib
	pop {r1}
	add r0, r0, r1
	pop {pc}
