.set noat
.set noreorder

hello:
bgezal $0, hello + 4
add $2, $2, $31
jr $0
