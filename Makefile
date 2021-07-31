
CC = g++
GTEST_DIR = external/gtest/googletest/include
CFLAGS = -Wall -g -IHtmlToHipe/src/ -LHtmlToHipe/src/ -I$(GTEST_DIR) -L/usr/local/lib/googletest -lgtest_main -Lexternal/gtest/googletest/src/ -lgtest -lpthread

TARGET = HtmlCsstoHipe

all: $(TARGET)
	@echo "Building HtmlCsstoHipe..."
	
$(TARGET): $(TARGET).o 
	@echo "defining the targets..."
	$(CC) $(CFLAGS) HtmlCsstoHipe.o -o HtmlCsstoHipe

HtmlCsstoHipe.o: HtmlCsstoHipe.cpp htmltohipe.o
	@echo "compiling HtmlCsstoHipe.o ..."
	$(CC) $(CFLAGS) -c HtmlCsstoHipe.cpp

htmltohipe.o: htmltohipe.cpp
	@echo "making htmltohipe cpp"
	$(CC) $(CFLAGS) -c htmltohipe.cpp

clean:
	@echo "cleaning up..."