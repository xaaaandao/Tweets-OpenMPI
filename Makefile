compile:
	make remove
	cd libraries/string && mpicc manipulateString.c -c
	cd libraries/tweets && mpicc generateTweets.c -c
	cd libraries/openmpi && mpicc initializeMPI.c -c
	cd libraries/files && mpicc manipulateFiles.c -c
	cd libraries/list && mpicc manipulateList.c -c
	cd libraries/jaccard && mpicc jaccard.c -c
	mpicc main.c -lpthread -o main libraries/openmpi/initializeMPI.o libraries/tweets/generateTweets.o libraries/string/manipulateString.o libraries/files/manipulateFiles.o libraries/list/manipulateList.o libraries/jaccard/jaccard.o

execute-l:
	make remove
	mpirun -np $(NP) ./main -f $(FILE)

execute-r:
	make remove
	mpirun -np $(NP) -hosts $(IP) ./main -f $(FILE)

remove:
	rm -f /home/xandao/cloud/Tweets-OpenMPI/teste.txt 
	rm -f /home/xandao/cloud/Tweets-OpenMPI/output.txt

