#! /bin/bash

latest_tag=`git tag --sort=-creatordate --sort=-v:refname| head -n 1`

echo "Uploading new docs.."
git clone https://github.com/cubeos/pm-tools
./pm-tools/docs/upload.py $latest_tag ./html/
