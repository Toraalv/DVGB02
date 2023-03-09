#!/bin/bash
make pre-clean

make sim

if [ $? -eq 0 ]; then
    echo "ナイス"
else
    echo "良くない、それ"
fi

make post-clean