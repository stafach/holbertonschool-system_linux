BITS 64

global asm_strchr

section .text

; char *asm_strchr(const char *s, int c);
; 
; Entrée : RDI = s, ESI = c
; Sortie : RAX = &s[i] ou NULL

asm_strchr:			; RDI = s, ESI = c
	xor	rcx, rcx		; i = 0
.loop:
	movzx	eax, byte [rdi + rcx]	; eax = s[i]
	cmp	al, sil			; s[i] == c ?
	je	.found			; oui → on renvoie son adresse
	test	al, al			; s[i] == '\0' ?
	je	.not_found		; oui → c n'est pas dans s
	inc	rcx
	jmp	.loop

.found:
	lea	rax, [rdi + rcx]	; rax = &s[i]
	ret

.not_found:
	xor	eax, eax		; rax = NULL
	ret
