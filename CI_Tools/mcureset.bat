setlocal

set "sn=%1"
set "flash_tool=D:/DoNotTouch_install/STM32CubeProgrammer/bin/STM32_Programmer_CLI"

"%flash_tool%" --connect port=SWD sn=%1% -hardRst
