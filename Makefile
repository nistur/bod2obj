TARGET=bod2obj

SRCDIR=src
OBJDIR=obj
OUTDIR=bin

CFLAGS=-std=c++20 -O3

OBJS:=$(patsubst %.cpp,%.o,$(wildcard src/*.cpp))
OBJS:=$(subst ${SRCDIR},${OBJDIR},${OBJS})

.phony: all dir run

all: dir ${OUTDIR}/${TARGET}

run: ${OUTDIR}/${TARGET}
	${OUTDIR}/${TARGET} dat/argon_M3.bod ArgonNova

${OUTDIR}/${TARGET}: ${OBJS}
	g++ -o ${OUTDIR}/${TARGET} ${OBJS} ${CFLAGS}

${OBJDIR}/%.o:${SRCDIR}/%.cpp
	g++ -o $@ $< -c ${CFLAGS}

dir:
	@mkdir -p ${OBJDIR} ${OUTDIR}


clean:
	@rm -rf ${OBJDIR}
	@rm -rf ${OUTDIR}
