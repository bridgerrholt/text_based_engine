# Text-Based Engine
An engine programmed in C++ that reads XML files that form a text-based game.

## Dependencies
The default makefile assumes all dependency libraries to be in a directory named "_libs" that is in the same directory as this project.
Furthermore, it assumes the binary objects (i.e. .dylib .so .o .dll) to be in "_libs/_master/bin/" and the library objects (i.e. .lib .a) to be in "_libs/_master/lib/".


### Xerces-C++ XML Parser
The front page can be found [here](https://xerces.apache.org/xerces-c/ "Xerces-C++ front page").
The default makefile expects the main directory for Xerces-C++ (i.e. the directory containing the directory "src") to be called "xerces-c".