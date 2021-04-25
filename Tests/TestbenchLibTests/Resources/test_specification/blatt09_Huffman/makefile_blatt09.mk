#
# Makefile fuer Blatt 09 (Huffman-Kodierung)
#
# author  Ulrike Griefahn
# date    2017-01-12
#

# ============================================================================
# Variablen
# ============================================================================

# Titel Aufgabenblatt (Aufgabenkurzbezeichnung)
LABEL = HUFFMAN (Blatt 09)

# Zeitlimit fuer die Prozessausfuehrung [sec].
TIMEOUT = 60.0

# Blattspezifische Splint-Konfiguration
SPLINT_ADD_OPTIONS = +exportlocal -warnposix +skip-sys-headers -preproc

# Blattspezifische GCC-Konfiguration
GCC_ADD_OPTIONS = 

# Name des Programms zum Prüfen des jeweiligen Testfalls
TEST = ppr_tb_test_huffman


# ============================================================================
# Regeln
# ============================================================================

# ----------------------------------------------------------------------------
# Regel fuer das Vorbereiten von Splint
splint-setup:

	@for file in $(BUILD_DIR)/*.c; do \
		sed 's/#include <sys\\stat.h>/#include <sys\/stat.h>/g' "$$file" > $(TMP_MAIN); \
		mv $(TMP_MAIN) "$$file"; \
	done
	@echo


# ----------------------------------------------------------------------------
# Regel fuer das Vorbereiten der Tests
compile-setup: 

    # Testprogramm im build-Verzeichnis erzeugen...
	@gcc $(TESTS_DIR)/$(TEST).c $(SRC_GLOBAL_DIR)/$(LOGGING).c \
	             -o $(BUILD_DIR)/$(TEST).o \
	             -I$(SRC_GLOBAL_DIR) -DTESTBENCH;

    # wait_and_exit im build-Verzeichnis erzeugen
	@gcc $(SRC_GLOBAL_DIR)/$(CTRL).c -o $(BUILD_DIR)/$(CTRL).o \
	                                 -DFUNCTION_TEST;
                                     
# ----------------------------------------------------------------------------
# Regel zum Testen des aktuellen Programms
test: start \
      test1 test2 test3 test4 test5 test6 test7 test8 test9 test10 \
      end

start:
	@echo -e "\f"; 
	@echo "+--------------------------------------------------------------+" ;
	@echo "| TEST $(LABEL)" ;
	@echo "+--------------------------------------------------------------+" ;
	@echo ;
    # Testdateien ins build-Verzeichnis kopieren
	-@cp $(TESTFILES_DIR)/* $(BUILD_DIR)/ 2> /dev/null ;

# Regeln fuer die einzelnen Testfaelle
test1:
	@echo 
	@echo ================================================================;
	@echo Testfall 1: Einfacher Test mit laengerem Text ;
	@echo 

	-@cd $(BUILD_DIR) \
	    && ( \
            ( \
                echo  - Aufruf : ./huffman -c -o 01_in.txt.hc 01_in.txt ; \
                ./$(USER_SUBMISSION).o -c -o 01_in.txt.hc 01_in.txt ; \
	            echo  - Aufruf : ./huffman -d -o 01_out.txt 01_in.txt.hc ; \
	            ./$(USER_SUBMISSION).o -d -o 01_out.txt 01_in.txt.hc ; \
	            echo ;\
	            ./$(TEST).o 01_in.txt \
	                        01_in.txt.hc \
	                        01_out.txt \
            ) \
            & ./$(CTRL).o -builddir . \
	                      -app $(USER_SUBMISSION).o \
	                      -timeout $(TIMEOUT) \
        )

test2:
	@echo
	@echo ================================================================;
	@echo Testfall 2: Kurzer Test ;
	@echo

	-@cd $(BUILD_DIR) \
	    && ( \
            ( \
                echo  - Aufruf : ./huffman -c -o 02_ab.txt.hc 02_ab.txt ; \
                ./$(USER_SUBMISSION).o -c -o 02_ab.txt.hc 02_ab.txt ; \
	            echo  - Aufruf : ./huffman -d -o 02_ab.txt.hc.hd 02_ab.txt.hc ; \
	            ./$(USER_SUBMISSION).o -d -o 02_ab.txt.hc.hd 02_ab.txt.hc ; \
	            echo ;\
	            ./$(TEST).o 02_ab.txt \
	                        02_ab.txt.hc \
	                        02_ab.txt.hc.hd \
            ) \
            & ./$(CTRL).o -builddir . \
	                      -app $(USER_SUBMISSION).o \
	                      -timeout $(TIMEOUT) \
        )

test3:
	@echo
	@echo ================================================================;
	@echo Testfall 3: Test mit leerer Datei ;
	@echo

	-@cd $(BUILD_DIR) \
	    && ( \
            ( \
                echo  - Aufruf : ./huffman -c -o 03_leerecompress.txt 03_leere.txt ; \
                ./$(USER_SUBMISSION).o -c -o 03_leerecompress.txt 03_leere.txt ; \
	            echo  - Aufruf : ./huffman -d -o 03_auchleer.txt 03_leerecompress.txt ; \
	            ./$(USER_SUBMISSION).o -d -o 03_auchleer.txt 03_leerecompress.txt ; \
	            echo ;\
	            ./$(TEST).o 03_leere.txt \
	                        03_leerecompress.txt \
	                        03_auchleer.txt \
            ) \
            & ./$(CTRL).o -builddir . \
	                      -app $(USER_SUBMISSION).o \
	                      -timeout $(TIMEOUT) \
        )

test4:
	@echo
	@echo ================================================================;
	@echo Testfall 4: Test mit Datei mit 1 Byte ;
	@echo

	-@cd $(BUILD_DIR) \
	    && ( \
            ( \
                echo  - Aufruf : ./huffman -c -o 04_1Byte.txt.hc 04_1Byte.txt ; \
                ./$(USER_SUBMISSION).o -c -o 04_1Byte.txt.hc 04_1Byte.txt ; \
	            echo  - Aufruf : ./huffman -d -o 04_1Byte.txt.hc.hd 04_1Byte.txt.hc ; \
	            ./$(USER_SUBMISSION).o -d -o 04_1Byte.txt.hc.hd 04_1Byte.txt.hc ; \
	            echo ;\
	            ./$(TEST).o 04_1Byte.txt \
	                        04_1Byte.txt.hc \
	                        04_1Byte.txt.hc.hd \
            ) \
            & ./$(CTRL).o -builddir . \
	                      -app $(USER_SUBMISSION).o \
	                      -timeout $(TIMEOUT) \
        )

test5:
	@echo
	@echo ================================================================;
	@echo Testfall 5: Test mit allen 256 ASCII Zeichen ;
	@echo

	-@cd $(BUILD_DIR) \
	    && ( \
            ( \
                echo  - Aufruf : ./huffman -c -o 05_0-255.txt.hc 05_0-255.txt ; \
                ./$(USER_SUBMISSION).o -c -o 05_0-255.txt.hc 05_0-255.txt ; \
	            echo  - Aufruf : ./huffman -d -o 05_0-255.txt.hc.hd 05_0-255.txt.hc ; \
	            ./$(USER_SUBMISSION).o -d -o 05_0-255.txt.hc.hd 05_0-255.txt.hc ; \
	            echo ;\
	            ./$(TEST).o 05_0-255.txt \
	                        05_0-255.txt.hc \
	                        05_0-255.txt.hc.hd \
            ) \
            & ./$(CTRL).o -builddir . \
	                      -app $(USER_SUBMISSION).o \
	                      -timeout $(TIMEOUT) \
        )

test6:
	@echo
	@echo ================================================================;
	@echo Testfall 6: Kurzer Test mit 8 Nutzbits im letzten Byte ;
	@echo

	-@cd $(BUILD_DIR) \
	    && ( \
            ( \
                echo  - Aufruf : ./huffman -c -o 06_8NutzbitsComp.txt 06_8Nutzbits.txt ; \
                ./$(USER_SUBMISSION).o -c -o 06_8NutzbitsComp.txt 06_8Nutzbits.txt ; \
	            echo  - Aufruf : ./huffman -d -o 06_8NutzbitsDecomp.txt 06_8NutzbitsComp.txt ; \
	            ./$(USER_SUBMISSION).o -d -o 06_8NutzbitsDecomp.txt 06_8NutzbitsComp.txt ; \
	            echo ;\
	            ./$(TEST).o 06_8Nutzbits.txt \
	                        06_8NutzbitsComp.txt \
	                        06_8NutzbitsDecomp.txt \
            ) \
            & ./$(CTRL).o -builddir . \
	                      -app $(USER_SUBMISSION).o \
	                      -timeout $(TIMEOUT) \
        )

test7:
	@echo
	@echo ================================================================;
	@echo Testfall 7: Langer Text mit 8 Nutzbits im letzten Byte ;
	@echo

	-@cd $(BUILD_DIR) \
	    && ( \
            ( \
                echo  - Aufruf : ./huffman -c -o 07_in8Bits.txt.hc 07_in8Bits.txt ; \
                ./$(USER_SUBMISSION).o -c -o 07_in8Bits.txt.hc 07_in8Bits.txt ; \
	            echo  - Aufruf : ./huffman -d -o 07_in8Bits.txt.hc.hd 07_in8Bits.txt.hc ; \
	            ./$(USER_SUBMISSION).o -d -o 07_in8Bits.txt.hc.hd 07_in8Bits.txt.hc ; \
	            echo ;\
	            ./$(TEST).o 07_in8Bits.txt \
	                        07_in8Bits.txt.hc \
	                        07_in8Bits.txt.hc.hd \
            ) \
            & ./$(CTRL).o -builddir . \
	                      -app $(USER_SUBMISSION).o \
	                      -timeout $(TIMEOUT) \
        )

test8:
	@echo
	@echo ================================================================;
	@echo Testfall 8: Test mit grosser Binaer-Datei \(1.4MB\) ;
	@echo

	-@cd $(BUILD_DIR) \
	    && ( \
            ( \
                echo  - Aufruf : ./huffman -c -o 08_splint.bin.hc 08_splint.bin ; \
                ./$(USER_SUBMISSION).o -c -o 08_splint.bin.hc 08_splint.bin ; \
	            echo  - Aufruf : ./huffman -d -o 08_splint.bin.hc.hd 08_splint.bin.hc ; \
	            ./$(USER_SUBMISSION).o -d -o 08_splint.bin.hc.hd 08_splint.bin.hc ; \
	            echo ;\
	            ./$(TEST).o 08_splint.bin \
	                        08_splint.bin.hc \
	                        08_splint.bin.hc.hd \
            ) \
            & ./$(CTRL).o -builddir . \
	                      -app $(USER_SUBMISSION).o \
	                      -timeout $(TIMEOUT) \
        )

test9:
	@echo
	@echo ================================================================;
	@echo Testfall 9: The Lord Of The Rings \(ca 2.6MB\) ;
	@echo

	-@cd $(BUILD_DIR) \
	    && ( \
            ( \
                echo  - Aufruf : ./huffman -c -v -o 09_LordOfTheRings.txt.hc 09_LordOfTheRings.txt ; \
                ./$(USER_SUBMISSION).o -c -v -o 09_LordOfTheRings.txt.hc 09_LordOfTheRings.txt ; \
	            echo  - Aufruf : ./huffman -d -v -o 09_LordOfTheRings.txt.hc.hd 09_LordOfTheRings.txt.hc ; \
	            ./$(USER_SUBMISSION).o -d -v -o 09_LordOfTheRings.txt.hc.hd 09_LordOfTheRings.txt.hc ; \
	            echo ;\
	            ./$(TEST).o 09_LordOfTheRings.txt \
	                        09_LordOfTheRings.txt.hc \
	                        09_LordOfTheRings.txt.hc.hd \
            ) \
            & ./$(CTRL).o -builddir . \
	                      -app $(USER_SUBMISSION).o \
	                      -timeout $(TIMEOUT) \
        )

test10:
	@echo
	@echo ================================================================;
	@echo Testfall 10: Test ohne Angabe der Ausgabedatei ;
	@echo

	-@cd $(BUILD_DIR) \
	    && ( \
            ( \
                echo  - Aufruf : ./huffman -c 10_in.txt ; \
                ./$(USER_SUBMISSION).o -c 10_in.txt ; \
	            echo  - Aufruf : ./huffman -d 10_in.txt.hc ; \
	            ./$(USER_SUBMISSION).o -d 10_in.txt.hc ; \
	            echo ;\
	            ./$(TEST).o 10_in.txt \
	                        10_in.txt.hc \
	                        10_in.txt.hc.hd \
            ) \
            & ./$(CTRL).o -builddir . \
	                      -app $(USER_SUBMISSION).o \
	                      -timeout $(TIMEOUT) \
        )

end:
    # Endbewertung durchfuehren (OK-Anzahl in %) 
	-@cd $(BUILD_DIR) \
	&& ./$(TEST).o -summary 10 $(STATS_DIR)/$(LEISTUNGEN)_$(TEST_DIR).csv
