@echo off
cl main.c /Fegame.exe /Zi /D "UNICODE" /D "_UNICODE" /nologo user32.lib gdi32.lib 
