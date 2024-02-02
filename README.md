# Embedded SW Booting
- Boot Manager for controlling jumping to Bootloader or App/Bootloader Updater based on shared flags and some integrity checks
- BootLoader for communicating with BCM to get App with both capabilities ( **Normal Update <sub>/</sub> Delta Update** ) 
- BootLoader Updater ( **Silent <sub>/</sub> Communicative** ) for updating BootLoader
- Application 
# Design 
### Memory Design
![Design](https://github.com/abdelrahman99999/Booting/blob/main/Docs/Memory%20Design.png?raw=true)
### Memory Constraints
- Boot manager Maximum Size must be <= **12.5%** of the total flash size
- BootLoader Maximum Size must be <= **18.75%** of the total flash size
- Application or Bootloader Updater Maximum Size must be <= **68.75%** of the total flash size (***they share the same memory area***)
# CI Pipeline with Jenkins
![CI_Pipeline](https://github.com/abdelrahman99999/Booting/blob/main/Docs/CI_Pipeline.png?raw=true)
# Releases

### V_2.0.1 Design Flow and next Releases
<p align="center">
  <img src="https://raw.githubusercontent.com/abdelrahman99999/Booting/5f804fc6b00bd211a19187b64c504239a5dcbb9d/Docs/Design_flow_v_2_0_1.svg" alt="Design flow"/>
</p>

### V_1.0.0 Design Flow
![Design flow](https://github.com/abdelrahman99999/Booting/blob/main/Docs/Design_flow_v_1_0_0.png?raw=true "V_1.0.0 Design Flow")


# Delta Update Feature
### The Goal
The goal is to reduce the number of bytes that are being delivered to:
- Reduce the download time – The new software needs to quickly get to the car’s gateway (e.g., head-unit) in order to start the update process
- Decrease the amount of needed memory – After the new version is delivered, there needs to be room to store it before the update is started
- Decrease the transport time between the gateway and the target ECU – In case of ECU update, the new version needs to go through the CAN/Ethernet bus, which is limited in bandwidth
- Reduce the update time – The update time depends in some cases on the amount of changes that exist in the new version
### Delta Update vs Full Image Update
![Delta](https://github.com/abdelrahman99999/Booting/blob/main/Docs/Full_Image_VS_Delta.jpg?raw=true "Delta Update vs Full Image Update")
![Delta](https://github.com/abdelrahman99999/Booting/blob/main/Docs/Full_Image_VS_Delta2.jpg?raw=true "Delta Update vs Full Image Update")
### Algorithm
The used algorithm is JojoDiff, you can find more info about it <a href="https://jojodiff.sourceforge.net/"  target="_blank" rel="noopener noreferrer" >here</a>
### How to generate Patch File by WSL 
To generate patch files you'll need to build [JojoDiff](http://jojodiff.sourceforge.net) or [JDiff.js](https://github.com/janjongboom/jdiff-js).

1. Install a recent version of [Node.js](https://nodejs.org).
2. Install JDiff.js:

    ```
    >> npm install jdiff-js -g
    ```

3. Generate a patch file via:

    ```
    >> jdiff old_SW.bin new_SW.bin old_to_new_SW.patch
    ```


# USED TOOLS
### SW TOOLS
- STM32 CubeIDE 1.11.0
- STM32 St-Link Utility
- Ubuntu WSL
- Python 3.10.8
- Cppcheck
- Jenkins
### HW TOOLS
- STM32F439zi (Nucleo-144)
- USB To TTL Module
- Micro SD Card Adapter Module
- Micro SDHC 8 GB

# Connection
## Between Microcontroller and "USB To TTL Module" (UART Connection)
- Tx of Module connected to RX of Microcontroller( pin PC11 )
- Rx of Module connected to TX of Microcontroller( pin PA0 )
- Common Ground
## Between Microcontroller and "Micro SD Card Adapter Module" (SPI Connection)
- ( pin PA5 ) : SPI SCK
- ( pin PA6 ) : SPI MISO
- ( pin PB5 ) : SPI MOSI
- ( pin PC0 ) : SPI CS
- VCC
- Common Ground


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
<img src="https://github.com/abdelrahman99999/Booting/blob/Delta_Patching_New/Docs/New%20BCM.png?raw=true" alt="BCM" hight =70% width=70% />
</p>

## Some References 
- Bootloader Design for Microcontrollers in Embedded Systems <a href="https://www.beningo.com/insights/white-papers/bootloader-design-for-microcontrollers-in-embedded-systems/#"  target="_blank" rel="noopener noreferrer" >Link</a>
- Tutorial: An SD card over SPI using STM32CubeIDE and FatFS <a href="https://01001000.xyz/2020-08-09-Tutorial-STM32CubeIDE-SD-card/"  target="_blank" rel="noopener noreferrer" >Link</a>
- JojoDiff Alternative Patch library <a href="https://github.com/janjongboom/janpatch"  target="_blank" rel="noopener noreferrer" >Link</a>

# TO DO 
- [x] Bootloader
- [x] BOOT Manager
- [x] Normal update
- [x] Silent Bootloader Updater
- [x] Communicative Bootloader Updater
- [x] Delta patching update for Application
- [x] CI
- [ ] SECURE BOOT
- [ ] Doxygen Documentation


