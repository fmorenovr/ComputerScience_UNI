from pymongo import MongoClient
from datetime import datetime
import pymongo

#pip install pymongo

client = MongoClient()
#client = MongoClient("mongodb://mongodb0.example.net:27019")
db = client.test
#db = client['primer']
coll = db.dataset
#coll = db['dataset']

print coll
'''
result = db.restaurants.insert_one(
    {
        "address": {
            "street": "2 Avenue",
            "zipcode": "10075",
            "building": "1480",
            "coord": [-73.9557413, 40.7720266]
        },
        "borough": "Manhattan",
        "cuisine": "Italian",
        "grades": [
            {
                "date": datetime.strptime("2014-10-01", "%Y-%m-%d"),
                "grade": "A",
                "score": 11
            },
            {
                "date": datetime.strptime("2014-01-16", "%Y-%m-%d"),
                "grade": "B",
                "score": 17
            }
        ],
        "name": "Vella",
        "restaurant_id": "41704620"
    }
)

print result.inserted_id
'''
cursor = db.restaurants.find()
for document in cursor:
  print(document)
print "meow"

# buscar un objeto
cursor = db.restaurants.find({"borough": "Manhattan"})
for document in cursor:
  print(document)

# para buscar un objeto con su subobjeto
cursor = db.restaurants.find({"address.zipcode": "10075"})
for document in cursor:
  print(document)

# para buscar un objeto en un array
cursor = db.restaurants.find({"grades.grade": "B"})
for document in cursor:
  print(document)

# para filtrar datos
cursor = db.restaurants.find({"grades.score": {"$gt": 30}})
for document in cursor:
  print(document)

# AND
cursor = db.restaurants.find({"cuisine": "Italian", "address.zipcode": "10075"})

# OR
cursor = db.restaurants.find({"$or": [{"cuisine": "Italian"}, {"address.zipcode": "10075"}]})

# SORT
cursor = db.restaurants.find().sort([
    ("borough", pymongo.ASCENDING),
    ("address.zipcode", pymongo.ASCENDING)
])

# update el primero con las condiciones de name = Juni
result = db.restaurants.update_one(
    {"name": "Juni"},
    {
        "$set": {
            "cuisine": "American (New)"
        },
        "$currentDate": {"lastModified": True}
    }
)

# embedded field
result = db.restaurants.update_one(
    {"restaurant_id": "41156888"},
    {"$set": {"address.street": "East 31st Street"}}
)

# update todos con las condiciones de cuisine:other y address.zipcode=10016
result = db.restaurants.update_many(
    {"address.zipcode": "10016", "cuisine": "Other"},
    {
        "$set": {"cuisine": "Category To Be Determined"},
        "$currentDate": {"lastModified": True}
    }
)


# reemplazar toda una fila (o documento)
result = db.restaurants.replace_one(
    {"restaurant_id": "41704620"},
    {
        "name": "Vella 2",
        "address": {
            "coord": [-73.9557413, 40.7720266],
            "building": "1480",
            "street": "2 Avenue",
            "zipcode": "10075"
        }
    }
)

# borrar
result = db.restaurants.delete_many({"borough": "Manhattan"})

# borrar todo
result = db.restaurants.delete_many({})

# eliminar base datos restauransts
db.restaurants.drop()
