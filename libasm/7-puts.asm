BITS 64

global asm_puts
extern asm_strlen

section .text

; size_t asm_puts(const char *str);
;
; Entrée : RDI = str
; Sortie : RAX = nombre d'octets écrits

asm_puts:
	push	rbx		; RBX doit être préservé : on sauve sa valeur
	mov	rbx, rdi	; met str à l'abri avant le call
	call	asm_strlen	; RAX = longueur de str
	mov	rdx, rax	; count = longueur  (AVANT d'écraser RAX)
	mov	rsi, rbx	; buf = adresse de str
	mov	edi, 1		; fd = stdout
	mov	eax, 1		; syscall n°1 = write
	syscall			; RAX = octets écrits
	pop	rbx		; rend sa valeur à RBX
	ret
