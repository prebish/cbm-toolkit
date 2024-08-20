# CBM File Toolkit

Convert CBM image files to BMP format with the CBM-2-BMP program! Extract image data from CBM files, view CBM/BMP information, and easily convert CBM images to BMP.

You can also find more information about CBM files here: [file.org](https://file.org/extension/cbm)

### Table of Contents

- [Installation & Setup](#installation--setup)
  1. [Clone the Repository](#1-clone-the-repository)
  2. [Move to Program Directory](#2-move-to-program-directory)
- [Usage](#usage)
  1. [Program Startup](#program-startup)
  2. [Conversion Options](#toolkit-features)
- [License](#license)

## Installation & Setup

Make sure you have GCC installed to compile the program. You can install it via your package manager or download it from the official website.

### 1. Clone the Repository

```bash
git clone https://github.com/prebish/cbm-toolkit.git
```

### 2. Move to Program Directory

```bash
cd ./cbm-toolkit
```

## Usage

### Program Startup

Compile the program using the provided Makefile in the project root:

```bash
make
```

After compiling, you can start using the program by running the following command:

```bash
./cbmtk --convert <input_file.cbm> <output_file.bmp>
```

You can use the sample files included in the `samples` directory for testing.

### Toolkit Features

You can run the program with the following commands:

**Convert CBM to BMP:**

  ```bash
  ./cbmtk --convert samples/input.cbm output.bmp
  ```

**Get CBM File Info:**

  ```bash
  ./cbmtk --info samples/input.cbm
  ```

**Get BMP File Info:**

  ```bash
  ./cbmtk --bmp-info output.bmp
  ```

## License
This project is licensed under the MIT License - see the `LICENSE` file for details.
