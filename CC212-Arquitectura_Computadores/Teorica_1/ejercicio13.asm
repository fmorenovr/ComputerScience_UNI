;Hacer un programa que encienda 4 leds conectados a los pines 
;P1.0, P1.1, P1.2 y P1.3 del Puerto 1.

org 8000h
mov P1,#0Fh
ljmp 2F0h
end