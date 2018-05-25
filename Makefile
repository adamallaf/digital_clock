CC = avr-gcc
OBJC = avr-objcopy

SRCDIR = src
OBJDIR = obj
BINDIR = bin

MCU = atmega328p
# f = 1MHz
F_CPU = 1000000

# compiler flags
CFLAGS = -Wall -Os -mmcu=$(MCU) -DF_CPU=$(F_CPU)

PORT = /dev/ttyACM0
PROGRAMMER = avrisp
BAUDRATE = 19200

# avrdude flags
PFLAGS = -P $(PORT) -c $(PROGRAMMER) -b $(BAUDRATE) -p $(MCU)

OBJS = main.o	wdt.o

all:	dirs	$(OBJS)
	$(CC) $(CFLAGS) -o $(OBJDIR)/digiclock.out $(addprefix $(OBJDIR)/,$(OBJS))
	$(OBJC) -j .text -j .data -O ihex $(OBJDIR)/digiclock.out $(BINDIR)/digiclock.hex

%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $(OBJDIR)/$@

%.o: $(SRCDIR)/%.s
	$(CC) $(CFLAGS) -c $< -o $(OBJDIR)/$@

dirs:
	+@[ -d ./$(OBJDIR) ] || mkdir $(OBJDIR)
	+@[ -d ./$(BINDIR) ] || mkdir $(BINDIR)

install:	all
	avrdude $(PFLAGS) -U flash:w:$(BINDIR)/digiclock.hex:i

clean:
	@rm -rf $(OBJDIR) $(BINDIR)
