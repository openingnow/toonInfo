EXECUTABLE=toonInfo
SOURCE=$(EXECUTABLE).c toonStruct.c directory.c fillMemChunk.c regexOperation.c makeToonTable.c
CC=clang
CFLAGS=-W -Wall -pedantic
LIBS = -lcurl

all:
	$(CC) $(CFLAGS) $(LIBS) $(SOURCE) -o $(EXECUTABLE)

chunk_html:
	$(CC) $(CFLAGS) $(LIBS) $(SOURCE) -DCHUNK_HTML_TEST -o $(EXECUTABLE)
	
debug:
	$(CC) $(CFLAGS) $(LIBS) -g $(SOURCE) -o $(EXECUTABLE)
	
clean:
	rm -f ./$(EXECUTABLE)
	rm -rf $(EXECUTABLE).dSYM/