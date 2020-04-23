#! /usr/bin/env python
#
# Support module generated by PAGE version 4.3.1
# In conjunction with Tcl version 8.6
#    Nov 16, 2014 07:33:31 PM


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

import csv
from biolib import *

def fillList():
    with open('motif.csv', 'rb') as f:
        reader = csv.reader(f)
        motif_list = map(tuple, reader)

    for item in motif_list:
        w.MultiListBox1.insert(END, item)

    w.MultiListBox1.selection_set(0);

def Procesar():
    idx = w.MultiListBox1.curselection()
    motif = w.MultiListBox1.get(idx[0])

    seq1 = w.Text1.get("1.0", END).strip(' \t\n\r')
    seq2 = w.Text2.get("1.0", END).strip(' \t\n\r')
    seq3 = w.Text3.get("1.0", END).strip(' \t\n\r')

    dist = w.Entry1.get()
    radio = w.Entry2.get()
    conservacion = w.Entry3.get()

    list = [seq1, seq2, seq3]
    parameters = [dist, radio, conservacion]

    bio = BioLib(list, parameters)
    bio.matchMotif(motif[2])
    bio.showMatches()

def init(top, gui, arg=None):
    global w, top_level, root
    w = gui
    top_level = top
    root = top
    fillList()

def destroy_window ():
    # Function which closes the window.
    global top_level
    top_level.destroy()
    top_level = None


