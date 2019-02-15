CC=g++
CXXFLAGS=-O2 -Wall -Wpedantic -g -std=c++17
LIBS=-ljpeg -lpng

SRC=src
BIN=bin
ODIR=src/obj
IDIR=src

TEST=test

_DEPS=load_img.hpp display_img.hpp
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ=load_img.o display_img.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

all : $(BIN)/img_reader

test_load_img : $(BIN)/test_load_img
test_display_img : $(BIN)/test_display_img

$(ODIR)/%.o: $(SRC)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CXXFLAGS) 

$(BIN)/img_reader : $(OBJ)
	$(CC) $(IDIR)/img_reader.cpp -o $@ $^ $(CXXFLAGS) $(LIBS)

$(BIN)/test_load_img : $(OBJ)
	$(CC) test/test_load_img.cpp -o $@ $^ $(CXXFLAGS) $(LIBS)

$(BIN)/test_display_img : $(OBJ)
	$(CC) test/test_display_img.cpp -o $@ $^ $(CXXFLAGS) $(LIBS)
	
.PHONY: clean install

clean:
	rm $(ODIR)/*.o