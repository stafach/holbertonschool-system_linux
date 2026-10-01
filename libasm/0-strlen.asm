BITS 64

global asm_strlen		; rend asm_strlen visible pour le main en C

section .text

; size_t asm_strlen(const char *str);
;
; Entrée : RDI = str (adresse du premier caractère)
; Sortie : RAX = nombre de caractères avant le '\0'
asm_strlen:
	xor	rax, rax		; compteur = 0

.loop:
	cmp	byte [rdi + rax], 0	; str[compteur] == '\0' ?
	je	.end			; oui : on a fini
	inc	rax			; non : compteur++
	jmp	.loop			; caractère suivant

.end:
	ret				; la longueur est déjà dans RAX
