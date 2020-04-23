// hyper admin
// amo y señor
use admin
db.createUser({
  user: "hyper-admin",
  pwd: "smrtct",
  roles: [ "root"]
})

// super admin
// puede crear mas usuarios para una admin, pero no borrarlos
// puede crear/eliminar usuarios para cualquier otra db
// puede modificar beagons
db.createUser({
  user: "super-admin",
  pwd: "smrtct",
  roles: [
    {role: "clusterAdmin", db: "admin" },
    {role: "dbAdminAnyDatabase", db: "admin" },
    {role: "userAdminAnyDatabase", db: "admin" },
    {role: "readWriteAnyDatabase", db: "admin" }
  ]}
)

// user admin
// administra la base de datos especificada
use Beagons
db.createUser({
  user: "beagons-admin",
  pwd: "bgns",
  roles: [
    {role: "userAdmin", db: "Beagons" },
    {role: "readWrite", db: "Beagons" }
  ]}
)

// simple user
db.createUser({
  user: "pymach-user",
  pwd: "pymach",
  roles: [
    {role: "read", db: "Beagons", collection:"datameasured" }
  ]}
)

sudo mongod -f /etc/mongod.conf
sudo mongod --auth --port 2750 --dbpath /var/lib/mongodb/

mongo admin --port 2750 --username hyper-admin --password smrtct --authenticationDatabase admin

mongo admin --port 2750 --username super-admin --password smrtct --authenticationDatabase admin

mongo Beagons --port 2750 --username beagons-admin --password bgns --authenticationDatabase Beagons

mongo Beagons --port 2750 --username pymach-user --password pymach --authenticationDatabase Beagons

Export

mongoexport --db Beagons --collection users --out  users.json
mongoexport --db Beagons --collection modulesiot --out  modulesiot.json
mongoexport --db Beagons --collection datameasured --out  datameasured.json

Import

mongoimport --db Beagons --collection users --file users.json
mongoimport --db Beagons --collection modulesiot --file modulesiot.json
mongoimport --db Beagons --collection datameasured --file datameasured.json

