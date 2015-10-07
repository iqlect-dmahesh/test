#!/bin/bash

PID_OF="/bin/pidof"
READLINK="/bin/readlink"
SCRIPT_DIR="$(dirname $(${READLINK} -f $0))"

SERVER_EXEC_NAME="iqlect_time_server"

kill -9 $(${PID_OF} ${SERVER_EXEC_NAME})
