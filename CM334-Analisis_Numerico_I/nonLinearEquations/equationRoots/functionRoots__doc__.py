# ------------------------------------------------------------

# ECUACIONES NO LINEALES

# ------------------------------------------------------------

# Econtrar las soluciones (Raices) de ecuaciones NO lineales

# ejemplo:
#  f(x) = cox(x) + x^2

# ------------------------------------------------------------

#   1. Biseccion
#     En un intervalo [a,b], busca c = (a+b)/2
#     tal que f(c) = 0

#   2. Brent
#     Combina biseccion e interpolacion cuadratica
#     identifica x3 = (x1 + x2)/2 e inicia la interpolacion haciendo infervsa de f(x) a x(f)
#     x = x(0)
#     dx = x-x3 = f3(...)

#   3. Secante
#     Similar al de newton, pero este aproxima con los 2 valores de iteraciones a,b
#     y no necesita evaluar f/f', es mas eficiente

#   4. Newton
#     Tambien conocida como Newton-Raphson
#     ene un intervalo encuentra la raiz a partir de su derivada
#     x1 = x0 - f(x0)/f'(x0)

#   5. Newton-Raphson
#     Este metodo usa el metodo de newton con bisection.

#   6. Posicion Falsa
#     Tambien llamado la regla falsa, genera aproximaciones del mismo
#     modo que el metodo secante, pero este metodo designa
#     que la raiz esta en una iteracion n y otra n+1

#   7. Punto Fijo
#     Tambien llamado, iteracion del Sustitucion Sucesiva
#     Se quiere encontrar un p / f(p) = 0
#     definimos una funcion g(x) = x - f(x)
#     si g tiene un punto fijo en p, entonces f tiene 
#     un cero en p, y p es un cero de f
#     tal que se forme un contorno gE[a,b] y g(x)E[a,b]
#     y g' < 1

#   8. Steffensen
#     Similar al metodo del punto fijo(sustitucion sucesiva)
#     pero lo hace de manera mas rapida, porque toma 2 puntos consecutivos

#   9. Ridders
#     Similar a la posicion falsa, usa la funcion exp para aproximar la raiz

#   10. Halley
#     Metodo de newton con orden de convergencia 3 (cubica)

#   11. Householder
#     Es el metodo de newton con orden de convergencia alto
