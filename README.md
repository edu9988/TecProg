This repository contains the source for a C written GNU/Linux-compatible game called spacewar

### spacewar

The spacewar project started as a college assignment.

Currently, it needs a graphics library provided by the professor (Marco Dimas Gubitoso)to run. This library is but a wrapper to the X11 library just to make it easier to use, afterall, the original course was given in the 1st year of a computer science undergraduate course.

Valgrind also picks up numerous errors, which were not noticed at the time by the authors, since they had not started using valgrind by then.

##### Future goals

- Use a different library for increased portability.

- Perhaps redo the entire graphical module in order to remove bugs and errors.

- Make the program multi-threaded, an attempt to solve keyboard issues.

Add gaming features later

##### July 3rd 2023 screenshot

![Game screenshot](/assets/screenshot.jpg)
