#!/bin/bash
DIR=venv
if [ -d "$DIR" ];
then
    echo "$DIR directory exists."
else
	echo "$DIR directory does not exist."
    python3 -m venv $DIR
fi

source $DIR/bin/activate
