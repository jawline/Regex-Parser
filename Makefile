ifeq "$(OS)" ""
	OS = $(shell uname -s)
endif

#Output executable
OUTPUT_DIR  = ./bin/
OUTPUT_FILE = regexpm

OUTPUT_LIB_NAME  = regexpm

ifeq "$(OS)" "Darwin"
	OUTPUT_LIB = lib$(OUTPUT_LIB_NAME).dylib
else
	OUTPUT_LIB = lib$(OUTPUT_LIB_NAME).so
endif

EXECUTABLE  = $(OUTPUT_DIR)$(OUTPUT_FILE)
LIBRARY     = $(OUTPUT_DIR)$(OUTPUT_LIB)

#Directory information
OBJ_DIR=obj

INSTALL_EXE_PATH = /usr/bin/
INSTALL_LIB_PATH = /usr/lib/
INSTALL_INCLUDE_PATH = /usr/local/include/regexpm/

#Compiler settings
CC=gcc
CFLAGS=-c -Wall -ggdb -fPIC
LDFLAGS=-ggdb

#Rules to find source code - NOTE: Look for a better way to scan directories. Nonrecursive works but is a bit ugly
SOURCES=$(shell find src/ -type f -name '*.c')
HEADERS=$(shell find src/ -type f -name '*.h')
OBJECTS=$(patsubst %.c,obj/%.o,$(SOURCES))

all: preprocess $(SOURCES) $(EXECUTABLE) $(LIBRARY)

install:
	@cp $(EXECUTABLE) $(INSTALL_EXE_PATH)$(OUTPUT_FILE)
	@cp $(LIBRARY) $(INSTALL_LIB_PATH)$(OUTPUT_LIB)
	@mkdir $(INSTALL_INCLUDE_PATH)
	@cp $(HEADERS) $(INSTALL_INCLUDE_PATH)

remove:
	@rm $(INSTALL_EXE_PATH)$(OUTPUT_FILE)

clean:
	-@rm -r $(OBJ_DIR) $(EXECUTABLE)

#The executable rule compiles the set of objects into the target executable
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)
	
$(LIBRARY): $(OBJECTS)
	$(CC) $(LDFLAGS)  -shared  $(OBJECTS) -o $@

#These rule tells the compiler to generate an object from the source code.
$(OBJECTS) : $(OBJ_DIR)

$(OBJ_DIR):
	-@mkdir -p $@
	
$(OBJ_DIR)/%.o: %.c
	-@mkdir -p $(@D)
	$(CC) $(CFLAGS) $< -o $@
	
#The preprocess rules will update the build number
preprocess:
	-@mkdir -p $(OUTPUT_DIR)
