SYSROOT ?= 
PREFIX ?= /usr
LIBPATH ?= ${SYSROOT}${PREFIX}/lib
INCPATH ?= ${SYSROOT}${PREFIX}/include
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

all: libds.a

clean: 
	-rm -f $(OBJ)
	-rm -f $(wildcard *.d)
	-rm ${LIBPATH}/libds.a
	
%.o : %.c 
	$(CC) -MM -MF $(patsubst %.o,%.d,$@) $(CFLAGS) $(CPPFLAGS) -I"${INCPATH}" -c $<
	$(CC) $(CFLAGS) $(CPPFLAGS) -I"${INCPATH}" -c $< -o $@
	
libds.a: $(OBJ) 
	-mkdir ${INCPATH}/ds
	cp *.h ${INCPATH}/ds -r 
	$(AR) ${ARFLAGS} -rcs ${LIBPATH}/$@ $(OBJ)