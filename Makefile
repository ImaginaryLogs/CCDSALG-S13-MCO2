
PROJECT_NAME = graph
SRC_DIR = src
BIN_DIR = bin
TST_DIR = tests


CC = gcc
CFLAGS = -Wall -o

SRCS = $(wildcard $(SRC_DIR)/*.c $(SRC_DIR)/*.h)
TESTS = $(wildcard $(TST_DIR)/*.c $(TST_DIR)/*.h)

all: build run
.SILENT:
build: $(SRCS)
	@echo "=== Building . . . ===================================="
	@echo ""
	for file in $^; \
	do \
		echo "   Building... $${file}";\
	done
	@echo ""
	$(CC) $(CFLAGS) bin/main $^ -lm
	@echo ""
	@echo "=== Building Complete ================================="

run: $(BIN_DIR)/main.exe
	@echo ""
	@echo "Running Graphing Program..."
	@echo ""
	cd $(BIN_DIR); \
		./main.exe

test:
	@echo "\nBuilding\n"
	$(CC) $(CFLAGS) $(TST_DIR)/$(BIN_DIR)/test.exe $^
