@echo off
setlocal

REM 设置源文件夹路径（同级目录下的SSH文件夹）
set "source_path=SSH"
REM 设置目标路径（公共文档目录）
set "target_path=C:\Users\Public\Documents\SSH"

REM 检查源文件夹是否存在
if not exist "%source_path%" (
    echo not find
    pause
    exit /b 1
)

REM 使用xcopy命令复制文件夹（含子目录和空文件夹）
xcopy "%source_path%" "%target_path%" /E /I /Y

REM 提示操作结果
if %errorlevel% equ 0 (
    echo  done %target_path%
) else (
    echo error
)
