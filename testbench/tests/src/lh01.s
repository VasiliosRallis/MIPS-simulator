.set noreorder

start:
	li $t1, 0x20000000
	li $t2, 0x00000001
	sw $t2, 0($t1)
	lh $v0, 2($t1)
	jr $zero
	nop

