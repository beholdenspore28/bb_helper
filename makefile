
SRCFILES != find src -name '*.c'
OBJFILES := ${SRCFILES:%.c=build/obj/%.o} 
LIBS := -lm
MODE ?= DEBUG

LDFLAGS := -Wall -std=c11
CFLAGS := -Wall -std=c11
LDFLAGS_DEBUG := -g3 -O0 -gdwarf-4
CFLAGS_DEBUG := -g3 -O0 -gdwarf-4
LDFLAGS_RELEASE := -flto
CFLAGS_RELEASE := -flto
LDFLAGS += ${LDFLAGS_${MODE}}
CFLAGS += ${CFLAGS_${MODE}}

default: clearscreen run

clearscreen:
	clear

run: build/bin/test
	./build/bin/test

build/bin/test: ${OBJFILES};
	@mkdir -p build/bin
	clang ${OBJFILES} ${LIBS} ${LDFLAGS} -o build/bin/test

${OBJFILES}: ${@:build/obj/%.o=%.c}
	@mkdir -p ${dir ${@}}
	clang -c ${@:build/obj/%.o=%.c} ${CFLAGS} -o ${@}

clean: 
	rm -r build/*
