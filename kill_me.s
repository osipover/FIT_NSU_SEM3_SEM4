PiByGregoryLeibniz:
        pushq   %rbp                    #сохраняем указатель кадра,
                                        #вызвавшей подпрограммы

        movq    %rsp, %rbp              #пишем в регистр rbp значение регистра rsp:
                                        #(это будет начала стекового кадры для функции)

        movq    %rdi, -40(%rbp)         #записываем по адресу -40(rbp) значение из %rdi
                                        #это мы добавили в стек значение параметра N,
                                        #передаваемое в качетсве аргумента функции

        movsd   .LC0(%rip), %xmm0       #записываем в регистр сопроцессора xmm0 значение 
                                        #из .LC0(%rip), где у нас хранится 1.0 

        movsd   %xmm0, -8(%rbp)         #добавляем в стек по адресу -8(%rbp) значение 
                                        #из xmm0. В программе на Си это операция 
                                        #pi = 1.0

        movsd   .LC1(%rip), %xmm0       #записываем в xmm0 значение из .LC1(%rip), где
                                        #у нас хранится -1

        movsd   %xmm0, -16(%rbp)        #добавляем в стек по адресу -16(%rbp) значение 
                                        #из xmm0. В программе это pow = -1

        movq    $1, -24(%rbp)           #записываем в стек по адресу -24(%rbp) значение 1.
                                        #в программе это i = 1 в цикле

        jmp     .L2                     #безусловный переход на .L2 (там условие цикла 
                                        #и конец функции)
.L3:
        movq    -24(%rbp), %rax         #записываем в rax значение по адресу
                                        #-24(%rbp). Т.е. дублируем значение i

        addq    %rax, %rax              #выполняем (%rax) += (%rax). В программе на Си
                                        #это операция 2*i

        addq    $1, %rax                #выполняем (%rax) += 1. Этой и предыдущей 
                                        #командой мы реализовали (2*i+1)

        pxor    %xmm1, %xmm1            #обнуление регистра xmm1

        cvtsi2sdq       %rax, %xmm1     #приводим значение в rax к вещестенному и
                                        #записываем в xmm1

        movsd   -16(%rbp), %xmm0        #записываем в xmm0 значение по адресу 
                                        #-16(%rbp). Т.е. дублируем значение pow

        divsd   %xmm1, %xmm0            #выполняем (%xmm0) /= (%xmm1). В программе на Си
                                        #это pow/(2i+1). (2i+1) хранится в xmm1

        movsd   -8(%rbp), %xmm1         #записываем в xmm1 значение из переменной pi

        addsd   %xmm1, %xmm0            #выполняем (%xmm0) += (%xmm1).
                                        #pi += pow/(2*i+1)

        movsd   %xmm0, -8(%rbp)         #возвращаем по адресу -8(%rbp) новое значение
                                        #переменной pi

        movsd   -16(%rbp), %xmm0        #записывыаем в xmm0 значение переменной pow

        movq    .LC2(%rip), %xmm1       #записываем в xmm1 значение из .LC2(%rip),
                                        #где у нас хранится (-1)

        xorpd   %xmm1, %xmm0            #выполняем (%xmm0) ^= (%xmm1)
                                        #этим реализуем умножение
                                        #pow *= (-1)

        movsd   %xmm0, -16(%rbp)        #возвращаем по адресу -16(%rbp) обновленное
                                        #значение pow

        addq    $1, -24(%rbp)           #реализуем ++i
.L2:
        movq    -24(%rbp), %rax         #в rax записываем значение из -24(%rbp), 
                                        #где у нас лежит значение i

        cmpq    -40(%rbp), %rax         #выполняется сравнение значений,
                                        #хранящихся по адресам -40(%rbp) и 
                                        #%rax соответственно (N >= i)

        jle     .L3                     #если условие цикла выполенно, то 
                                        #переходим по .L3 (там тело цикла)

        movsd   -8(%rbp), %xmm1         #дублируем значение pi из -8(%rbp)
                                        #в регистр xmm1

        movsd   .LC3(%rip), %xmm0       #записываем в xmm0 значение из .LC3(%rip),
                                        #где у нас записана 4

        mulsd   %xmm1, %xmm0            #выполняем (%xmm0) *= (*xmm1)
                                        #pi *= 4

        movsd   %xmm0, -8(%rbp)         #возвращаем по адресу -8(%rbp) 
                                        #обновленное значение pi

        movsd   -8(%rbp), %xmm0         #записываем в xmm0 значение pi из 
                                        #-8(%rbp)

        movq    %xmm0, %rax            
        movq    %rax, %xmm0

        popq    %rbp                    #востанавливаем состояние стека и кадра,
                                        #которые были до вызова функции

        ret                             #выходим из подпрограммы (PiByGregoryLeibniz)

.LC4:                                   #здесь хранится строка "%f", которую
                                        #мы используем при вызове printf
        .string "%f"
main:
        pushq   %rbp                    #сохраняем указатель кадра вызвавшей 
                                        #программы

        movq    %rsp, %rbp              #ормируем указатель нашего кадра

        subq    $16, %rsp               #выделяем место в стеке под кадр

        movq    $1000000, -8(%rbp)      #записываем значение 1000000 по адресу 
                                        #-8(%rbp). N = 1000000

        movq    -8(%rbp), %rax          #записываем в rax значение переменной N

        movq    %rax, %rdi              #записываем в rdi значение N. Далее в 
                                        #функции PiByGregoryLeibniz мы берем 
                                        #значение N из этого регистра

        call    PiByGregoryLeibniz      #вызываем подпрограмму PiByGregoryLeibniz

        movq    %xmm0, %rax             #в xmm0 у нас лежит результат работы ф-ии
                                        #PiByGregoryLeibniz, т.е. pi, которое мы
                                        #записываем в rax

        movq    %rax, -16(%rbp)         
        movq    -16(%rbp), %rax
        movq    %rax, %xmm0

        movl    $.LC4, %edi             #записываем в edi строку "%f" из .LC4

        movl    $1, %eax                #записываем в eax значение 1. Это количество
                                        #аргументов, передаваемое ф-ии printf

        call    printf                  #вызываем функции printf

        movl    $0, %eax                #зануляем eax

        leave                           #востанавливаем указатели стека и кадра

        ret                             #возврат из функции main

.LC0:                                   #здесь записано значение 1.0 (double)
        .long   0
        .long   1072693248
.LC1:                                   #здесь записано значение -1 (double)                       
        .long   0
        .long   -1074790400
.LC2:                                   #здесь записано значение -1 (double),
                                        #используемое в цикле: pow *= (-1)
        .long   0
        .long   -2147483648
        .long   0
        .long   0
.LC3:                                   #здесь записано значение 4 (double)
        .long   0
        .long   1074790400
