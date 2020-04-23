package patterns

import (
  "sync";
  "gopkg.in/mgo.v2";
)

type singletonMongoDBSession struct {
  session *mgo.Session
  errDial error
}

var instance *singletonMongoDBSession
var once sync.Once

func GetSessErrMongoDBSession(dialInfo string) (*mgo.Session, error){
  var instance *singletonMongoDBSession
  if dialInfo == "Dial"{
    instance = NewMongoDBSession()
  } else if dialInfo == "DialWithInfo"{
    instance = NewMongoDBSessionInfo()
  }
  return instance.session, instance.errDial
}

func NewMongoDBSession() (*singletonMongoDBSession) {
  once.Do(func() {
    sess, err := mgo.Dial(urldb)
    instance = &singletonMongoDBSession{session: sess, errDial: err}
  })
  return instance
}

func NewMongoDBSessionInfo() (*singletonMongoDBSession) {
  once.Do(func() {
    sess, err := mgo.DialWithInfo(mongoDBDialInfo)
    instance = &singletonMongoDBSession{session: sess, errDial: err}
  })
  return instance
}

func NewMongoDBSessionClassic() *singletonMongoDBSession {
  if instance == nil {
    instance = &singletonMongoDBSession{}   // <--- NOT THREAD SAFE
  }
  return instance
}
