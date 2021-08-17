#!/usr/bin/bash

echo "Init simulation brenchmark"

go run *.go --broker tcp://localhost:1883 --count 100 --size 100 --clients 100 --qos 2 --format text

echo "Finalize simulation brenchmark"
