# Name des ausfuehrbaren Programms
EXE = dist/Debug/Cygwin-Windows/Blatt09_Huffman.exe
TEST = build/Debug/Cygwin-Windows/tests/TestFiles/f1.exe


# Pfad zu den Quell-Dateien
SRC_PATH = src
SRC_FILES = $(SRC_PATH)/*.c $(SRC_PATH)/*.h

# Pfade zu BHEAP/BTREE
DIST = dist


# Compiler-Optionen
GCC_OPTION = -g -DDEBUG

# Konfiguration fuer Doxygen
DOXYGEN      = doxygen ppr_doxygen.cfg
DOXYGEN_PATH = doxygen
DOXYGEN_FILE = $(DOXYGEN_PATH)/html/index.html

# Pfad fuer Test-Dateien 
TEST_PATH = testfiles


# Environment 
MKDIR=mkdir
CP=cp
CCADMIN=CCadmin
RANLIB=ranlib


# build
build: .build-pre .build-impl .build-post

.build-pre:
# Add your pre 'build' code here...

.build-post:
# Add your post 'build' code here...


# clean
clean: .clean-pre .clean-impl .clean-post

.clean-pre:
# Add your pre 'clean' code here...

.clean-post:
# Add your post 'clean' code here...


# clobber
clobber: .clobber-pre .clobber-impl .clobber-post

.clobber-pre:
# Add your pre 'clobber' code here...

.clobber-post:
# Add your post 'clobber' code here...


# all
all: .all-pre .all-impl .all-post

.all-pre:
# Add your pre 'all' code here...

.all-post:
# Add your post 'all' code here...


# help
help: .help-pre .help-impl .help-post

.help-pre:
# Add your pre 'help' code here...

.help-post:
# Add your post 'help' code here...


# include project implementation makefile
include nbproject/Makefile-impl.mk


# build tests
build-tests: .build-tests-post

.build-tests-pre:
# Add your pre 'build-tests' code here...

.build-tests-post: .build-tests-impl
# Add your post 'build-tests' code here...


# run tests
test: test_own #.test-post

.test-pre:
# Add your pre 'test' code here...

.test-post: .test-impl
# Add your post 'test' code here...


# ----------------------------------------------------------------------------
# Das erste Ziel ist das Standardziel.
build_own : $(EXE)

# ----------------------------------------------------------------------------
# Regel zum Testen des aktuellen Programms
test_own : build test_start test1 test2 test3 test4 test5 test6 test7 test8 test9 test10 test_end

# ----------------------------------------------------------------------------
# Regeln zum Erzeugen des Projekts
clean_and_build : clean build
build_all : $(EXE) $(DOXYGEN_FILE)

# ----------------------------------------------------------------------------

# Erzeugung der exe-Datei aus .c- und .h-Dateien
$(EXE) : $(SRC_FILES) #$(LIB_FILES)
	@echo ========================================================
	@echo Erzeuge $(EXE)
	@echo --------------------------------------------------------
	gcc $(GCC_OPTION) $(SRC_PATH)/*.c -o $(EXE) 
	

	
# ----------------------------------------------------------------------------
# Regel zum Loeschen aller erzeugten Dateien
clean :
	@echo ========================================================
	@echo Loesche alle abgeleiteten Dateien
	@echo --------------------------------------------------------
	rm -f $(EXE)
	rm -f -r $(DOXYGEN_PATH)
	rm -f $(ZIP_FILE)

# ----------------------------------------------------------------------------
# Regeln für Splint und Doxygen 
# ----------------------------------------------------------------------------
include ~/Makefile-ppr.mk


# ----------------------------------------------------------------------------
# Regeln fuer die einzelnen Testfaelle
    
test_start :
	-./$(TEST) -init
	
test1 :
	@echo .
	@echo ========================================================
	@echo 1. Testfall
	@echo ========================================================
	-./$(TEST) -start test1
	mkdir -p $(TEST_PATH)
	-./$(EXE) -c -o $(TEST_PATH)/01_in.txt.hc $(TEST_PATH)/01_in.txt
	-./$(EXE) -d -o $(TEST_PATH)/01_in.txt.hc.hd $(TEST_PATH)/01_in.txt.hc
	-diff $(TEST_PATH)/01_in.txt $(TEST_PATH)/01_in.txt.hc.hd
	-./$(TEST) -cmp $(TEST_PATH)/01_in.txt $(TEST_PATH)/01_in.txt.hc $(TEST_PATH)/01_in.txt.hc.hd test1
	-./$(TEST) -finish test1
    
test2 :
	@echo .
	@echo ========================================================
	@echo 2. Testfall
	@echo ========================================================
	-./$(TEST) -start test2
	mkdir -p $(TEST_PATH)
	-./$(EXE) -c -o $(TEST_PATH)/02_ab.txt.hc $(TEST_PATH)/02_ab.txt 
	-./$(EXE) -d -o $(TEST_PATH)/02_ab.txt.hc.hd $(TEST_PATH)/02_ab.txt.hc
	-diff $(TEST_PATH)/02_ab.txt $(TEST_PATH)/02_ab.txt.hc.hd
	-./$(TEST) -cmp $(TEST_PATH)/02_ab.txt $(TEST_PATH)/02_ab.txt.hc $(TEST_PATH)/02_ab.txt.hc.hd test2
	-./$(TEST) -finish test2

test3 :
	@echo .
	@echo ========================================================
	@echo 3. Testfall
	@echo ========================================================
	-./$(TEST) -start test3
	mkdir -p $(TEST_PATH)
	-./$(EXE) -c -o $(TEST_PATH)/03_leere.txt.hc $(TEST_PATH)/03_leere.txt 
	-./$(EXE) -d -o $(TEST_PATH)/03_leere.txt.hc.hd $(TEST_PATH)/03_leere.txt.hc
	-diff $(TEST_PATH)/03_leere.txt $(TEST_PATH)/03_leere.txt.hc.hd
	-./$(TEST) -cmp $(TEST_PATH)/03_leere.txt $(TEST_PATH)/03_leere.txt.hc $(TEST_PATH)/03_leere.txt.hc.hd test3
	-./$(TEST) -finish test3

test4 :
	@echo .
	@echo ========================================================
	@echo 4. Testfall
	@echo ========================================================
	-./$(TEST) -start test4
	mkdir -p $(TEST_PATH)
	-./$(EXE) -c -o $(TEST_PATH)/04_1Byte.txt.hc $(TEST_PATH)/04_1Byte.txt 
	-./$(EXE) -d -o $(TEST_PATH)/04_1Byte.txt.hc.hd $(TEST_PATH)/04_1Byte.txt.hc
	-diff $(TEST_PATH)/04_1Byte.txt $(TEST_PATH)/04_1Byte.txt.hc.hd
	-./$(TEST) -cmp $(TEST_PATH)/04_1Byte.txt $(TEST_PATH)/04_1Byte.txt.hc $(TEST_PATH)/04_1Byte.txt.hc.hd test4
	-./$(TEST) -finish test4

test5 :
	@echo .
	@echo ========================================================
	@echo 5. Testfall
	@echo ========================================================
	-./$(TEST) -start test5
	mkdir -p $(TEST_PATH)
	-./$(EXE) -c -o $(TEST_PATH)/05_0-255.txt.hc $(TEST_PATH)/05_0-255.txt 
	-./$(EXE) -d -o $(TEST_PATH)/05_0-255.txt.hc.hd $(TEST_PATH)/05_0-255.txt.hc
	-diff $(TEST_PATH)/05_0-255.txt $(TEST_PATH)/05_0-255.txt.hc.hd
	-./$(TEST) -cmp $(TEST_PATH)/05_0-255.txt $(TEST_PATH)/05_0-255.txt.hc $(TEST_PATH)/05_0-255.txt.hc.hd test5
	-./$(TEST) -finish test5

test6 :
	@echo .
	@echo ========================================================
	@echo 6. Testfall
	@echo ========================================================
	-./$(TEST) -start test6
	mkdir -p $(TEST_PATH)
	-./$(EXE) -c -o $(TEST_PATH)/06_8Nutzbits.txt.hc $(TEST_PATH)/06_8Nutzbits.txt 
	-./$(EXE) -d -o $(TEST_PATH)/06_8Nutzbits.txt.hc.hd $(TEST_PATH)/06_8Nutzbits.txt.hc
	-diff $(TEST_PATH)/06_8Nutzbits.txt $(TEST_PATH)/06_8Nutzbits.txt.hc.hd
	-./$(TEST) -cmp $(TEST_PATH)/06_8Nutzbits.txt $(TEST_PATH)/06_8Nutzbits.txt.hc $(TEST_PATH)/06_8Nutzbits.txt.hc.hd test6
	-./$(TEST) -finish test6

test7 :
	@echo .
	@echo ========================================================
	@echo 7. Testfall
	@echo ========================================================
	-./$(TEST) -start test7
	mkdir -p $(TEST_PATH)
	-./$(EXE) -c -o $(TEST_PATH)/07_in8Bits.txt.hc $(TEST_PATH)/07_in8Bits.txt 
	-./$(EXE) -d -o $(TEST_PATH)/07_in8Bits.txt.hc.hd $(TEST_PATH)/07_in8Bits.txt.hc
	-diff $(TEST_PATH)/07_in8Bits.txt $(TEST_PATH)/07_in8Bits.txt.hc.hd
	-./$(TEST) -cmp $(TEST_PATH)/07_in8Bits.txt $(TEST_PATH)/07_in8Bits.txt.hc $(TEST_PATH)/07_in8Bits.txt.hc.hd test7
	-./$(TEST) -finish test7

test8 :
	@echo .
	@echo ========================================================
	@echo 8. Testfall
	@echo ========================================================
	-./$(TEST) -start test8
	mkdir -p $(TEST_PATH)
	-./$(EXE) -c -o $(TEST_PATH)/08_splint.bin.hc $(TEST_PATH)/08_splint.bin 
	-./$(EXE) -d -o $(TEST_PATH)/08_splint.bin.hc.hd $(TEST_PATH)/08_splint.bin.hc
	-diff $(TEST_PATH)/08_splint.bin $(TEST_PATH)/08_splint.bin.hc.hd
	-./$(TEST) -cmp $(TEST_PATH)/08_splint.bin $(TEST_PATH)/08_splint.bin.hc $(TEST_PATH)/08_splint.bin.hc.hd test8
	-./$(TEST) -finish test8

test9 :
	@echo .
	@echo ========================================================
	@echo 9. Testfall
	@echo ========================================================
	-./$(TEST) -start test9
	mkdir -p $(TEST_PATH)
	-./$(EXE) -c -o $(TEST_PATH)/09_LordOfTheRings.txt.hc $(TEST_PATH)/09_LordOfTheRings.txt 
	-./$(EXE) -d -o $(TEST_PATH)/09_LordOfTheRings.txt.hc.hd $(TEST_PATH)/09_LordOfTheRings.txt.hc
	-diff $(TEST_PATH)/09_LordOfTheRings.txt $(TEST_PATH)/09_LordOfTheRings.txt.hc.hd
	-./$(TEST) -cmp $(TEST_PATH)/09_LordOfTheRings.txt $(TEST_PATH)/09_LordOfTheRings.txt.hc $(TEST_PATH)/09_LordOfTheRings.txt.hc.hd test9
	-./$(TEST) -finish test9
	
test10 :
	@echo .
	@echo ========================================================
	@echo 10. Testfall
	@echo ========================================================
	-./$(TEST) -start test10
	mkdir -p $(TEST_PATH)
	-./$(EXE) -c -o $(TEST_PATH)/10_in.txt.hc $(TEST_PATH)/10_in.txt
	-./$(EXE) -d -o $(TEST_PATH)/10_in.txt.hc.hd $(TEST_PATH)/10_in.txt.hc
	-diff $(TEST_PATH)/10_in.txt $(TEST_PATH)/10_in.txt.hc.hd
	-./$(TEST) -cmp $(TEST_PATH)/10_in.txt $(TEST_PATH)/10_in.txt.hc $(TEST_PATH)/10_in.txt.hc.hd test10
	-./$(TEST) -finish test10

test_end :
	-./$(TEST) -end