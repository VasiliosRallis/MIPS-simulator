.set noat
.set noreorder

lui $1,0x1234
ori $1, 0x5678
lui $3,0x9abc
ori $3,$3,0xdef0
lui $4,0x2000
sw $1, 0($4)
sw $3, 4($4)
lb $5, 0($4)
lb $6, 1($4)
lb $7, 4($4)
lbu $8, 5($4)
addu $5,$5,$6
addu $7,$7,$8
sb $9,1($4)
lw $9,0($4)
lui $1,0x129C
ori $1,$1,0x5671
sub $9,$9,$1
addi $2,$9,0
jr $0			# $2 = 7 is the result
