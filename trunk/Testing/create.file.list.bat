@ECHO off

SET DIR=Database
SET CATEGORY=(Allat;Asvany;Epuletek;Neprajzi_motivum;Noveny)
SET FILE_LIST_NAME=input\file_list.txt

ECHO Y | DEL %FILE_LIST_NAME%

ECHO ^<?xml version="1.0"?^> >> %FILE_LIST_NAME%
ECHO ^<opencv_storage^> >> %FILE_LIST_NAME%
ECHO ^<images^> >> %FILE_LIST_NAME%

FOR %%c IN %CATEGORY% DO (
	SET CAT_PATH=%DIR%\%%c
	FOR /r %CAT_PATH% %%n IN (*.gif;*.jpg;*.jpeg;*.png;*.bmp;*.tiff) DO (
		ECHO %%n >> %FILE_LIST_NAME%
	)
)

ECHO ^</images^> >> %FILE_LIST_NAME%
ECHO ^</opencv_storage^> >> %FILE_LIST_NAME%

PAUSE
