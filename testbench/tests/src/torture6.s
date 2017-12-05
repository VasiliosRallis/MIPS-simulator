.set noat
.set noreorder

b_top:	add $s5,$0,$0			# clear $s5
	beq $s5,$0,b_skip1		# if $s5 = 0 goto b_skip1
	nop
b_bad1:	addi $s5,$s5,7			# should not happen!
b_skip1:addi $s5,$s5,1			# $s5 = 1 now if all is well
	addi $t0,$0,-1			# $t0 = -1
	bgez $t0,b_skip2		# if $t0 >= 0 goto b_skip2 (it isn't!)
	nop
b_good1:addi $s5,$s5,-10		# should do this!
b_skip2:addi $s5,$s5,11			# $s5 = 2 now if all is well
	bltz $t0,b_skip3		# if $t0 < 0 goto b_skip 3 (it is!)
	nop
b_bad2:	addi $s5,$s5,13			# should not happen!
b_skip3:addi $s5,$s5,1			# $s5 = 3 now if all is well
	add  $t1,$0,$0			# clear $t1
	blez $t1,b_skip4		# if $t1 <= 0 goto b_skip4 (it is!)
	nop
	addi $s5,$s5,17			# should not happen!
b_skip4:bgtz $t1,b_skip5		# if $t1 > 0 goto b_skip5 (it isn't!)
	nop
	addi $s5,$s5,-14		# should do this!
b_skip5:addi $s5,$s5,16			
	addi $2,$s5,0			# $2 = 5 now if all is well
	jr $0
