# ------------------------------------------------------------	

# METODOS ITERATIVOS DE RESOLUCION DE SISTEMAS DE ECUACIONES LINEALES

# METODOS DE KRYLOV

# ------------------------------------------------------------	

#   1.1: Descenso Gradiente
#     Se tiene el sistema Ax = b ===> r = Ax - b = 0, se construye una funcion a partir del sistema
#     la funcion F(x) = ||Ax - b||2, donde Grad F(x) = 2.At.(Ax - b) o tambien g(x) = <x,Ax> - 2<x,b>
#     donde g(x) = 0 o F(x) = 0, cuando x es solucion del sistema
#     entonces g(x1,x2,...,xn) = Sum.Sum ( aij.xi.xj ) - 2.Sum ( xi.bi )
#     cuyas derivadas parciales:
#     dg(x)/dxk = 2.Sum ( aki.xi ) - 2.bk
#     entonces el gradiente de g(x) = 2.(Ax - b) = -2.r, y el minimo local o maximo descenso esta dado por 
#     - grad g = en la direccion del vector r, residual
#     donde g(x + tv) = g(x) + 2t.<v,Ax-b> + t*t.<v,Av> ...(1)
#     sea H(t) = g(x + tv) --> H'(t) = 2.<v,Ax-b> + 2t.<v,Av>, como debe ser minimo, H'(t) = 0
#     t = - <v,Ax-b>/<v,Av> = <v,b-Ax>/<v,Av>
#     remplazando en (1), se tiene:
#     g(x+tv) = g(x) - <v,b-Ax>.v,b-Ax>/<v,Av>
#     entonces: g(x+tv) < g(x), excepto cuando <v,Ax-b> = 0 ---> g(x+tv) = g(x)
#     donde v = r


#   1.2: Gradiente Conjugado
#     Usa matrices Simetricas y definidas positivas
#     Consiste en encontrar el vector X que minimice esta funcion
#     f(x) = 1/2Xt.A.X - bt.X
#     donde Ax = b, A es simetrica definida positiva
#     y Grad f = Ax - b es zero


#   1.3: Gradiente Biconjugado
#     Usa matrices NO simetricas
#     Converge mas rapido que con conjugado normal( generalmente el doble de rapido)

#   1.4: GMRES
#     Residuos minimos

#   1.5: TFQMR
#     Usa los algoritmos de Lanzocs

# ------------------------------------------------------------	
