
CC = g++
GTEST_DIR = external/gtest/googletest/include
CFLAGS = -Wall -g -LHtmlToHipe/src/ -L$(GTEST_DIR) -IHtmlToHipe/src/ -I$(GTEST_DIR)

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