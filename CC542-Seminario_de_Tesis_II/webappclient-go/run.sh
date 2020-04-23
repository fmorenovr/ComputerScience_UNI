#!/usr/bin/bash

go build main.go

mv main webappclient-go

rm -rf .git
rm -rf conf
rm -rf handlers
rm -rf routers
rm main.go
rm TODO.txt
rm Readme.md
rm .gitignore
