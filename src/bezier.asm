    section .text
    global _bezier

_bezier:
    push rbp
    mov rbp, rsp

    mov     QWORD [rbp - 8], rdi      ; store buffer address
    mov     DWORD [rbp - 12], esi     ; store width
    mov     DWORD [rbp - 16], edx     ; store height
    mov     QWORD [rbp - 24], rcx     ; store points buffer

    xorps    xmm0, xmm0          ; reset register

_bezier_calculate_x:
    mov     rax, QWORD [rbp - 24]     ; get points buffer address

    mov         edx, DWORD [rax]        ; load x1
    cvtsi2ss    xmm1, edx               ; convert to double

    mov         edx, DWORD [rax + 8]    ; load x2
    cvtsi2ss    xmm2, edx               ; convert to double

    ; lerp(1, 2)
    subss   xmm2, xmm1             ; sub x1
    mulss   xmm2, xmm0             ; mul t
    addss   xmm2, xmm1             ; add x1

    mov         edx, DWORD [rax + 16]   ; load x3
    cvtsi2ss    xmm3, edx               ; convert to double

    ; lerp(2, 3)
    subss   xmm3, xmm2             ; sub x2
    mulss   xmm3, xmm0             ; mul t
    addss   xmm3, xmm2             ; add x2

    mov         edx, DWORD [rax + 24]   ; load x4
    cvtsi2ss    xmm4, edx               ; convert to double

    ; lerp(3, 4)
    subss   xmm4, xmm3             ; sub x3
    mulss   xmm4, xmm0             ; mul t
    addss   xmm4, xmm3             ; add x3

    mov         edx, DWORD [rax + 32]   ; load x5
    cvtsi2ss    xmm5, edx               ; convert to double

    ; lerp(4, 5)
    subss   xmm5, xmm4             ; sub x4
    mulss   xmm5, xmm0             ; mul t
    addss   xmm5, xmm4             ; add x4


    cvtss2si    r8, xmm5        ; save x

_bezier_calculate_y:
    mov         rax, QWORD [rbp - 24]     ; get points buffer address

    mov         edx, DWORD [rax + 4]    ; load y1
    cvtsi2ss    xmm1, edx               ; convert to double

    mov         edx, DWORD [rax + 12]    ; load y2
    cvtsi2ss    xmm2, edx               ; convert to double

    subss   xmm2, xmm1             ; sub y1
    mulss   xmm2, xmm0             ; mul t
    addss   xmm2, xmm1             ; add y1

    mov         edx, DWORD [rax + 20]   ; load y3
    cvtsi2ss    xmm3, edx               ; convert to double

    ; lerp(2, 3)
    subss   xmm3, xmm2             ; sub y2
    mulss   xmm3, xmm0             ; mul t
    addss   xmm3, xmm2             ; add y2

    mov         edx, DWORD [rax + 28]   ; load y4
    cvtsi2ss    xmm4, edx               ; convert to double

    ; lerp(3, 4)
    subss   xmm4, xmm3             ; sub y3
    mulss   xmm4, xmm0             ; mul t
    addss   xmm4, xmm3             ; add y3


    mov         edx, DWORD [rax + 36]    ; load y5
    cvtsi2ss    xmm5, edx               ; convert to double

    ; lerp(4, 5)
    subss   xmm5, xmm4             ; sub y4
    mulss   xmm5, xmm0             ; mul t
    addss   xmm5, xmm4             ; add y4


    cvtss2si    r9, xmm5        ; save y


_bezier_draw:
    mov         rcx, 10      ; load pen size

_bezier_draw_loop:
    cmp         r8d, DWORD [rbp - 12]   ; check if x < width
    jge         _bezier_check_t             ; stop drawing if is greater

    cmp         r9d, DWORD [rbp - 16]   ; check if y < height
    jge         _bezier_check_t             ; stop drawing if is greater

    mov         eax, DWORD [rbp - 12]   ; load width
    mul         r9                      ; multiply by y
    add         rax, r8                 ; add x
    shl         rax, 2                  ; multiply by 4
    add         rax, QWORD [rbp - 8]    ; add buffer address

    ; set pixel color
    mov         BYTE [rax + 0], 235
    mov         BYTE [rax + 1], 0
    mov         BYTE [rax + 2], 0

    inc         r9                      ; increment y
    loop _bezier_draw_loop

_bezier_check_t:
    mov         eax, 1
    cvtsi2ss    xmm15, eax
    ucomiss     xmm15, xmm0

    mov     eax, __float32__(0.000001)
    movd    xmm15, eax
    addss   xmm0, xmm15

    jae      _bezier_calculate_x

_bezier_end:
    pop rbp
    ret