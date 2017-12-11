compile:
	make remove
	cd libraries/string && mpicc manipulateString.c -c
	cd libraries/tweets && mpicc generateTweets.c -c
	cd libraries/openmpi && mpicc initializeMPI.c -c
	cd libraries/files && mpicc manipulateFiles.c -c
	cd libraries/list && mpicc manipulateList.c -c
	cd libraries/jaccard && mpicc jaccard.c -c
	mpicc main.c -lpthread -o main libraries/openmpi/initializeMPI.o libraries/tweets/generateTweets.o libraries/string/manipulateString.o libraries/files/manipulateFiles.o libraries/list/manipulateList.o libraries/jaccard/jaccard.o

execute:
	make remove
	mpirun -np $(NP) ./main -f dataset_A_SBSC_500.json

remove:
	rm -f teste.txt

git:	
	make remove
	git checkout master
	git pull origin master
	git merge xandao
	git push origin master
	git checkout xandao
