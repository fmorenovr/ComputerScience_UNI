org 8000h
mov r1,#39h
clr c
mov r0,#7h
mov a,r1
subb a,r0
mov 41h,a
ljmp 2F0H
end