rem
rem usage: build build-dir {Debug|Release} {all|clean}
rem

setlocal

if not [%3]==[] goto :get_args
echo "Insufficient arguments"
exit /b 1

:get_args

set "build_dir=%1"
set "build_type=%2"
set "target=%3"

cd "%build_dir%"

"PATH=D:\DoNotTouch_install\STM32CubeIDE_1.11.0\STM32CubeIDE\plugins\com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.10.3-2021.10.win32_1.0.100.202210260954\tools\bin;D:\DoNotTouch_install\STM32CubeIDE_1.11.0\STM32CubeIDE\plugins\com.st.stm32cube.ide.mcu.externaltools.make.win32_2.0.100.202202231230\tools\bin;D:/DoNotTouch_install/STM32CubeIDE_1.11.0/STM32CubeIDE//plugins/com.st.stm32cube.ide.jre.win64_2.3.0.202207290817/jre/bin/server;D:/DoNotTouch_install/STM32CubeIDE_1.11.0/STM32CubeIDE//plugins/com.st.stm32cube.ide.jre.win64_2.3.0.202207290817/jre/bin;C:\WinAVR-20100110\bin;C:\WinAVR-20100110\utils\bin;C:\Program Files\Common Files\Oracle\Java\javapath;C:\Program Files (x86)\Common Files\Oracle\Java\javapath;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Windows\System32\OpenSSH\;C:\Program Files (x86)\NVIDIA Corporation\PhysX\Common;C:\Program Files\NVIDIA Corporation\NVIDIA NvDLISR;C:\Program Files (x86)\GnuWin32\bin;C:\Program Files\Microsoft SQL Server\120\Tools\Binn\;C:\Program Files\Common Files\Autodesk Shared\;C:\Program Files\Git\cmd;C:\Program Files\Graphviz\bin;C:\Program Files\dotnet\;C:\sqlite3;C:\mingw64;C:\mingw64\bin;C:\Program Files\Cppcheck;C:\Program Files (x86)\GNU Arm Embedded Toolchain\10 2021.10\bin;C:\WINDOWS\system32;C:\WINDOWS;C:\WINDOWS\System32\Wbem;C:\WINDOWS\System32\WindowsPowerShell\v1.0\;C:\WINDOWS\System32\OpenSSH\;C:\yagarto-20121222\bin;C:\Program Files (x86)\STMicroelectronics\STM32 ST-LINK Utility\ST-LINK Utility;C:\Program Files\OpenSSL-Win64\bin;C:\Program Files\OpenSSL-Win64;D:\DoNotTouch_install\Students Material\CodeBlocks + SDCC\sdcc\bin;D:\DoNotTouch_install\Students Material\CodeBlocks + SDCC\gputils\bin;C:\Program Files\MongoDB\Server\6.0\bin;C:\Program Files\mongosh;C:\Program Files (x86)\dotnet\;C:\Program Files (x86)\WinMerge;C:\Users\Lenovo\AppData\Local\Programs\Python\Python310\Scripts\;C:\Users\Lenovo\AppData\Local\Programs\Python\Python310\;C:\Program Files (x86)\GNU Arm Embedded Toolchain\10 2021.10\bin;C:\Users\Lenovo\AppData\Local\Microsoft\WindowsApps;C:\Users\Lenovo\AppData\Local\Programs\Microsoft VS Code\bin;C:\Program Files\IntelliJ\IntelliJ IDEA Community Edition 2020.3.4\bin;;C:\Program Files (x86)\qemu;C:\Users\Lenovo\AppData\Local\GitHubDesktop\bin;C:\Program Files\OpenSSL-Win64\bin;;D:\DoNotTouch_install\STM32CubeIDE_1.11.0\STM32CubeIDE"

set compiler_prefix=arm-none-eabi-

make -j12 "%target%"
