FRONTEND_SRCDIR		:= src/frontend
BACKEND_SRCDIR		:= src/backend
BUILDDIR					:= obj
TARGETDIR					:= bin
SRCEXT						:= cpp
DEPEXT						:= d
OBJEXT						:= o

CC								:= g++
CFLAGS						:= -c -std=c++11 -lboost_system 
LDFLAGS						:= -lboost_system

BACKEND_SOURCES		:= $(wildcard $(BACKEND_SRCDIR)/*.$(SRCEXT))
BACKEND_OBJECTS		:= $(BACKEND_SOURCES:$(BACKEND_SRCDIR)/%.$(SRCEXT)=$(BUILDDIR)/%.$(OBJEXT))
BACKEND_EXEC			:= bin/backend

FRONTEND_SOURCES	:= $(wildcard $(FRONTEND_SRCDIR)/*.$(SRCEXT))
FRONTEND_OBJECTS	:= $(FRONTEND_SOURCES:$(FRONTEND_SRCDIR)/%.$(SRCEXT)=$(BUILDDIR)/%.$(OBJEXT))
FRONTEND_EXEC			:= bin/frontend


all: backend frontend

backend: $(BACKEND_EXEC)

frontend: $(FRONTEND_EXEC)

$(BACKEND_EXEC): $(BACKEND_OBJECTS)
	mkdir -p bin
	$(CC) $(LDFLAGS) $(BACKEND_OBJECTS) -o $@

$(FRONTEND_EXEC): $(FRONTEND_OBJECTS)
	mkdir -p bin
	$(CC) $(LDFLAGS) $(FRONTEND_OBJECTS) -o $@

$(BUILDDIR)/%.$(OBJEXT): $(BACKEND_SRCDIR)/%.$(SRCEXT)
	mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $@

$(BUILDDIR)/%.$(OBJEXT): $(FRONTEND_SRCDIR)/%.$(SRCEXT)
	mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(BUILDDIR)/*.$(OBJEXT) $(TARGETDIR)/*

