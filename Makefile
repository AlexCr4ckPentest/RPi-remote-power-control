C=gcc
CFLAGS=-Os -Wall

CLIENT=Client/main.c
SERVER=Server/main.c

all: rpi-powerctl-sender rpi-powerctl-receiver

rpi-powerctl-sender: $(CLIENT)
	$(C) $(CLIENT) $(CFLAGS) -o $@

rpi-powerctl-receiver: $(SERVER)
	$(C) $(SERVER) $(CFLAGS) -o $@

clean:
	rm -f *rpi-powerctl*
