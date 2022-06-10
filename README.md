## helloos
Simple home made OS for x86.

## Building

Ubuntu:
```bash
# run to configure
apt install qemu-system-x86 gcc-multilib nasm
git clone https://github.com/kotleni/helloos
cd helloos
make init

# run to build
make

# run to test
make run
```

MacOS:
```bash
# run to configure
brew install x86_64-elf-gcc
brew install nasm
brew install qemu-system-x86
git clone https://github.com/kotleni/helloos
cd helloos
make init

# run to build
make

# run to test
make run
```
