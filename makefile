
DDIR =./includes
_DEPS = tache.h todo_list.h
DEPS = $(patsubst %,$(DDIR)/%,$(_DEPS))

RDIR = ./saves
_REFRESH = id.txt save.txt
REFRESH = $(patsubst %,$(RDIR)/%,$(_REFRESH))

SDIR = ./sources
_SOURCE = main.cpp
SOURCE = $(patsubst %,$(SDIR)/%,$(_SOURCE))


CC=g++
CFLAGS=-I $(DDIR)

todo_list: $(SOURCE) $(DEPS)
	rm $(REFRESH)
	touch $(REFRESH)
	$(CC) -o todo_app $(SOURCE) $(CFLAGS)
