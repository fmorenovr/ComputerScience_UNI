# ------------------------------------------------------------

# METODOS DIRECTOS DE RESOLUCION DE SISTEMAS DE ECUACIONES LINEALES

# METODOS DE FACTORIZACION MATRICES SIMETRICAS

# ------------------------------------------------------------

#   De la descomposicion LU = L (DMt)
#   A=LDMt, se cumple que si A es simetrica, L=M
#   Entonces:
#   A = LDLt

 
# 3. Metodos de factorizacion de matrices Simetricas
#   3.1: Definidas Positivas (xtAx>0)
#     Todos sus autovalores son positvos
#     3.1.1: LDLt
#       Matriz Regular(Matriz cuadrada que tiene inversa) y simetrica
#       A = LDLt
#     3.1.2: Cholesky
#       Matrices Simetricas definidas positivas
#       A=G.Gt


#   3.2: Semidefinidas Positivas (x*Ax>=0) x*:conjugado de x
#     3.2.1: PAPt
#       Matrices Simetricas Semi Positivas:
#       para cada i!=j se tiene:
#       |aij| <=( aii + ajj )/2
#       |aij| <= sqrt( aii*ajj ) 
#       max|aij| <= max|aii|
#       si aii=0 ---> aij=aji=0 j=1,..,n
#       PAPt = G.Gt


#   3.3: Indefinidas (xtAx>0 y/o XtAx<0 )
#     Autovalores >0 y/o <0
#     Descomposicion dematrices en Trigonales
#     PAPt = LTLt , T es triagonal
#     PAPtx = PbPt
#     LTLtx = PbPt

#     LTLty = Pb, x=Pty
#     LTw = Pb, Lty = w
#     Lz = Pb, Tw = z .. se resuelve por el metodo de gauss
#     

#     3.3.1: Parlett-Reid
#       Utilizacion de transformaciones de Gauss, con pivoteo parcial debajo de la diagonal
#       PAPt = LTLt
#       T = (MnPnMn1Pn1...)A(MnPnMn1Pn1)t
#       MP = (MnPnMn1Pn1 ...)
#       P = PnPn-1 ... P2P1
#       L = (MP.Pt)^-1
#     3.3.2: Aasen
#       Similar a Parlett-Reid usando el metodo de Gauss para cada operacion de filas (pivoteo)
#     3.3.3: Bunch-Kaufman
#       Similar a PArlett-Reid, pero se descompone en LBLt
#       Donde B es una matriz diagonal por bloques 2x2
