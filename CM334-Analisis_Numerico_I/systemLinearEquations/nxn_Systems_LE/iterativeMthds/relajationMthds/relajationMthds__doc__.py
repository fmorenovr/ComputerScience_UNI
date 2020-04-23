# ------------------------------------------------------------	

# METODOS ITERATIVOS DE RESOLUCION DE SISTEMAS DE ECUACIONES LINEALES

# METODOS DE RELAJACION

# ------------------------------------------------------------	

#   1.1: Jacobi
#     Este metodo sirve para determinar las soluciones de matrices 
#     Diagonales Dominantes: que son cuando para cada fila de la matriz,
#     la magnitud de la entrada diagonal en una fila es >= a la suma de las magnitudes
#     de los demas ( no diagonal ), es decir, A es dominante si:
#     |a[i][i]| >= Sum(i!=j) |a[i][j]| , Para todo i
#     y |a[i][i]| > Sum(i!=j) |a[i][j]| , es estrictamente dominante

#     Donde A = D + R, D=A talque D[i][i] = A[i][i] y D[i][j]=0 (i!=j) 
#     y R = A, talque R[i][i]=0 y R[i][j]=A[i][j] (i!=j)
#     Ax=b ===> x = (I-R-1.A)x + R-1.b
#     J = I - R-1.A


# ------------------------------------------------------------	
#   1.2: Gauss-Seidel
#       Tambien conocido como el metodo de liebmann o desplazamineto sucesivo
#       Similar al metodo de Jacobi, pero se aplica a cualquier matriz con elementos != 0 en su diagonal
#       Sirve en matrices Diagonales Dominantes o Simetricas Definida Positiva
#       Donde A = L + U, L = triangular inferior, U triangular superior
#       Lx = b - Ux
#       L=A, L[i][j] = A[i][j] (i>=j) y L[i][j]=0 (j>i)
#       U=A, U[i][j] = 0 (i>=j) y U[i][j] = A[i][j] (j>i)
#       A = (D-E)-F
#       x = (I - (D-E)-1.A))x + (D-E)-1.b
#       G = (D-E)-1.F


# ------------------------------------------------------------	
#   1.3: Sucesive Over-Relajation (SOR)
#       Variante de Gauss-Seidel
#       A = D + L + U, donde 
#       D = A, D[i][i] = A[i][i], D[i][j]=0 (i!=j), matriz diagonal
#       L = A, L[i][j] = A[i][j] (i>j) y L[i][j]=0 (j>=i), triangular inferior estricta
#       U = A, U[i][j] = A[i][j] (i<j) y U[i][j]=0 (j<=i), triangular superior estricta
#       Fue hecho especialmente para las computadoras
#       Este metodo, aplica un peso w, donde para cada iteracion
#       Los valores de cada X, cambian muy pequeno, entonces w>1, para dar pasos
#       Largos entre cada valor de X, o w<1, para pasos mas cortos
