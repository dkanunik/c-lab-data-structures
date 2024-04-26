CC = gcc

CFLAGS = -Wall -Wextra -fPIC -shared

TARGET_LIB = libtest_data_utils.so
TARGET_LIB_DIR=/usr/local/lib
TARGET_INCLUDE_DIR=/usr/local/include

INCLUDES = include
SOURCES = src/test_data_utils.c

all: $(TARGET_LIB)

$(TARGET_LIB): $(SOURCES)
	$(CC) $(CFLAGS) -I$(INCLUDES) -o $(TARGET_LIB) $(SOURCES) -lc

install:
	@if [ -w $(TARGET_LIB_DIR) ]; then \
		sudo \cp -r $(TARGET_LIB) $(TARGET_LIB_DIR); \
		echo "Copy $(TARGET_LIB) to $(TARGET_LIB_DIR)"; \
		exit 0; > /dev/null 2>&1 \
	else \
		echo "You do not have the necessary permissions to write to $(TARGET_LIB_DIR)."; \
		exit 1; \
	fi

	@if [ -w $(TARGET_INCLUDE_DIR) ]; then \
		sudo \cp -r $(INCLUDES) $(TARGET_INCLUDE_DIR); \
		echo "Copy $(INCLUDES) to $(TARGET_INCLUDE_DIR)"; \
		exit 0; > /dev/null 2>&1; \
	else \
		echo "You do not have the necessary permissions to write to $(TARGET_INCLUDE_DIR)."; \
		exit 2; \
	fi

uninstall:
	rm $(TARGET_LIB_DIR)/$(TARGET_LIB)
	rm $(TARGET_INCLUDE_DIR)/$(INCLUDES)

clean:
	$(RM) *.o *.so
