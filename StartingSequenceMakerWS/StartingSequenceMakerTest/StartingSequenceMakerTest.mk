##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=StartingSequenceMakerTest
ConfigurationName      :=Debug
WorkspacePath          :=G:/Arduino/Projects/TwoMinuteCountdown2/StartingSequenceMakerWS
ProjectPath            :=G:/Arduino/Projects/TwoMinuteCountdown2/StartingSequenceMakerWS/StartingSequenceMakerTest
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Geoff
Date                   :=10/03/2017
CodeLitePath           :="G:/Program Files/CodeLite"
LinkerName             :=C:/TDM-GCC-64/bin/g++.exe
SharedObjectLinkerName :=C:/TDM-GCC-64/bin/g++.exe -shared -fPIC
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
RcCompilerName         :=C:/TDM-GCC-64/bin/windres.exe
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
AR       := C:/TDM-GCC-64/bin/ar.exe rcu
CXX      := C:/TDM-GCC-64/bin/g++.exe
CC       := C:/TDM-GCC-64/bin/gcc.exe
CXXFLAGS :=  -g -O0 -Wall -std=c++11 $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := C:/TDM-GCC-64/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=G:\Program Files\CodeLite
Objects0=$(IntermediateDirectory)/up_up_StartingSequenceMakerTest_main.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_StartingSequenceMaker.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_StartingSequenceMaker211.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_StartingSequenceMaker220.cpp$(ObjectSuffix) 



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
$(IntermediateDirectory)/up_up_StartingSequenceMakerTest_main.cpp$(ObjectSuffix): ../../StartingSequenceMakerTest/main.cpp $(IntermediateDirectory)/up_up_StartingSequenceMakerTest_main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "G:/Arduino/Projects/TwoMinuteCountdown2/StartingSequenceMakerTest/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_StartingSequenceMakerTest_main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_StartingSequenceMakerTest_main.cpp$(DependSuffix): ../../StartingSequenceMakerTest/main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_StartingSequenceMakerTest_main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_StartingSequenceMakerTest_main.cpp$(DependSuffix) -MM ../../StartingSequenceMakerTest/main.cpp

$(IntermediateDirectory)/up_up_StartingSequenceMakerTest_main.cpp$(PreprocessSuffix): ../../StartingSequenceMakerTest/main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_StartingSequenceMakerTest_main.cpp$(PreprocessSuffix) ../../StartingSequenceMakerTest/main.cpp

$(IntermediateDirectory)/up_up_StartingSequenceMaker.cpp$(ObjectSuffix): ../../StartingSequenceMaker.cpp $(IntermediateDirectory)/up_up_StartingSequenceMaker.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "G:/Arduino/Projects/TwoMinuteCountdown2/StartingSequenceMaker.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_StartingSequenceMaker.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_StartingSequenceMaker.cpp$(DependSuffix): ../../StartingSequenceMaker.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_StartingSequenceMaker.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_StartingSequenceMaker.cpp$(DependSuffix) -MM ../../StartingSequenceMaker.cpp

$(IntermediateDirectory)/up_up_StartingSequenceMaker.cpp$(PreprocessSuffix): ../../StartingSequenceMaker.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_StartingSequenceMaker.cpp$(PreprocessSuffix) ../../StartingSequenceMaker.cpp

$(IntermediateDirectory)/up_up_StartingSequenceMaker211.cpp$(ObjectSuffix): ../../StartingSequenceMaker211.cpp $(IntermediateDirectory)/up_up_StartingSequenceMaker211.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "G:/Arduino/Projects/TwoMinuteCountdown2/StartingSequenceMaker211.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_StartingSequenceMaker211.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_StartingSequenceMaker211.cpp$(DependSuffix): ../../StartingSequenceMaker211.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_StartingSequenceMaker211.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_StartingSequenceMaker211.cpp$(DependSuffix) -MM ../../StartingSequenceMaker211.cpp

$(IntermediateDirectory)/up_up_StartingSequenceMaker211.cpp$(PreprocessSuffix): ../../StartingSequenceMaker211.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_StartingSequenceMaker211.cpp$(PreprocessSuffix) ../../StartingSequenceMaker211.cpp

$(IntermediateDirectory)/up_up_StartingSequenceMaker220.cpp$(ObjectSuffix): ../../StartingSequenceMaker220.cpp $(IntermediateDirectory)/up_up_StartingSequenceMaker220.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "G:/Arduino/Projects/TwoMinuteCountdown2/StartingSequenceMaker220.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_StartingSequenceMaker220.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_StartingSequenceMaker220.cpp$(DependSuffix): ../../StartingSequenceMaker220.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_StartingSequenceMaker220.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_StartingSequenceMaker220.cpp$(DependSuffix) -MM ../../StartingSequenceMaker220.cpp

$(IntermediateDirectory)/up_up_StartingSequenceMaker220.cpp$(PreprocessSuffix): ../../StartingSequenceMaker220.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_StartingSequenceMaker220.cpp$(PreprocessSuffix) ../../StartingSequenceMaker220.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


