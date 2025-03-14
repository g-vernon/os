.section .init
	/* GCC will paste crtend.o's .init section here */
	popl %ebp
	ret

.section .fini
	/* GCC will paste crtend.o's .fini section here */
	popl %ebp
	ret

