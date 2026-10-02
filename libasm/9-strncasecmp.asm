BITS 64

global asm_strncasecmp

section .text

; int asm_strncasecmp(const char *s1, const char *s2, size_t n);
;
; Entrée : RDI = s1, RSI = s2, RDX = n
; Sortie : EAX = s1[i] - s2[i] au premier caractère différent,
;          0 si les n premiers caractères sont égaux

asm_strncasecmp:
	movzx	eax, byte [rdi]		; eax = s1[0]
	movzx	r8d, byte [rsi]		; r8d = s2[0]
	test	eax, eax		; s1 vide ?
	je	.end			; oui : différence brute
	test	r8d, r8d		; s2 vide ?
	je	.end			; oui : différence brute

	xor	rcx, rcx		; i = 0

.loop:
	cmp	rcx, rdx		; i >= n ?
	jae	.equal			; oui : n caractères comparés → 0
	movzx	eax, byte [rdi + rcx]	; eax = s1[i]
	movzx	r8d, byte [rsi + rcx]	; r8d = s2[i]

	; --- s1[i] en minuscule ---
	cmp	eax, 'A'
	jb	.s1_ok
	cmp	eax, 'Z'
	ja	.s1_ok
	add	eax, 32
.s1_ok:

	; --- s2[i] en minuscule ---
	cmp	r8d, 'A'
	jb	.s2_ok
	cmp	r8d, 'Z'
	ja	.s2_ok
	add	r8d, 32
.s2_ok:

	cmp	eax, r8d		; s1[i] == s2[i] ?
	jne	.end
	test	eax, eax		; fin des deux chaînes ?
	je	.end
	inc	rcx
	jmp	.loop

.end:
	sub	eax, r8d		; eax = s1[i] - s2[i]
	ret

.equal:
	xor	eax, eax		; eax = 0
	ret
