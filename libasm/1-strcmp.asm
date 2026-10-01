BITS 64

global asm_strcmp

section .text

; int asm_strcmp(const char *s1, const char *s2);
;
; Entrée : RDI = s1, RSI = s2
; Sortie : EAX = s1[i] - s2[i] au premier caractère différent (0 si égales)

asm_strcmp:
	xor	rcx, rcx		; compteur i = 0 (RCX, pas RAX)

.loop:
	movzx	eax, byte [rdi + rcx]	; eax = s1[i]
	movzx	edx, byte [rsi + rcx]	; edx = s2[i]
	cmp	eax, edx		; s1[i] == s2[i] ?
	jne	.end			; non : on a trouvé une différence
	test	eax, eax		; s1[i] == '\0' ? (donc s2[i] aussi)
	je	.end			; oui : les deux chaînes sont finies
	inc	rcx			; i++
	jmp	.loop

.end:
	sub	eax, edx		; eax = s1[i] - s2[i]
	ret
