CORELIB_SRC=$(wildcard corelib/*.c)
CORELIB_OBJ=$(CORELIB_SRC:.c=.o)
CFLAGS = -ansi -Os

all: corelib.a clitest/main.exe

corelib.a: $(CORELIB_OBJ)
	echo $(CORELIB_OBJ)
	$(AR) ru $@ $+

clitest/main.exe: clitest/main.cpp corelib.a
	$(CXX) -Icorelib -o $@ $+

clean:
	rm -f corelib/*.o corelib.a
