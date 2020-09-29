@echo off

ren %cd%\main.cpp main_temp123.cpp
ren %cd%\not_main.cpp main.cpp
ren %cd%\main_temp123.cpp not_main.cpp