.set noat
.set noreorder

	add $s6, $0, $0			# clear $s6
	addi $t0, $0, -10			# $t0 = -10 ( = 0xFFFFFFF6)
	addi $t1, $0, 20			# $t1 = 20
	slt $t2, $t0, $t1			# $t2 = 1 if $t0 < $t1 (it is!)
	add $s6, $s6, $t2			# $s6 = 1 now if all is well
	sltu $t3, $t0, $t1		# $t3 = 1 if $t0 < $t1 unsigned (not!)
	add $s6, $s6, $t3			# $s6 = 1 still if all is well
	slti $t4, $t0, -5			# $t4 = 1 if $t0 < -5 (it is!)
	add $s6, $s6, $t4			# $s6 = 2 now if all is well
	add $s6, $s6, $s6
	sltiu $t5, $t0, -5		# $t5 = 1 if $t0 < -5 unsigned (yes!)
					# sltiu sign-extends but then compares
					# as unsigned; 0xFF..F6 is < 0xFF..FB
	add $s6, $s6, $t5			# $s6 = 5 still if all is well
	add $s6, $s6, 1			
	addi $2, $s6, 0			# $2 = 6 if all is well
	jr $0
