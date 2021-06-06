#!/usr/bin/env bash
if [[ ! -e "Doxyfile" ]]; then
  echo "docs: create doxyfile"
  doxygen -g
fi

if [[ ! -e "header.html" ]]; then
  echo "docs: create html files"
  doxygen -w html header.html footer.html stylesheet.css
fi

doxygen Doxyfile
if [[ -e /mnt/f/html ]]; then
  rm -rf /mnt/f/html
  echo "docs: delete html"
fi
cp -R html /mnt/f/
echo "docs: copy html"