hashing : main.o LinearHashImplementation.o menu.o
	gcc -o hashing main.o LinearHashImplementation.o menu.o
main.o : main.c HashTableTypes.h HashTableInterface.h menuInterface.h
	gcc -c main.c
LinearHashImplementation.o : LinearHashImplementation.c HashTableTypes.h HashTableInterface.h
	gcc -c LinearHashImplementation.c
menu.o : menu.c HashTableInterface.h
	gcc -c menu.c
clean :
	rm main.o menu.o LinearHashImplementation.o
