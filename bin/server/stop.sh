#!/bin/bash

PID_OF="/bin/pidof"
READLINK="/bin/readlink"
SCRIPT_DIR="$(dirname $(${READLINK} -f $0))"

SERVER_EXEC_NAME="iqlect_time_server"

if ps ax | grep -v grep | grep ${SERVER_EXEC_NAME} > /dev/null
then
  kill -9 $(${PID_OF} ${SERVER_EXEC_NAME})
fi
