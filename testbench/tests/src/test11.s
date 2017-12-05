.set noat
.set noreorder

start:
bgezal $0, start + 4
lb $2, 3($31)
jr $0
