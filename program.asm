[bits 16]

;mov byte [0xb800], 0x12
;times 16 - ($ - $$) db 0x90
;mov word [0xb800], 0x1234
;times 2*16 - ($ - $$) db 0x90

;mov byte [di+0xb8], 0x12
;times 3*16 - ($ - $$) db 0x90
;mov word [di+0xb8], 0x1234
;times 4*16 - ($ - $$) db 0x90

;mov byte [di+0xb800], 0x12
;times 5*16 - ($ - $$) db 0x90
;mov word [di+0xb800], 0x1234
;times 6*16 - ($ - $$) db 0x90

;mov byte [di], 0x12
;times 7*16 - ($ - $$) db 0x90
mov word [di], 0x1234
times 8*16 - ($ - $$) db 0x90
