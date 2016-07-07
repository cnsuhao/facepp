#!/bin/bash
libdir="thirdparth"
if [ ! -d "libs" ]; then
	cd $libdir
    sh install.sh
else
    echo "libs already install"
fi
