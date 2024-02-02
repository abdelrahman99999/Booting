rem
rem usage: flash st-link-sn image-file
rem

setlocal


if not [%2]==[] goto :get_args
echo "Missing arguments"
exit /b 1

:get_args

set "sn=%1"
set "image_file=%2"
set "flash_tool=D:/DoNotTouch_install/STM32CubeProgrammer/bin/STM32_Programmer_CLI"
set "flash_start_addr=%3"

"%flash_tool%" --connect port=SWD sn=%sn% --download "%image_file%" %flash_start_addr% -hardRst
