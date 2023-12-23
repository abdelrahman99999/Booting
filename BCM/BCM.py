import struct
import serial
import serial.tools.list_ports as ports 
import os
from Crypto.Hash import SHA256


APP_NAME ="application_green_blink.bin"
BOOTLOADER_UPDATER_NAME ="Silent_Bootloader_Updater_for_BL_v123.bin"

BOOTLOADER_GET_VERION_COMMAND                          = 0
BOOTLOADER_MEM_WRITE_FOR_APP_COMMAND                   = 1
BOOTLOADER_MEM_ERASE_FOR_APP_COMMAND                   = 2
BOOTLOADER_LEAVING_TO_BOOT_MANAGER_COMMAND             = 3
BOOTLOADER_MEM_WRITE_FOR_BOOTLOADER_UPDATER_COMMAND    = 4
BOOTLOADER_MEM_ERASE_FOR_BOOTLOADER_UPDATER_COMMAND    = 5
BOOTLOADER_LEAVING_TO_BOOTLOADER_UPDATER_COMMAND       = 6
APP_LEAVING_BOOTLOADER_ENTER_COMMAND    = 11

global ser

def CalulateBinFileLength(File_name):
    BinFileLength = os.path.getsize(File_name)
    return BinFileLength

def Open_Read_BinFile(File_name):
    fileSize = str(CalulateBinFileLength(File_name))
    BinFile = open(File_name, 'rb')
    bytes = BinFile.read()
    BinFile.close()
    return fileSize,bytes
    
def Check_Available_Serial_Ports():
    com_ports = list(ports.comports())
    if(len(com_ports) == 0):
            print("NO Available Serial Ports")
    else:
            print("[ ",end="")
            counter = -1
            for i in com_ports:
                    counter+=1       
                    print(i.device,end="") # returns 'COMx' 
                    if(counter != (len(com_ports)-1)):
                            print(", ",end="")
            print(" ]")

def Read_Serial_Port(Data_Lenth):
    
    Value_readed = ser.read(Data_Lenth) #take care from max size of input buffer
    # Value_readed_len = len(Value_readed)
    return Value_readed

def Write_Serial_Port(Data):
    count =0
    for i in Data:
        value = struct.pack('>B', i)
        ser.write(value)
        count+=1
    return count #return no of data send

def Generate_Digest(Data):
     return SHA256.new(Data).digest()

def Execute_Get_version_Command():
    ser.write(bytes([0x01, 0x00]))
    data_received = ser.read(3)
    print("Major version: ",data_received[0])
    print("Minor version: ",data_received[1])
    print("Patch version: ",data_received[2])

def Execute_MEM_ERASE_FOR_APP():
    app_size  = str(CalulateBinFileLength(APP_NAME))
    #make the variable no_bytes_to_send with 8 bytes length
    while(len(app_size) < 8):
        app_size += " "

    data_to_send =bytes([0x09, 0x02])
    ser.write(data_to_send)
    ser.write(app_size.encode())
    data_received = ser.read(1)
    if(data_received[0] == 0):
         print("Erase successfully")
    else:
         print("Erase failed")
   
def Execute_MEM_WRITE_FOR_APP():

    no_bytes_to_send ,bytes_to_send=Open_Read_BinFile(APP_NAME)
    #make the variable no_bytes_to_send with 8 bytes length
    while(len(no_bytes_to_send) < 8):
        no_bytes_to_send += " "

    digest = Generate_Digest(bytes_to_send)

    data_to_send =bytes([(1+8+32), 0x01])

    ser.write(data_to_send)  
    ser.write(no_bytes_to_send.encode())
    ser.write(digest)

    no_bytes_sent = Write_Serial_Port(bytes_to_send)
    print("Total no of bytes readed from file: ",no_bytes_to_send)
    print("Total no of bytes sent: ",no_bytes_sent)

    if no_bytes_to_send.strip() == str(no_bytes_sent) :
        print("App data sent Successfully")
    else:
        print("Failed to send data")
    
    data_received = ser.read(1)
    if(data_received[0] == 0):
         print("Flash successfully")
    else:
         print("Flash failed")

def Execute_Bootloader_Leaving_To_Boot_Manager_Command():

    data_to_send =bytes([0x01, 0x03])
    ser.write(data_to_send)
    print("starting to leave bootloader...")

def Execute_App_Leaving_Command():
    data_to_send =bytes([0x01, 0x01])
    ser.write(data_to_send)
    print("starting to leave Application...")

def Execute_MEM_ERASE_FOR_Bootloader_Updater():
    app_size  = str(CalulateBinFileLength(BOOTLOADER_UPDATER_NAME))
    #make the variable no_bytes_to_send with 8 bytes length
    while(len(app_size) < 8):
        app_size += " "

    data_to_send =bytes([0x09, 0x05])
    ser.write(data_to_send)
    ser.write(app_size.encode())
    data_received = ser.read(1)
    if(data_received[0] == 0):
         print("Erase successfully")
    else:
         print("Erase failed")

def Execute_Bootloader_Leaving_To_Bootloader_Updater_Command():

    data_to_send =bytes([0x01, 0x06])
    ser.write(data_to_send)
    print("starting to leave bootloader...")

