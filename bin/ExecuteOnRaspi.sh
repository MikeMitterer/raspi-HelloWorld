#!/usr/bin/env bash

HOST="pi@192.168.0.90"

EXE="RaspiHelloWorld"

ssh ${HOST} sudo killall ${EXE}
ssh ${HOST} "bin/${EXE}"
#ssh ${HOST} sudo chmod 4775 "bin/${EXE}"


