.data

msg:
	.ascii "Hello world\n"
	len = . - msg

.text
	.global _start

_start:
	movq $4, %rax	 	# 4 - номер write в таблице системных вызовов
	movq $1, %rbx	 	# 1 - номер потока вывода
	movq $msg, %rcx
	movq $len, %rdx
	int $0x80

	movq $1, %rax		# 1 - номер exit в таблице системных вызовов
	xorq %rdi, %rdi
	int $0x80

