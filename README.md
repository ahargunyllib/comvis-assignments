# Computer Vision Assignments

A collection of 8 OpenGL-based computer vision assignments demonstrating various graphics programming concepts, rendering techniques, and visual effects.

## 📋 Table of Contents

- [Description](#description)
- [Prerequisites](#prerequisites)
- [Project Structure](#project-structure)
- [Quick Start](#quick-start)
- [Activities](#activities)
- [Building & Running](#building--running)
- [Advanced Usage](#advanced-usage)
- [Credits](#credits)

## Description

This project contains 8 computer vision activities implemented using OpenGL 4.1 and GLFW on macOS. Each activity demonstrates different graphics programming concepts, from basic rendering to advanced visual effects.

**Note:** Activity 5 is intentionally skipped in this assignment series.

## Prerequisites

Before building this project, ensure you have:

- **macOS**: 10.15 or later
- **Xcode Command Line Tools**:
  ```bash
  xcode-select --install
  ```
- **GLFW3**:
  ```bash
  brew install glfw
  ```
- **pkg-config** (optional but recommended):
  ```bash
  brew install pkg-config
  ```

## Project Structure

```
comvis-assignments/
├── src/
│   ├── activities/          # Individual activity implementations
│   │   ├── activity1_instalasi.cpp
│   │   ├── activity2_clipping.cpp
│   │   ├── activity3_color_interpolation.cpp
│   │   ├── activity4_bulls_eye.cpp
│   │   ├── activity6_bola_rgb.cpp
│   │   ├── activity7_satelite_duo.cpp
│   │   └── activity8_undistorted_cray.cpp
│   └── common/              # Shared utilities
│       └── opengl_setup.h   # Common OpenGL initialization functions
├── build/                   # Build output directory (created automatically)
│   ├── activity1            # Individual executables
│   ├── activity2
│   └── ...
├── main.cpp                 # Activity dispatcher (main executable)
├── Makefile                 # Build system
└── README.md                # This file
```

## Quick Start

```bash
# Build all activities
make

# Run an activity via main dispatcher
./main 1                    # Run Activity 1

# Or run an activity directly
./build/activity1           # Run Activity 1 standalone

# Or use make commands
make run ACTIVITY=4         # Build and run Activity 4
```

## Activities

### Activity 1: Instalasi (Installation Test)
**File:** `src/activities/activity1_instalasi.cpp`

Verifies OpenGL installation by displaying a simple black square on a white background. Uses modern OpenGL with orthographic projection.

**Purpose:**
- Confirm OpenGL and GLFW are correctly installed
- Test basic rendering pipeline with VAO/VBO
- Demonstrate orthographic projection (0-100 coordinate space)

**Visual Output:**
- White background (500x500 window)
- Black square positioned at (20, 20) to (80, 80)

**Based on:** square.cpp by Sumanta Guha (converted to modern OpenGL)

**Run:**
```bash
./main 1
# or
./build/activity1
```

---

### Activity 2: Clipping
**File:** `src/activities/activity2_clipping.cpp`

TBD

**Run:**
```bash
./main 2
# or
./build/activity2
```

---

### Activity 3: Color Interpolation
**File:** `src/activities/activity3_color_interpolation.cpp`

TBD

**Run:**
```bash
./main 3
# or
./build/activity3
```

---

### Activity 4: Bull's Eye Target
**File:** `src/activities/activity4_bulls_eye.cpp`

TBD

**Run:**
```bash
./main 4
# or
./build/activity4
```

---

### Activity 6: Bola Merah Kuning Biru (RGB Balls)
**File:** `src/activities/activity6_bola_rgb.cpp`

TBD

**Run:**
```bash
./main 6
# or
./build/activity6
```

---

### Activity 7: Satelite Duo (Satellite Duo)
**File:** `src/activities/activity7_satelite_duo.cpp`

TBD

**Run:**
```bash
./main 7
# or
./build/activity7
```

---

### Activity 8: Undistorted Cray 2
**File:** `src/activities/activity8_undistorted_cray.cpp`

TBD

**Run:**
```bash
./main 8
# or
./build/activity8
```

## Building & Running

### Build All Activities

```bash
make                        # Build all executables
```

This creates:
- `./main` - Main dispatcher executable
- `./build/activity1` through `./build/activity8` - Individual activity executables

### Build Specific Activity

```bash
make activity1              # Build only Activity 1
make activity4              # Build only Activity 4
```

### Running Activities

#### Method 1: Main Dispatcher (Recommended)

```bash
./main <activity_number>    # Run specific activity

# Examples:
./main 1                    # Run Activity 1
./main 7                    # Run Activity 7
```

#### Method 2: Direct Execution

```bash
./build/activity1           # Run Activity 1 directly
./build/activity4           # Run Activity 4 directly
```

#### Method 3: Make Commands

```bash
make run ACTIVITY=1         # Build and run Activity 1
make run ACTIVITY=4         # Build and run Activity 4

# Or run standalone:
make run-activity1          # Build and run Activity 1 standalone
make run-activity7          # Build and run Activity 7 standalone
```

### Cleaning Build Artifacts

```bash
make clean                  # Remove all build artifacts
make rebuild                # Clean and rebuild everything
```

## Advanced Usage

### List All Activities

```bash
make list-activities        # Show all available activities
./main                      # Show usage and activity list
```

### View Build Configuration

```bash
make info                   # Display compiler settings and paths
```

### Get Help

```bash
make help                   # Show all available make targets
```

### Manual Compilation

If you need to compile manually:

**With pkg-config:**
```bash
g++ -std=c++11 main.cpp -o main \
    $(pkg-config --cflags --libs glfw3) \
    -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
```

**Without pkg-config:**
```bash
g++ -std=c++11 main.cpp -o main \
    -I/opt/homebrew/include -Isrc \
    -L/opt/homebrew/lib \
    -lglfw \
    -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
```

**Note:** Adjust paths for Intel Macs (`/usr/local` instead of `/opt/homebrew`)

## Controls

All activities support the following controls:
- **ESC** - Close the application
- **Window Resize** - Automatically adjusts viewport

## Credits

- **Original OpenGL Demo**: [zamirmf/OpenGLOnMac](https://github.com/zamirmf/OpenGLOnMac)
- **GLFW**: Marcus Geelnard & Camilla Löwy
- **OpenGL**: Khronos Group

## License

This project is for educational purposes as part of a Computer Vision course.

---

**Tip:** Run `make help` for a complete list of available commands!
