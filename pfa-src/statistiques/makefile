EXE=statistiques
SRCDIR=src
BINDIR=bin

.phony: all clean

all: $(EXE)

$(EXE):
	( cd ${SRCDIR} ; $(MAKE) )
	cp ${SRCDIR}/$(EXE) ${BINDIR}/

clean:
	( cd ${SRCDIR} ; $(MAKE) clean )
