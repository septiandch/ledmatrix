# path to selected program mode
PRGSEL ?= prg/sample

# path to STM32F103 standard peripheral library
STD_PERIPH_LIBS ?= /home/septiandc/Workspace/Program/stmlib
STD_PERIPH_STM32 ?= /Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x
STD_PERIPH_DRIVER ?= $(STD_PERIPH_LIBS)/Libraries/STM32F10x_StdPeriph_Driver/src

# list of peripheral source files
SOURCES  =	$(STD_PERIPH_LIBS)$(STD_PERIPH_STM32)/system_stm32f10x.c \
			$(STD_PERIPH_LIBS)$(STD_PERIPH_STM32)/startup/TrueSTUDIO/startup_stm32f10x_md.s \
			$(STD_PERIPH_DRIVER)/stm32f10x_rcc.c \
			$(STD_PERIPH_DRIVER)/stm32f10x_spi.c \
			$(STD_PERIPH_DRIVER)/stm32f10x_dma.c \
			$(STD_PERIPH_DRIVER)/stm32f10x_gpio.c \
			$(STD_PERIPH_DRIVER)/stm32f10x_usart.c \
			$(STD_PERIPH_DRIVER)/stm32f10x_i2c.c \
			$(STD_PERIPH_DRIVER)/stm32f10x_exti.c \
			$(STD_PERIPH_DRIVER)/stm32f10x_flash.c \
			$(STD_PERIPH_DRIVER)/stm32f10x_tim.c \
			$(STD_PERIPH_DRIVER)/misc.c

# list of main program source files
SOURCES +=	main.c \
			# $(PRGSEL)/prg_.c \
			# $(PRGSEL)/prg_.c \
			# $(PRGSEL)/prg_.c

# list of libraries source files
SOURCES +=	lib/utils.c

# list of DMD source files
SOURCES +=	dmd/dmd_prm.c \
			dmd/dmd_hal.c \
			dmd/dmd_proc.c


# name for output binary files
OBJDIR ?= .obj
PROJECT ?= $(OBJDIR)/LedMatrix

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
CFLAGS += -I$(STD_PERIPH_LIBS)/Libraries/CMSIS/CM3/CoreSupport/
CFLAGS += -I$(STD_PERIPH_LIBS)/Libraries/STM32F10x_StdPeriph_Driver/inc/

OBJS	= $(SOURCES:.c=$(OBJDIR)/%.o)

all: $(PROJECT).elf

# compile
$(PROJECT).elf: $(SOURCES)
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $^ -o $@
	$(OBJCOPY) -O ihex $(PROJECT).elf $(PROJECT).hex
	$(OBJCOPY) -O binary $(PROJECT).elf $(PROJECT).bin

# remove binary files
# rm -f *.o *.elf *.hex *.bin
clean:
	rm -f $(OBJDIR)/*.o $(OBJDIR)/*.elf $(OBJDIR)/*.hex $(OBJDIR)/*.bin
	rmdir -p $(OBJDIR)

# flash
flash:
#	$(PROGRAMMER) $(PGFLAGS)
	$(ST_FLASH) write $(PROJECT).bin 0x8000000
