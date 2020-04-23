#! /usr/bin/env python
#
# GUI module generated by PAGE version 4.3.1
# In conjunction with Tcl version 8.6
#    Nov 16, 2014 07:33:45 PM
import sys

try:
    from Tkinter import *
except ImportError:
    from tkinter import *

try:
    import ttk
    py3 = 0
except ImportError:
    import tkinter.ttk as ttk
    py3 = 1

import gui_support

def vp_start_gui():
    '''Starting point when module is the main routine.'''
    global val, w, root
    root = Tk()
    root.title('Orthologs Comparison')
    root.geometry('1500x450+350+150')
    w = New_Toplevel_1 (root)
    gui_support.init(root, w)
    root.mainloop()

w = None
def create_New_Toplevel_1 (root, param=None):
    '''Starting point when module is imported by another program.'''
    global w, w_win, rt
    rt = root
    w = Toplevel (root)
    w.title('Resultados Motif y Ortologos')
    w.geometry('600x450+650+150')
    w_win = New_Toplevel_1 (w)
    gui_support.init(w, w_win, param)
    return w_win

def destroy_New_Toplevel_1 ():
    global w
    w.destroy()
    w = None

from multibox import *

class New_Toplevel_1:
  def __init__(self, master=None):
    # lista de motif
    self.Label1 = Label (master)
    self.Label1.place(relx=0.08,rely=0.04,height=19,width=192)
    self.Label1.configure(text='''Lista de MOTIF y secuencias''')
    
    self.MultiListBox1 = MultiListbox(master, (('ID', 1), ('Nombre', 10), ('Secuencia', 10)))
    self.MultiListBox1.place(relx=0.03,rely=0.11,relheight=0.56,relwidth=0.26)
    self.MultiListBox1.configure(width=154)

    # ortologo 1
    self.Label2 = Label (master)
    self.Label2.place(relx=0.32,rely=0.01,height=19,width=78)
    self.Label2.configure(text='''Ortologo 1''')

    self.Text1 = Text (master)
    self.Text1.place(relx=0.38,rely=0.01,relheight=0.05,relwidth=0.43)
    self.Text1.configure(background="green")
    self.Text1.configure(font="TkTextFont")
    self.Text1.configure(selectbackground="#c4c4c4")
    self.Text1.configure(width=376)

    # ortologo 2
    self.Label3 = Label (master)
    self.Label3.place(relx=0.32,rely=0.08,height=19,width=78)
    self.Label3.configure(text='''Ortologo 2''')

    self.Text2 = Text (master)
    self.Text2.place(relx=0.38,rely=0.08,relheight=0.05,relwidth=0.43)
    self.Text2.configure(background="green")
    self.Text2.configure(font="TkTextFont")
    self.Text2.configure(selectbackground="#c4c4c4")
    self.Text2.configure(width=376)

    # ortologo 3
    self.Label4 = Label (master)
    self.Label4.place(relx=0.32,rely=0.15,height=19,width=78)
    self.Label4.configure(text='''Ortologo 3''')

    self.Text3 = Text (master)
    self.Text3.place(relx=0.38,rely=0.15,relheight=0.05,relwidth=0.43)
    self.Text3.configure(background="green")
    self.Text3.configure(font="TkTextFont")
    self.Text3.configure(selectbackground="#c4c4c4")
    self.Text3.configure(width=376)

    # ortologo 4
    self.Label5 = Label (master)
    self.Label5.place(relx=0.32,rely=0.22,height=19,width=78)
    self.Label5.configure(text='''Ortologo 4''')

    self.Text4 = Text (master)
    self.Text4.place(relx=0.38,rely=0.22,relheight=0.05,relwidth=0.43)
    self.Text4.configure(background="green")
    self.Text4.configure(font="TkTextFont")
    self.Text4.configure(selectbackground="#c4c4c4")
    self.Text4.configure(width=376)

    # ortologo 5
    self.Label6 = Label (master)
    self.Label6.place(relx=0.32,rely=0.29,height=19,width=78)
    self.Label6.configure(text='''Ortologo 5''')

    self.Text5 = Text (master)
    self.Text5.place(relx=0.38,rely=0.29,relheight=0.05,relwidth=0.43)
    self.Text5.configure(background="green")
    self.Text5.configure(font="TkTextFont")
    self.Text5.configure(selectbackground="#c4c4c4")
    self.Text5.configure(width=376)

    # ortologo 6
    self.Label7 = Label (master)
    self.Label7.place(relx=0.32,rely=0.36,height=19,width=78)
    self.Label7.configure(text='''Ortologo 6''')

    self.Text6 = Text (master)
    self.Text6.place(relx=0.38,rely=0.36,relheight=0.05,relwidth=0.43)
    self.Text6.configure(background="green")
    self.Text6.configure(font="TkTextFont")
    self.Text6.configure(selectbackground="#c4c4c4")
    self.Text6.configure(width=376)

    # ortologo 7
    self.Label8 = Label (master)
    self.Label8.place(relx=0.32,rely=0.43,height=19,width=78)
    self.Label8.configure(text='''Ortologo 7''')

    self.Text7 = Text (master)
    self.Text7.place(relx=0.38,rely=0.43,relheight=0.05,relwidth=0.43)
    self.Text7.configure(background="green")
    self.Text7.configure(font="TkTextFont")
    self.Text7.configure(selectbackground="#c4c4c4")
    self.Text7.configure(width=376)

    # ortologo 8
    self.Label9 = Label (master)
    self.Label9.place(relx=0.32,rely=0.50,height=19,width=78)
    self.Label9.configure(text='''Ortologo 8''')

    self.Text8 = Text (master)
    self.Text8.place(relx=0.38,rely=0.50,relheight=0.05,relwidth=0.43)
    self.Text8.configure(background="green")
    self.Text8.configure(font="TkTextFont")
    self.Text8.configure(selectbackground="#c4c4c4")
    self.Text8.configure(width=376)

    # ortologo 9
    self.Label10 = Label (master)
    self.Label10.place(relx=0.32,rely=0.57,height=19,width=78)
    self.Label10.configure(text='''Ortologo 9''')

    self.Text9 = Text (master)
    self.Text9.place(relx=0.38,rely=0.57,relheight=0.05,relwidth=0.43)
    self.Text9.configure(background="green")
    self.Text9.configure(font="TkTextFont")
    self.Text9.configure(selectbackground="#c4c4c4")
    self.Text9.configure(width=376)

    # ortologo 10
    self.Label11 = Label (master)
    self.Label11.place(relx=0.32,rely=0.64,height=19,width=78)
    self.Label11.configure(text='''Ortologo 10''')

    self.Text10 = Text (master)
    self.Text10.place(relx=0.38,rely=0.64,relheight=0.05,relwidth=0.43)
    self.Text10.configure(background="green")
    self.Text10.configure(font="TkTextFont")
    self.Text10.configure(selectbackground="#c4c4c4")
    self.Text10.configure(width=376)

    self.Label12 = Label (master)
    self.Label12.place(relx=0.32,rely=0.71,height=19,width=78)
    self.Label12.configure(text='''Ortologo 11''')

    self.Text11 = Text (master)
    self.Text11.place(relx=0.38,rely=0.71,relheight=0.05,relwidth=0.43)
    self.Text11.configure(background="green")
    self.Text11.configure(font="TkTextFont")
    self.Text11.configure(selectbackground="#c4c4c4")
    self.Text11.configure(width=376)

    self.Label13 = Label (master)
    self.Label13.place(relx=0.32,rely=0.78,height=19,width=78)
    self.Label13.configure(text='''Ortologo 12''')

    self.Text12 = Text (master)
    self.Text12.place(relx=0.38,rely=0.78,relheight=0.05,relwidth=0.43)
    self.Text12.configure(background="green")
    self.Text12.configure(font="TkTextFont")
    self.Text12.configure(selectbackground="#c4c4c4")
    self.Text12.configure(width=376)

    # distancia
    self.Label5 = Label (master)
    self.Label5.place(relx=0.07,rely=0.8,height=19,width=176)
    self.Label5.configure(text='''distancia de desplazamiento''')

    self.Entry1 = Entry (master)
    self.Entry1.place(relx=0.25,rely=0.8,relheight=0.05,relwidth=0.24)
    self.Entry1.configure(background="yellow")
    self.Entry1.configure(font="TkFixedFont")

    # parte del radio
    self.Label6 = Label (master)
    self.Label6.place(relx=0.06,rely=0.87,height=19,width=176)
    self.Label6.configure(activebackground="#f9f9f9")
    self.Label6.configure(text='''radio de conservacion''')

    self.Entry3 = Entry (master)
    self.Entry3.place(relx=0.25,rely=0.87,relheight=0.05,relwidth=0.24)
    self.Entry3.configure(background="yellow")
    self.Entry3.configure(font="TkFixedFont")
    self.Entry3.configure(selectbackground="#c4c4c4")

    # parte de la conservacion
    self.Label7 = Label (master)
    self.Label7.place(relx=0.05,rely=0.94,height=19,width=176)
    self.Label7.configure(activebackground="#f9f9f9")
    self.Label7.configure(text='''% conservacion''')

    self.Entry2 = Entry (master)
    self.Entry2.place(relx=0.25,rely=0.94,relheight=0.05,relwidth=0.24)
    self.Entry2.configure(background="yellow")
    self.Entry2.configure(font="TkFixedFont")
    self.Entry2.configure(selectbackground="#c4c4c4")

    # boton procesar
    self.Procesar = Button (master)
    self.Procesar.place(relx=0.57,rely=0.81,height=87,width=237)
    self.Procesar.configure(activebackground="blue")
    self.Procesar.configure(command=gui_support.Procesar)
    self.Procesar.configure(text='''Procesar''')
    self.Procesar.configure(width=237)


if __name__ == '__main__':
    vp_start_gui()

