#!/usr/bin/env bash
git reset --hard origin/gh-pages
git rebase origin/master
cd ..
python setup.py develop
cd doc
make clean
make html
git ls-files ./build | grep '\.html$' | xargs git add
git ls-files ./build | grep '\.txt$' | xargs git add
git add build/html/searchindex.js
git commit --amend -C HEAD
git push -f