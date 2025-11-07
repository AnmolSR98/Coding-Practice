			// Anmol Ratol, 30231177
		// defining 1 and false, as done in the C code


        int_size = 4		// calculating the total size of each cuboid and the total memory allocation needed for main 
        point_size = 2*int_size	
        dim_size = 2*int_size
        cuboid_size = point_size + dim_size + 2*int_size
        total = 2*cuboid_size
        alloc = -(16+total) & -16
        dealloc = -alloc

        a_s = 16		// calculating the offset for the cuboids, and the point and dimension structures
	point_s = 0		// within them and the integers that are further nested within them
        x_s = 0
        y_s = int_size
	dimension_s = point_size
	width = 0
        length = int_size
	height = dimension_s + dim_size 
        volume = height + int_size
        b_s = a_s + cuboid_size

initial:.string "Initial cuboid values:\n"	// strings that are printed for the various prints that occur in main
changed:.string "Changed cuboid values:\n"
first:  .string "first"
second: .string "second"
        .balign 4				// word aligned
        .global main				// make main global

main:	stp x29, x30, [sp, alloc]!		// allocating the memory needed
	mov x29, sp				// moving x29 to the stack pointer

finit:	add x8, x29, a_s			// passing the position of a_s into the x8 register for use in init
	bl init					// initializing the cuboid

	add x8, x29, b_s			// doing the same for the b_s cuboid
	bl init

	adrp x0, initial			// printing the initial string 
	add x0, x0, :lo12:initial
	bl printf
	
fprint:	add x8, x29, a_s			// passing off the position of a_s into x8 to use to print its contents
	adrp x1, first				// and filling the x1 with the first string as an arg
	add x1, x1, :lo12:first
	bl cprint
	
	add x8, x29, b_s			// doing the exact same thing but for the b_s cuboid and the second string as the arg
	adrp x1, second
	add x1, x1, :lo12:second
	bl cprint

	add x8, x29, a_s			// using x8 to store the value of a_s in the stack
        add x0, x29, b_s			// and using x0 to do the same but with b_s
        bl compare
	
	cmp x19, 1				// the result is stored in x19, and if it is 1
	b.ne after				// then go ahead with the changes
	
	mov w0, 3				// using w0 and w1 as the arguments for the move subroutine
	mov w1, -6				// and moving the address for a_s into the x8 register as the cuboid to be moved	
imove:	add x8, x29, a_s
	bl move

	mov w0, 4				// using w0 as the argument for the value of the 
iscale:	add x8, x29, b_s
	bl scale
			
after:	adrp x0, changed			// printing the changed string
	add x0, x0, :lo12:changed	
	bl printf
	
	add x8, x29, a_s			// exactly the same as before, printing the updated values for a_s
	adrp x1, first
	add x1, x1, :lo12:first
	bl cprint

	add x8, x29, b_s			// printing the updated values for b_s
	adrp x1, second
	add x1, x1, :lo12:second
	bl cprint

	ldp x29, x30, [sp], dealloc		// deallocating memory and ending the program
	ret

	alloc = -(16 + cuboid_size) & -16	// allocating memory for the init subroutine, placing base where the frame record ends
	dealloc = -alloc
	base = 16

init: 	stp x29, x30, [sp, alloc]!
	mov x29, sp
	
	add x9, x29, base
	
	mov w12, 0				// constructing the cuboid in the init stack first, starting with the point values
	str w12, [x9, point_s + x_s]		// used x9 to point where to store, previously shifted it to immediately past the frame record 
	mov w12, 0
	str w12, [x9, point_s + y_s]

	mov w12, 2
	str w12, [x9, dimension_s + width] 	// before doing the same for the dimension values
	mov w12, 2
	str w12, [x9, dimension_s + length]

	mov w12, 3
	str w12, [x9, height]			// and doing the same for the height
	
	ldr w11, [x9, dimension_s + width]	// loading the width, length , and height values to use to calculate the volume
	ldr w12, [x9, dimension_s + length]
	ldr w13, [x9, height]

	mul w11, w11, w12			// multiplying them together and storing them in the the position for volume
	mul w11, w11, w13
	str w11, [x9, volume]

	ldr w11, [x9, point_s + x_s]		// transferring all of the various values in the stack of init to the stack in main
	str w11, [x8, point_s + x_s]
	
	ldr w11, [x9, point_s + y_s]
	str w11, [x8, point_s + y_s]
	
	ldr w11, [x9, dimension_s + width]
	str w11, [x8, dimension_s + width]

	ldr w11, [x9, dimension_s + length]
	str w11, [x8, dimension_s + length]

	ldr w11, [x9, height]
	str w11, [x8, height]

	ldr w11, [x9, volume]
	str w11, [x8, volume]
	
	ldp x29, x30, [sp], dealloc
	ret
	
