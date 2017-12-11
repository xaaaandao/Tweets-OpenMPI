all:
	make compile
	make execute

compile:
	#Verifica se o arquivo existe
	rm -f teste.txt
	cd libraries/string && mpicc manipulateString.c -c
	cd libraries/tweets && mpicc generateTweets.c -c
	cd libraries/openmpi && mpicc initializeMPI.c -c
	cd libraries/files && mpicc manipulateFiles.c -c
	cd libraries/list && mpicc manipulateList.c -c
	cd libraries/jaccard && mpicc jaccard.c -c
	mpicc main.c -lpthread -o main libraries/openmpi/initializeMPI.o libraries/tweets/generateTweets.o libraries/string/manipulateString.o libraries/files/manipulateFiles.o libraries/list/manipulateList.o libraries/jaccard/jaccard.o

execute:
	mpirun -np 1 main 

git:	
	git checkout master
	git pull origin master
	git merge xandao
	git push origin master
	git checkout xandao
