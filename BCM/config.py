APP_NAME = "Examples\\application_green_blink.bin"
BOOTLOADER_UPDATER_NAME ="Examples\\Communicative_Bootloader_Updater_v729.bin"
BOOTLOADER_NAME = "Examples\\Bootloader_v123.bin"
DELTA_FILE_NAME = "Examples\\diff2.bin" #diff1 green/red  #diff2 red/green
APP_NAME_FOR_DELTA_PATCHING ="Examples\\application_green_blink.bin" #used to get it's digest and make sure that reconstruction of image is successfully correct

#Supported commands for bootloader
BOOTLOADER_GET_VERION_COMMAND                          = 0
BOOTLOADER_MEM_WRITE_FOR_APP_COMMAND                   = 1
BOOTLOADER_MEM_ERASE_FOR_APP_COMMAND                   = 2
BOOTLOADER_MEM_WRITE_FOR_BOOTLOADER_UPDATER_COMMAND    = 3
BOOTLOADER_MEM_ERASE_FOR_BOOTLOADER_UPDATER_COMMAND    = 4
BOOTLOADER_LEAVING_TO_BOOT_MANAGER_COMMAND             = 5
BOOTLOADER_DELTA_PATCHING_APP_COMMAND                  = 6

#Supported commands for app
APP_LEAVING_TO_BOOT_MANAGER_COMMAND    = 10

#Supported commands for Communicative bootloader updater
BOOTLOADER_UPDATER_GET_VERION_COMMAND                          = 20
BOOTLOADER_UPDATER_MEM_WRITE_FOR_BOOTLOADER_COMMAND            = 21
BOOTLOADER_UPDATER_MEM_ERASE_FOR_BOOTLOADER_COMMAND            = 22
BOOTLOADER_UPDATER_LEAVING_TO_BOOT_MANAGER_COMMAND             = 23

#UART Configuartions
BAUDRATE = 115200