@ECHO off

SET DIR=Database
SET FILE_LIST_NAME=input\file_list.txt

ECHO Y | DEL %FILE_LIST_NAME%

ECHO ^<?xml version="1.0"?^> >> %FILE_LIST_NAME%
ECHO ^<opencv_storage^> >> %FILE_LIST_NAME%
ECHO ^<images^> >> %FILE_LIST_NAME%

FOR /r %DIR% %%n IN (*.gif;*.jpg;*.jpeg;*.png;*.bmp;*.tiff) DO (
	ECHO %%n >> %FILE_LIST_NAME%
)

ECHO ^</images^> >> %FILE_LIST_NAME%
ECHO ^</opencv_storage^> >> %FILE_LIST_NAME%

PAUSE
