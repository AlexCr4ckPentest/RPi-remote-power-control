# Rasberry_Pi-remote-power-control
For personal use only

## Dependencies
1. C++ Compiler (with C++17 support)
1. [Sockpp](https://github.com/fpagliughi/sockpp) (Modern C++ socket library)
1. Rasberry Pi and installed Rasberry Pi OS xD

## Building
1. Run `make all` or `make` for build all versions
1. Run `make home_net` for build version for home local network
1. Run `make phone_net` for build version for phone local network
1. Run `make clean` for delete all binaries

## Installing and using
### Server (receiver)
1. Copy `rpi-powerctl-receiver_home` or `rpi-powerctl-receiver_phone` to the Rasberry Pi (path - /usr/bin)
1. Configure the service entity for systemd ([See here](https://www.dexterindustries.com/howto/run-a-program-on-your-raspberry-pi-at-startup/) (Method 4: SYSTEMD))
1. Enable new configured service: `sudo systemstl enable <service_entity>.service`
1. Reboot Rasberry Pi
1. Check service status: `sudo systemctl status <service_entity>.service`
1. That's all! Now the receiver service is listening for connections on port 4455

### Client
1. If you not configured receiver - configure it
1. Run `rpi-powerctl-sender_home <command>` or `rpi-powerctl-sender_phone <command>`
#### Power control commands
1. `reboot` - reboot the Rasberry Pi
1. `poweroff` - poweroff the Rasberry Pi
