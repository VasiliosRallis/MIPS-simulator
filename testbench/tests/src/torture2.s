.set noat
.set noreorder

	lui $t0,0x5555			# $t0 = 0x55555555
	ori $t0,$t0,0x5555
	lui $t1,0x0000			# $t1 = 0x00000000
	ori $t1,$t1,0x0000			
	lui $t2,0xCCCC			# $t2 = 0xCCCCCCCC
	ori $t2,$t2,0xCCCC
	or  $t0,$t2,$t0			# $t0 OR $t2  = 0xDDDDDDDD
	lui $t3,0x3333			# $t3 = 0x33333333
	ori $t3,$t3,0x3333
	and $t0,$t3,$t0			# $t0 AND $t3 = 0x11111111
	sll $t0,$t0,2			# $t0 = 0x44444444
	sra $t0,$t0,1			# $t0 = 0x22222222
	srl $t0,$t0,1			# $t0 = 0x11111111
	sll $t0,$t0,3			# $t0 = 0x88888888
	sra $t0,$t0,1			# $t0 = 0xC4444444
	lui $t7,0xC444			# $t7 = 0xC4444445
	ori $t7,$t7,0x4445
	xor $s1,$t0,$t7			
	addi $2,$s1,0			#   if correct, set $2 = 1
	jr $0
