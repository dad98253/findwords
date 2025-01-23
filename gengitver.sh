#!/bin/sh

GITHEAD=$(git rev-parse HEAD)
GITTAG=$(git describe --always --dirty --tags)
GITBRANCH=$(git branch --show-current)
echo "const char *gitcommit = \"$GITHEAD\";const char *gittag = \"$GITTAG\";const char *gitbranch = \"$GITBRANCH\";"  > src/gitversion.h
touch src/findwords.cpp
exit
