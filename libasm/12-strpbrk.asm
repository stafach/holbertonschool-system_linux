BITS 64

global asm_strpbrk

section .text

; char *asm_strpbrk(const char *s, const char *accept);
;
; Entrée : RDI = s, RSI = accept
; Sortie : RAX = nombre de caractères au début de s qui sont tous dans accept

asm_strpbrk:
	xor	rcx, rcx		; i = 0

.outer:
	lea	r9, [rdi + rcx]		; p = &s[i]
	test	r9, r9		; s[i] == '\0' ?
	je	.null			; oui : aucune occurrence trouvée
	xor	rdx, rdx		; j = 0

.inner:
	movzx	r8d, byte [rsi + rdx]	; r8d = accept[j]   (R8D, pas EDX !)
	test	r8d, r8d		; fin de accept ?
	je	.next			; oui : s[i] n'est pas dans accept → next
	cmp	eax, r8d		; s[i] == accept[j] ?
	je	.end			; oui : return &s[i]
	inc	rdx			; j++
	jmp	.inner

.next:
	inc	rcx			; i++
	jmp	.outer

.end:
	mov	rax, r9		; renvoie i
	ret

.null:
	xor	eax, eax		; renvoie NULL
	ret
