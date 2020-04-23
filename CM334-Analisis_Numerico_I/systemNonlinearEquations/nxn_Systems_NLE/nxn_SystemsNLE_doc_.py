# ------------------------------------------------------------	

#       METODOS DE SOLUCION DE SISTEMAS LINEALES nxn

# ------------------------------------------------------------	

# 1. METODOS ITERATIVOS DE RESOLUCION DE SISTEMAS DE ECUACIONES LINEALES

# ------------------------------------------------------------	
# 1.1 Newton Generalizado
#   xk+1 = xk - Jk-1.F(xk)
#   Aproxima mediante las derivadas de cada componente

# 1.2 Newton Jacobi
#   xk+1 = xk - Dk-1.F(xk)
#   Aproxima los elementos de su diagonal principal
#   Dkk = Jkk

# 1.3 Newton Gauss Seidel
#   xk+1 = xk - Lk-1.F(xk)
#   Aproxima los elementos por la matriz triangular inferior
#   incluido la diagonal
#   Lij = Jij, i>=j

# 1.4 Newton SOR
#   xk+1 = xk - (rho.Dk + Lk)-1.F(xk)
#   donde w = 1/(rho+1.0)

# 1.5 Broyden
#   Metodo de la secante generalizado para n-dimensional

# 1.6 Punto fijo
#   Punto fijo en n-dimensional

# 1.7 Descenso Gradiente
#   determina minimos locales para funciones de forma f: R^n ---> R, (minimo local puede ser 0)
#   un sistema nxn, tiene solucion en un Sistema F nxn, si la funcion f = SUMATORIA(Fi(x1,x2,...,xn))
#   Determinacin de un minimo local: g: R^n ---> R
#     1. evaluar g(x) para x = x0
#     2. determinar una direccion que origine el valor de g, es decir, la derivada direccional
#     3. desplazar hacia esa direccion y a ese x1 lo llamamos x0
#     X(k) = X(k-1) - alpha*grad(g(X(k-1)))
#     4. repetimos los pasos
#     PARA SISTEMAS NO LINEALES:
#     se contruye una funcion a partir de F: R^n ---> R^n
#     G = Ft.F*0.5, de tal modo que  gradiente de G = Jac(X)t.F(x)
#     y se hace el descenso gradiente, para encontrar un minimo local de esa funcion
#     dende la direccion de maximo descenso es - grad g
#     se construye:     x = x - alpha.grad g, alpha >0
#     entonces nos faltaria escoger un alpha adecuado
#     se construye h(alpha) = g( x - alpha.grad g(x) )
#     por lo que se construye un polinomio de interpolacion de tres valores alpha1 < alpha2 < alpha3
#     por conveniencia, alpha2 = alpha3/2 y alpha1 = 0
#     h1 = (g2-g1)/(alpha2-alpha1), h2 = (g3-g2)/alpha3-alpha2, h3 = (h2 - h1)/(alpha3 - alpha1)
#     g1 = g(x0), g2 = g(x - alpha2.z), g3 = g(x - alpha3.z), donde z = grad g(x0)
#     y el polinmio P(alpha) = g1 + h1.alpha + h3.alpha.(alpha - alpha2)
#     se toma alpha0 = alpha0 = 0.5*(alpha2 - h1/h3) como solucion de P, se toma g0 = g(x - alpha0.z)
#     y finalmente el alpha adecuado es el valor entre alpha0 y alpha3 tal que galpha = min(g0,g3)
#     x = x - alpha.z


# 1.8 HOMOTOPIA Y CONTINUACION
#   Se contruye un sistema partiedo de la funcion F:R^n --> R^n, de una solucion conocida X
#   G: [0,1]xR^n ---> R^n , con solucion conocida cuando lambda = 0 y desconocida cuando lambda = 1
#   G(lambda,x) = lambda.F(x) + ( 1 - lambda ).( F(x) - F(x0) ) = F(x) + ( lambda - 1 ).F(x0)
#   para diversos valores de lambda, se determina una solucion:
#   G(lambda,x) = 0
#   cuando lambda = 0, G(0,x) = F(x) - F(x(0)), con x(0) es una solucion.
#   cuando lambda = 1, G(1,x) = F(x) y x(1) es una solucion.
#   como lambda nos proporciona toda una familia de solucion en G. qeu conducen del valor solucion conocido x(0) ( inicial )
#   al valor de x(1) ( solucion desconocida ).
#
#   la funcion G se llama HOMOTOPIA entre G(0,x) y G(1,x).
#
#   el problema de continuacion consiste en determina como pasar de la solucion conocida ( o inicial ) x(0) a la desconocida
#   ( o real aproximada ) x(1) de G(1,x) que resuelva F(x) = 0
#   supondremos que x(lambda) es la unica solucion de G(lambda,x) = 0,
#   vemos que para 0<=lambda<=1, se contruye una curva en R^nde x(0) a x(1) parametrizada por lambda
#   si lambda --> x(lambda) y G son diferenciables, entonces al derivar G(lambda,x) respecto a lambda
#   0 = dG(lambda,x(lambda))/dlambda + dG(lambda,x(lambda))/dx . x'(lambda)
#   y despejando x'(lambda)
#   se genera un sistema de ecuaciones diferenciales

#   x'(lambda) = [ dG(lambda,x(lambda))/dx ]-1 . dG(lambda,x(lambda))/dlambda ... (1)

#   donde dG(lambda,x(lambda))/dx = J(x(lambda)) y dG(lambda,x(lambda))/dlambda = F(x(0))

#   donde si J es no singular y ||J-1||<=M, existe una UNICA funcion x(lambda) tal que G(lambda,x(lambda)) = 0
#   para lambda [0,1], se genera el sistema de ecuaciones diferenciales (1)
#   se para a resolver por runge-Kutta de 4to orden
