 // defining a bunch of macros to make the code more legible








output: .string "w18 = 0x%08x (%d) w19 = 0x%08x (%d)\n" // defining a bunch of my strings here
output2:.string "w20 = 0x%08x (%d) w18 = 0x%08x (%d)\n"
output3:.string "64-bit x23 = 0x%016lx (%ld) \n"
        .balign 4 						        // align 4 bits
        .global main							// setting up main 

main:   stp x29, x30, [sp, -16]! // generic program setup code
        mov x29, sp 		 // more generic program beginning code

initial_print:

        mov w19, -16843010	// moving the desired value into w19
        mov w18, 70		// moving the desired value into w18
        mov w20, 0			// initially moving a zero into w20, the algorithm will build this term

        adrp x0, output			// initial print statement
        add x0, x0, :lo12:output	// assigning the first string formatting to this
        sxtw x1, w18		// extending into 64 bit registers for printing moving w18 here twice for both base 10 and hexadecimal
        sxtw x2, w18
        sxtw x3, w19		// doing the same thing for the w19 for both base 10 and hexadecimal
        sxtw x4, w19

        bl printf			// print the contents of x0

define_negative:

        mov w22, 0			// checking whether the w18 is w22, will have it as 0 to begin with
        mov w21, 0			// initializing w21 as 0
        cmp w18, 0		// directly compare w18 to zero
        b.ge loop			// if greater than or equal to, jump ahead to the loop	
        mov w22, 1			// else, define w22 as 1 (true)

loop:   
					
        and w26, w18, 0x1		// testing if the last digit of the w18 is 1
        cmp w26, 1				// check if it is a one
        b.ne middle_of_loop			// if it is not, then skip ahead to the rest of the loop
        add w20, w20, w19	// if it is, then add the w19 to the w20

middle_of_loop:
	
        asr w18, w18, 1		// arithmetic shift right the w18 by 1 bit
        and w26, w20, 0x1			// check if the last digit of w20 is a 1 

        cmp w26, 1				// compare the two values
        b.ne else2				// if it is not equal, jump ahead 

        orr w18, w18, 0x80000000	// if it is, use orr statement with 0x80000000
        b posttest				// then jump ahead to the posttest so we dont also use and

else2:  

        and w18, w18, 0x7FFFFFFF	// if not, use the and statement 

posttest:

        asr w20, w20, 1			// arithmetic shift right the w20
        add w21, w21, 1				// add one to w21 value
        cmp w21, 32				// compare it to the value of 32
        b.lt loop				// if it is less than, repeat the loop

negative_check:

        cmp w22, 1				// compare the w22 value to 1
        b.ne secondprint			// if the w18 is not w22, then jump ahead to the second print
        sub w20, w20, w19	// if it is w22, then subtract the multiplcand from the w20

secondprint:
      
        adrp x0, output2			// formatting for the second print statement
        add x0, x0, :lo12: output2
        sxtw x1, w20			// once again extending twice to get both hexadecimal and base ten values for the number im using
        sxtw x2, w20
        sxtw x3, w18
        sxtw x4, w18
        bl printf

nearly_end:
        
        sxtw x24, w20			// extending w20 into the 64 bit register of x24
        and x24, x24, 0xFFFFFFFF		// using and statement on w20 before moving into x24 
        lsl x24, x24, 32			// logical shifting x24 left by 32 bits
		
        sxtw x25, w18			// extending 32-bit w18 into 64 bit register of x25
        and x25, x25, 0xFFFFFFFF		// using and statement to preserve the values

        add x23, x24, x25		// adding the two together

        adrp x0, output				// final print statement, utilizing the 64 bit print statement from earlier, no need to use sxth
        add x0, x0, :lo12: output3
        mov x1, x23
        mov x2, x23
        bl printf

end:    ldp x29, x30, [sp], 16			// boiler plate ending code
        ret
