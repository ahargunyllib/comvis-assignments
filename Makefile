# Computer Vision Assignments Makefile
# Platform: macOS
# Dependencies: GLFW3, OpenGL

# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -O2
MAIN_TARGET := main
BUILD_DIR := build

# Activity sources
ACTIVITY_SRCS := $(wildcard src/activities/*.cpp)
ACTIVITY_NAMES := activity1 activity2 activity3 activity4 activity6 activity7 activity8
ACTIVITY_TARGETS := $(addprefix $(BUILD_DIR)/,$(ACTIVITY_NAMES))

# Detect Homebrew installation path
UNAME_M := $(shell uname -m)
ifeq ($(UNAME_M),arm64)
    # Apple Silicon
    BREW_PREFIX := /opt/homebrew
else
    # Intel Mac
    BREW_PREFIX := /usr/local
endif

# Try to use pkg-config first, fallback to manual paths
PKG_CONFIG := $(shell command -v pkg-config 2> /dev/null)

ifdef PKG_CONFIG
    # Use pkg-config to get GLFW flags
    GLFW_CFLAGS := $(shell pkg-config --cflags glfw3 2>/dev/null)
    GLFW_LIBS := $(shell pkg-config --libs glfw3 2>/dev/null)

    # Check if pkg-config found GLFW
    ifeq ($(GLFW_CFLAGS),)
        # Fallback to manual paths
        INCLUDES := -I$(BREW_PREFIX)/include -Isrc
        LDFLAGS := -L$(BREW_PREFIX)/lib
        LIBS := -lglfw
    else
        INCLUDES := $(GLFW_CFLAGS) -Isrc
        LDFLAGS :=
        LIBS := $(GLFW_LIBS)
    endif
else
    # No pkg-config, use manual paths
    INCLUDES := -I$(BREW_PREFIX)/include -Isrc
    LDFLAGS := -L$(BREW_PREFIX)/lib
    LIBS := -lglfw
endif

# macOS Frameworks
FRAMEWORKS := -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo

# Combine all flags
ALL_CXXFLAGS := $(CXXFLAGS) $(INCLUDES)
ALL_LDFLAGS := $(LDFLAGS) $(LIBS) $(FRAMEWORKS)

# Colors for output
COLOR_RESET := \033[0m
COLOR_GREEN := \033[32m
COLOR_YELLOW := \033[33m
COLOR_BLUE := \033[34m
COLOR_CYAN := \033[36m

# Phony targets
.PHONY: all clean help rebuild info list-activities
.PHONY: activity1 activity2 activity3 activity4 activity6 activity7 activity8
.PHONY: run run-activity1 run-activity2 run-activity3 run-activity4 run-activity6 run-activity7 run-activity8

# Default target
all: $(MAIN_TARGET) activities
	@echo "$(COLOR_GREEN)✓ Build complete!$(COLOR_RESET)"
	@echo ""
	@echo "$(COLOR_CYAN)═══════════════════════════════════════════════════$(COLOR_RESET)"
	@echo "$(COLOR_CYAN)  Available executables:$(COLOR_RESET)"
	@echo "$(COLOR_CYAN)═══════════════════════════════════════════════════$(COLOR_RESET)"
	@echo "  • $(COLOR_GREEN)./$(MAIN_TARGET) <N>$(COLOR_RESET)        - Run activity N via main dispatcher"
	@echo "  • $(COLOR_GREEN)./$(BUILD_DIR)/activityN$(COLOR_RESET) - Run individual activity executable"
	@echo ""
	@echo "$(COLOR_YELLOW)Examples:$(COLOR_RESET)"
	@echo "  ./$(MAIN_TARGET) 1                  # Run activity 1"
	@echo "  ./$(BUILD_DIR)/activity1            # Run activity 1 directly"
	@echo "  make run ACTIVITY=4         # Run activity 4"
	@echo ""
	@echo "Type '$(COLOR_GREEN)make help$(COLOR_RESET)' for more options"

# Create build directory
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Build the main dispatcher executable
$(MAIN_TARGET): main.cpp $(ACTIVITY_SRCS) | $(BUILD_DIR)
	@echo "$(COLOR_BLUE)Building main dispatcher...$(COLOR_RESET)"
	$(CXX) $(ALL_CXXFLAGS) main.cpp -o $(MAIN_TARGET) $(ALL_LDFLAGS)

# Build all individual activity executables
activities: $(ACTIVITY_TARGETS)

# Pattern rule for individual activities
$(BUILD_DIR)/activity%: src/activities/activity%_*.cpp | $(BUILD_DIR)
	@echo "$(COLOR_BLUE)Building $@...$(COLOR_RESET)"
	$(CXX) $(ALL_CXXFLAGS) $< -o $@ $(ALL_LDFLAGS)

# Explicit targets for each activity
activity1: $(BUILD_DIR)/activity1
activity2: $(BUILD_DIR)/activity2
activity3: $(BUILD_DIR)/activity3
activity4: $(BUILD_DIR)/activity4
activity6: $(BUILD_DIR)/activity6
activity7: $(BUILD_DIR)/activity7
activity8: $(BUILD_DIR)/activity8

# Run activities using main dispatcher
run:
ifndef ACTIVITY
	@echo "$(COLOR_YELLOW)Please specify an activity number:$(COLOR_RESET)"
	@echo "  make run ACTIVITY=1"
	@echo "  make run ACTIVITY=2"
	@echo "  etc."
	@echo ""
	@echo "Available activities: 1, 2, 3, 4, 6, 7, 8"
	@echo "Type '$(COLOR_GREEN)./$(MAIN_TARGET)$(COLOR_RESET)' to see full activity list"
else
	@echo "$(COLOR_GREEN)Running Activity $(ACTIVITY)...$(COLOR_RESET)"
	@./$(MAIN_TARGET) $(ACTIVITY)
endif

# Run individual activities directly
run-activity1: $(BUILD_DIR)/activity1
	@echo "$(COLOR_GREEN)Running Activity 1 (standalone)...$(COLOR_RESET)"
	@./$(BUILD_DIR)/activity1

run-activity2: $(BUILD_DIR)/activity2
	@echo "$(COLOR_GREEN)Running Activity 2 (standalone)...$(COLOR_RESET)"
	@./$(BUILD_DIR)/activity2

run-activity3: $(BUILD_DIR)/activity3
	@echo "$(COLOR_GREEN)Running Activity 3 (standalone)...$(COLOR_RESET)"
	@./$(BUILD_DIR)/activity3

run-activity4: $(BUILD_DIR)/activity4
	@echo "$(COLOR_GREEN)Running Activity 4 (standalone)...$(COLOR_RESET)"
	@./$(BUILD_DIR)/activity4

run-activity6: $(BUILD_DIR)/activity6
	@echo "$(COLOR_GREEN)Running Activity 6 (standalone)...$(COLOR_RESET)"
	@./$(BUILD_DIR)/activity6

run-activity7: $(BUILD_DIR)/activity7
	@echo "$(COLOR_GREEN)Running Activity 7 (standalone)...$(COLOR_RESET)"
	@./$(BUILD_DIR)/activity7

run-activity8: $(BUILD_DIR)/activity8
	@echo "$(COLOR_GREEN)Running Activity 8 (standalone)...$(COLOR_RESET)"
	@./$(BUILD_DIR)/activity8

# List all available activities
list-activities:
	@echo "$(COLOR_CYAN)══════════════════════════════════════════════════════$(COLOR_RESET)"
	@echo "$(COLOR_CYAN)  Computer Vision Assignments - Available Activities$(COLOR_RESET)"
	@echo "$(COLOR_CYAN)══════════════════════════════════════════════════════$(COLOR_RESET)"
	@echo ""
	@echo "  $(COLOR_GREEN)1$(COLOR_RESET) - Instalasi (Installation Test)"
	@echo "  $(COLOR_GREEN)2$(COLOR_RESET) - Clipping"
	@echo "  $(COLOR_GREEN)3$(COLOR_RESET) - Color Interpolation"
	@echo "  $(COLOR_GREEN)4$(COLOR_RESET) - Bull's Eye Target"
	@echo "  $(COLOR_GREEN)6$(COLOR_RESET) - Bola Merah Kuning Biru (RGB Balls)"
	@echo "  $(COLOR_GREEN)7$(COLOR_RESET) - Satelite Duo"
	@echo "  $(COLOR_GREEN)8$(COLOR_RESET) - Undistorted Cray 2"
	@echo ""

# Clean build artifacts
clean:
	@echo "$(COLOR_YELLOW)Cleaning build artifacts...$(COLOR_RESET)"
	@rm -rf $(BUILD_DIR) $(MAIN_TARGET)
	@echo "$(COLOR_GREEN)✓ Clean complete!$(COLOR_RESET)"

# Rebuild from scratch
rebuild: clean all

# Show build information
info:
	@echo "$(COLOR_BLUE)═══════════════════════════════════════════════════$(COLOR_RESET)"
	@echo "$(COLOR_BLUE)  Build Configuration$(COLOR_RESET)"
	@echo "$(COLOR_BLUE)═══════════════════════════════════════════════════$(COLOR_RESET)"
	@echo "Compiler:         $(CXX)"
	@echo "C++ Standard:     C++11"
	@echo "Main Target:      $(MAIN_TARGET)"
	@echo "Build Directory:  $(BUILD_DIR)"
	@echo "Brew Prefix:      $(BREW_PREFIX)"
	@echo "Architecture:     $(UNAME_M)"
	@echo ""
	@echo "$(COLOR_BLUE)═══════════════════════════════════════════════════$(COLOR_RESET)"
	@echo "$(COLOR_BLUE)  Compiler Flags$(COLOR_RESET)"
	@echo "$(COLOR_BLUE)═══════════════════════════════════════════════════$(COLOR_RESET)"
	@echo "CXXFLAGS:     $(CXXFLAGS)"
	@echo "INCLUDES:     $(INCLUDES)"
	@echo "LDFLAGS:      $(LDFLAGS)"
	@echo "LIBS:         $(LIBS)"
	@echo "FRAMEWORKS:   $(FRAMEWORKS)"
	@echo ""
ifdef PKG_CONFIG
	@echo "$(COLOR_GREEN)✓ pkg-config found$(COLOR_RESET)"
	@pkg-config --modversion glfw3 2>/dev/null && echo "GLFW version: $$(pkg-config --modversion glfw3)" || echo "$(COLOR_YELLOW)⚠ GLFW not found via pkg-config$(COLOR_RESET)"
else
	@echo "$(COLOR_YELLOW)⚠ pkg-config not found, using manual paths$(COLOR_RESET)"
endif
	@echo ""

# Help target
help:
	@echo "$(COLOR_CYAN)═══════════════════════════════════════════════════$(COLOR_RESET)"
	@echo "$(COLOR_CYAN)  Computer Vision Assignments - Makefile Help$(COLOR_RESET)"
	@echo "$(COLOR_CYAN)═══════════════════════════════════════════════════$(COLOR_RESET)"
	@echo ""
	@echo "$(COLOR_BLUE)Building:$(COLOR_RESET)"
	@echo "  $(COLOR_GREEN)make$(COLOR_RESET) or $(COLOR_GREEN)make all$(COLOR_RESET)          - Build all executables"
	@echo "  $(COLOR_GREEN)make activity1$(COLOR_RESET)               - Build only activity 1"
	@echo "  $(COLOR_GREEN)make activity2$(COLOR_RESET)               - Build only activity 2"
	@echo "  $(COLOR_GREEN)make clean$(COLOR_RESET)                   - Remove all build artifacts"
	@echo "  $(COLOR_GREEN)make rebuild$(COLOR_RESET)                 - Clean and rebuild everything"
	@echo ""
	@echo "$(COLOR_BLUE)Running (via main dispatcher):$(COLOR_RESET)"
	@echo "  $(COLOR_GREEN)./main <N>$(COLOR_RESET)                   - Run activity N (1,2,3,4,6,7,8)"
	@echo "  $(COLOR_GREEN)make run ACTIVITY=<N>$(COLOR_RESET)        - Build and run activity N"
	@echo ""
	@echo "$(COLOR_BLUE)Running (standalone executables):$(COLOR_RESET)"
	@echo "  $(COLOR_GREEN)./build/activity1$(COLOR_RESET)            - Run activity 1 directly"
	@echo "  $(COLOR_GREEN)make run-activity1$(COLOR_RESET)           - Build and run activity 1 directly"
	@echo "  $(COLOR_GREEN)make run-activity2$(COLOR_RESET)           - Build and run activity 2 directly"
	@echo "  (Similarly for activities 3, 4, 6, 7, 8)"
	@echo ""
	@echo "$(COLOR_BLUE)Information:$(COLOR_RESET)"
	@echo "  $(COLOR_GREEN)make list-activities$(COLOR_RESET)         - List all available activities"
	@echo "  $(COLOR_GREEN)make info$(COLOR_RESET)                    - Show build configuration"
	@echo "  $(COLOR_GREEN)make help$(COLOR_RESET)                    - Show this help message"
	@echo ""
	@echo "$(COLOR_BLUE)Examples:$(COLOR_RESET)"
	@echo "  make && ./main 1                    # Build all, run activity 1"
	@echo "  make run ACTIVITY=4                 # Build and run activity 4"
	@echo "  make activity1 && ./build/activity1 # Build and run standalone"
	@echo "  make clean && make activity2        # Clean build activity 2"
	@echo ""
	@echo "$(COLOR_BLUE)Prerequisites:$(COLOR_RESET)"
	@echo "  1. Xcode Command Line Tools: xcode-select --install"
	@echo "  2. GLFW3:                     brew install glfw"
	@echo "  3. pkg-config (optional):     brew install pkg-config"
	@echo ""
