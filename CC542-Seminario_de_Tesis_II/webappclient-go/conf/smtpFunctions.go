package conf

import (
  "fmt";
  "bytes";
  "net/http";
  "net/mail";
  "net/smtp";
  "crypto/tls";
  "html/template";
)

func SentEmails(r *http.Request, templateService string, templateUser string){
  // destino
  dest:= MailDest{
    Name: r.Form["nombres"][0],
    Last: r.Form["apellidos"][0],
    Telefono: r.Form["telefono"][0],
    Email: r.Form["email"][0],
    Message: r.Form["message"][0],
  }

  // message to mail service
  from    := mail.Address{dest.Name + " " + dest.Last, ""}
  to      := mail.Address{"BeaGons! contacto", ServerMail}
  subject := dest.Name + " " + dest.Last + ": Solicito Informacion sobre el servicio BeaGons!";
  // sent mail to service
  SentEmailtoContact(from,to,subject,dest,templateService)
  
  // message to user
  from    = mail.Address{"BeaGons! mail service",""}
  to      = mail.Address{dest.Name + " " + dest.Last, dest.Email}
  subject = "Respuesta automatica BeaGons!";
  // sent mail to user
  SentEmailtoContact(from,to,subject,dest,templateUser)
}

func SentEmailtoContact(from mail.Address, to mail.Address, subject string, dest MailDest, templateResponse string){
  // preparamos la estructura de info del mensaje
  headers := make(map[string]string)
  headers["From"] = from.String()
  headers["To"] = to.String()
  headers["Subject"] = subject
  headers["Content-Type"] = `text/html; charset="UTF-8"`

  // añadimos informacion del contacto
  message := ""
  for k,v := range headers {
    message += fmt.Sprintf("%s: %s\r\n",k,v)
  }
  
  t, err := template.ParseFiles(templateResponse)
  VerifyError(err)
  
  // añadimos el mensaje
  buffer := new(bytes.Buffer)
  err = t.Execute(buffer, dest)
  VerifyError(err)

  message += buffer.String()
  
  // autentificacion: Identidad, correo, clave, host
  auth := smtp.PlainAuth("", ServerMail, ServerPassword, Mailhost)
  
  // configuramos el DNS
  tlsConfig := &tls.Config{
    InsecureSkipVerify: true,
    ServerName: Mailhost,
  }
  
  conn, err := tls.Dial(Mailprotocol, MailDomain, tlsConfig)
  VerifyError(err)
  
  client, err := smtp.NewClient(conn, Mailhost)
  VerifyError(err)
  
  err = client.Auth(auth)
  VerifyError(err)
  
  err = client.Mail(ServerMail)
  VerifyError(err)
  
  err = client.Rcpt(to.Address)
  VerifyError(err)
  
  w, err := client.Data()
  VerifyError(err)
  
  _, err = w.Write([]byte(message))
  VerifyError(err)
  
  err = w.Close()
  VerifyError(err)
  
  defer client.Quit()
}

