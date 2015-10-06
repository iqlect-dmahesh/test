INCLUDES=./include
OBJDIR=./objs
GCC=g++
OFLAGS=
CFLAGS=-I$(INCLUDES) -c -Wall -pedantic -Werror
DBGFLAGS=-g -D__DEBUG__
SOURCES=server/s.cc \
	client/c.cc \

OBJECTS=$(SOURCES:.cc=.o)
OBJECTSD=$(SOURCES:.cc=.od)

BIN_DIR=bin
S_BIN=$(BIN_DIR)/server
C_BIN=$(BIN_DIR)/client
S_EXECNAME=iqlect_time_server
C_EXECNAME=iqlect_time_client

all: $(SOURCES) $(OBJECTS)
	$(GCC) $(OBJDIR)/server/*.o -o $(S_BIN)/$(S_EXECNAME)
	$(GCC) $(OBJDIR)/client/*.o -o $(C_BIN)/$(C_EXECNAME)

server: $(SOURCES) $(OBJECTS)
	$(GCC) $(OBJDIR)/server/*.o -o $(S_BIN)/$(S_EXECNAME)

client: $(SOURCES) $(OBJECTS)
	$(GCC) $(OBJDIR)/client/*.o -o $(C_BIN)/$(C_EXECNAME)

debug: $(SOURCES) $(OBJECTSD)

clean:
	rm -rf $(OBJDIR)

%.od:%.cc
	mkdir -p $(OBJDIR)/server $(OBJDIR)/client
	$(GCC) $(DBGFLAGS) $(CFLAGS) $< -o $(OBJDIR)/$@

%.o:%.cc
	mkdir -p $(OBJDIR)/server $(OBJDIR)/client
	$(GCC) $(OFLAGS) $(CFLAGS) $< -o $(OBJDIR)/$@


