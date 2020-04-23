package main

import (
  webservice "webappclient-go/routers"
)

func main() {
  webservice.HttpListenerServiceInit("HTTP")
  //webservice.HttpListenerServiceInit("HTTPS")
  //webservice.HttpListenerServiceInit("Redirect")
}
