.set noat
.set noreorder

	lui $3,0
	ori $3,$3,0
	lui $1,21845
	ori $1,$1,21845
	lui $4,52428
	ori $4,$4,52428
	or $1,$4,$1
	lui $5,13107
	ori $5,$5,13107
	and $1,$5,$1
	sll $1,$1,2
	sra $1,$1,1
	srl $1,$1,1
	sll $1,$1,3
	sra $1,$1,1
	lui $8,50244
	ori $8,$8,17477
	xor $10,$1,$8
	addi $2,$10,0		# $2 = 1 is the result
	jr $0
