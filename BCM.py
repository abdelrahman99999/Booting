import serial
import serial.tools.list_ports as ports 
import os

APP_NAME ="Application.bin"
global ser

def CalulateBinFileLength():
    BinFileLength = os.path.getsize(APP_NAME)
    return BinFileLength

def Open_Read_BinFile():
    # print("size: "+ str(CalulateBinFileLength()))
    BinFile = open(APP_NAME, 'rb')
    bytes = BinFile.read()
    # print(len(bytes))
    return bytes

def Check__Available_Serial_Ports():
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

def Read_Serial_Port(Data_Len):
    
    Serial_Value = ser.read(Data_Len)
    Serial_Value_len = len(Serial_Value)
    while Serial_Value_len <= 0 and Serial_Value_len < Data_Len:
        Serial_Value = ser.read(Data_Len)
        Serial_Value_len = len(Serial_Value) + Serial_Value_len
        print("Waiting")
    return Serial_Value

print("Welcome To BCM")
print("-------------------")
print("There Are The Available Serial Ports")
Check__Available_Serial_Ports()
print("Enter Needed Serial Port")
port_needed =input()

try:
    ser = serial.Serial(port_needed, 115200 ,timeout=2)
    # ser.open()
    # ser.set_buffer_size(rx_size=10000,tx_size=10000)
except:
    print("An exception occurred, The port may be used by another process")
    exit()
    
if ser.is_open:
    print("Port Open Success")
else:
    print("Port Open Failed")



# # ser.write(b"Hello world")
# # x = ser.readline()


bytes_to_send=Open_Read_BinFile()
# for i in bytes_to_send:
#     print(i)

datalen = ser.write(bytes_to_send)
# x =Read_Serial_Port(datalen)

print(datalen)
# print(len(x))

# ser.reset_input_buffer()

ser.close()
if ser.is_open:
    print("Port still open\n")
else:
    print("\nPort closed \n")
