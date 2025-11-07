// Author: Anmol Ratol 30231177
// Program: creating an assembly code program to find the integer minimum of
// 3x^3 +31x^2 -15x -127 in the range of natural numbers from [-10, 4] 

output: .string "The minimum thus far at (x = %3d) (y = %4d) is: %4d\n" // setting up a string ahead of time
        .balign 4 // // aligning 4 bits
        .global main // default code setup for any assembly program

main:   stp x29, x30, [sp, -16]! // the necessary code for initialization
        mov x29, x30 // more code for initialization

        mov x28, -10 // actually initializating variables for the program, setting the loop to begin at -10
        mov x23, 50000 // setting up the initial value as something preposterously high

pretest:cmp x28, 4 // the pretest loop, comparing x28 to 4 
        b.gt end // jump ahead to the end if greater than 4

adding: mov x18, x28 // creating the x^3 term using mov and mul
	mov x20, x18 // moving value into register to represent x term
        mul x18, x18, x28 // multiplying it again to get squared
	mov x19, x18 // moving it into the registered for the value of x^2
        mul x18, x18, x28 // mulii
        mov x25, 3 // using x25 as my the multiplication constant for this program
        mul x18, x18, x25 // multiplying cubic term by constant
	
        mov x25, 31 // changing value of constant
        mul x19, x19, x25 // multiplying quadratic term by constant

        mov x25, -15 // redefining constant
        mul x20, x20, x25 // multiplying linear term by constant

        mov x21, -127 // tacking on the -127 to x21

        add x18, x18, x19 // adding on quadratic
        add x18, x18, x20 // adding on linear
        add x18, x18, x21 // adding on constant

if:     cmp x18, x23 // if the new minimum is less than the previous minimum, proceed normally, otherwise go to else
        b.ge print // skip ahead to print otherwise 
	mov x23, x18 // if new minimum less than, update 

print:  adrp x0, output // address place instruction for the output string
        add x0, x0, :lo12: output // changing the value of x0
        mov x1, x28 // moving the value of the first number in string as x
	mov x2, x18 // moving the value of the second number in string as y
	mov x3, x23 // moving the value of the third number in string as minimum

        bl printf // print out

        add x28, x28, 1 // add one to our loop register
        b pretest // cycle back to the pretest loop

end:    ldp x29, x30, [sp], 16 // generic program ending code
        ret // final return to indicate program is over
