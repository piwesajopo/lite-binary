#!/usr/bin/env zsh
if [[ -z "$@" ]] ; then
   echo "Usage: $0 [command]" 
   echo "Where [command] is the command you want to execute inside gcc:latest"
   exit
fi
echo "Running on gcc container: $@"
docker run --rm -v "$PWD":/usr/src/myapp -w /usr/src/myapp gcc:latest $@
