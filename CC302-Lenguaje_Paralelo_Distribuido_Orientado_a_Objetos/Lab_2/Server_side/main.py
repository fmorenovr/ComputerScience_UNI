from bottle import run, get, post, view, request, route, static_file, template, redirect

chatContent = []
name = ""

@route('/static/<filepath:path>')
def server_static(filepath):
    return static_file(filepath, root='static')

@route('/')
def chatRedirect():
    redirect('/chat')

@get('/chat')
@view('chat')
def chat():
    return dict(name=name, chatContent=chatContent)

@post('/send')
def sendMessage():
    global name
    nme = request.forms.getunicode('name')
    message = request.forms.getunicode('message')
    if nme != None and message != None:
        chatContent.append([nme, message])
        name = nme
        redirect('/chat')

run(host='localhost', port=8080)
