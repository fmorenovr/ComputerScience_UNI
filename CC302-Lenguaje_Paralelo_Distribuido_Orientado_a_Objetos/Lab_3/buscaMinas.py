from random import *
from bottle import run, get, post, view, redirect, request 
import requests, bottle, json, threading, time, sys
from frozendict import frozendict

tabuleiro = []
tabuleiroView = []
todasJogadas = []
jogadas = set([])
peers = sys.argv[2:]
porta = int(sys.argv[1])

pontos = 0
estado="jogando"
meuHash = {}

caminho_porta ="http://localhost:" + str(porta)

#peers.append("http://localhost:"+str(sys.argv[1]))  

print(peers)


class VC:
    def __init__(self, name):
        self.name = name
        self.vClock = { self.name: 0 }

    def __repr__(self):
        return "V%s" % repr(self.vClock)

    def increment(self):
        self.vClock[self.name] += 1
        return self

    def update(self, t):
        self.increment()
        for k, v in t.items():
            if k not in vc.vClock or vc.vClock[k] < t[k]:
                vc.vClock[k] = v



vc = VC('http://localhost:' + sys.argv[1]);

@get('/')
@view('campo_minado')
def criaCampoMinado():
    global tabuleiroView
    global tabuleiro
    
    seed(5)

    tabuleiroView  = [[ '-' for x in range(10)] for x in range(10)]
    tabuleiro  = [[ randint(0,3) for x in range(10)] for x in range(10)]
    #print (tabuleiroView)
    
    # print (len(tabuleiro))
    for i in range(len(tabuleiro)):
        for j in range(len(tabuleiro)):
            if tabuleiro[i][j] != 1:
                tabuleiro[i][j] = 0

    for i in range(len(tabuleiro)):
        for j in range(len(tabuleiro)):
            if tabuleiro[i][j] == 1:
                tabuleiro[i][j] = 10

    # print (tabuleiro)
    for i in range(len(tabuleiro)):
        for j in range(len(tabuleiro)):
            if tabuleiro[i][j] >= 10 and j > 0: #soma no lado esquerdo da bomba 
                tabuleiro[i][j-1]+=1

            if tabuleiro[i][j] >= 10 and j > 0 and i < 9: #soma no lado esquerdo pra baixo 
                tabuleiro[i+1][j-1]+=1

            if tabuleiro[i][j] >= 10 and j > 0 and i > 0: #soma no lado esquerdo pra cima
                tabuleiro[i-1][j-1]+=1

            if tabuleiro[i][j] >= 10 and j < 9: #soma na direita 
                tabuleiro[i][j+1]+=1

            if tabuleiro[i][j] >= 10 and j < 9 and i < 9: #soma na direita pra baixo 
                tabuleiro[i+1][j+1]+=1

            if tabuleiro[i][j] >= 10 and j < 9 and i > 0: #soma na direita pra cima 
                tabuleiro[i-1][j+1]+=1

            if tabuleiro[i][j] >= 10 and i > 0: #soma em cima
                tabuleiro[i-1][j]+=1

            if tabuleiro[i][j] >= 10 and i < 9: #soma embaixo
                tabuleiro[i+1][j]+=1
    
    #atualizaJogadas(jogadas)
    redirect('/tabuleiro')


@get('/tabuleiro')
@view('campo_minado')
def retornaTabuleiroview():
    global todasJogadas
    global tabuleiroView
    global retornaEstado
    global estado

    todasJogadas = list(jogadas)
    ordenacaoJogadas()
    atualizaJogadas(todasJogadas)

    return {'tabuleiroView': tabuleiroView, 'pontos': pontos, 'hash': meuHash, 'estado': estado}


def ordenacaoJogadas():
    global todasJogadas
    for i in range(1, len(todasJogadas)):
        jog = todasJogadas[i]
        j = i
        while j > 0 and testeMenor(jog, todasJogadas[j - 1]):
            todasJogadas[j] = todasJogadas[j - 1]
            j -= 1
            todasJogadas[j] = jog

def testeMenor(m1, m2):
    keys  = list(set(m1[2].keys()).union(m2[2].keys()))
    keys.sort()
    m1 = tuple(m1[2][j] if j in m1[2] else 0 for j in keys)
    m2 = tuple(m2[2][j] if j in m2[2] else 0 for j in keys)
    for i in range(0, len(m1)):
        if m1 < m2: return True
        if m2 < m1: return False
    return False



