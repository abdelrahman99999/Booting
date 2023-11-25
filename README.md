# Embedded SW Booting
- Boot Manager
- BootLoader
- BootLoader Updater
- Application
# Initial Design 
### Memory Design
![Design](https://github.com/abdelrahman99999/Booting/blob/main/Docs/Initial_Design.png?raw=true)
### Memory Constraints
- Boot manager Maximum Size must be <= **12.5%** of the total flash size
- BootLoader Maximum Size must be <= **18.75%** of the total flash size
- Application Maximum Size must be <= **68.75%** of the total flash size



## TO DO 
- [ ] Silent Bootloader Updater
- [ ] Communicattive Bootloader Updater
- [ ] Delta patching update
- [x] Normal update
- [x] BOOT Manager
- [ ] SECURE BOOT

