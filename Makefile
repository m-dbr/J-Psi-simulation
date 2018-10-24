

USER_SRCS := $(wildcard *.cc)
EXE := $(patsubst %.cc,%, $(USER_SRCS))
.PHONY: all clean

 
CXXFLAGS := $(shell root-config --cflags)
LDFLAGS  := $(shell root-config --ldflags)
LDFLAGS  += -Wl,--no-as-needed
LDFLAGS  += $(shell root-config --glibs)  

all: $(EXE)

run: $(EXE)
	$(SHELL) runAll.sh $(TESTFILE) $@

clean:
	- rm -f run core $(EXE)
