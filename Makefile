#
# Name: Eitan Raitses and Sofia Kardonik
# Date: 14 feb 2016
# 
# Note: Makefiles begin with a captal M
#   Indentation MUST be with a tab
#
# targets build, test, and clean are required.
# 

SHELL= /bin/bash

COPTS= -D
COPTS= -Wall

RANDOMSEED = 555
TIME = 30000
PROB = .5
FILE_O = output.csv
FILE_I = output.csv
FILE_ENTROPY = entropy.csv
BOATV = "0 0 randomwalk"
BOATU = "10000 1000 right"
ACTIVITY = randomwalk

all:
	make build
	make clean

build:
	make diver-prob getStats

diver-prob: diver.c approaching.o bresenham.o chasing_prob.o classification.o detection.o Fifo.o disguised_following.o randomwalk.o uMoves.o diver.h
	cc ${COPTS} -o $@ $< approaching.o bresenham.o chasing_prob.o classification.o detection.o Fifo.o disguised_following.o randomwalk.o uMoves.o

diver-time: diver.c approaching.o bresenham.o chasing.o classification.o detection.o Fifo.o following.o randomwalk.o uMoves.o diver.h
	cc ${COPTS} -o $@ $< approaching.o bresenham.o chasing.o classification.o detection.o Fifo.o following.o randomwalk.o uMoves.o

getStats: getStats.c diver.h
	cc ${COPTS} -o $@ $<

run-diver-detect: diver-prob
	./diver-prob -V -R ${RANDOMSEED} -v ${BOATV} -u ${BOATU} -o ${FILE_O} -t ${TIME} -d ${FILE_I}
	
run-diver-prob: diver-prob
	./diver-prob -V -R ${RANDOMSEED} -v ${BOATV} -u ${BOATU} -o ${FILE_O} -t ${TIME} -p ${PROB}

run-diver-no-prob: diver-prob
	./diver-prob -V -R ${RANDOMSEED} -v ${BOATV} -u ${BOATU} -o ${FILE_O} -t ${TIME}

run-detect: diver-prob
	./diver-prob -V -o ${FILE_I} -f ${FILE_ENTROPY} -d ${ACTIVITY}
	
run-synthesize-detect: diver-prob
	./diver-prob -V -v ${BOATV} -u ${BOATU} -p ${PROB} -o ${FILE_O} -t ${TIME} -d ${ACTIVITY} -f ${FILE_ENTROPY} 

stats: getStats
	./getStats ${FILE_ENTROPY}

clean:
	-rm diver-prob diver-time getStats approaching.o bresenham.o chasing.o chasing_prob.o classification.o detection.o Fifo.o following.o disguised_following.o randomwalk.o uMoves.o

clean-csv:
	-rm *.csv