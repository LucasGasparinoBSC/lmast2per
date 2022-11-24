# LMAST2PER

A simple program that reverses a list of slave/master nodes into a list of master/slave nodes.
Created to convert the output of pyAlya for the periodic nodes into a file that can be used
by SOD2D.

## Build

Simply run:

```bash
make
```

into the root directory of the project.

## Usage

```bash
./lmast2per.x <file_name>
```

Make sure that the output of pyAlya is in the same directory as the executable, and has a `.per.dat` extension.
The output file will be named `<file_name>.per` and will be placed in the same directory as the executable.
