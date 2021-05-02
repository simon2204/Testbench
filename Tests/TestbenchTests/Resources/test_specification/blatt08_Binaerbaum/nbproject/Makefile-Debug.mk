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
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/btree.o \
	${OBJECTDIR}/src/btreenode.o \
	${OBJECTDIR}/src/frequency.o \
	${OBJECTDIR}/src/main.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1

# Test Object Files
TESTOBJECTFILES= \
	${TESTDIR}/tests/data.o \
	${TESTDIR}/tests/ppr_tb_extern_prototypes.o \
	${TESTDIR}/tests/ppr_tb_test_btree.o

# C Compiler Flags
CFLAGS=-Wall -DDEBUG

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/blatt08_binaerbaum.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/blatt08_binaerbaum.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/blatt08_binaerbaum ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/btree.o: src/btree.c
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../../02_vorlesung/08_Strukturen/code_beispiele/frequency/src -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/btree.o src/btree.c

${OBJECTDIR}/src/btreenode.o: src/btreenode.c
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../../02_vorlesung/08_Strukturen/code_beispiele/frequency/src -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/btreenode.o src/btreenode.c

${OBJECTDIR}/src/frequency.o: src/frequency.c
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../../02_vorlesung/08_Strukturen/code_beispiele/frequency/src -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/frequency.o src/frequency.c

${OBJECTDIR}/src/main.o: src/main.c
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../../02_vorlesung/08_Strukturen/code_beispiele/frequency/src -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main.o src/main.c

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-tests-subprojects .build-conf ${TESTFILES}
.build-tests-subprojects:

${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/data.o ${TESTDIR}/tests/ppr_tb_extern_prototypes.o ${TESTDIR}/tests/ppr_tb_test_btree.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c} -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS}   


${TESTDIR}/tests/data.o: tests/data.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../../02_vorlesung/08_Strukturen/code_beispiele/frequency/src -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/data.o tests/data.c


${TESTDIR}/tests/ppr_tb_extern_prototypes.o: tests/ppr_tb_extern_prototypes.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../../02_vorlesung/08_Strukturen/code_beispiele/frequency/src -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/ppr_tb_extern_prototypes.o tests/ppr_tb_extern_prototypes.c


${TESTDIR}/tests/ppr_tb_test_btree.o: tests/ppr_tb_test_btree.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../../02_vorlesung/08_Strukturen/code_beispiele/frequency/src -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/ppr_tb_test_btree.o tests/ppr_tb_test_btree.c


${OBJECTDIR}/src/btree_nomain.o: ${OBJECTDIR}/src/btree.o src/btree.c 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/btree.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../../02_vorlesung/08_Strukturen/code_beispiele/frequency/src -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/btree_nomain.o src/btree.c;\
	else  \
	    ${CP} ${OBJECTDIR}/src/btree.o ${OBJECTDIR}/src/btree_nomain.o;\
	fi

${OBJECTDIR}/src/btreenode_nomain.o: ${OBJECTDIR}/src/btreenode.o src/btreenode.c 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/btreenode.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../../02_vorlesung/08_Strukturen/code_beispiele/frequency/src -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/btreenode_nomain.o src/btreenode.c;\
	else  \
	    ${CP} ${OBJECTDIR}/src/btreenode.o ${OBJECTDIR}/src/btreenode_nomain.o;\
	fi

${OBJECTDIR}/src/frequency_nomain.o: ${OBJECTDIR}/src/frequency.o src/frequency.c 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/frequency.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../../02_vorlesung/08_Strukturen/code_beispiele/frequency/src -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/frequency_nomain.o src/frequency.c;\
	else  \
	    ${CP} ${OBJECTDIR}/src/frequency.o ${OBJECTDIR}/src/frequency_nomain.o;\
	fi

${OBJECTDIR}/src/main_nomain.o: ${OBJECTDIR}/src/main.o src/main.c 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/main.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../../02_vorlesung/08_Strukturen/code_beispiele/frequency/src -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main_nomain.o src/main.c;\
	else  \
	    ${CP} ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/main_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
