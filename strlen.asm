; usage:
; size_t strlen(const char *s);
; x64-specific

section .text
	global strlen

strlen:
	xor rax, rax ; clear retval register
	mov rcx, -1 ; set rcx to ...111
	repne scasb ; compare [rdi] to AL (...000), dec rax each loop and inc rdi
	not rcx ; reverse bits
	dec rcx ; remove count of null byte
	mov rax, rcx ; put length into retval
	ret
