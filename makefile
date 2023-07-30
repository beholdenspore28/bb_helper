SRCFILES != find src -name '*.c'
EXAMPLESRCFILES != find example -name '*.c'
OBJFILES := ${SRCFILES:%.c=build/obj/%.o} 
EXAMPLEOBJFILES := ${EXAMPLESRCFILES:%.c=build/example/obj/%.o} 
INCDIR := src
LIBS := -lm
MODE ?= DEBUG

LDFLAGS := -Wall -std=c89 
CFLAGS := -Wall -std=c89 
LDFLAGS_DEBUG := -g3
CFLAGS_DEBUG := -g3
LDFLAGS_RELEASE := -flto
CFLAGS_RELEASE := -O2 -flto
LDFLAGS += ${LDFLAGS${MODE}}
CFLAGS += ${CFLAGS_${MODE}}

default: all

all: build/lib/lite-lib.a build/bin/example

${OBJFILES}: ${@:build/obj/%.o=%.c}
	@mkdir -p ${dir ${@}}
	clang -c ${@:build/obj/%.o=%.c} ${CFLAGS} ${INCDIR:%=-I%} -o ${@}

${EXAMPLEOBJFILES}: ${@:build/example/obj/%.o=%.c}
	@mkdir -p ${dir ${@}}
	clang -c ${@:build/example/obj/%.o=%.c} ${CFLAGS} ${INCDIR:%=-I%} -o ${@}

clean: 

	rm -r -v build
	rm -r -v lib

build/lib/lite-lib.a: ${OBJFILES}
	@mkdir -p build/lib
	ar rcs ${@} ${OBJFILES}

example: build/lib/lite-lib.a build/bin/example

build/bin/example: ${OBJFILES} ${EXAMPLEOBJFILES};
	@mkdir -p build/bin
	clang ${OBJFILES} ${EXAMPLEOBJFILES} -I ${INCDIR} ${LIBS} ${LDFLAGS} -o build/bin/example
	./build/bin/example

fuzz: build/lib/lite-lib.a
	clang -g -O1 -fsanitize=fuzzer,address example/fuzzer.c ${SRCFILES} ${LIBS} ${INCDIR:%=-I%} -o build/fuzz.out
	./build/fuzz.out