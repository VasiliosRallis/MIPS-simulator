.set noat
.set noreorder

add $1,$0,$0
addi $1,$1,255
addi $1,$1,-240
addiu $3,$0,15
mult $3,$1
mflo $4
mfhi $5
add $6,$5,$4
li $3,0x4FFFFFFF
mult $6,$3
mflo $3
mfhi $4
add $6,$4,$3
li $1,0x4FFFFF62
subu $6,$6,$1
addi $2,$6,0
jr $0			# $2 = 3
