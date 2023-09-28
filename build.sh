#!/bin/bash
g++ -Wall -o cairo_print main.cpp a4.cpp cairo_helper.cpp -I. `pkg-config --cflags --libs cairo` `cups-config --cflags --libs`
