@echo off
title Unreal Editor Standalone EOS Tester

:: ========================================================================
:: [설정 영역] 본인의 환경에 맞게 꼭 수정해주세요!
:: ========================================================================
set ENGINE_PATH="C:\UE_5.7\Engine\Binaries\Win64\UnrealEditor.exe"
set PROJECT_PATH="C:\UEGames\Project_Raid\Project_Raid.uproject"

:: ★중요: 프로젝트 세팅(DefaultEngine.ini)에 적어둔 실제 아티팩트 이름을 정확히 적으세요!
set ARTIFACT_NAME=Project:Raid
set AUTH_TOOL_IP=127.0.0.1:8081

echo ========================================================================
echo  Standalone Test.
echo ========================================================================
echo.

:: ------------------------------------------------------------------------
:: 1. HostUser Client
:: ------------------------------------------------------------------------
echo [1/2] HostUser Client is running...
start "" %ENGINE_PATH% %PROJECT_PATH% -game -epicapp=%ARTIFACT_NAME% -AUTH_TYPE=developer -AUTH_LOGIN=%AUTH_TOOL_IP% -AUTH_CREDENTIALS=HostUser -UserDir="HostUser" -windowed -resx=1280 -resy=720 -LOG
echo.

timeout /t 10 >nul

:: ------------------------------------------------------------------------
:: 2. GuestUser Client
:: ------------------------------------------------------------------------
echo [2/2]GuestUser Clientis running...
start "" %ENGINE_PATH% %PROJECT_PATH% -game -epicapp=%ARTIFACT_NAME% -AUTH_TYPE=developer -AUTH_LOGIN=%AUTH_TOOL_IP% -AUTH_CREDENTIALS=GuestUser -UserDir="GuestUser" -windowed -resx=1280 -resy=720 -LOG
echo.

echo all Client is Activated
timeout /t 3 >nul
exit