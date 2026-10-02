BITS 64

global asm_memcpy

section .text

; void *asm_memcpy(void *dest, const void *src, size_t n);
;
; Entrée : RDI = dest, RSI = src, RDX = n
; Sortie : RAX = dest

asm_memcpy:
	mov	rax, rdi		; la valeur de retour est dest
	xor	r10, r10		; i = 0

.loop:
	cmp	r10, rdx		; i >= n ?
	jae	.end			; oui : n octets copiés
	mov	r8b, byte [rsi + r10]	; r8b = src[i]
	mov	byte [rdi + r10], r8b	; dest[i] = r8b
	inc	r10			; i++
	jmp	.loop

.end:
	ret
