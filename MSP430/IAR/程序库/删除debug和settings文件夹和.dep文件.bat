@echo on

@echo 删除本文件夹和子文件夹下的debug settings文件夹和*.dep文件;Ctrl+C可以取消

@pause

@rem 删除调试用文件、文件夹

@rem for /r . %%a in (.) do @if exist "%%a\debug" @echo "%%a\debug"
@for /r . %%a in (.) do @if exist "%%a\debug" rd /s /q "%%a\debug"

@rem for /r . %%a in (.) do @if exist "%%a\settings" @echo "%%a\settings"
@for /r . %%a in (.) do @if exist "%%a\settings" rd /s /q "%%a\settings"

@del /F /S /Q *.dep

@echo completed
@pause