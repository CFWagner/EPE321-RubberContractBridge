@echo off

ren %cd%\main.cpp main_temp123.cpp
ren %cd%\test_main.cpp main.cpp
ren %cd%\main_temp123.cpp test_main.cpp