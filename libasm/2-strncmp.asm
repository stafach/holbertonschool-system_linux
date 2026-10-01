BITS 64

global asm_strncmp

section .text

; int asm_strncmp(const char *s1, const char *s2, size_t n);
;
; Entrée : RDI = s1, RSI = s2, RDX = n
; Sortie : EAX = s1[i] - s2[i] au premier caractère différent,
;          0 si les n premiers caractères sont égaux

asm_strncmp:
	xor	rcx, rcx		; i = 0

.loop:
	cmp	rcx, rdx		; i >= n ?
	jae	.equal			; oui : n caractères comparés → 0
	movzx	eax, byte [rdi + rcx]	; eax = s1[i]
	movzx	r8d, byte [rsi + rcx]	; r8d = s2[i]
	cmp	eax, r8d		; s1[i] == s2[i] ?
	jne	.end			; non : différence trouvée
	test	eax, eax		; s1[i] == '\0' ?
	je	.end			; oui : les deux chaînes sont finies
	inc	rcx			; i++
	jmp	.loop

.end:
	sub	eax, r8d		; eax = s1[i] - s2[i]
	ret

.equal:
	xor	eax, eax		; eax = 0
	ret
