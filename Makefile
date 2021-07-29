#
# Name: Eitan Raitses and Sofia Kardonik
# Date: 14 feb 2016
# 
# Note: Makefiles begin with a captal M
#   Indentation MUST be with a tab
#
# targets build, test, and clean are required.


SHELL= /bin/bash

COPTS= -D
COPTS= -Wall

RANDOMSEED =  0
TIME = 5000
PROB = .85
FILE_O = test.csv
FILE_I = test.csv
FILE_ENTROPY = testentropy.csv
BOATV = "200 0 chasing"
BOATU = "1500 100 up"
ACTIVITY = chasing

all:
	make build
	make clean

build:
	make diver-prob getStats

diver-prob: diver.c approaching.o bresenham.o chasing_prob.o classification.o detection.o Fifo.o fish_following.o randomwalk.o uMoves.o diver.h
	cc ${COPTS} -o $@ $< approaching.o bresenham.o chasing_prob.o classification.o detection.o Fifo.o fish_following.o randomwalk.o uMoves.o

diver-time: diver.c approaching.o bresenham.o chasing.o classification.o detection.o Fifo.o following.o randomwalk.o uMoves.o diver.h
	cc ${COPTS} -o $@ $< approaching.o bresenham.o chasing.o classification.o detection.o Fifo.o following.o randomwalk.o uMoves.o

getStats: getStats.c diver.h
	cc ${COPTS} -o $@ $<

run-diver-detect: diver-prob
	./diver-prob -V -R ${RANDOMSEED} -v ${BOATV} -u ${BOATU} -o ${FILE_O} -t ${TIME} -d ${FILE_I}
	
run-diver-prob: diver-prob
	./diver-prob -V -R ${RANDOMSEED} -v ${BOATV} -u ${BOATU} -o ${FILE_O} -t ${TIME} -c ${PROB}

run-diver-no-prob: diver-prob
	./diver-prob -V -R ${RANDOMSEED} -v ${BOATV} -u ${BOATU} -o ${FILE_O} -t ${TIME}

run-detect: diver-prob
	./diver-prob -V -o ${FILE_I} -f ${FILE_ENTROPY} -d ${ACTIVITY}
	
run-diver-prob-detect: diver-prob
	make getStats
	./diver-prob -V -R ${RANDOMSEED} -v ${BOATV} -u ${BOATU} -c ${PROB} -o ${FILE_O} -t ${TIME} -d ${ACTIVITY} -f ${FILE_ENTROPY} 
	./getStats ${FILE_ENTROPY} 

run-diver-no-prob-detect: diver-prob
	make getStats
	./diver-prob -V -R ${RANDOMSEED} -v ${BOATV} -u ${BOATU} -o ${FILE_O} -t ${TIME} -d ${ACTIVITY} -f ${FILE_ENTROPY}
	./getStats ${FILE_ENTROPY} 
	
tests: diver-prob
	make getStats
	./diver-prob -V -R 12345 -v ${BOATV} -u ${BOATU} -o ${FILE_O} -t ${TIME} -d ${ACTIVITY} -f ${FILE_ENTROPY}
	./getStats testentropy.csv | grep 'Average:' | sed 's/^.*: //' >> test.out
	./getStats testentropy.csv | grep 'Variance:' | sed 's/^.*: //' >> test.out
	./diver-prob -V -R 12345 -v ${BOATV} -u ${BOATU} -c .975 -o ${FILE_O} -t ${TIME} -d ${ACTIVITY} -f ${FILE_ENTROPY} 
	./getStats testentropy.csv | grep 'Average:' | sed 's/^.*: //' >> test.out
	./getStats testentropy.csv | grep 'Variance:' | sed 's/^.*: //' >> test.out
	./diver-prob -V -R 12345 -v ${BOATV} -u ${BOATU} -c .95 -o ${FILE_O} -t ${TIME} -d ${ACTIVITY} -f ${FILE_ENTROPY} 
	./getStats testentropy.csv | grep 'Average:' | sed 's/^.*: //' >> test.out
	./getStats testentropy.csv | grep 'Variance:' | sed 's/^.*: //' >> test.out
	
	./diver-prob -V -R 67890 -v ${BOATV} -u ${BOATU} -o ${FILE_O} -t ${TIME} -d ${ACTIVITY} -f ${FILE_ENTROPY}
	./getStats testentropy.csv | grep 'Average:' | sed 's/^.*: //' >> test.out
	./getStats testentropy.csv | grep 'Variance:' | sed 's/^.*: //' >> test.out
	./diver-prob -V -R 67890 -v ${BOATV} -u ${BOATU} -c .975 -o ${FILE_O} -t ${TIME} -d ${ACTIVITY} -f ${FILE_ENTROPY} 
	./getStats testentropy.csv | grep 'Average:' | sed 's/^.*: //' >> test.out
	./getStats testentropy.csv | grep 'Variance:' | sed 's/^.*: //' >> test.out
	./diver-prob -V -R 67890 -v ${BOATV} -u ${BOATU} -c .95 -o ${FILE_O} -t ${TIME} -d ${ACTIVITY} -f ${FILE_ENTROPY} 
	./getStats testentropy.csv | grep 'Average:' | sed 's/^.*: //' >> test.out
	./getStats testentropy.csv | grep 'Variance:' | sed 's/^.*: //' >> test.out
	
	./diver-prob -V -R 54321 -v ${BOATV} -u ${BOATU} -o ${FILE_O} -t ${TIME} -d ${ACTIVITY} -f ${FILE_ENTROPY}
	./getStats testentropy.csv | grep 'Average:' | sed 's/^.*: //' >> test.out
	./getStats testentropy.csv | grep 'Variance:' | sed 's/^.*: //' >> test.out
	./diver-prob -V -R 54321 -v ${BOATV} -u ${BOATU} -c .975 -o ${FILE_O} -t ${TIME} -d ${ACTIVITY} -f ${FILE_ENTROPY} 
	./getStats testentropy.csv | grep 'Average:' | sed 's/^.*: //' >> test.out
	./getStats testentropy.csv | grep 'Variance:' | sed 's/^.*: //' >> test.out
	./diver-prob -V -R 54321 -v ${BOATV} -u ${BOATU} -c .95 -o ${FILE_O} -t ${TIME} -d ${ACTIVITY} -f ${FILE_ENTROPY} 
	./getStats testentropy.csv | grep 'Average:' | sed 's/^.*: //' >> test.out
	./getStats testentropy.csv | grep 'Variance:' | sed 's/^.*: //' >> test.out
	cat test.out
	

stats: getStats
	./getStats ${FILE_ENTROPY}

clean:
	-rm diver-prob diver-time getStats approaching.o bresenham.o chasing.o chasing_prob.o classification.o detection.o Fifo.o fish_following.o disguised_following.o randomwalk.o uMoves.o *.out *.csv

clean-csv:
	-rm *.csv
