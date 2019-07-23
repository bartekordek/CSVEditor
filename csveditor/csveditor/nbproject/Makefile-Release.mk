#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=Cygwin-Windows
CND_DLIB_EXT=dll
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/5c0/CSVFile.o \
	${OBJECTDIR}/_ext/5c0/Spreadsheet.o \
	${OBJECTDIR}/_ext/5c0/Table.o \
	${OBJECTDIR}/_ext/5c0/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=../../deps/fltk-1.3.4-1/Build-Cygwin/libfltk.a ../../deps/fltk-1.3.4-1/Build-Cygwin/libfltk_forms.a ../../deps/fltk-1.3.4-1/Build-Cygwin/libfltk_gl.a ../../deps/fltk-1.3.4-1/Build-Cygwin/libfltk_images.a ../../deps/fltk-1.3.4-1/Build-Cygwin/libfltk_jpeg.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/csveditor.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/csveditor.exe: ../../deps/fltk-1.3.4-1/Build-Cygwin/libfltk.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/csveditor.exe: ../../deps/fltk-1.3.4-1/Build-Cygwin/libfltk_forms.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/csveditor.exe: ../../deps/fltk-1.3.4-1/Build-Cygwin/libfltk_gl.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/csveditor.exe: ../../deps/fltk-1.3.4-1/Build-Cygwin/libfltk_images.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/csveditor.exe: ../../deps/fltk-1.3.4-1/Build-Cygwin/libfltk_jpeg.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/csveditor.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/csveditor ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/5c0/CSVFile.o: ../CSVFile.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/5c0
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I.. -I../../deps/fltk-1.3.4-1/inc -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/5c0/CSVFile.o ../CSVFile.cpp

${OBJECTDIR}/_ext/5c0/Spreadsheet.o: ../Spreadsheet.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/5c0
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I.. -I../../deps/fltk-1.3.4-1/inc -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/5c0/Spreadsheet.o ../Spreadsheet.cpp

${OBJECTDIR}/_ext/5c0/Table.o: ../Table.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/5c0
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I.. -I../../deps/fltk-1.3.4-1/inc -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/5c0/Table.o ../Table.cpp

${OBJECTDIR}/_ext/5c0/main.o: ../main.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/5c0
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I.. -I../../deps/fltk-1.3.4-1/inc -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/5c0/main.o ../main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
