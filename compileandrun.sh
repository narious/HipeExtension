#!/bin/bash
make clean;
make;
echo "=================running main===================="
./main "templatehtml_css/index.html" "templatehtml_css/style.css";