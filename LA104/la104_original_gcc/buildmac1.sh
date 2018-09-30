#!/bin/bash
#https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads

export PATH="/Users/gabrielvalky/Downloads/gcc-arm-none-eabi-7-2018-q2-update/bin/":"$PATH"
mkdir -p build
cd build

SOURCES="../source/Main.c ../source/Menu.c ../source/Bios.c ../source/GUI.c ../source/Ctrl.c ../source/Interrupt.c ../source/Analyze.c ../source/Func.c ../source/Files.c ../lib/STM32F10x_StdPeriph_Driver/src/stm32f10x_flash.c ../source/FAT12.c ../source/Disk.c ../source/Ext_Flash.c ../lib/MSD/USB_prop.c ../lib/MSD/USB_desc.c ../lib/MSD/USB_pwr.c ../lib/MSD/USB_bot.c ../lib/MSD/USB_scsi.c ../lib/MSD/USB_istr.c ../lib/STM32_USB-FS-Device_Driver/src/usb_core.c ../lib/STM32_USB-FS-Device_Driver/src/usb_regs.c ../lib/STM32_USB-FS-Device_Driver/src/usb_int.c ../lib/STM32_USB-FS-Device_Driver/src/usb_init.c ../lib/STM32_USB-FS-Device_Driver/src/usb_mem.c ../lib/STM32F10x_StdPeriph_Driver/src/stm32f10x_spi.c ../lib/STM32F10x_StdPeriph_Driver/src/stm32f10x_rcc.c ../source/STM32F103_System.c ../startup.c"
OBJECTS="Main.o Menu.o Bios.o GUI.o biosstub.o Ctrl.o Interrupt.o Analyze.o Func.o Files.o stm32f10x_flash.o FAT12.o Disk.o Ext_Flash.o USB_prop.o USB_desc.o USB_pwr.o usb_core.o usb_regs.o usb_int.o usb_init.o usb_mem.o USB_bot.o USB_scsi.o stm32f10x_spi.o USB_istr.o stm32f10x_rcc.o STM32F103_System.o startup.o"
INCLUDES="-I ../sources -I ../lib/STM32_USB-FS-Device_Driver/inc -I ../lib/MSD -I ../lib/CMSIS/Include -I ../lib/STM32F10x_StdPeriph_Driver/inc  -I .. -I ../source -I ../lib/CMSIS/Device/STM32F10x/Include"
DEFINES="-D USE_STDPERIPH_DRIVER -D STM32F10X_HD"

arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -c ../bios.s -o biosstub.o
arm-none-eabi-gcc -specs=nano.specs -specs=nosys.specs -Os -Werror -fno-common -mcpu=cortex-m3 -mthumb -MD ${DEFINES} ${INCLUDES} -c ${SOURCES}
#arm-none-eabi-gcc -Os -Werror -fno-common -mcpu=cortex-m3 -mthumb -msoft-float -MD ${DEFINES} ${INCLUDES} -c ../source/Menu.c
arm-none-eabi-gcc -specs=nano.specs -specs=nosys.specs      -mcpu=cortex-m3 -mthumb -o output.elf -nostartfiles -T ../app.lds ${OBJECTS} -lnosys


arm-none-eabi-objcopy -O binary ./output.elf ./output.bin
arm-none-eabi-objcopy -O ihex ./output.elf ./output.hex

arm-none-eabi-readelf -all output.elf > output.txt
arm-none-eabi-objdump -d -S output.elf > output.asm
