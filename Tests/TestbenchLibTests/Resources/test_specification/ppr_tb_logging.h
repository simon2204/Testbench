/* 
 * @file:   ppr_tb_logging.h
 * Author: Ulrike Griefahn
 *
 * Created on 30. Januar 2014, 15:43
 */

#ifndef PPR_TB_LOGGING_H
#define	PPR_TB_LOGGING_H

/**
 * Protokolliert in der Datei #ASSERT_FILENAME, dass ein weiterer Testfall 
 * erfolgreich durchgeführt wurde. Dazu wird die in der Datei stehende 
 * dreistellige Zahl um 1 erhöht.
 */
extern void ppr_tb_log_assert(void);

/**
 * Gibt das Gesamtergebnis des Testlaufs auf dem Bildschirm aus, d.h. die 
 * Anzahl aller Testfälle, die Anzahl der erfolgreichen Testfälle und den
 * prozentualen Anteil der erfolgreichen zur Gesamtanzahl der Testläufe.
 * 
 * @param directory    Gibt den Pfad zum Build Ordner an. Mit "/" am Ende.
 * @param exercise     Aufgabe, zu der der Testlauf gehört
 */
extern void ppr_tb_write_summary(char* directory, char *exercise);

/**
 * Setzt in der Datei praktikumsleistungen_blatt??.csv den prozentualen an 
 * erfolgreichen Testfällen zu allen Testfällen. 
 * 
 * @param rate         Erfolgsquote des Testlaufs
 * @param directory    Gibt den Pfad zum Build Ordner an. Mit "/" am Ende.
 * @param exercise     Aufgabe, zu der der Testlauf gehört
 */
extern void ppr_tb_log_total_result(int rate, char* directory, char *exercise);

/**
 * Erzeugt die ppr_tb_asserts.log Datei und schreibt die maximal
 * möglichen Testfälle in die Datei.
 *
 * @param total_assert Maximal mögliche Testfälle
 */
extern void ppr_tb_write_total_assert(int total_assert);

#endif

