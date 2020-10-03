C=gcc
CFLAGS=-Os -Wall

CLIENT=Client/main.c
SERVER=Server/main.c

all: rpi-powerctl-sender_home rpi-powerctl-sender_hotspot rpi-powerctl-receiver

rpi-powerctl-sender_home: $(CLIENT)
	$(C) $(CLIENT) -DHOME_LAN_NETWORK $(CFLAGS) -o $@

rpi-powerctl-sender_hotspot: $(CLIENT)
	$(C) $(CLIENT) -DHOTSPOT_LAN_NETWORK $(CFLAGS) -o $@

rpi-powerctl-receiver: $(SERVER)
	$(C) $(SERVER) $(CFLAGS) -o $@

clean:
	rm -f *rpi-powerctl*
