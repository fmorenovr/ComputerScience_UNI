package handlers

import (
  "fmt";
)

type Block struct {
  Try     func()
  Catch   func(Exception)
  Finally func()
}

type Exception interface{}

func Throw(up Exception) {
  panic(up)
}

func (tcf Block) Do() {
  if tcf.Finally != nil {
    defer tcf.Finally()
  }

  if tcf.Catch != nil {
    defer func() {
      if r := recover(); r != nil {
        tcf.Catch(r)
      }
    }()
  }
  tcf.Try()
}

func main() {
  fmt.Println("We started")
  Block{
    Try: func() {
      fmt.Println("I tried")
      Throw("Oh,...sh...")
    },
    Catch: func(e Exception) {
      fmt.Printf("Caught %v\n", e)
      Block{
        Try: func(){
          Throw(e)
        }, Catch: func(m Exception) {
          fmt.Printf("Caught #2 %v\n", m)
        },
      }.Do()
    },
    Finally: func() {
      fmt.Println("Finally...")
    },
  }.Do()
  fmt.Println("We went on")
}