origins:.string "Cuboid %s origin (%d, %d)\n"			// defining the various strings needed to print the contents of the cuboid	
bases:	.string "\tBase width = %d Base length = %d\n"
heights:.string "\tHeight = %d\n"
volumes:.string "\tVolume = %d\n\n"
	.balign 4

cprint:	stp x29, x30, [sp, -16]!		// setting allocation to 16 since that is all this subroutine requires
	mov x29, sp	

	mov x19, x8				// using x19 since x8 appears to clear after each branch and link instruction, causes segmentation error
						// otherwise
	adrp x0, origins			// load the values from the origin to attach to origins string and print
	add x0, x0, :lo12:origins		
	ldr x2, [x19, point_s + x_s]
	ldr x3, [x19, point_s + y_s]
	bl printf

	adrp x0, bases				// doing the same but for bases
	add x0, x0, :lo12:bases
	ldr x1, [x19, dimension_s + width]
	ldr x2, [x19, dimension_s + length]
	bl printf

	adrp x0, heights			// and for height
	add x0, x0, :lo12:heights
	ldr x1, [x19, height]
	bl printf

	adrp x0, volumes			// likewise for volume
	add x0, x0, :lo12:volumes
	ldr x1, [x19, volume]
	bl printf

	ldp x29, x30, [sp], 16			// deallocating and returning
	ret

move:	stp x29, x30, [sp, -16]!		// allocating memory for move		
	mov x29, sp
	
	ldr w11, [x8, point_s + x_s]		// loading the x and y values into the w11 register
	add w11, w11, w0			// adding the values stored in the w0 and w1 registers (the amount to be shifted by)
	str w11, [x8, point_s + x_s]		// and then storing them back in their stack location

	ldr w11, [x8, point_s + y_s]
	add w11, w11, w1
	str w11, [x8, point_s + y_s]
	
	ldp x29, x30, [sp], 16			// deallocation and return 
	ret

scale:	stp x29, x30, [sp, -16]!		// allocating memory and moving x29
	mov x29, sp				
	
	ldr w11, [x8, dimension_s + width]	// retrieving the values from the stack into w11, multiplying
	mul w11, w11, w0			// w11 by the value in w0 and then placing back into the stack
	str w11, [x8, dimension_s + width]

	ldr w12, [x8, dimension_s + length]
	mul w12, w12, w0
	str w12, [x8, dimension_s + length]

	ldr w13, [x8, height]
	mul w13, w13, w0
	str w13, [x8, height]
	
	mul w11, w11, w12			// recalculating the new value for volume and placing it in stack
	mul w11, w11, w13
	str w11, [x8, volume]

	ldp x29, x30, [sp], 16			// dealloc and return
	ret

compare:stp x29, x30, [sp, -16]!		// allocation
	mov x29, sp

	mov x9, x0				// moving the stack address for the second cuboid into x9
	mov x19, 0				// setting the default as 0

	ldr w11, [x8, dimension_s + width]	// for the width, length, and volume, checking the values for both cuboids
	ldr w12, [x9, dimension_s + width]	// if they don't match, skip to the end deallocation and return

	cmp w11, w12
	b.ne end

	ldr w11, [x8, dimension_s + length]
	ldr w12, [x9, dimension_s + length]
	
	cmp w11, w12
	b.ne end

	ldr w11, [x8, height]
	ldr w12, [x9, height]
	
	cmp w11, w12
	b.ne end

	mov x19, 1				// otherwise, if they are all the same, store the value in x19 as 1

end:	ldp x29, x30, [sp], 16			// deallocation and return
	ret	
