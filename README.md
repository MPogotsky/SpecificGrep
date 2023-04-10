# SpecificGrep

## Installation
### Prerequisites
Before you can install Grep, you need to have the following software installed:

- CMake 3.22.1
- Boost

### Building from source

1. Clone the repository:

```console
git clone https://github.com/MPogotsky/SpecificGrep.git
cd SpecificGrep
```

2. Create a build directory:

```console
mkdir build
cd build
```

3. Build the executable:

```console
cmake ..
make
```

## Usage

```console
./specific_grep PATTERN OPTIONS
```

Possible options, you can also find them in --help menu

| Parameter  | Description | Default value |
|------------|-------------|---------------|
| -d or --dir |	Start directory | Current directory |
|-l or --log_file| Name of the log file | \<program name\>.log |
|-r or --result_file| Name of the file where result is given| \<program name\>.txt |
|-t or --threads| Number of threads in the pool| 4 |
