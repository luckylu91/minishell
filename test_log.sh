#!/bin/bash
top -pid $1 -c a | awk 'NR== 5, NR == 6 {print $7}'