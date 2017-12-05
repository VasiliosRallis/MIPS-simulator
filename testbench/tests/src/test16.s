.set noat
.set noreorder

start:
addi $3, $3, -1
sll $3, $3, 16
slti $2, $3, -1
jr $0
nop
nop
