# Logger

The Logger class is signaled every time something should be logged.
It will then print the log on the command line and send the log to the server’s GUI via a signal.

## Unit test

The unit tests is implemented with QTest.

## Running the unit tests

*Run swap_mains.bat - To swap the unit test main and the application main.
*Build and run the project.
*Examine the test results.

## Files of interest

*testLogger.h
*testLogger.cpp
*not_main.cpp - The main that run the tests.
*swap_mains.bat