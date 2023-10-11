#!/bin/bash
#TODO: CMake
g++ -Wall -o cairo_print \
	main.cpp a4.cpp cairo_helper.cpp \
	printing_module/printer_sheet.cpp printing_module/printer_interface.cpp \
	-I. -Iprinting_module `pkg-config --cflags --libs cairo` `cups-config --cflags --libs`
