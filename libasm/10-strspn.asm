BITS 64

global asm_strspn

section .text

; size_t asm_strspn(const char *s, const char *accept);
;
; Entrée : RDI = s, RSI = accept
; Sortie : Nombre de char de accept dans s

asm_strspn:
	xor rcx, rcx	; i = 0

.outer:
	xor	rdx, rdx					; j = 0
	xor	r8, r8						; count = 0
	inc r8							; count ++

.first_loop:
	movzx	eax, byte [rdi + rcx]	; eax = s[i]
	movzx	edx, byte [rsi + rdx]	; edx = accept[j]
	test	eax, eax				; s[i] == '\0' ?
	je	.end						; oui : fin
	test	edx, edx				; accept[j] == '\0'?
	je	.first_char					; oui : vérification si premier char de s ou non
	cmp	eax, edx					; s[i] == accept[j] ?
	je	.second_loop				; oui : prochain char de s
	inc	rdx							; j++
	jmp	.first_loop

.first_char:
	cmp	rcx, 0						; i == 0 ?
	je	.null						; oui : fin
	jmp	.second_loop				; sinon : prochain char de s1

.second_loop:
	inc	rcx							; i++
	jmp .outer						; retour à j == 0

.end:
	mov	rax, r8
	sub	rax, 1						; Return count - 1
	ret

.null:
	xor	eax, eax		; renvoie NULL
	ret
	