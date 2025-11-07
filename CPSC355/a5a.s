






	int_size = 4
.data
queue:	.skip 8*int_size
head:	.word -1
tail:	.word -1
over:	.string "\nQueue overflow! Cannot enqueue into a full queue.\n"
under:	.string "\nQueue underflow! Cannot dequeue from an empty queue.\n"
empty: 	.string "\nEmpty Queue\n"
current:.string "\nCurrent queue contents:\n"
elem:	.string " %d"
headstr:.string " <-- head of queue"
tailstr:.string " <-- tail of queue"
new:	.string "\n"

	.text
	.balign 4
	.global queueFull
	.global queueEmpty
	.global enqueue
	.global dequeue
	.global display

queueFull:	
	stp x29, x30, [sp, -16]!
	mov x29, sp
	
	mov w0, 0			// setting the argument automatically as 0 to begin with

	adrp x20, tail
	add x20, x20, :lo12:tail
	ldr w9, [x20]			// load the tail value into temp register w9
	
	adrp x20, head
	add x20, x20, :lo12:head
	ldr w10, [x20]			// load the head value into temp register w10

	add w9, w9, 1			// add one to tail value
	and w9, w9, 0x7		// 0x7 it
	cmp w9, w10			// if they dont match, then skip to end, returning 0
	b.ne end_1	 	

	mov w0, 1 			// otherwise change to 1 and x20 1

end_1:	ldp x29, x30, [sp], 16
	ret




queueEmpty:
	stp x29, x30, [sp, -16]!	
	mov x29, sp
	
	mov w0, 0			// similarly to above, setting as initially 0

	adrp x20, head			// load the head value
	add x20, x20, :lo12:head
	ldr w9, [x20] 

	cmp w9, -1			// if it is not -1, then x20 0
	b.ne end_2
	
	mov w0, 1			// otherwise x20 1

end_2:	ldp x29, x30, [sp], 16
	ret




enqueue:stp x29, x30, [sp, -16]!	
	mov x29, sp
	
	mov w11, w0			// loading the integer to be potentially enqueued into w9

	bl queueFull			// check whether the queue is full or not, if it isn't go to else_1
	cmp w0, 1
	b.ne else_1

	adrp x0, over			// if not, print the overflow statement
	add x0, x0, :lo12:over
	bl printf 	

	b end_3

else_1:	bl queueEmpty			// now check whether the queue is empty
	cmp w0, 1
	b.ne else_2
	
	adrp x20, head			// if empty, set the head to 0
	add x20, x20, :lo12:head	
	mov w10, 0
	str w10, [x20]
	
	adrp x20, tail			// also set the tail to 0
	add x20, x20, :lo12:tail
	str w10, [x20]

	adrp x20, queue			// store the value of w9 into the tail, using the tail value as the offset
	add x20, x20, :lo12:queue
	sxtw x21, w10 
	str w11, [x20, x21, LSL 2] 	
	
	b end_3

else_2:	adrp x20, tail 			// otherwise add one to the tail and mod mask it
	add x20, x20, :lo12:tail
	ldr w10, [x20]
	
	add w10, w10, 1 		// add one to the value of the tail
	and w10, w10, 0x7		// then 0x7 to ensure it stays between 0 or 7
	str w10, [x20]

	adrp x20, queue			
	add x20, x20, :lo12:queue	// get the queue address and store the value using the tail value as the offset
	sxtw x21, w10
	str w11, [x20, x21, LSL 2]	

end_3:	ldp x29, x30, [sp], 16
	ret



dequeue:stp x29, x30, [sp, -16]!	
	mov x29, sp
	
	bl queueEmpty			// check whether the queue is empty or not, if so, skip to else 3
	cmp w0, 1
	b.ne else_3

	adrp x0, under			// if empty, then print underflow error and x20 -1
	add x0, x0, :lo12:under
	bl printf
	mov w0, -1
	b end_4
	
else_3:	adrp x20, head			// if the queue is not empty, then check the head and tail
	add x20, x20, :lo12:head
	ldr w10, [x20]

	adrp x20, tail 
	add x20, x20, :lo12:tail
	ldr w11, [x20]

	adrp x20, queue			// get the x20 value
	add x20, x20, :lo12:queue
	sxtw x21, w10
	ldr w0, [x20, x21, LSL 2]

	cmp w10, w11			// if they are the same, then set both of them as -1, ie queueEmpty
	b.ne else_4
	
	mov w10, -1
	
	adrp x20, head
	add x20, x20, :lo12:head
	str w10, [x20]

	adrp x20, tail
	add x20, x20, :lo12:tail
	str w10, [x20]
	
	b end_4

else_4:	adrp x20, head			// if they are not the same, add one to the head and 0x7 it
	add x20, x20, :lo12:head
	ldr w10, [x20]
	add w10, w10, 1
	and w10, w10, 0x7
	str w10, [x20]   		

end_4:	ldp x29, x30, [sp], 16
	ret





display:stp x29, x30, [sp, -16]!
	mov x29, sp
        
	adrp x20, queue			// loading the address for the queue into the x20 register
        add x20, x20, :lo12:queue
	
	adrp x22, head			// loading the contents of head into w21
	add x22, x22, :lo12:head	
	ldr w21, [x22]

	adrp x22, tail			// doing the same for the contents of the tail
	add x22, x22, :lo12:tail
	ldr w22, [x22]
	add w22, w22, 1			// setting it to stop the element after tail 
	and w22, w22, 0x7		

	mov w23, w21                    // using w23 as roughly analoguous to the count in the assignment, only the loop
                                        // 0x7 rather than working completely linearly

	cmp w23, -1                     // if the head is -1 it is empty and print the empty statement
        b.eq emptypr

	adrp x0, current		// printing the current queue contents statements
	add x0, x0, :lo12:current
	bl printf

	b loop

emptypr:adrp x0, empty			// printing the empty string
	add x0, x0, :lo12:empty
	bl printf
	b end_5

headprint:
	adrp x0, headstr		// printing the head string when w23 equals w22(head value)
        add x0, x0, :lo12:headstr
        bl printf
	
	b tailch	

loop:	adrp x0, elem			// print the element
	add x0, x0, :lo12:elem
	ldr w1, [x20, w23, SXTW 2]
	bl printf

	cmp w23, w21                    // if the value is equal to head pointer, jump to print the head string
        b.eq headprint

tailch:	add w23, w23, 1			// update the value and loop back
	and w23, w23, 0x7

	cmp w23, w22                    // if it is equal to the position after the tail pointer, print that string
        b.eq tailprint	

	b loop 

tailprint:	
	adrp x0, tailstr
	add x0, x0, :lo12:tailstr
	bl printf

	adrp x0, new
	add x0, x0, :lo12:new 
	bl printf

end_5:	ldp x29, x30, [sp], 16
	ret
	
