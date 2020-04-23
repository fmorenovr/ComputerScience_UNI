# ------------------------------------------------------------

# RAICES DE POLINOMIOS

# ------------------------------------------------------------

# Econtrar las soluciones (Raices) de ecuaciones NO lineales POLINOMIALES

# ejemplo:
#  f(x) = 3 + x + 3*x^2 + ...

# ------------------------------------------------------------

# METODOS DE 1 RAIZ A LA VEZ

# 1.1 Muller ( RAICES COMPLEJAS/REALES )
#   Hace aproximaciones mediante polinomios cuadraticos
#   P(x) = a(x-x2)**2 + b(x-x2) + c
#   que pasan por los puntos (x0,f(x0)) , (x1,f(x1)) (x2,f(x2))
#   donde x1,x2,x3 son numeros iniciales cualesquiera

# 1.2 HornerRuffini
#   Mediante las divisiones de Ruffini y el metodo de Newton, evalua las raices
#   y las aproxima
#   donde P(x) = (x - x0)Q(x) + b0, P'(x0) = Q(x) + (x-x0)Q'(x)
#   b0 = P(x0), P'(x0) = Q(x0)

# 1.3 Laguerre
#   Mediantte la primera y segunda derivada evalua las aproximaciones de la raiz

# 1.4 Inverse Quadratic Inpertoplation (IQI)
#   Usa la interpolacion cuadratica para aproximar polinomios por parabolas
#   y usa la inversa para aproximar las raices
#   Usado en el metodo de Brent

# 1.6 Jenkins-Traub
#   Usando el metodo de horner y ruffini, calcula aproximacion
#   mediante variable de distribucion uniforme y exponencial
#   usando polinomios de cauchy para aproximar a una raiz

# METODOS DE 2 RAIZ A LA VEZ

# 1.5 Bairstow
#   Calcula raices de 2 en 2, por medio de divisiones a polinomios cuadraticos
#   en x*x - r*x - s, donde r y s son las raices pares del polinomio
#   donde R=b1*x + b0

# METODOS DE TODAS LAS RAICES A LA VEZ

# 1.7 Durand-Kerner ( Weiertrass )
#   Mediante valores iniciales, descompone al polinomio como
#   P(x) = (x-a)(x-b) ...(x-z)
#   y hace recursividad usando Iteracion del punto fijo y GaussSeidel
