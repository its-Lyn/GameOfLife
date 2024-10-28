CC=clang++

INCLUDE=-Iinclude
DEBUG=-fsanitize=address,undefined -g3
LIBS=-lraylib

OPTIONS=-std=c++20 -Wall -Wextra -Werror -Wno-unused-parameter

SOURCES := $(shell find src -name '*.cc')

OUT_DEBUG=out/debug
OUT_RELEASE=out/release
BINARY=LifeGame

debug:
	mkdir -p $(OUT_DEBUG)
	$(CC) $(INCLUDE) $(OPTIONS) $(LIBS) $(DEBUG) $(SOURCES) -o $(OUT_DEBUG)/$(BINARY)


release:
	mkdir -p $(OUT_RELEASE)
	$(CC) $(INCLUDE) $(OPTIONS) $(LIBS) $(SOURCES) -o $(OUT_RELEASE)/$(BINARY)


clean:
	rm -rf out