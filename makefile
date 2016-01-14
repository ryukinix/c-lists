GCC = gcc
LFLAGS = -Wall -o

BUILD_TARGET = build
STATIC_TARGET = static
DYNAMIC_TARGET = dynamic

all: .static .dynamic

.dynamic:
	@echo ":: Compiling dynamic lists"
	@mkdir -p $(BUILD_TARGET)/$(DYNAMIC_TARGET)
	@cd $(DYNAMIC_TARGET); make all
	@echo ":: Moving binaries to build folder"
	mv $(DYNAMIC_TARGET)/*.out ./$(BUILD_TARGET)/$(DYNAMIC_TARGET)/

.static:
	@echo ":: Compiling static lists"
	@mkdir -p $(BUILD_TARGET)/$(STATIC_TARGET)
	@cd $(STATIC_TARGET); make all
	@echo ":: Moving binaries to build folder"
	mv $(STATIC_TARGET)/*.out ./$(BUILD_TARGET)/$(STATIC_TARGET)/

clean:
	@echo ":: Cleaning previous build files"
	@rm -Rv $(BUILD_TARGET)