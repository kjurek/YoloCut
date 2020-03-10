#!/bin/sh

make split
make detect -j`nproc`
make filter
make join
