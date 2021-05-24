#!/bin/bash
norminette $(find src -type d -mindepth 1 -maxdepth 1 | grep -v "src/_") | ./goto.py | grep -v OK