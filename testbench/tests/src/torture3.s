.set noat
.set noreorder

	lui $t0,0x7654			# $t0 = 0x76543210
	ori $t0, $t0, 0x3210
	lui $t1, 0x2000			# $t1 = &var1 (pointer to var1)
	sw $t0,0($t1)			# var1 = $t0
	lui $t2, 0x1234			# $t2 = 0x12345678
	ori $t2, $t2, 0x5678
	lui $t3, 0x2000			# $t3 = &var2
	addi $t3, $t3, 4
	sw $t2,0($t3)			# var2 = $t3
	# now retrieve the two numbers and add them
	lw $t4, 0($t1)			# $t4 = var1
	lw $t5, 0($t3)			# $t5 = var2
	addu $s2, $t4, $t5		# $s2 = $t4 + $t5
	lui $t7, 0x8888			# $t7 = 0x88888886
	ori $t7, $t7, 0x8886
	sub $s2, $s2, $t7		
	add $2, $s2, 0			#   if correct, set $2 = 2
	jr $0
