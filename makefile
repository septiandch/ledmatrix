# path to STM32F103 standard peripheral library
STD_PERIPH_LIBS ?= /home/septiandc/Workspace/library/STM32-Library-V3.5
STD_PERIPH_DRIVER ?= $(STD_PERIPH_LIBS)/Libraries/STM32F10x_StdPeriph_Driver/src

# list of source files
SOURCES  = main.c
SOURCES += utils.c
SOURCES += dmd/dmdproc.c
SOURCES += dmd/dmdhal.c
SOURCES += peripherals/usart.c
SOURCES += peripherals/i2c.c
SOURCES += peripherals/rtc.c
SOURCES += peripherals/at24cxx.c
SOURCES += peripherals/fmem.c
SOURCES += prayertime/prayertime.c
SOURCES += prayertime/pdisplay.c
SOURCES += $(STD_PERIPH_LIBS)/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/system_stm32f10x.c
SOURCES += $(STD_PERIPH_DRIVER)/stm32f10x_rcc.c
SOURCES += $(STD_PERIPH_DRIVER)/stm32f10x_spi.c
SOURCES += $(STD_PERIPH_DRIVER)/stm32f10x_dma.c
SOURCES += $(STD_PERIPH_DRIVER)/stm32f10x_gpio.c
SOURCES += $(STD_PERIPH_DRIVER)/stm32f10x_usart.c
SOURCES += $(STD_PERIPH_DRIVER)/stm32f10x_i2c.c
SOURCES += $(STD_PERIPH_DRIVER)/stm32f10x_exti.c
SOURCES += $(STD_PERIPH_DRIVER)/stm32f10x_flash.c
SOURCES += $(STD_PERIPH_DRIVER)/stm32f10x_tim.c
SOURCES += $(STD_PERIPH_DRIVER)/misc.c
SOURCES += $(STD_PERIPH_LIBS)/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/startup/TrueSTUDIO/startup_stm32f10x_md.s

# name for output binary files
PROJECT ?= LedMatrix

# compiler, objcopy (should be in PATH)
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

# path to st-flash (or should be specified in PATH)
ST_FLASH ?= st-flash

# specify compiler flags
CFLAGS  = -w -g -O2 -Wall
CFLAGS += -T$(STD_PERIPH_LIBS)/Project/STM32F10x_StdPeriph_Template/TrueSTUDIO/STM3210B-EVAL/stm32_flash.ld
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m4 -mthumb-interwork
CFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16
CFLAGS += --specs=rdimon.specs
CFLAGS += -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER
CFLAGS += -Wl,--gc-sections
CFLAGS += -I.
CFLAGS += -I$(STD_PERIPH_LIBS)/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/
CFLAGS += -I$(STD_PERIPH_LIBS)/Libraries/CMSIS/CM3/CoreSupport
CFLAGS += -I$(STD_PERIPH_LIBS)/Libraries/STM32F10x_StdPeriph_Driver/inc
 
OBJS = $(SOURCES:.c=.o)

all: $(PROJECT).elf

# compile
$(PROJECT).elf: $(SOURCES)
	$(CC) $(CFLAGS) $^ -o $@
	$(OBJCOPY) -O ihex $(PROJECT).elf $(PROJECT).hex
	$(OBJCOPY) -O binary $(PROJECT).elf $(PROJECT).bin

# remove binary files
clean:
	rm -f *.o *.elf *.hex *.bin

# flash
flash:
#	$(PROGRAMMER) $(PGFLAGS)
	$(ST_FLASH) write $(PROJECT).bin 0x8000000
