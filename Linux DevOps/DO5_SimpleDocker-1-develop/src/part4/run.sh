#!/bin/bash

gcc -o part4 part4.c -lfcgi
service nginx start
spawn-fcgi -p 8080 -n ./part4