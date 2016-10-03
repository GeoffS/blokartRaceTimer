##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=StartingSequenceMakerTest
ConfigurationName      :=Debug
WorkspacePath          :=D:/stuff/Arduino/Projects/TwoMinuteCountdown2/StartingSequenceMakerWS
ProjectPath            :=D:/stuff/Arduino/Projects/TwoMinuteCountdown2/StartingSequenceMakerWS/StartingSequenceMakerTest
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=gsobering
Date                   :=03/10/2016
CodeLitePath           :="C:/Program Files/CodeLite"
LinkerName             :=C:/MinGW32-xy/bin/g++.exe
SharedObjectLinkerName :=C:/MinGW32-xy/bin/g++.exe -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="StartingSequenceMakerTest.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=C:/MinGW32-xy/bin/windres.exe
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := C:/MinGW32-xy/bin/ar.exe rcu
CXX      := C:/MinGW32-xy/bin/g++.exe
CC       := C:/MinGW32-xy/bin/gcc.exe
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := C:/MinGW32-xy/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/StartingSequenceMaker.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@$(MakeDirCommand) "./Debug"


$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): ../../StartingSequenceMakerTest/main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/stuff/Arduino/Projects/TwoMinuteCountdown2/StartingSequenceMakerTest/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): ../../StartingSequenceMakerTest/main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM ../../StartingSequenceMakerTest/main.cpp

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): ../../StartingSequenceMakerTest/main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix)../../StartingSequenceMakerTest/main.cpp

$(IntermediateDirectory)/StartingSequenceMaker.cpp$(ObjectSuffix): ../../StartingSequenceMaker.cpp $(IntermediateDirectory)/StartingSequenceMaker.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/stuff/Arduino/Projects/TwoMinuteCountdown2/StartingSequenceMaker.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/StartingSequenceMaker.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/StartingSequenceMaker.cpp$(DependSuffix): ../../StartingSequenceMaker.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/StartingSequenceMaker.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/StartingSequenceMaker.cpp$(DependSuffix) -MM ../../StartingSequenceMaker.cpp

$(IntermediateDirectory)/StartingSequenceMaker.cpp$(PreprocessSuffix): ../../StartingSequenceMaker.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/StartingSequenceMaker.cpp$(PreprocessSuffix)../../StartingSequenceMaker.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


