.set noat
.set noreorder

	lui $t0, 0x1234			# $t0 = 0x12345678
	ori $t0, $t0, 0x5678
	lui $t1, 0x9abc			# $t1 = 0x9abcdef0
	ori $t1, $t1, 0xdef0

	#la $t2,var3			# $t2 = &var3 (pointer to var3)
	lui $t2, 0x2000
	sw $t0, 0($t2)			# var3[0] = $t0
	sw $t1, 4($t2)			# var3[1] = $t1

	lb $t3, 0($t2)			# $t3 = 0x00000012
	lb $t4, 1($t2)			# $t4 = 0x00000034
	lb $t5, 4($t2)			# $t5 = 0xffffff9a (sign extends)
	lbu $t6, 5($t2)			# $t6 = 0x000000bc (doesn't sign extend)
	addu $t3, $t3, $t4
	addu $t5, $t5, $t6
	addu $s7, $t3, $t5		# $s3 = 9C
	sb $s7, 1($t2)			# var3[0] = 0x129c5678
	lw $s7, 0($t2)			# $s7 = 0x129c5678 if all is well
	lui $t0, 0x129c			# $t0 = 0x129c5671
	ori $t0,$t0, 0x5671
	sub $s7, $s7, $t0			
	addi $2, $s7, 0			# $2 = 7 if all is well
	jr $0
