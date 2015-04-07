  400d2f:       55                      push   rbp
  400d30:       48 89 e5                mov    rbp,rsp
  400d33:       53                      push   rbx
  400d34:       48 83 ec 18             sub    rsp,0x18
  400d38:       e8 93 fc ff ff          call   4009d0 <mcount@plt>
  400d3d:       48 89 7d e8             mov    QWORD PTR [rbp-0x18],rdi
  400d41:       bb 00 00 00 00          mov    ebx,0x0
  400d46:       48 8b 45 e8             mov    rax,QWORD PTR [rbp-0x18]
  400d4a:       0f b6 00                movzx  eax,BYTE PTR [rax]
  400d4d:       84 c0                   test   al,al
  400d4f:       75 07                   jne    400d58 <hash3+0x29>
  400d51:       b8 00 00 00 00          mov    eax,0x0
  400d56:       eb 3c                   jmp    400d94 <hash3+0x65>
  400d58:       48 8b 45 e8             mov    rax,QWORD PTR [rbp-0x18]
  400d5c:       48 83 c0 01             add    rax,0x1
  400d60:       0f b6 00                movzx  eax,BYTE PTR [rax]
  400d63:       84 c0                   test   al,al
  400d65:       75 0c                   jne    400d73 <hash3+0x44>
  400d67:       48 8b 45 e8             mov    rax,QWORD PTR [rbp-0x18]
  400d6b:       0f b6 00                movzx  eax,BYTE PTR [rax]
  400d6e:       0f b6 c0                movzx  eax,al
  400d71:       eb 21                   jmp    400d94 <hash3+0x65>
  400d73:       48 8b 45 e8             mov    rax,QWORD PTR [rbp-0x18]
  400d77:       48 83 c0 01             add    rax,0x1
  400d7b:       48 89 c7                mov    rdi,rax
  400d7e:       e8 ac ff ff ff          call   400d2f <hash3>
  400d83:       89 c3                   mov    ebx,eax
  400d85:       8d 14 1b                lea    edx,[rbx+rbx*1]
  400d88:       48 8b 45 e8             mov    rax,QWORD PTR [rbp-0x18]
  400d8c:       0f b6 00                movzx  eax,BYTE PTR [rax]
  400d8f:       0f b6 c0                movzx  eax,al
  400d92:       31 d0                   xor    eax,edx
  400d94:       48 83 c4 18             add    rsp,0x18
  400d98:       5b                      pop    rbx
  400d99:       5d                      pop    rbp
  400d9a:       c3                      ret  