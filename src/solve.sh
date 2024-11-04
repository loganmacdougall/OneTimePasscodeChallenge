#!/bin/bash

password=`echo 1 | ncat localhost 3000 | grep -oE '([a-zA-Z]{24})'`
echo \"$password\"

echo $password | ncat localhost 3000
