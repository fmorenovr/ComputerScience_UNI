package models

// list of alerts
type Alert struct {
  Id_alert        string  `json:"id_alert"`
}

// alert recieve
type AlertMeasured struct{
  Id_alert  string          `json:"id_alert"`
  Type      string          `json:"type"`
  Date      string          `json:"date"`
  Values    []DataMeasured  `json:"values"`
}
