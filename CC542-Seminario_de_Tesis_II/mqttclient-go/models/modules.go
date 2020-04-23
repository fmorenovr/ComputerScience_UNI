package models

// data receive
type DataMeasured struct{
  Id_moduleiot     string  `json:"id_moduleiot"`
  Id_sensor        string  `json:"id_sensor"`
  Value            float32 `json:"value"`
  Type             string  `json:"type"`
  Date             string  `json:"date"`
}

// list of modules
type Module struct{
  Id_moduleiot       string   `json:"id_moduleiot"`
  Sensors          []Sensor   `json:"sensors"`
}

// list of sensors per module
type Sensor struct {
  Type            string  `json:"type"`
  State           string  `json:"state"`
}
