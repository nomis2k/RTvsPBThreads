CCC      = g++

# Subsystems that have compilable libraries
SUBSYS   = 
LIB      = libRTTree.so

# Get list of all heads, sources and objects. Each source (%.cc) whould have
# an object file except programs listed in PROGS
HEADS    = $(wildcard ./interface/*.h)
MSGS     = $(wildcard ./pb/*LinkDef.h)
DICS     = $(wildcard ./src/*LinkDef.h)
SRCS     = $(wildcard ./src/*.cc) 

OBJS       = $(foreach obj,$(addprefix ./obj/,$(patsubst %.cc,%.o,$(notdir $(SRCS)))),$(obj))

PROTOCS    = $(wildcard ./message/*.proto)
PROTOCOBJS = $(subst ./message/,./obj/,$(patsubst %.proto,%.o,$(PROTOCS)))

CINTS      = $(foreach dic,$(addprefix ./dic/,$(patsubst %.h,%.cxx,$(notdir $(DICS)))),$(subst LinkDef,Dict,$(dic)))
CINTOBJS   = $(foreach obj,$(subst ./dic/,,$(patsubst %.cxx,%.o,$(CINTS))),$(addprefix ./obj/,$(obj)))
CINTHEADS  = interface/RTEvent.h interface/RTJet.h

# List of programs with main functions to be filtered out of objects
PROGS    = $(patsubst ./src/%.cpp,%,$(wildcard ./src/*.cpp))

# Flags used in compilation
ifeq ($(strip $(DEBUG)),)
	DEBUG = -O2
else
	DEBUG = -O0 -g
endif

CXXFLAGS = ${DEBUG} -pipe -Wall -I./  -I/opt/local/include/ -I${BOOST_ROOT}/include -I${ROOTSYS}/include
LIBS     = -L/opt/local/lib -lprotobuf -lboost_filesystem -lboost_system -lboost_thread-mt -lboost_program_options
LDFLAGS  = -shared -W1 `root-config --libs`

# Rules to be always executed: empty ones
.PHONY: all

all: pb dict $(OBJS) lib $(PROGS)

help:
	@echo "make <rule>"
	@echo
	@echo "Rules"
	@echo "-----"
	@echo
	@echo "  all        compile executables"
	@echo



# Protocol Buffers
#
pb: $(PROTOCOBJS)

$(PROTOCOBJS):
	@echo "[+] Compiling Protocol Buffers ..."
	protoc -I=message --cpp_out pb $(patsubst obj/%.o,message/%.proto,$@)
	$(CCC) $(CXXFLAGS) -c $(addprefix ./pb/,$(patsubst %.o,%.pb.cc,$(notdir $@))) -o $@
	@echo



# ROOT Dictionaries
#
dict: $(CINTS) $(CINTOBJS)

$(CINTS): $(CINTHEADS)
	@echo "[+] Generating ROOT Dictionaries ..."
	rootcint $@ -c -I./ $(CINTHEADS) $(subst Dict.cxx,LinkDef.h,$(subst dic,./src,$@))
	@echo

$(CINTOBJS): $(CINTS)
	@echo "[+] Compiling ROOT Dictionaries ..."
	$(CCC) $(CXXFLAGS) -c $(addprefix ./dic/,$(patsubst %.o,%.cxx,$(notdir $@))) -o $@
	@echo



# Regular compilcation
#
$(OBJS): $(SRCS) $(HEADS)
	@echo "[+] Compiling objects ..."
	$(CCC) $(CXXFLAGS) -c $(addprefix ./src/,$(patsubst %.o,%.cc,$(notdir $@))) -o $@
	@echo



# Libraries
#
lib: $(LIB)

$(LIB): $(CINTOBJS) $(OBJS)
	@echo "[+] Generating Library ..."
	$(CCC) $(LDFLAGS) -o $(addprefix ./lib/,$@) $(CINTOBJS) obj/RTEvent.o obj/RTJet.o
	@echo



# Executables
#
$(PROGS): $(OBJS) 
	@echo "[+] Compiling programs ..."
	$(CCC) $(CXXFLAGS) `root-config --glibs` $(LIBS) $(OBJS) $(CINTOBJS) $(PROTOCOBJS) ./src/$@.cpp -o ./bin/$@
	@echo



# Cleaning
#
clean:
ifeq ($(strip $(PROGS)),)
	rm -f ./pb/*.{h,cc}
	rm -f ./obj/*.o
	rm -f $(addprefix ./lib/,$(LIB))
else
	rm -f $(addprefix ./bin/,$(PROGS))
	rm -f ./pb/*.{h,cc}
	rm -f ./obj/*.o
	rm -f ./dic/*.{h,cxx}
	rm -f $(addprefix ./lib/,$(LIB))
endif
