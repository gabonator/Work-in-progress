#https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads

export PATH="/Users/gabrielvalky/Downloads/gcc-arm-none-eabi-7-2018-q2-update/bin/":"$PATH"
mkdir -p build
cd build

arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -c ../bios.s
arm-none-eabi-gcc -Wall -Os -Werror -fno-common -mcpu=cortex-m3 -mthumb -msoft-float -MD -D USE_STDPERIPH_DRIVER -D STM32F10X_HD -I ../lib/CMSIS/Include -I ../lib/STM32F10x_StdPeriph_Driver/inc  -I ../ -I ../lib/CMSIS/Device/STM32F10x/Include -c ../startup.c ../interrupt.c ../lib/STM32F10x_StdPeriph_Driver/src/stm32f10x_flash.c ../lib/STM32F10x_StdPeriph_Driver/src/stm32f10x_spi.c ../lib/STM32F10x_StdPeriph_Driver/src/stm32f10x_rcc.c
arm-none-eabi-g++ -Wall -Os -Werror -fno-common -mcpu=cortex-m3 -mthumb -msoft-float -MD -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wno-psabi -c -Wall -Werror -D USE_STDPERIPH_DRIVER -D STM32F10X_HD -I ../lib/CMSIS/Include -I ../lib/STM32F10x_StdPeriph_Driver/inc  -I ../ -I ../lib/CMSIS/Device/STM32F10x/Include -c ../main.cpp ../source/Manager.cpp ../source/framework/Wnd.cpp ../source/bios/sys.cpp ../source/bios/lcd.cpp ../source/bios/memory.cpp ../source/bios/fat.cpp ../source/framework/Utils.cpp ../source/bios/dbg.cpp ../source/library/spf.c ../source/Execute.cpp ../source/Framework/Serialize.cpp ../source/bios/imports.cpp
arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -o output.elf -nostartfiles -T ../app.lds ./main.o ./startup.o ./interrupt.o ./sys.o ./Wnd.o ./lcd.o ./memory.o ./fat.o ./Utils.o ./dbg.o ./spf.o ./Execute.o ./Serialize.o ./imports.o ./stm32f10x_flash.o ./stm32f10x_spi.o ./stm32f10x_rcc.o ./Manager.o 

arm-none-eabi-objcopy -O binary ./output.elf ./output.bin
arm-none-eabi-objcopy -O ihex ./output.elf ./output.hex

arm-none-eabi-readelf -all output.elf > output.txt
arm-none-eabi-objdump -d -S output.elf > output.asm