def Execute_MEM_WRITE_FOR_Bootloader_Updater():
    no_bytes_to_send ,bytes_to_send=Open_Read_BinFile(BOOTLOADER_UPDATER_NAME)
    #make the variable no_bytes_to_send with 8 bytes length
    while(len(no_bytes_to_send) < 8):
        no_bytes_to_send += " "


    data_to_send =bytes([(1+8), 0x04])

    ser.write(data_to_send)  
    ser.write(no_bytes_to_send.encode())

    no_bytes_sent = Write_Serial_Port(bytes_to_send)
    print("Total no of bytes readed from file: ",no_bytes_to_send)
    print("Total no of bytes sent: ",no_bytes_sent)

    if no_bytes_to_send.strip() == str(no_bytes_sent) :
        print("App data sent Successfully")
    else:
        print("Failed to send data")
    
    data_received = ser.read(1)
    if(data_received[0] == 0):
         print("Flash successfully")
    else:
         print("Flash failed")     

def Execute_Command(Command):
    #for bootloader
    if(Command ==BOOTLOADER_GET_VERION_COMMAND):
        Execute_Get_version_Command()
    elif(Command ==BOOTLOADER_MEM_WRITE_FOR_APP_COMMAND):
        Execute_MEM_WRITE_FOR_APP()     
    elif(Command ==BOOTLOADER_MEM_ERASE_FOR_APP_COMMAND):
        Execute_MEM_ERASE_FOR_APP()   
    elif(Command ==BOOTLOADER_LEAVING_TO_BOOT_MANAGER_COMMAND):
        Execute_Bootloader_Leaving_To_Boot_Manager_Command()
    elif(Command ==BOOTLOADER_MEM_WRITE_FOR_BOOTLOADER_UPDATER_COMMAND):
        Execute_MEM_WRITE_FOR_Bootloader_Updater()
    elif(Command ==BOOTLOADER_MEM_ERASE_FOR_BOOTLOADER_UPDATER_COMMAND):
        Execute_MEM_ERASE_FOR_Bootloader_Updater()
    elif(Command ==BOOTLOADER_LEAVING_TO_BOOTLOADER_UPDATER_COMMAND):
        Execute_Bootloader_Leaving_To_Bootloader_Updater_Command()
    #for application
    elif(Command ==APP_LEAVING_BOOTLOADER_ENTER_COMMAND):
        Execute_App_Leaving_Command()
    elif (Command ==99):
        ser.close()
        if ser.is_open:
            print("--Port still open\n")
        else:
            print("--Port closed\n")
        exit()
     


print("Welcome To BCM")
print("-------------------")
print("There Are The Available Serial Ports")
Check_Available_Serial_Ports()
print("Enter Needed Serial Port")
port_needed =input()

try:
    ser = serial.Serial(port_needed, 115200 ,timeout=2)
except:
    print("--An exception occurred, The port may be used by another process")
    exit()
    
if ser.is_open:
    print("--Port Open Successfully")
else:
    print("--Port Open Failed\n")

while True:
    print("\n---------The Supported Commands For Bootloader---------")
    print("\tBOOTLOADER_GET_VERION_COMMAND                           - CODE: {}".format(BOOTLOADER_GET_VERION_COMMAND))
    print("\tBOOTLOADER_MEM_WRITE_FOR_APP_COMMAND                    - CODE: {}".format(BOOTLOADER_MEM_WRITE_FOR_APP_COMMAND))
    print("\tBOOTLOADER_MEM_ERASE_FOR_APP_COMMAND                    - CODE: {}".format(BOOTLOADER_MEM_ERASE_FOR_APP_COMMAND))
    print("\tBOOTLOADER_LEAVING_TO_BOOT_MANAGER_COMMAND              - CODE: {}".format(BOOTLOADER_LEAVING_TO_BOOT_MANAGER_COMMAND))
    print("\tBOOTLOADER_MEM_WRITE_FOR_BOOTLOADER_UPDATER_COMMAND     - CODE: {}".format(BOOTLOADER_MEM_WRITE_FOR_BOOTLOADER_UPDATER_COMMAND))
    print("\tBOOTLOADER_MEM_ERASE_FOR_BOOTLOADER_UPDATER_COMMAND     - CODE: {}".format(BOOTLOADER_MEM_ERASE_FOR_BOOTLOADER_UPDATER_COMMAND))
    print("\tBOOTLOADER_LEAVING_TO_BOOTLOADER_UPDATER_COMMAND        - CODE: {}".format(BOOTLOADER_LEAVING_TO_BOOTLOADER_UPDATER_COMMAND))

    print("\n---------The Supported Commands For Application---------")
    print("\tAPP_LEAVING_BOOTLOADER_ENTER_COMMAND                    - CODE: {}\n".format(APP_LEAVING_BOOTLOADER_ENTER_COMMAND))
    print("\n>>>> Enter code 99 if you want to Exit")

    Command_To_Send = input("Enter Command code : ")
    Execute_Command(int(Command_To_Send))

   


