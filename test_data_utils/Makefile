CC = gcc

CFLAGS = -Wall -Wextra

TARGET_LIB = libtest_data_utils.so

LIB_DIR=/usr/local/lib
INCLUDE_DIR=/usr/local/include

INCLUDES = include/test_data_utils.h

SOURCES = src/test_data_utils.c

all: $(TARGET_LIB)

$(TARGET_LIB): $(SOURCES)
	$(CC) $(CFLAGS) -fPIC -shared -o $(TARGET_LIB) $(SOURCES) -lc

install:
	@if [ -w $(LIB_DIR) ]; then \
		sudo \cp -r $(TARGET_LIB) /usr/local/lib; \
		echo "Copy $(TARGET_LIB) to /usr/local/lib"; \
		exit 0; > /dev/null 2>&1 \
	else \
		echo "You do not have the necessary permissions to write to /usr/local/lib."; \
		exit 1; \
	fi

	@if [ -w /usr/local/include ]; then \
		sudo \cp -r $(INCLUDES) /usr/local/include; \
		echo "Copy $(INCLUDES) to /usr/local/include"; \
		exit 0; > /dev/null 2>&1; \
	else \
		echo "You do not have the necessary permissions to write to /usr/local/include."; \
		exit 2; \
	fi

uninstall:
	rm /usr/local/lib/$(TARGET_LIB)
	rm /usr/local/include/$(INCLUDES)

clean:
	$(RM) *.o *.so
