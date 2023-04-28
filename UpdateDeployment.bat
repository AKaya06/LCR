@ECHO OFF
REM This script requires the following environment variables to be set:
REM 1. DEVENV_ROOT_2022
REM 2. QTDIR_ROOT
REM 3. LCR_ROOT

IF "%DEVENV_ROOT_2022%" == "" (
	ECHO Please specify the following environment variables: DEVENV_ROOT_2022
	goto PAUSE_END
)

IF "%QTDIR_ROOT%" == "" (
	ECHO Please specify the following environment variables: QTDIR_ROOT
	goto PAUSE_END
)

IF "%LCR_ROOT%" == "" (
	ECHO Please specify the following environment variables: LCR_ROOT
	goto PAUSE_END
)

REM Setup eviroment
SET QTDIR=%QTDIR_ROOT%
SET QDIR=%QTDIR%

IF "%LCR_DEPLOYMENT_DIR%" == "" (
    SET LCR_DEPLOYMENT_DIR="%LCR_ROOT%\Deployment"
)

del "%LCR_DEPLOYMENT_DIR%\LCR.exe"
COPY "%LCR_ROOT%\x64\Release\LCR.exe" "%LCR_DEPLOYMENT_DIR%"

del "%LCR_DEPLOYMENT_DIR%\stylesheet.qss"
COPY "%LCR_ROOT%\stylesheet.qss" "%LCR_DEPLOYMENT_DIR%"

del "%LCR_DEPLOYMENT_DIR%\LCR.ico"
COPY "%LCR_ROOT%\LCR.ico" "%LCR_DEPLOYMENT_DIR%"

GOTO END

:PAUSE_END
pause
GOTO END

:END
