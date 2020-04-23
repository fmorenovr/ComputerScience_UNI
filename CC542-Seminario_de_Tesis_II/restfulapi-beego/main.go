package main

import (
  restservice "restfulapi-beego/conf"
)

func main() {
  restservice.RestfulAPIServiceInit("HTTP")
  //restservice.RestfulAPIServiceInit("HTTPS")
}
