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

REM Clean up the Deployment directory

RMDIR /S /Q "%LCR_DEPLOYMENT_DIR%"
MKDIR "%LCR_DEPLOYMENT_DIR%"

REM ===========================================================================
REM Copy the library files
REM ===========================================================================

REM Qt
COPY "%QTDIR_ROOT%\bin\libEGL.dll" "%LCR_DEPLOYMENT_DIR%"
COPY "%QTDIR_ROOT%\bin\libGLESv2.dll" "%LCR_DEPLOYMENT_DIR%"
COPY "%QTDIR_ROOT%\bin\opengl32sw.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt53DAnimation.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt53DCore.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt53DExtras.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt53DInput.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt53DLogic.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt53DQuick.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt53DQuickAnimation.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt53DQuickExtras.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt53DQuickInput.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt53DQuickRender.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt53DQuickScene2D.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt53DRender.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt5Bluetooth.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt5Charts.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt5Concurrent.dll" "%LCR_DEPLOYMENT_DIR%"
COPY "%QTDIR_ROOT%\bin\Qt5Core.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt5DataVisualization.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt5DBus.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt5Gamepad.dll" "%LCR_DEPLOYMENT_DIR%"
COPY "%QTDIR_ROOT%\bin\Qt5Gui.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt5Help.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt5Location.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt5Multimedia.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt5MultimediaQuick.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt5MultimediaWidgets.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt5Network.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt5NetworkAuth.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt5Nfc.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt5OpenGL.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt5Positioning.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt5PositioningQuick.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt5PrintSupport.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt5Purchasing.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt5Qml.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt5Quick.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt5QuickControls2.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt5QuickParticles.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt5QuickTemplates2.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt5QuickTest.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt5QuickWidgets.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt5RemoteObjects.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt5Script.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt5ScriptTools.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt5Scxml.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt5Sensors.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt5SerialBus.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt5SerialPort.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt5Sql.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt5Svg.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt5Test.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt5TextToSpeech.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt5WebChannel.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt5WebEngine.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt5WebEngineCore.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt5WebEngineWidgets.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt5WebSockets.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt5WebView.dll" "%LCR_DEPLOYMENT_DIR%"
COPY "%QTDIR_ROOT%\bin\Qt5Widgets.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt5WinExtras.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt5Xml.dll" "%LCR_DEPLOYMENT_DIR%"
REM COPY "%QTDIR_ROOT%\bin\Qt5XmlPatterns.dll" "%LCR_DEPLOYMENT_DIR%"

MKDIR "%LCR_DEPLOYMENT_DIR%\plugins"
MKDIR "%LCR_DEPLOYMENT_DIR%\plugins\designer"
MKDIR "%LCR_DEPLOYMENT_DIR%\plugins\iconengines"
MKDIR "%LCR_DEPLOYMENT_DIR%\plugins\imageformats"
MKDIR "%LCR_DEPLOYMENT_DIR%\plugins\platforminputcontexts"
MKDIR "%LCR_DEPLOYMENT_DIR%\plugins\platforms"
MKDIR "%LCR_DEPLOYMENT_DIR%\plugins\platformthemes"
MKDIR "%LCR_DEPLOYMENT_DIR%\plugins\styles"
XCOPY /S "%QTDIR_ROOT%\plugins\designer" "%LCR_DEPLOYMENT_DIR%\plugins\designer"
XCOPY /S "%QTDIR_ROOT%\plugins\iconengines" "%LCR_DEPLOYMENT_DIR%\plugins\iconengines"
XCOPY /S "%QTDIR_ROOT%\plugins\imageformats" "%LCR_DEPLOYMENT_DIR%\plugins\imageformats"
XCOPY /S "%QTDIR_ROOT%\plugins\platforminputcontexts" "%LCR_DEPLOYMENT_DIR%\plugins\platforminputcontexts"
XCOPY /S "%QTDIR_ROOT%\plugins\platforms" "%LCR_DEPLOYMENT_DIR%\plugins\platforms"
XCOPY /S "%QTDIR_ROOT%\plugins\platformthemes" "%LCR_DEPLOYMENT_DIR%\plugins\platformthemes"
XCOPY /S "%QTDIR_ROOT%\plugins\styles" "%LCR_DEPLOYMENT_DIR%\plugins\styles"

REM ===========================================================================
REM Copy the build files
REM ===========================================================================

CALL "%LCR_ROOT%\UpdateDeployment.bat"

ECHO [Paths] > "%LCR_DEPLOYMENT_DIR%\qt.conf"
ECHO Plugins = .\\plugins >> "%LCR_DEPLOYMENT_DIR%\qt.conf"

GOTO END

:PAUSE_END
pause
GOTO END

:END
