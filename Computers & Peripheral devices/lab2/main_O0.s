PiByGregoryLeibniz: //PiByGregoryLeibniz (до цикла) 
        pushq   %rbp                //создаем стековый кадр
        movq    %rsp, %rbp			
        movq    %rdi, -40(%rbp)     //Кладем на стек аргумент N
        movsd   .LC0(%rip), %xmm0   //double pi = 1.0
        movsd   %xmm0, -8(%rbp)     //pi: -8(%rbp)
        movsd   .LC1(%rip), %xmm0   //double pow = -1
        movsd   %xmm0, -16(%rbp)    //pow: -16(%rbp)		
        movq    $1, -24(%rbp)       //i = 1: -24(%rbp)
        jmp     .L2                 //Переходим к циклу

.L3: //Здесь реализовано тело цикла
//Этот блок реализует pi += pow/(2*i + 1)
        movq    -24(%rbp), %rax
        addq    %rax, %rax
        addq    $1, %rax
        pxor    %xmm1, %xmm1
        cvtsi2sdq       %rax, %xmm1
        movsd   -16(%rbp), %xmm0
        divsd   %xmm1, %xmm0
        movsd   -8(%rbp), %xmm1
        addsd   %xmm1, %xmm0
//Этот блок реализует pow *= (-1)
        movsd   %xmm0, -8(%rbp)
        movsd   -16(%rbp), %xmm0
        movq    .LC2(%rip), %xmm1
        xorpd   %xmm1, %xmm0
        movsd   %xmm0, -16(%rbp)

        addq    $1, -24(%rbp)        //++i

.L2: //Условие цикла for и конец функции PiByGregoryLeibniz
//Условие цикла for
        movq    -24(%rbp), %rax
        cmpq    -40(%rbp), %rax
        jle     .L3                 //в случае истинности cmpq переходим к телу цикла
//Этот блок реализует pi *= 4
        movsd   -8(%rbp), %xmm1
        movsd   .LC3(%rip), %xmm0
        mulsd   %xmm1, %xmm0
        movsd   %xmm0, -8(%rbp)
//Этот блок реализует выход из функции PiByGregoryLeibniz
        movsd   -8(%rbp), %xmm0	
        movq    %xmm0, %rax
        movq    %rax, %xmm0
        popq    %rbp
        ret

.LC4:
        .string "Pi: %f\n"
.LC6:
        .string "Time taken by clock_gettime: %lf sec.\n"

TestClockGettime: 
//Создание стекового кадра
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $64, %rsp
        movq    %rdi, -56(%rbp)		  //N: -56(%rbp)
//Этот блок реализует вызов clock_gettime для start
        leaq    -32(%rbp), %rax		  //start: -32(%rbp)
        movq    %rax, %rsi
        movl    $4, %edi
        call    clock_gettime
//Этот блок отвечает за вызов функции PiByGregoryLeibniz
        movq    -56(%rbp), %rax
        movq    %rax, %rdi
        call    PiByGregoryLeibniz
        movq    %xmm0, %rax
        movq    %rax, -8(%rbp)		  //pi: -8(%rbp)
//Этот блок реализует вызов clock_gettime для end
        leaq    -48(%rbp), %rax		  //end: -48(%rbp)		
        movq    %rax, %rsi
        movl    $4, %edi
        call    clock_gettime
//Этот блок отвечает за вызов printf для pi
        movq    -8(%rbp), %rax
        movq    %rax, %xmm0
        movl    $.LC4, %edi
        movl    $1, %eax
        call    printf
//Этот блок отвечает за вызов printf для вывода времени
// Реализуем end.tv_sec - start.tv_sec 
        movq    -48(%rbp), %rdx
        movq    -32(%rbp), %rax
        subq    %rax, %rdx

        pxor    %xmm1, %xmm1
        cvtsi2sdq       %rdx, %xmm1
// Реализуем end.tv_nsec - start.tv_nsec
        movq    -40(%rbp), %rdx
        movq    -24(%rbp), %rax
        subq    %rax, %rdx
        pxor    %xmm2, %xmm2
        cvtsi2sdq       %rdx, %xmm2
//Реализуем 0.000000001*(end.tv_nsec - start.tv_nsec)
        movsd   .LC5(%rip), %xmm0
        mulsd   %xmm2, %xmm0
//Реализуем end.tv_sec - start.tv_sec + 0.000000001*(end.tv_nsec - start.tv_nsec)
        addsd   %xmm0, %xmm1
        movq    %xmm1, %rax
//Вызываем printf
        movq    %rax, %xmm0
        movl    $.LC6, %edi
        movl    $1, %eax
        call    printf
//Выходим из функции
        nop
        leave
        ret

main:
//Выделяем стековый кадр
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $32, %rsp
//Кладем аргументы main в стек
        movl    %edi, -20(%rbp)
        movq    %rsi, -32(%rbp)

        movq    $0, -8(%rbp)		     //N = 0: -8(%rbp)
//Этот блок отвечает за вызов atoll
        movq    -32(%rbp), %rax
        addq    $8, %rax
        movq    (%rax), %rax
        movq    %rax, %rdi
        call    atoll
        movq    %rax, -8(%rbp)		  //N: -8(%rbp)
//Этот блок отвечает за вызов подпрограммы ClockGettime
        movq    -8(%rbp), %rax
        movq    %rax, %rdi
        call    TestClockGettime
//Выходим из функции
        movl    $0, %eax
        leave
        ret

.LC0: //double 1
        .long   0
        .long   1072693248

.LC1: //double -1
        .long   0
        .long   -1074790400

.LC2:	//double -1
        .long   0
        .long   -2147483648
        .long   0
        .long   0

.LC3:	//double 4
        .long   0
        .long   1074790400
.LC5:	//double 0.000000001
        .long   -400107883
        .long   1041313291
