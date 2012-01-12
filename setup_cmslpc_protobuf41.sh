#!/usr/bin/env bash

if [[ "" -ne "$PROTOBUF" ]]
then
    echo "Protobuf is already set."
else
    export PROTOBUF=$HOME/Applications/protobuf
    export PATH=$PROTOBUF/bin:$PATH
    export LD_LIBRARY_PATH=$PROTOBUF/lib:$LD_LIBRARY_PATH
    export CXXFLAGS="-I $PROTOBUF/include $CXXFLAGS"
fi
