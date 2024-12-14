CC = gcc
WFLAGS = -Wno-deprecated-declarations
WFLAGS += -Wall

demo: demo.c device.o mbuffer.o
	$(CC) $(WFLAGS) demo.c device.o mbuffer.o -o demo -lopenal -lsndfile -lm

device.o: SoundDevice.c SoundDevice.h
	$(CC) $(WFLAGS) -I/usr/local/include -c SoundDevice.c -o device.o

mbuffer.o: MusicBuffer.c MusicBuffer.h
	$(CC) $(WFLAGS) -I/usr/local/include -c MusicBuffer.c -o mbuffer.o

sample: sample.c
	$(CC) $(WFLAGS) -o sample sample.c -lopenal -lm

clean:
	rm demo device.o mbuffer.o
