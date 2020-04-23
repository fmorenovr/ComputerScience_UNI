package models

import (
  "errors"
  "fmt"
)

type AlertMeasured struct{
  Id_alert  string          `json:"id_alert" bson:"id_alert"`
  Type      string          `json:"type"     bson:"type"`
  Date      string          `json:"date"     bson:"date"`
  Values    []DataMeasured  `json:"values"   bson:"values"`
}

var listAlMea []AlertMeasured

func init(){}

func GetAllAlertMeasured() []AlertMeasured{
  listAlMea = alertMeasuredRequest("","","","","","","")
  return listAlMea
}

func GetAlertMeasured(Id_usuario string, Id_alert string, dateinit string, datefin string, horainit string, horafin string, last string) (listUsrxSensor []AlertMeasured, err error) {
  id_user := UsernameToId(Id_usuario)
  listAlMea = alertMeasuredRequest(id_user,Id_alert, dateinit, datefin, horainit, horafin, last)
  if listAlMea ==nil {
    fmt.Printf("\nNo se encontro Alertas !\n\n")
    return nil, errors.New("Alertas no existen")
  } else {
    return listAlMea, nil
  }
}
