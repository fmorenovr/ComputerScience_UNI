package conf

import(
  "time";
  "regexp";
  "strings";
  "io/ioutil";
)

// verify error
func VerifyError(err error){
  if err !=nil {
    Logger.Error("%s",err)
    panic(err)
  }
}

// load page
func LoadPage(filename string) (*Page, error) {
  body, err := ioutil.ReadFile(filename)
  if err != nil {
    return nil, err
  }
  return &Page{Title: filename, Body: body}, nil
}

func VerifyEmail(email string) (bool){
  Re := regexp.MustCompile(`^[a-z0-9._%+\-]+@[a-z0-9.\-]+\.[a-z]{2,4}$`)
 	return Re.MatchString(email)
}

func LogServer(method, path, name string){
  Logger.Info("Started %s %s", method, path)
  Logger.Info("Executing BeaGons "+name+" Handler")
}

func GenerateFileName(filename string, username string) (string){
  tim := time.Now().Format("20060102150405")
  splitsName := strings.Split(filename,".")
  var lenfilename = len(splitsName)
  /*for i:=0; i<lenfilename-1;i++{
    newFileName += splitsName[i]
  }*/
  //newFileName += "_"+tim+"."+splitsName[lenfilename-1]
  newFileName := username + "_"+tim+"."+splitsName[lenfilename-1]
  return newFileName
}