@get('/perdeu')
@view('perdeu')
def retornaTabuleiroviewPerdeu():
    return {'tabuleiroView': tabuleiroView, 'porta': porta, 'pontos': pontos, 'hash': meuHash}


@post('/jogada')
def atualizaTabuleiroView():
    global jogadas
    global tabuleiro
    global tabuleiroView
    global pontos
    global estado

    x = int(request.forms.get('x'))-1
    y = int(request.forms.get('y'))-1

    if x != None and y != None:
        vc.increment()
        m = (x, y, frozendict(vc.vClock))
        if(tabuleiro[x][y]) < 10 : 
            jogadas.add(m)
            if((tabuleiroView[x][y] != tabuleiro[x][y]) and (tabuleiro[x][y]!=-1)) :pontos = pontos + tabuleiro[x][y]
            redirect('/tabuleiro')
        else :
            estouraBombas()      

    


def estouraBombas():
    global tabuleiroView
    global tabuleiro
    global estado


    for i in range(len(tabuleiro)):
        for j in range(len(tabuleiro)):
            if tabuleiro[i][j] >= 10:
                tabuleiroView[i][j] = '*'

    estado="morto"            
    redirect('/perdeu')



def testaJogadas(x,y):
    global tabuleiroView
    global tabuleiro
    global estado
    
    if (tabuleiro[x][y] < 10 and tabuleiro[x][y] != 0):
        tabuleiroView[x][y] = tabuleiro[x][y]
    

    elif (tabuleiro[x][y] == 0):
        verificaVizinho(x,y)


    

def atualizaJogadas(todasJogadas):
    for jogada in todasJogadas: #lista de jogadas
        testaJogadas(jogada[0],jogada[1])


    


def verificaVizinho(x,y):
    if tabuleiro[x][y] == 0:
        tabuleiroView[x][y] = 0
        tabuleiro[x][y] = -1
        if y > 0:
            if tabuleiro[x][y-1] == 0:
                verificaVizinho(x,y-1)
        if y < 9:
            if tabuleiro[x][y+1] == 0:
                verificaVizinho(x,y+1)
        if x > 0:
            if tabuleiro[x-1][y] == 0:
                verificaVizinho(x-1,y)
        if x < 9:
            if tabuleiro[x+1][y] == 0:
                verificaVizinho(x+1,y)
        if x > 0 and y > 0:
            if tabuleiro[x-1][y-1] == 0:
                verificaVizinho(x-1,y-1)
        if x > 0 and y < 9:
            if tabuleiro[x-1][y+1] == 0:
                verificaVizinho(x-1,y+1)
        if x < 9 and y > 0:
            if tabuleiro[x+1][y-1] == 0: #aqui
                verificaVizinho(x+1,y-1)
        if x < 9 and y < 9:
            if tabuleiro[x+1][y+1] == 0:
                verificaVizinho(x+1,y+1)

@get('/peers')
def index():
    return json.dumps(peers)

@get('/jogadas')
def index():
    return json.dumps([(x, y, dict(tmp)) for (x, y, tmp) in jogadas])

@get('/pontos')
def index():
    return json.dumps(pontos)

@get('/estado')
def index():
    return json.dumps(estado)    


def clientePeers():
    time.sleep(5)
    while True:
        time.sleep(1)
        np = []
        for p in peers:
            r = requests.get(p + '/peers')
            np = np + json.loads(r.text)
        peers[:] = list(set(np + peers))
        print(peers)
        time.sleep(2)



def clienteMessages():
    while True:
                time.sleep(2)
                global jogadas
                for p in peers:
                        time.sleep(2)
                        jog = recebeJogada(p)
                        pon = requests.get(p + '/pontos')
                        e = requests.get(p + '/estado')

                        e = json.loads(e.text)
                        ponts = json.loads(pon.text)
                        atualizaPontos(ponts, p, e)

                        for (x, y, tmp) in jog.difference(jogadas):
                            vc.update(tmp)
                            jogadas.add((x, y, tmp))

def recebeJogada(p):
    r = requests.get(p + "/jogadas")
    obj = json.loads(r.text)
    rm = set((a, b, frozendict(t)) for [a,b,t] in obj)
    return rm

def atualizaPontos(pt, p, e):
    global meuHash
    st = str(pt)
    st = st + "  | " + "  Estado : " + e 
    meuHash[p] = st    

    

t1 = threading.Thread(target=clientePeers)
t1.start()

t2 = threading.Thread(target=clienteMessages)
t2.start()


run(host='localhost', port=porta)
