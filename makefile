# program name
PRGNAME ?= pakwahyu_v2

# path to selected program name
PRGSEL ?= program/$(PRGNAME)

# path to STM32F103 standard peripheral library
STD_PERIPH_LIBS ?= /home/septiandc/Workspace/Program/stmlib
STD_PERIPH_STM32 ?= /Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x
STD_PERIPH_DRIVER ?= $(STD_PERIPH_LIBS)/Libraries/STM32F10x_StdPeriph_Driver/src

# list of main program source files
SOURCES =	$(PRGSEL)/prg_main.c \
			$(PRGSEL)/prg_io.c \
			$(PRGSEL)/prg_disp.c \
			$(PRGSEL)/prg_cmd.c
			#	$(PRGSEL)/prg_.c
			
SOURCES +=	common/usart.c \
			#	common/qfplib.s \
			#	common/qfpio.s \
			#	common/qfplibm.c

# list of peripheral source files
SOURCES +=	$(STD_PERIPH_LIBS)$(STD_PERIPH_STM32)/system_stm32f10x.c \
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

# list of common libraries source files
SOURCES +=	common/utils.c          \
			common/i2c.c            \
			common/delay.c

# list of external device libraries source files
SOURCES +=	library/rtc/ds1307.c \
			library/eeprom/at24cxx.c \
			library/dmd/dmd_hal.c \
			library/dmd/dmd_proc.c

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
CFLAGS += -T$(STD_PERIPH_LIBS)/Linker/stm32f103.ld
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m3 -mthumb-interwork
CFLAGS += --specs=rdimon.specs
CFLAGS += -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER
CFLAGS += -Wl,--gc-sections
CFLAGS += -I.
CFLAGS += -I$(STD_PERIPH_LIBS)/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/
CFLAGS += -I$(STD_PERIPH_LIBS)/Libraries/CMSIS/CM3/CoreSupport/
CFLAGS += -I$(STD_PERIPH_LIBS)/Libraries/STM32F10x_StdPeriph_Driver/inc/

# exclude standard C libraries. We will use newlib.
# CFLAGS += -nostdlib
# wrap the __aeabi functions in gcc to become __wrap___aeabi so that we can rewrite them.
# CFLAGS += -Wl,-wrap,__aeabi_d2f "
CFLAGS += -Wl,--wrap=__aeabi_d2iz
CFLAGS += -Wl,--wrap=__aeabi_d2uiz
CFLAGS += -Wl,--wrap=__aeabi_dadd
CFLAGS += -Wl,--wrap=__aeabi_dcmpeq
CFLAGS += -Wl,--wrap=__aeabi_dcmpge
CFLAGS += -Wl,--wrap=__aeabi_dcmpgt
CFLAGS += -Wl,--wrap=__aeabi_dcmple
CFLAGS += -Wl,--wrap=__aeabi_dcmplt
CFLAGS += -Wl,--wrap=__aeabi_dcmpun
CFLAGS += -Wl,--wrap=__aeabi_ddiv
CFLAGS += -Wl,--wrap=__aeabi_dmul
CFLAGS += -Wl,--wrap=__aeabi_dsub
# CFLAGS += -Wl,-wrap,__aeabi_f2d
CFLAGS += -Wl,--wrap=__aeabi_fadd
CFLAGS += -Wl,--wrap=__aeabi_fdiv
CFLAGS += -Wl,--wrap=__aeabi_fmul
CFLAGS += -Wl,--wrap=__aeabi_fsub
# CFLAGS += -Wl,-wrap,__aeabi_i2d
# CFLAGS += -Wl,-wrap,__aeabi_ui2d
# CFLAGS += -Wl,-wrap,__powidf2
# for unwrapped __aeabi functions, link with libgcc.a.
# wrap the gcc floating-point functions.
CFLAGS += -Wl,--wrap=__addsf3
CFLAGS += -Wl,--wrap=__divsf3
CFLAGS += -Wl,--wrap=__mulsf3
CFLAGS += -Wl,--wrap=__subsf3

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
