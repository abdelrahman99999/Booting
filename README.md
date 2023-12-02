# Embedded SW Booting
- Boot Manager
- BootLoader
- BootLoader Updater
- Application
# Initial Design 
### Memory Design
![Design](https://github.com/abdelrahman99999/Booting/blob/main/Docs/Memory%20Design.png?raw=true)
### Memory Constraints
- Boot manager Maximum Size must be <= **12.5%** of the total flash size
- BootLoader Maximum Size must be <= **18.75%** of the total flash size
- Application or Bootloader Updater Maximum Size must be <= **68.75%** of the total flash size

# Releases
### V_1.0.0 Design Flow
![Design flow](https://github.com/abdelrahman99999/Booting/blob/main/Docs/Design_flow_v_1_0_0.png?raw=true)
### V_2.0.0 Design Flow
![Design flow](https://github.com/abdelrahman99999/Booting/blob/main/Docs/Design_flow_v_2_0_0.png?raw=true)

# TOOLS
## SW TOOLS
- STM CubeIDE
- STM Link Utility
- WSL
## HW TOOLS
- stm32f439zi
- USB To TTL Module


## TO DO 
- [x] Silent Bootloader Updater
- [ ] Communicattive Bootloader Updater
- [ ] Delta patching update
- [x] Normal update
- [x] BOOT Manager
- [ ] SECURE BOOT
