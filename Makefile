# Makefile generated by MakefileGenerator.cs
# *DO NOT EDIT*

UNREALROOTPATH = /media/eric/storage_linux_2/dev/Linux_Unreal_Engine_5.3.2
GAMEPROJECTFILE =/media/eric/storage_linux_2/projects/FebGameJam/FebGameJam.uproject

TARGETS = \
	UnrealEditor-Linux-DebugGame  \
	UnrealEditor-Linux-Shipping  \
	UnrealEditor \
	UnrealGame-Linux-DebugGame  \
	UnrealGame-Linux-Shipping  \
	UnrealGame \
	FebGameJam-Linux-DebugGame  \
	FebGameJam-Linux-Shipping  \
	FebGameJam \
	FebGameJamEditor-Linux-DebugGame  \
	FebGameJamEditor-Linux-Shipping  \
	FebGameJamEditor\
	configure

BUILD = bash "$(UNREALROOTPATH)/Engine/Build/BatchFiles/Linux/Build.sh"
PROJECTBUILD = "$(UNREALROOTPATH)/Engine/Binaries/ThirdParty/DotNet/6.0.302/linux/dotnet" "$(UNREALROOTPATH)/Engine/Binaries/DotNET/UnrealBuildTool/UnrealBuildTool.dll"

all: StandardSet

RequiredTools: CrashReportClient-Linux-Shipping CrashReportClientEditor-Linux-Shipping ShaderCompileWorker UnrealLightmass EpicWebHelper-Linux-Shipping

StandardSet: RequiredTools UnrealFrontend FebGameJamEditor UnrealInsights

DebugSet: RequiredTools UnrealFrontend-Linux-Debug FebGameJamEditor-Linux-Debug


UnrealEditor-Linux-DebugGame:
	 $(BUILD) UnrealEditor Linux DebugGame  $(ARGS)

UnrealEditor-Linux-Shipping:
	 $(BUILD) UnrealEditor Linux Shipping  $(ARGS)

UnrealEditor:
	 $(BUILD) UnrealEditor Linux Development  $(ARGS)

UnrealGame-Linux-DebugGame:
	 $(BUILD) UnrealGame Linux DebugGame  $(ARGS)

UnrealGame-Linux-Shipping:
	 $(BUILD) UnrealGame Linux Shipping  $(ARGS)

UnrealGame:
	 $(BUILD) UnrealGame Linux Development  $(ARGS)

FebGameJam-Linux-DebugGame:
	 $(PROJECTBUILD) FebGameJam Linux DebugGame  -project="$(GAMEPROJECTFILE)" $(ARGS)

FebGameJam-Linux-Shipping:
	 $(PROJECTBUILD) FebGameJam Linux Shipping  -project="$(GAMEPROJECTFILE)" $(ARGS)

FebGameJam:
	 $(PROJECTBUILD) FebGameJam Linux Development  -project="$(GAMEPROJECTFILE)" $(ARGS)

FebGameJamEditor-Linux-DebugGame:
	 $(PROJECTBUILD) FebGameJamEditor Linux DebugGame  -project="$(GAMEPROJECTFILE)" $(ARGS)

FebGameJamEditor-Linux-Shipping:
	 $(PROJECTBUILD) FebGameJamEditor Linux Shipping  -project="$(GAMEPROJECTFILE)" $(ARGS)

FebGameJamEditor:
	 $(PROJECTBUILD) FebGameJamEditor Linux Development  -project="$(GAMEPROJECTFILE)" $(ARGS)

configure:
	xbuild /property:Configuration=Development /verbosity:quiet /nologo "$(UNREALROOTPATH)/Engine/Source/Programs/UnrealBuildTool/UnrealBuildTool.csproj"
	$(PROJECTBUILD) -projectfiles -project="\"$(GAMEPROJECTFILE)\"" -game -engine 

.PHONY: $(TARGETS)
