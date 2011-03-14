#!/usr/bin/env bash

files=1
if [[ 0 -lt $# ]]
then
    files=$1
fi

events=10000
if [[ 1 -lt $# ]]
then
    events=$2
fi

rm ./data*.pb &> /dev/null
rm ./data*.root &> /dev/null

echo Generate $files files with $events events in each
echo

echo WRITING
echo =======
echo

time ./bin/write pb $files $events && echo ---===---  && time ./bin/write root $files $events
if [[ 0 -ne $? ]]
then
    exit 1
fi

echo
echo READING
echo =======
echo

time ./bin/read data*.pb && echo ---===--- && time ./bin/read data*.root
if [[ 0 -ne $? ]]
then
    exit 1
fi

echo
echo "READING (MULTITHREADS)"
echo =====================
echo

time ./bin/read --threads -1 data*.pb
if [[ 0 -ne $? ]]
then
    exit 1
fi

exit 0
