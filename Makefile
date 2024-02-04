FOLDER_NAME := build

ifeq ($(wildcard $(FOLDER_NAME)),)
create_folder:
	@echo "Creating $(FOLDER_NAME) directory"
	@mkdir -p $(FOLDER_NAME)
else
create_folder:
	@echo "$(FOLDER_NAME) directory already exists"
endif

main: main.o
	g++ build/main.o -o build/main -std=c++20
	./build/main
main.o: create_folder
	g++ main.cpp -c -o build/main.o -std=c++20

clean:
	rm -rf build

.PHONY: default
default: main