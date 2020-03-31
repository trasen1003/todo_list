
DDIR =./includes
_DEPS = tache.h todo_list.h
DEPS = $(patsubst %,$(DDIR)/%,$(_DEPS))

RDIR = ./saves
_REFRESH = id.txt save.txt
REFRESH = $(patsubst %,$(RDIR)/%,$(_REFRESH))

SDIR = ./sources
_SOURCE = main.cpp tache.cpp todo_list.cpp
SOURCE = $(patsubst %,$(SDIR)/%,$(_SOURCE))


CC=g++
CFLAGS=-I $(DDIR)

todo_app: $(SOURCE) $(DEPS)
	rm $(REFRESH)
	touch $(REFRESH)
	$(CC) -o todo_app $(SOURCE) $(CFLAGS)

.PHONY:todo_app
