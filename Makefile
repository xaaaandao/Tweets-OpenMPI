all:
	make compile
	make execute

compile:
	cd libraries/string && mpicc manipulateString.c -c
	cd libraries/tweets && mpicc generateTweets.c -c
	cd libraries/openmpi && mpicc initializeMPI.c -c
	cd libraries/files && mpicc readFile.c -c
	mpicc main.c -o main libraries/openmpi/initializeMPI.o libraries/tweets/generateTweets.o libraries/string/manipulateString.o libraries/files/readFile.o

execute:
	mpirun -np 1 main 