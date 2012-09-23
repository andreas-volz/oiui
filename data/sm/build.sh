#!/bin/sh
cp -f screens.edj screens.edj.bak
edje_cc $@ -id edc/images -fd /usr/share/fonts/truetype/ttf-dejavu edc/main.edc -o screens.edj
