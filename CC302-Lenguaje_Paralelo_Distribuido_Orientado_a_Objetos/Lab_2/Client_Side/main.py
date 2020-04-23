# -*- coding: utf-8 -*-

from bottle import run, get, post, view, request, route, static_file, template, redirect
import bottle
import json
import threading
import requests
import time
import sys

chatContent = set([])
name = ""
peers = ['localhost:' + p for p in sys.argv[2:]]
lock = threading.Lock()

@route('/static/<filepath:path>')
def server_static(filepath):
    return static_file(filepath, root='static')

# Just redirecting 'localhost:port/' to 'localhost:port/chat'
@route('/')
def chatRedirect():
    redirect('/chat')

@get('/chat')
@view('chat')
def chat():
    return dict(name=name, chatContent=list(chatContent))

@post('/send')
def sendMessage():
    global name
    nme = request.forms.getunicode('name')
    message = request.forms.getunicode('message')
    if nme != None and message != None:
        chatContent.add((nme, message))
        name = nme
        redirect('/chat')

@get('/peers')
def dumpsPeers():
    return json.dumps(peers)

def checkPeers():
    global lock
    # time.sleep() for debugging
    time.sleep(5)
    while True:
        time.sleep(1)
        newPeers = []
        for p in peers:
            try:
                # requests.get("http://" + p + '/peers') will return the peers known by host 'p' if this server is not
                # down. E.g.: if server 8080 knows 8081 and 8082 it will be returned
                # ["localhost:8080", "localhost:8082"]
                r = requests.get("http://" + p + '/peers')
                # if this line is reached it means that p is not down
                newPeers.append(p)
                # list.extend(seq): the method extend() appends the contents of seq to list
                # json.loads(fp, ...) deserialize fp (a .write()-supporting file-like object containing a
                # JSON document) to a Python object.
                newPeers.extend(json.loads(r.text))
            except:
                pass

            time.sleep(1)
        with lock:
            # newPeers is transformed into a 'set' to eliminate duplicates. After that it is transformed into
            # a list again and extended to peers
            peers.extend(list(set(newPeers)))

@get('/chatContent')
# dumpsMsg() returns a 'JSON list' with the messages known
def dumpsMsg():
    # chatContent is transformed into a list, because it is originally a set
    return json.dumps(list(chatContent))

# getMessagesFrom(p) get the messages from peer 'p'
def getMessagesFrom(p):
    try:
        r = requests.get("http://" + p + "/chatContent")
        # 200 OK is the code for success
        if r.status_code == 200:
            pMsg = json.loads(r.text)
            return set((a, b) for [a,b] in pMsg)

    except:
        print("Connection Error!")
    return set([])

def unionMsg():
    while True:
        time.sleep(1)
        newMsg = set([])
        global chatContent
        for p in peers:
            time.sleep(1)
            msgFromPeer = getMessagesFrom(p)
            # print(msgFromPeer)
            # if the messages from peer 'p' are different from the messages from
            # chatContent then newMsg is overwritten by the new messages (only ->
            # newMsg.union(msgFromPeer.difference(chatContent))). After this, the
            # content of newMsg is united with the content of chatContent
            if msgFromPeer.difference(chatContent):
                newMsg = newMsg.union(msgFromPeer.difference(chatContent))
        chatContent = chatContent.union(newMsg)

# thread for peers
thrPeers = threading.Thread(target=checkPeers)
thrPeers.start()

# thread for messages
thrUnionMsg = threading.Thread(target=unionMsg)
thrUnionMsg.start()

# run() starts a built-in development server. It runs on localhost port given in argv[1] and
# serves requests until you hit Control-c.
run(host='localhost', port=int(sys.argv[1]))
