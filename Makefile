CC = gcc
CFLAGS = -std=c99
LDFLAGS = 
FORMAT = clang-format-3.8
SOURCES = $(shell find src/ -iname *.c)
HEADERS = $(shell find src/ -iname *.h)
OBJECTS = $(SOURCES:src/%.c=obj/%.o)
EXE = factory

.PHONY: all clean format

all: $(EXE)

$(EXE): $(OBJECTS)
	@echo Linking
	@$(CC) $(OBJECTS) -o $(EXE) $(LDFLAGS)

obj/%.o: src/%.c
	@echo Compiling $<
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $(WARNINGS) -o $@ $<

clean:
	@rm -rf $(EXE) obj/

format:
	@echo Formatting files
	@$(FORMAT) -i $(SOURCES) $(HEADERS)
