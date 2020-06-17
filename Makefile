CXX=g++
CXXFLAGS=-std=c++17
LIBS=sockpp

CLIENT=Client/main.cpp
SERVER=Server/main.cpp

all: home_build phone_build

home_build: rpi-powerctl-sender_home \
			rpi-powerctl-receiver_home

phone_build: rpi-powerctl-sender_phone \
			 rpi-powerctl-receiver_phone

rpi-powerctl-sender_home: $(CLIENT)
	$(CXX) $(CLIENT) -DHOME_NET -l$(LIBS) $(CXXFLAGS) -o $@

rpi-powerctl-receiver_home: $(SERVER)
	$(CXX) $(SERVER) -DHOME_NET -l$(LIBS) $(CXXFLAGS) -o $@

rpi-powerctl-sender_phone: $(CLIENT)
	$(CXX) $(CLIENT) -DPHONE_NET -l$(LIBS) $(CXXFLAGS) -o $@

rpi-powerctl-receiver_phone: $(SERVER)
	$(CXX) $(SERVER) -DPHONE_NET -l$(LIBS) $(CXXFLAGS) -o $@

clean:
	rm -f *rpi-powerctl*
