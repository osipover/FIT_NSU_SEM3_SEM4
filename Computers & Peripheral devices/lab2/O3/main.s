PiByGregoryLeibniz:
        testq   %rdi, %rdi 			        //N: %rdi
        jle     .L4				        //если N==1, то переходим по .L4
        movsd   .LC0(%rip), %xmm1		        //pow = -1: %xmm1
        leaq    3(%rdi,%rdi), %rdx	                //N: %rdx
        movl    $3, %eax			
        movsd   .LC1(%rip), %xmm0		        //pi = 1.0: %xmm0
        movq    .LC3(%rip), %xmm4
.L3:  
//В этом блоке реализован цикл в функции PiByGregoryLeibniz
        pxor    %xmm3, %xmm3		                //(%xmm3) = 0
        movapd  %xmm1, %xmm2		                //pow: %xmm2
        xorpd   %xmm4, %xmm1		
        cvtsi2sdq       %rax, %xmm3
        addq    $2, %rax			
        divsd   %xmm3, %xmm2		                //pow /= (2*i+1)
        addsd   %xmm2, %xmm0		                //pi += pow/(2*i+1)
        cmpq    %rax, %rdx
        jne     .L3
//Выход из функции
        mulsd   .LC2(%rip), %xmm0
        ret
.L4:
        movsd   .LC2(%rip), %xmm0
        ret

.LC4:
        .string "Pi: %f\n"
.LC6:
        .string "Time taken by clock_gettime: %lf sec.\n"

TestClockGettime:
        pushq   %rbx				
        movq    %rdi, %rbx			        //N: %rbx
        movl    $4, %edi
        subq    $48, %rsp
        leaq    16(%rsp), %rsi		                 //start: 16(%rsp)
        call    clock_gettime
        testq   %rbx, %rbx			
        jle     .L10				        //если N==1, то переходим в .L10
//Ниже представлен тот же набор команд, что и функции PiByGregoryLeibniz
  movsd   .LC1(%rip), %xmm0		
        leaq    3(%rbx,%rbx), %rdx
        movl    $3, %eax
        movsd   .LC0(%rip), %xmm1
        movq    .LC3(%rip), %xmm4

.L9:	
//Цикл, аналогичный циклу в PiByGregoryLeibniz
        pxor    %xmm3, %xmm3
        movapd  %xmm1, %xmm2
        xorpd   %xmm4, %xmm1
        cvtsi2sdq       %rax, %xmm3
        addq    $2, %rax
        divsd   %xmm3, %xmm2
        addsd   %xmm2, %xmm0
        cmpq    %rax, %rdx
        jne     .L9
//Выход из цикла
        mulsd   .LC2(%rip), %xmm0

.L8:	
//Этот блок отвечает за вызов функции clock_gettime
        leaq    32(%rsp), %rsi		                //end: 32(%rsp)
        movl    $4, %edi
        movsd   %xmm0, 8(%rsp)
        call    clock_gettime
//Работа команды printf для Pi
        movsd   8(%rsp), %xmm0		                //pi: %xmm0
        movl    $.LC4, %edi
        movl    $1, %eax
        call    printf
//Реализуем (end.tv_nsec - start.tv_nsec)
        movq    40(%rsp), %rax		                //end.tv_nsec: 40(%rsp)
        pxor    %xmm0, %xmm0
        subq    24(%rsp), %rax		                //start.tv_nsec: 24(%rsp)
        cvtsi2sdq       %rax, %xmm0
//Реализуем (end.tv_sec - start.tv_sec)
        pxor    %xmm1, %xmm1
        movq    32(%rsp), %rax		                //end.tv_sec: 32(%rsp)
        subq    16(%rsp), %rax		                //start.tv_sec: 16(%rsp)
//Реализуем 0.000000001*(end.tv_nsec - start.tv_nsec)
        mulsd   .LC5(%rip), %xmm0
//Реализуем end.tv_sec - start.tv_sec + 0.000000001*(end.tv_nsec - start.tv_nsec)
        cvtsi2sdq	%rax, %xmm1
        movl    $.LC6, %edi
        movl    $1, %eax
        addsd   %xmm1, %xmm0
        call    printf
//Выходим из функции TestClockGettime
        addq    $48, %rsp			
        popq    %rbx
        ret

.L10:	//Условный переход, если N==1
        movsd   .LC2(%rip), %xmm0 	                //pi = 4: %xmm0
        jmp     .L8

main:
        subq    $8, %rsp
//Преобразование строки в long long int
        movq    8(%rsi), %rdi
        movl    $10, %edx
        xorl    %esi, %esi
        call    strtoll
        movq    %rax, %rdi

        call    TestClockGettime

        xorl    %eax, %eax
        addq    $8, %rsp
        ret


.LC0:	double -1
        .long   0
        .long   -1074790400

.LC1:	//double 1
        .long   0
        .long   1072693248

.LC2:	//double 4
        .long   0
        .long   1074790400

.LC3:
        .long   0
        .long   -2147483648
        .long   0
        .long   0

.LC5:	//double 0.000000001
        .long   -400107883
        .long   1041313291
