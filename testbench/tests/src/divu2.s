.set noreorder
.set noat

li $3,0xFFFFFFFF
li $4,0xFFFFFFFF
divu $3,$4
mflo $2
jr $0
nop			#return 1
