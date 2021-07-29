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
TIME = 1000
PROB = .85
FILE_O = test.csv
FILE_D = detection.csv
BOATV = "200 0 randomwalk"
BOATU = "1500 100 up"

all:
	make build
	make clean

build:
	make diver-prob getStats

diver-prob: diver.c approaching.o bresenham.o chasing_prob.o classification.o detection.o Fifo.o fish_following.o randomwalk.o uMoves.o mix_states.o diver.h
	cc ${COPTS} -o $@ $< approaching.o bresenham.o chasing_prob.o classification.o detection.o Fifo.o fish_following.o randomwalk.o uMoves.o mix_states.o

getStats: getStats.c diver.h
	cc ${COPTS} -lm -o $@ $<
	
run-diver: diver-prob
	./diver-prob -V -R ${RANDOMSEED} -v ${BOATV} -u ${BOATU} -o ${FILE_O} -t ${TIME}

run-diver-detect: diver-prob
	make getStats
	./diver-prob -V -R ${RANDOMSEED} -v ${BOATV} -u ${BOATU} -o ${FILE_O} -t ${TIME} -d -f ${FILE_D}
	./getStats ${FILE_D} 

run-diver-prob: diver-prob
	./diver-prob -V -R ${RANDOMSEED} -v ${BOATV} -u ${BOATU} -o ${FILE_O} -t ${TIME} -c ${PROB}

run-diver-prob-detect: diver-prob
	make getStats
	./diver-prob -V -R ${RANDOMSEED} -v ${BOATV} -u ${BOATU} -o ${FILE_O} -t ${TIME} -c ${PROB}  -d -f ${FILE_D} 
	./getStats ${FILE_D} 

run-detect: diver-prob
	./diver-prob -V -o ${FILE_O} -f ${FILE_D} -d 
	
stats: getStats
	./getStats ${FILE_D}	

tests: diver-prob
	make getStats
	./diver-prob -V -R 12345 -v ${BOATV} -u ${BOATU} -o ${FILE_O} -t ${TIME} -d -f ${FILE_D}
	./getStats testentropy.csv | grep 'Average:' | sed 's/^.*: //' >> test.out
	./getStats testentropy.csv | grep 'Variance:' | sed 's/^.*: //' >> test.out
	./diver-prob -V -R 12345 -v ${BOATV} -u ${BOATU} -c .975 -o ${FILE_O} -t ${TIME} -d -f ${FILE_D} 
	./getStats testentropy.csv | grep 'Average:' | sed 's/^.*: //' >> test.out
	./getStats testentropy.csv | grep 'Variance:' | sed 's/^.*: //' >> test.out
	./diver-prob -V -R 12345 -v ${BOATV} -u ${BOATU} -c .95 -o ${FILE_O} -t ${TIME} -d -f ${FILE_D} 
	./getStats testentropy.csv | grep 'Average:' | sed 's/^.*: //' >> test.out
	./getStats testentropy.csv | grep 'Variance:' | sed 's/^.*: //' >> test.out
	
	./diver-prob -V -R 67890 -v ${BOATV} -u ${BOATU} -o ${FILE_O} -t ${TIME} -d -f ${FILE_D}
	./getStats testentropy.csv | grep 'Average:' | sed 's/^.*: //' >> test.out
	./getStats testentropy.csv | grep 'Variance:' | sed 's/^.*: //' >> test.out
	./diver-prob -V -R 67890 -v ${BOATV} -u ${BOATU} -c .975 -o ${FILE_O} -t ${TIME} -d -f ${FILE_D} 
	./getStats testentropy.csv | grep 'Average:' | sed 's/^.*: //' >> test.out
	./getStats testentropy.csv | grep 'Variance:' | sed 's/^.*: //' >> test.out
	./diver-prob -V -R 67890 -v ${BOATV} -u ${BOATU} -c .95 -o ${FILE_O} -t ${TIME} -d -f ${FILE_D} 
	./getStats testentropy.csv | grep 'Average:' | sed 's/^.*: //' >> test.out
	./getStats testentropy.csv | grep 'Variance:' | sed 's/^.*: //' >> test.out
	
	./diver-prob -V -R 54321 -v ${BOATV} -u ${BOATU} -o ${FILE_O} -t ${TIME} -d -f ${FILE_D}
	./getStats testentropy.csv | grep 'Average:' | sed 's/^.*: //' >> test.out
	./getStats testentropy.csv | grep 'Variance:' | sed 's/^.*: //' >> test.out
	./diver-prob -V -R 54321 -v ${BOATV} -u ${BOATU} -c .975 -o ${FILE_O} -t ${TIME} -d -f ${FILE_D} 
	./getStats testentropy.csv | grep 'Average:' | sed 's/^.*: //' >> test.out
	./getStats testentropy.csv | grep 'Variance:' | sed 's/^.*: //' >> test.out
	./diver-prob -V -R 54321 -v ${BOATV} -u ${BOATU} -c .95 -o ${FILE_O} -t ${TIME} -d -f ${FILE_D} 
	./getStats testentropy.csv | grep 'Average:' | sed 's/^.*: //' >> test.out
	./getStats testentropy.csv | grep 'Variance:' | sed 's/^.*: //' >> test.out
	cat test.out

clean:
	-rm diver-prob getStats *.o *.out *.csv

clean-csv:
	-rm *.csv
