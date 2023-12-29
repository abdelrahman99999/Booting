# Embedded SW Booting
- Boot Manager
- BootLoader
- BootLoader Updater (Silent / Communicative)
- Application
# Design 
### Memory Design
![Design](https://github.com/abdelrahman99999/Booting/blob/main/Docs/Memory%20Design.png?raw=true)
### Memory Constraints
- Boot manager Maximum Size must be <= **12.5%** of the total flash size
- BootLoader Maximum Size must be <= **18.75%** of the total flash size
- Application or Bootloader Updater Maximum Size must be <= **68.75%** of the total flash size

# Releases

### V_2.0.1 Design Flow
<p align="center">
  <img src="https://raw.githubusercontent.com/abdelrahman99999/Booting/5f804fc6b00bd211a19187b64c504239a5dcbb9d/Docs/Design_flow_v_2_0_1.svg" alt="Design flow"/>
</p>

### V_1.0.0 Design Flow
![Design flow](https://github.com/abdelrahman99999/Booting/blob/main/Docs/Design_flow_v_1_0_0.png?raw=true "V_1.0.0 Design Flow")


# USED TOOLS
### SW TOOLS
- STM32 CubeIDE 1.11.0
- STM32 St-Link Utility
- WSL
- Python 3.10.8
### HW TOOLS
- STM32F439zi (Nucleo-144)
- USB To TTL Module

# Connection
## Between Microcontroller and "USB To TTL Module"
- Common Ground
- Tx of Module connected to RX of Microcontroller( pin PC11 )
- Rx of Module connected to TX of Microcontroller( pin PA0 )

# How to Try
1. Flash the boot manager manually (just for first time) using STM32 St-Link Utility
2. Flash bootloader manually (just for first time) using STM32 St-Link Utility
3. Run BCM python Script by 
```cmd
>> cd BCM
>> python.exe BCM.py
```
4. Use Serial Port that used by "USB To TTL Module"
5. Enjoy Communicating  with Bootloader / APP / Bootloader Updater

## BCM
<p align="center">
<img src="https://github.com/abdelrahman99999/Booting/blob/main/Docs/BCM.png?raw=true" alt="BCM" hight =50% width=50% />
</p>

# TO DO 
- [x] Silent Bootloader Updater
- [x] Communicative Bootloader Updater
- [ ] Delta patching update
- [x] Normal update
- [x] BOOT Manager
- [ ] SECURE BOOT
- [ ] Doxygen Documentation
