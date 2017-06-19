MODE ?= release

include confbase.mk
include $(MODE).mk

TSRC   := test.c test-hashmap.c
TESTS  := $(TSRC:.c=.test)

CFLAGS    := $(BASE_CFLAGS)    $(MODE_CFLAGS)   $(CFLAGS_FOR_TARGET)
CPPFLAGS  := $(BASE_CPPFLAGS)  $(MODE_CPPFLAGS) $(CPPFLAGS_FOR_TARGET)
ARFLAGS   := $(BASE_ARFLAGS)   $(MODE_ARFLAGS)  $(ARLAGS_FOR_TARGET)

CC := gcc
AR := ar

.PHONY: all clean tests
.PRECIOUS: $(TESTS)

all: clean tests

clean:
	-rm -f $(TESTS)

%.test : %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -I"../ds/include/ds/" -I"../testsrc/" $< ../ds/lib/libds.a ../testsrc/libds-tests.a -o $@
	chmod +x $@
	./$@

tests: $(TESTS)
