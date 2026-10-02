BITS 64

global asm_strcasecmp

section .text

; int asm_strcasecmp(const char *s1, const char *s2);
;
; Entrée : RDI = s1, RSI = s2
; Sortie : EAX = différence entre les premiers caractères différents,
;          après passage en minuscule (0 si les chaînes sont égales)

asm_strcasecmp:
	xor	rcx, rcx		; i = 0

.loop:
	movzx	eax, byte [rdi + rcx]	; eax = s1[i]
	movzx	r8d, byte [rsi + rcx]	; r8d = s2[i]

	; --- s1[i] en minuscule ---
	cmp	eax, 'A'
	jb	.s1_ok			; < 'A' : pas une majuscule
	cmp	eax, 'Z'
	ja	.s1_ok			; > 'Z' : pas une majuscule
	add	eax, 32			; 'A'..'Z' → 'a'..'z'
.s1_ok:

	; --- s2[i] en minuscule ---
	cmp	r8d, 'A'
	jb	.s2_ok
	cmp	r8d, 'Z'
	ja	.s2_ok
	add	r8d, 32
.s2_ok:

	; --- comparaison, comme dans strcmp ---
	cmp	eax, r8d		; s1[i] == s2[i] ?
	jne	.end			; non : différence trouvée
	test	eax, eax		; s1[i] == '\0' ?
	je	.end			; oui : les deux chaînes sont finies
	inc	rcx			; i++
	jmp	.loop

.end:
	sub	eax, r8d		; eax = s1[i] - s2[i] (en minuscules)
	ret
