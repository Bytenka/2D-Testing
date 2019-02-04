# 2D-Testing

This is an attempt to build a game from scratch using C++ and OpenGL. 
The goal is to make a 3D game, but also to build a solid code base for future projects.

## Getting started

We're using [Premake5](https://premake.github.io/) to build the project. 
The premake5.lua is a WIP and the actual configuration makes it easy to build under Linux with **make**.
Support for Windows will be comming some day.

### Prerequisites

```
- premake5
- make
```

### Installing

Clone this repo and run premake5 to create a makefile -> `premake5 gmake2`

`gmake2` mode is important because the project is using PCHs to speed up build time, and `gmake` can't deal with them properly

You can then run the makefile



*This README is a WIP*
