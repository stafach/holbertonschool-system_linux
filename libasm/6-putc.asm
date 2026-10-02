BITS 64

global asm_putc

section .text

; size_t asm_putc(int c);
;
; Entrée : RDI = c
; Sortie : Total number of bytes written

asm_putc:
	push rdi		; envoi c sur la pile
	mov eax, 1		; 1 = write pour syscall
	mov edi, 1		; 1 = stdout
	mov rsi, rsp	; met l'adress de c dans buf
	mov edx, 1		; n = 1 octet
	syscall			; appel de write
	pop rdi			; nettoie la pile
	ret
