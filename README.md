# BoltEng

## Project Structure

### Application

### Components

Common components that we expect will be universally useful for games made with the engine. Games themselves should write their own components that suit their particular needs, but there's some stuff that we can just provide for everyone.

### Entities

### Graphics

### Input

Handles user input classes and methods. Supports connecting up to 4 game pads, as well as keyboard and mouse.

### Maths

### Subsystems

Subsystems are an abstraction layer above platform specific code and third party libraries. It is there to give us the flexibility to change how we interact with the OS at a low level without impacting on game code. For example, SDL2 is used for window management, OpenGL etc at the moment. If at some point in the future we want to migrate to SDL3 or use some other library entirely, we can change it in the subsystem and the systems themselves should just keep working.

### Systems

Common systems that we expect will be universally useful for games made with the engine. Games themselves should write their own systems that suit their particular needs, but there's some stuff that we can just provide for everyone.

### Util

Helpful code and reusable elements that don't belong anywhere else.