def convert_binary_to_c_array(input_file, output_file, array_name):
    with open(input_file, 'rb') as file:
        binary_data = file.read()

    with open(output_file, 'w') as file:
        file.write(f"uint8_t {array_name}[] = {{\n")
        
        for byte in binary_data:
            file.write(f"0x{byte:02x}, ")
        
        file.write("\n};\n")


input_file = 'bootloader_v345.bin'
output_file = 'output.c'
array_name = 'bootloader_as_array'
convert_binary_to_c_array(input_file, output_file, array_name)