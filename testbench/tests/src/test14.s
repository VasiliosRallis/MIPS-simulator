.set noat
.set noreorder

addi $3, $3, 1
sll $3, $3, 29
addi $4, $4, 1
sll $4, $4, 15
sw $4, 0($3)
lhu $2, 2($3)
srl $2, $2, 15
jr $0
