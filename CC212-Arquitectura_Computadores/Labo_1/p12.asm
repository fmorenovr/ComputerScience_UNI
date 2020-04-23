org 8000h
mov r0,30h
clr c
mov r1,31h
mov a,r0
mov b,r1
div ab
mov 41h,a
mov 40h,b
lcall 2F0H
end