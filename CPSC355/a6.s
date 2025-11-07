// defining macros for the double calculations to be done






// defining regular macros here



// defining a bunch of values for the file read and write





// define function macros




	// some assemble equates for the where to store the 63 bytes, get the filename, alloc, and dealloc
	double_size = 8	
	alloc = -(16 + double_size) & -16
	dealloc = -alloc
	filename_cl = 8
	buf_s = 16

	.text	// 63 only needed for this assignment
// defining the minimum value to end the series calculations
min:	.double 1.0e-10	

// a bunch of string definitions, the last 5 declarations are related to file errors 
header:	.string "|   y   |      e^y         |    e^-y      |\n|-------|------------------|--------------|\n"
input1:	.string "| %-5.2f |"
input2:	.string " %-16.10f |"
input3:	.string " %-11.10f |\n"

err:	.string "There was an error with %s the file.\n"	
oerr:	.string "opening"
rerr:	.string "reading"
cerr:	.string "closing"
errmess:.dword oerr, rerr, cerr

	.balign 4	// word aligned
	.global main	// main is globally visible

main:	stp x29, x30, [sp, alloc]!	// allocate memory, move x29 to stack pointer position
	mov x29, sp
	
	mov w20, w0			// get the value in from the command line, got both but only x21 is truly necessary
	mov x21, x1

	mov w0, -100			// opening the file, -100 to denote
	ldr x1, [x21, filename_cl]	// getting the file name from command line string
	mov w2, 0			// 0 for 63 only, other values could be used for 63/64, 64 only
	mov w3, 0
	mov x8, 56			// relates back to the 56 macro
	svc 0
	
openchk:mov w25, w0			// error checking, moving w0 (file descriptor) into w25, setting up appropriate string in errmess
	mov w27, 0
	cmp w25, 0
	b.lt error			// branch to the error branch potentially

	adrp x0, header			// printing the table header
	add x0, x0, :lo12:header
	bl printf
	mov w27, 1			// shifting potential error string to problem with reading

reading:mov w0, w25			// adding file descriptor
	add x1, x29, buf_s		// getting location to put in stack, could also be put in .data
	mov x2, double_size		// specifying number of bytes to be 63
	mov x8, 63			// setting mode to 63
	svc 0				

	mov x26, x0			// error checking, if not as many bytes 63 as expected then branch to 57 file
	cmp x26, -1			// if a -1, then there was an error with reading the file
	b.eq error	
	cmp x26, double_size
	b.ne closef

	adrp x0, input1			// printing the first value, ie the value that was written in stack
	add x0, x0, :lo12:input1
	ldr d0, [x29, buf_s]
	bl printf	

	adrp x0, input1			// printing the second value, using the positive approximation subroutine
        add x0, x0, :lo12:input2
        ldr d0, [x29, buf_s]
        bl papprox
	bl printf

	adrp x0, input1			// printing the third value, using the negative approximation subroutine
        add x0, x0, :lo12:input3
        ldr d0, [x29, buf_s]
        bl napprox
	bl printf

	b reading			// branching back to 63 the next value

closef:	mov w0, w25			// closing the file, placing file descriptor in first value
	mov x8, 57			// setting mode to 57
	svc 0

	mov w26, w0			// checking if it went correctly, moving the error message to 2
	mov w27, 2
	cmp w26, 0
	b.ge end

error:	adrp x26, errmess		// potential error message printing using strings in errmess
	add x26, x26, :lo12:errmess 

	adrp x0, err
	add x0, x0, :lo12:err
	ldr x1, [x26, w27, SXTW 3]
	bl printf

end:	ldp x29, x30, [sp], dealloc	// deallocation and return 
	ret





papprox:stp x29, x30, [sp, -16]!
	mov x29, sp

	fmov d9, d0			// getting the d9 value from d0
	fmov d10, 1			// setting the values of d10 and d13
	fmov d13, 1
	
	adrp x20, min			// loading in the lower threshhold value
	add x20, x20, :lo12:min
	ldr d12, [x20]
	
	fmov d11, d9 			// starting with the 1st d11 to be added as d9
	fmov d14, 1

loop:	fcmp d11, d12		// used pre test in case d9 is very small
        b.lt p_end

	fadd d10, d10, d11		// add d11 to d10 
	
	fadd d13, d13, d14			// add 1 to d13

	fmul d11, d11, d9		// multiply the d11 by d9 over d13 to get d9^n / n!
	fdiv d11, d11, d13

	b loop				// loop back

p_end:	fmov d0, d10			// move the value into d0 for return 
	ldp x29, x30, [sp], 16
	ret





napprox:stp x29, x30, [sp, -16]!
	mov x29, sp

        fmov d9, d0			
        fmov d10, 1
        fmov d13, 1

        adrp x20, min
        add x20, x20, :lo12:min
        ldr d12, [x20]

        fmov d11, d9
        fmov d14, 1
	fneg d11, d11			// setup is identical apart from multiplying the d11 by minus one

loop_2: fabs d15, d11			// using d15 to store the absolute value for threshhold comparison
        fcmp d15, d12
        b.lt n_end

	fadd d10, d10, d11
        
	fadd d13, d13, d14
	
        fnmul d11, d11, d9		// multiply by -d9 / d13 to get (-d9)^n / n!
        fdiv d11, d11, d13
	
	b loop_2

n_end:  fmov d0, d10			// moving the calculated d10 into d0 prior to return 
        ldp x29, x30, [sp], 16
        ret
