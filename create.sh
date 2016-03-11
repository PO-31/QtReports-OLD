#!/bin/bash

#export REPO_PATH=git@github.com:tgockel/nginxconfig.git
#export HTML_PATH=build/doc/html
#export COMMIT_USER="Documentation Builder"
#export COMMIT_EMAIL="travis@gockelhut.com"
#export CHANGESET=$(git rev-parse --verify HEAD)

sudo apt-get install --yes doxygen

#mkdir -p ${HTML_PATH}

#cd $TRAVIS_BUILD_DIR
#git clone -b gh-pages "${REPO_PATH}" --single-branch ${HTML_PATH}
#git clone "https://github.com/PO-21/PO-21.github.io.git"
#cd PO-21.github.io
rm -r -f -d html
doxygen Doxyfile