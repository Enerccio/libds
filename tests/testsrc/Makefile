MODE ?= release

include confbase.mk
include $(MODE).mk

HSRC   := $(wildcard *.h)
SRC    := $(wildcard *.c)
OBJ    := $(SRC:.c=.o)
DEP    := $(SRC:.c=.d)
-include $(DEP)

CFLAGS    := $(BASE_CFLAGS)    $(MODE_CFLAGS)   $(CFLAGS_FOR_TARGET)
CPPFLAGS  := $(BASE_CPPFLAGS)  $(MODE_CPPFLAGS) $(CPPFLAGS_FOR_TARGET)
ARFLAGS   := $(BASE_ARFLAGS)   $(MODE_ARFLAGS)  $(ARLAGS_FOR_TARGET)

CC := gcc
AR := ar

.PHONY: all clean

all: libds-tests.a

clean:
	-rm -f $(OBJ)
	-rm -f $(wildcard *.d)
	-rm libds-tests.a

%.o : %.c
	$(CC) -MM -MF $(patsubst %.o,%.d,$@) $(CFLAGS) $(CPPFLAGS) -c $<
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

libds-tests.a: $(OBJ)
	$(AR) ${ARFLAGS} -rcs $@ $(OBJ)
