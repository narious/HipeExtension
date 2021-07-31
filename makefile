
CC = g++
GTEST_DIR = external/gtest/googletest/include
CFLAGS = -Wall -g -IHtmlToHipe/src/ -LHtmlToHipe/src/ -I$(GTEST_DIR) -L/usr/local/lib/googletest -lgtest_main -Lexternal/gtest/googletest/src/

TARGET = HtmlCsstoHipe

all: $(TARGET)
	@echo "Building HtmlCsstoHipe..."
	
$(TARGET): $(TARGET).o
	@echo "defining the targets..."
	$(CC) $(CFLAGS) HtmlCsstoHipe.o -o HtmlCsstoHipe

HtmlCsstoHipe.o: HtmlCsstoHipe.cpp
	@echo "compiling HtmlCsstoHipe.o ..."
	$(CC) $(CFLAGS) -c HtmlCsstoHipe.cpp


clean:
	@echo "cleaning up..."