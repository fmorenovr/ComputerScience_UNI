# -----------------------------------------------------

#  METODOS PARA ENCONTRAR AUTOVECTORES

#     Ax = lambda*x

# -----------------------------------------------------

# 1.1 Jacobi-Eigen
#   Es un metodo iterativo para los autovectores de matrices simetricas
#   Conocido como diagonalizacion
#   Tambien se puede estandarizar
#   1.1.1 StandardForm
#     Se basa en Jacobi, pero trabaja con vectores normalizados, donde 
#     La segunda matriz debe ser definida positiva
#     Ax = lam*Bx
#     donde B = LLt
#     x = (L-1t)z
#     H = L-1*A*(L-1)t
#     Hz = lambda*z

# 1.2 Power
#   determina autovalores de matrices dominantes, es decir, el mayor autovalor

# 1.3 Simmetryc Power
#   metodo power para matrices SIMETRICAS

# 1.4 Inverse Power
#   Encuentra el minimo autovalor y autovector aproximado a un numero inicial
#   Ax = lambda*x
#   sea v:
#   Av = z, calcule |z|, luego v = z/|z|, |z| = 1/lambda
#   Ax = lambda.Bx
#   Az = Bv
#   1.4.1 Max Eigen
#     de aqui deriva el metodo, max Eigen que devuelve el autovalor maximo
#     basado en el metodo de inverse power, basandose a un vector inicial
#     y el autovector asociado a dicho autovalor

# 1.5 Rayleigh
#   Similar a inverse power, pero con valores iniciales mas cercanos, sino diverge
#   a diferencia de las potencias, que escogen 1 autovector inicial
#   rayleigh escoge 1 autovalor inicial

# 1.6 gerschgorin - sturm
# Usado en Matrices SIMETRICAS tridiagonales
# STURM
#   en un conjunto [a,b], se tiene f0(x) , ... ,fn(x)
#   cumple:
#     *fn(x) != 0 para x E [a,b]
#     *fi(x) = 0 entonces, fi-1(x) y fi+1(x) != 0 y fi-1(x).fi+1(x) < 0
#     *f0(c) = 0, f0(x)/f1(x) va de - a +, f1(c)!=0 y es creciente
#   Construccion: por le algoritmos de Euclides
#   Pn(x) = 0 ==> f0(x) = Pn(x) y f1(x) = Pn'(x)
#   luego fi-1(x) = ci(x).fi(x) + ri(x), donde grado de ri es uno menos de fi
#   y hacemos fi+1(x) = -ri(x)
#   se obtiene D(x) de Pn(x) y Pn'(x), donde fi(x)/D(x) es una sucesion de
#   la ecuacion P(x)/D(x) = Q(x) = 0, porque tiene las misma raices de P(x)=0
#   (simples) si llegamos a un resto !=0, este determina la finalizacion
#   sea sig(f0(a)), ... sig(fn(a))
#       sig(f0(b)), ... sig(fn(b)) en un intervalo [a,b], si alguna se anula
#   en los extremosse reemplaza por + o -y denotamos N1 al numeor de cambios
#   y N2 de la segunda ( siempre es N1 >= N2 )
#   donde el numero de raices reales es N1 - N2 para f0(x)=0
# GERSCHGORIN
#   define circulos D1,D2, ... con centros de Aii y radio
#   ri = SUM|Aij|(j!=i) 
#   donde lambdaMin >= min(Aii - ri)
#   y lambdaMax <= max(Aii + ri)

# 1.7 METODO QR
#   Analiza MATRICES SIMETRICAS TRIDIAGONALES
#   hecho por  John G.F. Francis (England) and by Vera N. Kublanovskaya (USSR)
#   por medio de la factorizacion QR, calcula los autovectores aproximados
