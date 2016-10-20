CC = gcc -pedantic
CFLAGS = -Wall -g

testObjectFile : testObjectFile.o object.o types.h
	$(CC) $(CFLAGS) -o testObjectFile testObjectFile.o object.o


testObjectFile.o : testObjectFile.c object.h object.c types.h
	$(CC) $(CFLAGS) -c  testObjectFile.c

object.o : object.c object.h types.h
	$(CC) $(CFLAGS) -c object.c


clean : 
	rm -f *.o testObjectFile
