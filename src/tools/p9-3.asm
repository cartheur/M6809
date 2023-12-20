*  running code using 10ms tick

tick    equ $700e

	org $200

main    lda #0
        tfr a,dp     set page 0

	cwai #%11101111 enable IRQ 

loop  lda tick
	cmpa #100
	bne skip
	clr tick
 
        inc 0
	lda 0
	sta $8000

skip    bra loop

	end

