# RPi-remote-power-control
Simple utility for remote power control for Rasberry Pi

## Dependencies
1. C Compiler
1. Raspberry Pi and installed Raspberry Pi OS xD

## Building
1. Run `make all` or `make` for build all
1. Run `make rpi-powerctl-sender` for command sender (client)
1. Run `make rpi-powerctl-receiver` for build receiver (server)
1. Run `make clean` for delete all binaries

## Installing and using
### Server (receiver)
1. Copy `rpi-powerctl-receiver` executable file to the Raspberry Pi (path - /usr/bin)
1. Configure the service entity for systemd ([See here -> Method 4: SYSTEMD](https://www.dexterindustries.com/howto/run-a-program-on-your-raspberry-pi-at-startup/))
1. Enable new configured service: `sudo systemctl enable <service_entity>.service`
1. Reboot Raspberry Pi
1. Check service status: `sudo systemctl status <service_entity>.service`
1. That's all! Now the receiver service is listening for connections on port 4455
### Client (sender)
1. If you not configured receiver - configure it
1. Run `./rpi-powerctl-sender` for show help
