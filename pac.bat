@echo off

rem call "C:\Program Files\WinRAR\winrar.exe" a -r DEMO.exe DEMO\*.*

rem if not exist "archive" mkdir archive

dir /b /s /a-d *.txt > list.txt

SETLOCAL EnableDelayedExpansion

for /F "usebackq tokens=*" %%A in ("list.txt") do (
	set "_fullpath=%%~fA"
	set "_dirpath=%%~pA"
	set "_drive=%%~dA"
	set "_filename=%%~nA"
	set "_fileextension=%%~xA"
	set "_subpath=!_drive!!_dirpath!!_filename!"
	set "_subpath=!_subpath:%CD%\=!"
	set "_html_filename=!_subpath!!_fileextension!.html"
	set "_html_filename=!_html_filename:\=_!"
	set "_string=!_subpath:\=/!"
	if "!_fileextension!" == ".txt" (
		call "C:\Program Files\WinRAR\winrar.exe" a !_filename!.zip !_filename!.txt
	)

)	

pause
