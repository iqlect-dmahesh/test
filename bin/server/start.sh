#!/bin/bash

READLINK="/bin/readlink"
SCRIPT_DIR="$(dirname $(${READLINK} -f $0))"

SERVER_EXEC_NAME="iqlect_time_server"

echo $!
if ps ax | grep -v grep | grep ${SERVER_EXEC_NAME} > /dev/null
then
  echo "${SERVER_EXEC_NAME} service running, everything is fine"
else
  ${SCRIPT_DIR}/${SERVER_EXEC_NAME}
fi
