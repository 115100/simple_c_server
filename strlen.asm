; usage:
; size_t strlen(const char *s);
; x64-specific

section .text
	global strlen

strlen:
	push rbp
	mov rbp, rsp
	xor rax, rax ; clear retval register

_loop:
	cmp byte [rdi], 0 ; deref s
	je _end
	inc rdi
	inc rax
	jmp _loop

_end:
	pop rbp
	ret
