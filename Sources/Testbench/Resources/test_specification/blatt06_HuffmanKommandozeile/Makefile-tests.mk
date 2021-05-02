# Name des ausfuehrbaren Programms (NetBeans)
EXE = $(CND_ARTIFACT_PATH_Debug)/$(CND_ARTIFACT_NAME)

# Pfad zu den Quell-Dateien
SRC_PATH = ./src
SRC_FILES = $(SRC_PATH)/*.c $(SRC_PATH)/*.h

# Pfad fuer Test-Dateien 
TEST_PATH = testfiles

# ----------------------------------------------------------------------------
# Regel zum Testen des aktuellen Programms
.test-own : build test1 test2 test3 test4 test5 test6 test7 test8 test9 test10 \
	    test11 test12

# ----------------------------------------------------------------------------
# Regeln fuer die einzelnen Testfaelle
    
test1 :
	@echo .
	@echo ========================================================
	@echo "1. Testfall (alle Parameter, ausser -h)"
	@echo ========================================================
	-./$(EXE) -c -o $(TEST_PATH)/out.txt -l7 -v $(TEST_PATH)/in.txt
    
test2 :
	@echo .
	@echo ========================================================
	@echo "2. Testfall (Zu wenige Parameter)"
	@echo ========================================================
	-./$(EXE)

test3 :
	@echo .
	@echo ========================================================
	@echo "3. Testfall (-o ohne Ausgabedatei)"
	@echo ========================================================
	-./$(EXE) -c -o $(TEST_PATH)/in.txt
	
test4 :
	@echo .
	@echo ========================================================
	@echo "4. Testfall (-o out.txt)"
	@echo ========================================================
	-./$(EXE) -d -o $(TEST_PATH)/out.txt $(TEST_PATH)/in.txt
	
test5 :
	@echo .
	@echo ========================================================
	@echo "5. Testfall (Unbekannte Option -x)"
	@echo ========================================================
	-./$(EXE) -c -x $(TEST_PATH)/in.txt
	
test6 :
	@echo .
	@echo ========================================================
	@echo "6. Testfall (Level bei Option -l fehlt)"
	@echo ========================================================
	-./$(EXE) -c -l $(TEST_PATH)/in.txt
	
test7 :
	@echo .
	@echo ========================================================
	@echo "7. Testfall (Ungueltiger Level, muss zwischen 1 und 9 sein)"
	@echo ========================================================
	-./$(EXE) -c -l29 $(TEST_PATH)/in.txt
	
test8 :
	@echo .
	@echo ========================================================
	@echo "8. Testfall (Namen von Ein- und Ausgabedatei sind gleich)"
	@echo ========================================================
	-./$(EXE) -c -o $(TEST_PATH)/in.txt $(TEST_PATH)/in.txt
	
test9 :
	@echo .
	@echo ========================================================
	@echo "9. Testfall (weder -d noch -c angegeben)"
	@echo ========================================================
	-./$(EXE) $(TEST_PATH)/in.txt 	
	
test10 :
	@echo .
	@echo ========================================================
	@echo "10. Testfall (Eingabedatei existiert nicht)"
	@echo ========================================================
	-./$(EXE) -c $(TEST_PATH)/not_exists.txt

test11 :
	@echo .
	@echo ========================================================
	@echo "11. Testfall (-c, -v, -o testfiles/out.txt)"
	@echo ========================================================
	rm -f $(TEST_PATH)/out.txt
	-./$(EXE) -c -v -o $(TEST_PATH)/out.txt $(TEST_PATH)/in.txt
	
test12 :
	@echo .
	@echo ========================================================
	@echo "12. Testfall (-d -v, ohne -o filename)"
	@echo ========================================================
	rm -f $(TEST_PATH)/in.txt.hd
	-./$(EXE) -d -v $(TEST_PATH)/in.txt
	rm $(TEST_PATH)/in.txt.hd
    