.set noat
.set noreorder

start:
addi $2, $2, 2
sll $2, $2, 28
addi $3, $3, 1
sll $3, $3, 7
sw $3, 0($2)
lb $2, 3($2)
srl $2, $2, 7
jr $0
nop
nop
