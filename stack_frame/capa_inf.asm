global conversion
section .text

conversion:
    push ebp
    mov ebp, esp

    sub esp, 4             
    fld dword [ebp+8]      
    fistp dword [ebp-4]    

    mov eax, [ebp-4]       
    add eax, 1      
           
    mov esp, ebp
    pop ebp
    ret
