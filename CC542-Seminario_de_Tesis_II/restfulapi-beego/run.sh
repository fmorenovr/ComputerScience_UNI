#!/usr/bin/bash

go build main.go

mv main restfulapi-beego

rm -rf .git
rm -rf conf
rm -rf controllers
rm -rf models
rm -rf patterns
rm -rf routers
rm -rf test_database
rm main.go
rm TODO.txt
rm Readme.md
rm .gitignore
