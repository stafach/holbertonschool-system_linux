BITS 64

global asm_strstr

section .text

; char *asm_strstr(const char *haystack, const char *needle);
;
; Entrée : RDI = haystack, RSI = needle
; Sortie : RAX = adresse de la 1re occurrence de needle dans haystack,
;          ou NULL (0) si needle n'est pas trouvé

asm_strstr:
	xor	rcx, rcx		; i = 0

.outer:
	lea	r9, [rdi + rcx]		; p = &haystack[i]
	xor	rdx, rdx		; j = 0

.inner:
	movzx	r8d, byte [rsi + rdx]	; r8d = needle[j]
	test	r8d, r8d		; needle[j] == '\0' ?
	je	.found			; oui : tout needle a collé
	movzx	eax, byte [r9 + rdx]	; eax = p[j]
	cmp	eax, r8d		; p[j] == needle[j] ?
	jne	.next			; non : on essaie la position suivante
	inc	rdx			; j++
	jmp	.inner

.next:
	cmp	byte [r9], 0		; haystack[i] == '\0' ?
	je	.not_found		; oui : plus rien à essayer
	inc	rcx			; i++
	jmp	.outer

.found:
	mov	rax, r9			; renvoie p = &haystack[i]
	ret

.not_found:
	xor	eax, eax		; renvoie NULL
	ret
