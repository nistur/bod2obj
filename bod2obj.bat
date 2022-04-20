ECHO OFF

SET BodFile=%1

IF NOT EXIST %BodFile% (
   > usermessage.vbs ECHO MsgBox "Ship BOD file %BodFile% is invalid"
   CSCRIPT.EXE usermessage.vbs
   DEL usermessage.vbs
   EXIT
)

IF EXIST bod2obj.exe (
   SET b2o=bod2obj.exe
) ELSE (
  IF EXIST bin\bod2obj.exe (
    SET b2o=bin\bod2obj.exe
  )
)

IF NOT EXIST %b2o% (
   > usermessage.vbs ECHO MsgBox "bod2obj executable not found"
   CSCRIPT.EXE usermessage.vbs
   DEL usermessage.vbs
   EXIT
)

> usermessage.vbs ECHO WScript.Echo InputBox( "What is the name of the ship?", "bod2obj", "Argon Nova" )
FOR /F "tokens=*" %%A IN ('CSCRIPT.EXE //NoLogo usermessage.vbs') DO SET ShipName=%%A
DEL usermessage.vbs

%b2o% %BodFile% %ShipName: =%
