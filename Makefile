TARGET=bod2obj

SRCDIR=src
OBJDIR=obj
OUTDIR=bin

CFLAGS=-std=c++14 -g

OBJS=${OBJDIR}/bod2obj.o ${OBJDIR}/vertex.o ${OBJDIR}/triangle.o ${OBJDIR}/bod.o

.phony: all dir run

all: dir ${OUTDIR}/${TARGET}

${OUTDIR}/${TARGET}: ${OBJS}
	g++ -o ${OUTDIR}/${TARGET} ${OBJS} ${CFLAGS}

${OBJDIR}/%.o:${SRCDIR}/%.cpp
	g++ -o $@ $< -c ${CFLAGS}

dir:
	@mkdir -p ${OBJDIR} ${OUTDIR}


clean:
	@rm -rf ${OBJDIR}
	@rm -rf ${OUTDIR}
