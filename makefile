SRCFILES != find src -name '*.c'
OBJFILES := ${SRCFILES:%.c=build/obj/%.o} 
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
default: run
all: build/bin/test lib/libtest.a

run: build/bin/test
	./build/bin/test
build/bin/test: ${OBJFILES};
	@mkdir -p build/bin
	clang ${OBJFILES} -I ${INCDIR} ${LIBS} ${LDFLAGS} -o build/bin/test

${OBJFILES}: ${@:build/obj/%.o=%.c}
	@mkdir -p ${dir ${@}}
	clang -c ${@:build/obj/%.o=%.c} ${CFLAGS} ${INCDIR:%=-I%} -o ${@}
clean: 
	rm build/bin/test
lib/libtest.a: ${OBJFILES}
	@mkdir -p lib
	ar rcs ${@} ${OBJFILES}