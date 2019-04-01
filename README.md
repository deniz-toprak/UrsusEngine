UrsusEngine

Required VS 15.9.10

with 
 
Windows 10 SDK (10.0.17763.0)
 
Windows 10 SDK (10.0.17134.0)
 
Windows 10 SDK (10.0.10586.0)

Just-in-Time-Debugger
 
VC++ 2017 version 15.9 v14.16 latest v141 tools
 
C++-Profilerstellungstools
 
Windows 10 SDK (10.0.17763.0)
 
Visual C++-Tools für CMake
 
Visual C++-ATL für x86 und x64

Windows 10 SDK (10.0.17134.0)

Windows 10 SDK (10.0.10586.0)

In order for the project to work (load the preset resource) you need to follow these Steps:
Go to Project->Properties (Of SampleGame, UrsusEngine and tmxlite)
and under General->Debugging Set working directory to "$(OutDir)"
otherwise it won't load the files in ..\bin