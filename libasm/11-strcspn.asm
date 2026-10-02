BITS 64

global asm_strcspn

section .text

; size_t asm_strcspn(const char *s, const char *reject);
;
; Entrée : RDI = s, RSI = reject
; Sortie : RAX = nombre de caractères au début de s qui sont tous dans reject

asm_strcspn:
	xor	rcx, rcx		; i = 0

.outer:
	movzx	eax, byte [rdi + rcx]	; eax = s[i]
	test	eax, eax		; s[i] == '\0' ?
	je	.end			; oui : toute la chaîne est bonne → renvoie i
	xor	rdx, rdx		; j = 0

.inner:
	movzx	r8d, byte [rsi + rdx]	; r8d = reject[j]   (R8D, pas EDX !)
	test	r8d, r8d		; fin de reject ?
	je	.end			; oui : s[i] n'est pas dans reject → renvoie i
	cmp	eax, r8d		; s[i] == reject[j] ?
	je	.end			; oui : s[i] est autorisé → caractère suivant
	inc	rdx			; j++
	jmp	.inner

.next:
	inc	rcx			; i++
	jmp	.outer

.end:
	mov	rax, rcx		; renvoie i
	ret
