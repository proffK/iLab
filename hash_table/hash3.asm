[bits 64]
global hash3 

hash3: 
        xor rax, rax
        push rbx
        xor bl, bl 
        cmp [rdi], bl
        jne check2
        pop rbx
        ret
check2:
        cmp [rdi + 1], bl
        jne recursion
        mov al, [rdi]
        pop rbx
        ret
recursion:
        push rdi
        inc rdi
        call hash3
        pop rdi
        rol rax, 1
        xor al, [rdi]
        pop rbx
        ret
