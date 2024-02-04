FOLDER_NAME := build
OBJS = main.o
TARGET = main

ifeq ($(wildcard $(FOLDER_NAME)),)
create_folder:
	@echo "Creating $(FOLDER_NAME) directory"
	@mkdir -p $(FOLDER_NAME)
else
create_folder:
	@echo "$(FOLDER_NAME) directory already exists"
endif

$(TARGET): $(OBJS)
	g++ $(FOLDER_NAME)/$(OBJS) -o $(FOLDER_NAME)/$(TARGET) -std=c++20
	./$(FOLDER_NAME)/main
main.o: create_folder
	g++ main.cpp -c -o $(FOLDER_NAME)/main.o -std=c++20

clean:
	rm -rf build

.PHONY: default
default: $(TARGET)