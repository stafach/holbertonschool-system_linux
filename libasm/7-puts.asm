BITS 64

global asm_puts
extern asm_strlen

section .text

; size_t asm_puts(const char *str);
;
; Entrée : RDI = str
; Sortie : Total number of bytes written

asm_puts:
	call asm_strlen ; RAX = len de str
	push rdi		; envoi c sur la pile
	mov eax, 1		; 1 = write pour syscall
	mov edi, 1		; 1 = stdout
	mov rsi, rsp	; met l'adress de c dans buf
	mov edx, rax	; n = RAX
	syscall			; appel de write
	pop rdi			; nettoie la pile
	ret
