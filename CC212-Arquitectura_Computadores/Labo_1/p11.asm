org 8000h
mov r1,#20h
clr c
mov r2,#04h
mov a,r1
mov b,r2
mov 30h,r1
mov 31h,r2
div ab
mov 40h,a
mov 41h,b
ljmp 2F0H
end