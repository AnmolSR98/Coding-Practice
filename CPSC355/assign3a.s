	// defining the macro for 50, defining it as 50 
		// using w19 for w19
		// using w20 for w20
	// using w21 for w21
	// using w22 for w22, analogous to v[w20] in the C code
	// using w23 for w23, analogous to v[w20-1] in the C code
	
	int_size = 4			// integer 50 is 4 bytes
	total = int_size * 50		// total amount of memory needed for the array

	alloc = -(-16+total) & -16	// allocating that amount of memory

	dealloc = -alloc		// positive amount to deallocate

	a_s = 16			// address of the very first array element

output: .string "v[%02d]: %02d\n"	// the string for printing array elements
sorted: .string "\nSorted Array:\n"	// the string to mark the start of the sorted array
	.balign 4			// align with 4 bits
	.global main			// make main global

main:   stp x29, x30, [sp, alloc]!	// store pair 
        mov x29, sp			// moving x29 to the position where the stack pointer is

	mov w19, 0			// move the value of 0 into w19 before loop begins
	add x29, x29, a_s		// move the stack pointer register to the beginning of the array
	//mov w21, 50

loop1:	bl rand				// generating a random number into the x0 register
	and w21, w0, 0xFF		// moving that value into w21 using and 
	str w21, [x29, w19, SXTW 2] 	// store that value in x29 + 4*w19
			
	adrp x0, output			// setting up x0 for printing
	add x0, x0, :lo12:output	// formatting it properly
	sxtw x1, w19			// moving the value from w19 into output x1
	sxtw x2, w21			// moving the value from w21 into output x2
	bl printf			// print the statement

	add w19, w19, 1			// loop back if w19 is less than 50 after adding 1 to w19
	cmp w19, 50
	b.lt loop1
	
	mov w19, 1			// reset w19 to 1 for the next loop

loop2:	ldr w21, [x29, w19, SXTW 2]	// load the value of w21 from w19
	mov w20, w19			// set the value of w20 as w19

inner_loop:
	
	sub w20, w20, 1
load:	ldr w23, [x29, w20, SXTW 2]	// get the value of the array element in w20 - 1
		
	add w20, w20, 1			// reset w20 - 1 back to w20 
	cmp w21, w23			// first loop condition: if w21 < v[w20-1], continue, else skip to end of loop
        b.ge loop2_2

store:	str w23, [x29, w20, SXTW 2]	// move that value into array position w20

	sub w20, w20, 1			// w20 = w20 - 1
 
	cmp w20, 0			// if w20 less than/equal, break the loop, posttest
	b.le loop2_2 

	b inner_loop			// else loop back

loop2_2:str w21, [x29, w20, SXTW 2]  	// insert that value of w21 into the final w20 value that we get

	add w19, w19, 1			// w19 = w19 + 1
 
	cmp w19, 50			// compare w19 to 50, if lt loop back
	b.lt loop2

	mov w19, 0 			// reset w19 to 0 prior to print loop
	
	adrp x0, sorted			// print out the sorted array divider string
	add x0, x0, :lo12:sorted
	bl printf

print:	ldr w21, [x29, w19, SXTW 2]	// load the values from the list
	sxtw x19, w19
        sxtw x20, w21
        adrp x0, output			// and print them out
        add x0, x0, :lo12:output
        mov x1, x19
        mov x2, x20
	bl printf

	add w19, w19, 1			// w19 = w19 + 1

	cmp w19, 50			// compare w19 to 50, loop if less than
	b.lt print

end:	mov x0, 0			// ending code
	ldp x29, x30, [sp], dealloc 	// deallocating all of the stack memory used
	ret

