# Source Structure

I propose the following source structure:

base — all kinds of common stuff: data structures, signals, enumerations. Everything that
is applicable in every other single part of the engine.

core — everything related to a specific platform, such as windows.

debug — everything related to a goal of achieving the correct run of a game, such as: asserts,
exceptions, stacktrace, profilers and etc. (i.e. this kind of stuff are mostly not visible
to the end user, they are for developers).

input — everything related to input devices: input module, keyboard, mouse and gamepad interfaces, 
controls and utilities to work with them.

render — everything related to rendering.

utilities — for classes that are difficult to group into directories, like EndianUtils
(I can't think of a separate directory for EndianUtils).
