#
# Makefile fuer das Blatt02 (Determinantenberechnung)
#
# author  Ulrike Griefahn
# date    2014-01-27
#


# ============================================================================
# Variablen
# ============================================================================

# Titel Aufgabenblatt (Aufgabenkurzbezeichnung)
LABEL = MATRIX (Blatt 02)

# Zeitlimit fuer die Prozessausfuehrung [sec].
TIMEOUT = 5.0

# Blattspezifische Splint-Konfiguration
SPLINT_ADD_OPTIONS = -fixedformalarray

# Blattspezifische GCC-Konfiguration
GCC_ADD_OPTIONS = -DTESTBENCH


# ============================================================================
# Regeln
# ============================================================================

# ----------------------------------------------------------------------------
# Regel fuer das Vorbereiten von Splint
splint-setup :


# ----------------------------------------------------------------------------
# Regel fuer das Vorbereiten der Kompilierung
compile-setup :
    # main-Funktion der Loesung wird umbenannt 
	@for file in $(BUILD_DIR)/*.c; do \
		sed 's/\(int main *(\)/int _main\(/g' "$$file" > $(TMP_MAIN)1; \
		sed 's/#define *MAX_SIZE.*/#define MAX_SIZE 10/g' $(TMP_MAIN)1 > $(TMP_MAIN)2; \
		mv $(TMP_MAIN)2 "$$file"; \
	done
	@echo    

    # Testprogramme ins build-Verzeichnis kopieren
	@cp $(TESTS_DIR)/* $(BUILD_DIR)/;
	@cp $(SRC_GLOBAL_DIR)/$(LOGGING).* $(BUILD_DIR)/;

    # wait_and_exit im build-Verzeichnis erzeugen
	@gcc $(SRC_GLOBAL_DIR)/$(CTRL).c -o $(BUILD_DIR)/$(CTRL).o \
	                                     -DFUNCTION_TEST $(GCC_MATH_OPTION);


# ----------------------------------------------------------------------------
# Regel zum Testen des aktuellen Programms
test: start testfaelle end

start:
	@echo -e "\f"; 
	@echo "+--------------------------------------------------------------+"
	@echo "| TEST $(LABEL)"
	@echo "+--------------------------------------------------------------+"
	@echo

# Regeln fuer die (einzelnen) Testfaelle
testfaelle:
	-@cd $(BUILD_DIR) \
	    && ./$(USER_SUBMISSION).o $(STATS_DIR)/$(LEISTUNGEN)_$(TEST_DIR).csv &
	
	-@$(BUILD_DIR)/$(CTRL).o -builddir $(BUILD_DIR) \
	                       -app $(USER_SUBMISSION).o \
	                       -timeout $(TIMEOUT)\
			       -csv $(TEST_DIR)/stats/$(LEISTUNGEN)_$(TEST_DIR).csv;

end:
