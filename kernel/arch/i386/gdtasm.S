.global load_seg_registers
.global load_tss

.equ SEG_K_CODE, 0x1
.equ SEG_K_DATA, 0x2

load_seg_registers:
	mov 4(%esp), %eax
	lgdt (%eax)

	/* Segment selector bits
	15-3: GDT entry, 2: TI (0 = use GDT), 1-0: RPL (00 = kernel)
	*/
	mov $(SEG_K_DATA<<3), %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %ax, %ss
	/* See 7.3.15.1, Intel IA-32 Manual -- we have to use a 
	'far control transfer instruction' to place a value in the CS register.

	Section 7.3.8.1 specifies that when the CPU executes a far jump, the address
	segment selector is copied into the CS register and the offset is copied
	into the EIP register. The original EIP and CS values are pushed to the
	stack to be popped off when we do a 'far return'.

	Here we don't do a 'far return', and so we restore our EIP only but keep the
	new selector which we wrote in the CS register.
	*/
	ljmp $(SEG_K_CODE<<3), $.load_cs_reg
.load_cs_reg:
	ret

load_tss:
	mov $0x28, %ax
	ltr %ax
	ret
