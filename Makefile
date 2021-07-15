#
# Name: Eitan Raitses and Sofia Kardonik
# Date: 14 feb 2016
# 
# Note: Makefiles begin with a captal M
#   Indentation MUST be with a tab
#
# targets build, test, clean and submit are required.
# 

SHELL= /bin/bash

COPTS= -D
COPTS= -Wall

RANDOMSEED = 0
TIME = 6000
PROB = .3
FILE_O = output.csv
FILE_I = output.csv
BOATV = "0 0 chasing"
BOATU = "1000 1000 right"
ACTIVITY = chasing

all:
	make build
	make clean

build:
	make diver-prob

diver-prob: diver.c approaching.o bresenham.o chasing_prob.o classification.o detection.o Fifo.o following_prob.o randomwalk.o uMoves.o diver.h
	cc ${COPTS} -o $@ $< approaching.o bresenham.o chasing_prob.o classification.o detection.o Fifo.o following_prob.o randomwalk.o uMoves.o

diver-time: diver.c approaching.o bresenham.o chasing.o classification.o detection.o Fifo.o following.o randomwalk.o uMoves.o diver.h
	cc ${COPTS} -o $@ $< approaching.o bresenham.o chasing.o classification.o detection.o Fifo.o following.o randomwalk.o uMoves.o

run-diver-detect: diver-prob
	./diver-prob -V -R ${RANDOMSEED} -v ${BOATV} -u ${BOATU} -o ${FILE_O} -t ${TIME} -d ${FILE_I}
	
run-diver-prob: diver-prob
	./diver-prob -V -R ${RANDOMSEED} -v ${BOATV} -u ${BOATU} -o ${FILE_O} -t ${TIME} -p ${PROB}

run-detect: diver-prob
	./diver-prob -V -o ${FILE_I} -d ${ACTIVITY}
	

clean:
	-rm diver-prob diver-time approaching.o bresenham.o chasing.o chasing_prob.o classification.o detection.o Fifo.o following.o following_prob.o randomwalk.o uMoves.o

