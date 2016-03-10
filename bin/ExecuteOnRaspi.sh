#!/usr/bin/env bash

HOST="pi@192.168.0.90"

EXE="RaspiHelloWorld"

ssh ${HOST} sudo killall ${EXE}
scp -C -o 'CompressionLevel 9' -o 'IPQoS throughput' ${EXE} ${HOST}:~/bin
ssh ${HOST} sudo chmod 4775 "bin/${EXE}"

ssh ${HOST} "bin/${EXE}"
