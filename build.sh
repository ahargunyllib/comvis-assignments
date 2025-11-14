#!/bin/bash
# Build script for OpenGL Demo
# Usage: ./build.sh [clean|rebuild|run]

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Configuration
TARGET="opengl-demo"
BUILD_TYPE="${BUILD_TYPE:-Release}"

# Functions
print_header() {
    echo -e "${BLUE}========================================${NC}"
    echo -e "${BLUE}$1${NC}"
    echo -e "${BLUE}========================================${NC}"
}

print_success() {
    echo -e "${GREEN}✓ $1${NC}"
}

print_error() {
    echo -e "${RED}✗ $1${NC}"
}

print_warning() {
    echo -e "${YELLOW}⚠ $1${NC}"
}

check_dependencies() {
    print_header "Checking Dependencies"

    # Check for g++/clang++
    if ! command -v g++ &> /dev/null && ! command -v clang++ &> /dev/null; then
        print_error "No C++ compiler found. Install Xcode Command Line Tools:"
        echo "  xcode-select --install"
        exit 1
    fi
    print_success "C++ compiler found"

    # Check for GLFW
    if command -v pkg-config &> /dev/null; then
        if pkg-config --exists glfw3; then
            GLFW_VERSION=$(pkg-config --modversion glfw3)
            print_success "GLFW $GLFW_VERSION found via pkg-config"
        else
            print_warning "GLFW not found via pkg-config"
            check_glfw_manual
        fi
    else
        print_warning "pkg-config not found"
        check_glfw_manual
    fi
}

check_glfw_manual() {
    # Check common Homebrew paths
    if [ -f "/opt/homebrew/include/GLFW/glfw3.h" ] || [ -f "/usr/local/include/GLFW/glfw3.h" ]; then
        print_success "GLFW headers found in Homebrew directory"
    else
        print_error "GLFW not found. Install with:"
        echo "  brew install glfw"
        exit 1
    fi
}

build() {
    print_header "Building $TARGET"

    if [ -f "Makefile" ]; then
        make
        print_success "Build completed successfully!"
    else
        print_error "Makefile not found!"
        exit 1
    fi
}

clean() {
    print_header "Cleaning Build Artifacts"

    if [ -f "Makefile" ]; then
        make clean
        print_success "Clean completed!"
    else
        rm -f *.o "$TARGET"
        print_success "Manual clean completed!"
    fi
}

rebuild() {
    clean
    build
}

run_app() {
    if [ ! -f "$TARGET" ]; then
        print_warning "Executable not found. Building first..."
        build
    fi

    print_header "Running $TARGET"
    ./"$TARGET"
}

show_help() {
    echo "OpenGL Demo Build Script"
    echo ""
    echo "Usage: ./build.sh [COMMAND]"
    echo ""
    echo "Commands:"
    echo "  (none)    Build the project (default)"
    echo "  clean     Remove build artifacts"
    echo "  rebuild   Clean and build"
    echo "  run       Build (if needed) and run the application"
    echo "  check     Check dependencies only"
    echo "  help      Show this help message"
    echo ""
    echo "Examples:"
    echo "  ./build.sh           # Build the project"
    echo "  ./build.sh run       # Build and run"
    echo "  ./build.sh rebuild   # Clean rebuild"
}

# Main script
main() {
    case "${1:-build}" in
        build)
            check_dependencies
            build
            ;;
        clean)
            clean
            ;;
        rebuild)
            check_dependencies
            rebuild
            ;;
        run)
            check_dependencies
            run_app
            ;;
        check)
            check_dependencies
            ;;
        help|--help|-h)
            show_help
            ;;
        *)
            print_error "Unknown command: $1"
            show_help
            exit 1
            ;;
    esac
}

main "$@"
