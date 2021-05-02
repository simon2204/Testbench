/**
 * @mainpage
 * In diesem Projekt wird das Spiel Game of Life realisiert.
 * 
 * @file
 * In diesem Modul wird das Spiel Game of Life realisiert. Der Aufruf
 * erfolgt über die Funktion game_of_life. Vorher muss die erste Generation 
 * bereits gesetzt sein, bspw. mit der Funktion set_first_generation.
 * 
 * Game Of Life ist ein Spiel, das zeigt, wie "Lebewesen" nach bestimmten 
 * Regeln in nachfolgenden Generationen überleben, sterben oder neu 
 * entstehen. Entscheidend hierzu ist die Anzahl der Nachbarn. Hat ein 
 * Lebewesen zu viele Nachbarn, stirbt es wegen Überbevölkerung. Bei zu 
 * wenigen Nachbarn stirbt es aus Einsamkeit. Ein "gesunder Mittelwert" 
 * ist also der Weg für ein erfolgreiches Überleben der Gesellschaft und 
 * des Individuums. 
 *      
 * Game Of Life basiert auf einem rechteckigen Spielfeld, das in einzelne 
 * Felder aufgeteilt ist (ähnlich einem Schachbrett). Jedes dieser Felder 
 * kann leer oder mit genau einem Lebewesen belegt sein. Auf jedem Feld 
 * des Spielfelds kann sich maximal 1 Lebewesen befinden. Ob ein Feld 
 * in der nächsten Generation mit einem Lebewesen belegt ist oder nicht, 
 * ist von der Anzahl der belegten Nachbarfelder abhängig. 
 * + Ist ein Feld unbelegt
 *      - entsteht in der nachfolgenden Generation auf diesem Feld nur dann
 *        ein neues Lebewesen, wenn es genau 3 belegte Nachbarfelder hat. 
 * + Ist ein Feld bereits mit einem Lebewesen belegt, dann wird dieses 
 *      - überleben, wenn es 2 oder 3 Nachbarn hat, oder
 *      - sterben, wenn es weniger als 2 oder mehr als 3 Nachbarn hat.
 * 
 * Beispiel: Die Lebewesen sind durch o gekennzeichnet.
 * 
 * <TABLE>
 * <TR>
 * <TD>
 * <CENTER> Ausgangsgeneration
 * <CODE>
 * <br/>    +-+-+-+-+-+-+
 * <br/>    |o|o|o|-|-|-|
 * <br/>    +-+-+-+-+-+-+
 * <br/>    |-|-|o|-|-|-|
 * <br/>    +-+-+-+-+-+-+
 * <br/>    |-|o|-|o|o|o|
 * <br/>    +-+-+-+-+-+-+
 * <br/>    |-|-|-|o|-|-|
 * <br/>    +-+-+-+-+-+-+
 * <br/>    |-|-|-|-|o|-|
 * <br/>    +-+-+-+-+-+-+
 * </CODE>
 * </CENTER>
 * </TD>
 * <TD>
 * <CENTER> Folgegeneration
 * <CODE>
 * <br/>    +-+-+-+-+-+-+
 * <br/>    |-|o|o|-|-|-|
 * <br/>    +-+-+-+-+-+-+
 * <br/>    |o|-|-|-|o|-|
 * <br/>    +-+-+-+-+-+-+
 * <br/>    |-|-|-|o|o|-|
 * <br/>    +-+-+-+-+-+-+
 * <br/>    |-|-|o|o|-|o|
 * <br/>    +-+-+-+-+-+-+
 * <br/>    |-|-|-|-|-|-|
 * <br/>    +-+-+-+-+-+-+
 * </CODE>
 * </CENTER>
 * </TD>
 * </TR>
 * </TABLE>
 */


/* ============================================================================
 * Header-Dateien einbinden
 * ========================================================================= */

#include <string.h>
#include <stdio.h>
#include <stdbool.h>



/* ============================================================================
 * Symbolische Konstanten
 * ========================================================================= */

/**
 * Die Zeilenzahl des Spielfelds. 
 */
#define ALL_ROWS 10

/**
 * Die Spaltenzahl des Spielfelds. 
 */
#define ALL_COLS 10

/**
 * Anzahl der Bits in einem Byte 
 */
#define BITS_PER_BYTE 8

/** 
 * Anzahl der Bytes, die für die Speicherung der Generationen notwendig sind 
 */
#define ALL_BYTES (((ALL_ROWS * ALL_COLS) + 7) / BITS_PER_BYTE)


/* ============================================================================
 * Typdefinitionen
 * ========================================================================= */

/**
 * Mögliche Zustände für die Lebewesen einer Generation 
 */
typedef enum {
    /** Signalisiert, dass sich kein Lebewesen in der Zelle befindet. */
    DEAD,
    /** Signalisiert, dass sich ein Lebewesen in der Zelle befindet. */
    ALIVE
} STATE;


/* ============================================================================
 * Globale Variablen
 * ========================================================================= */

/**
 * Die aktuelle Generation wird über einen Zeichen-Vektor dargestellt. Jedes
 * Bit des Zeichenvektors stellt eine Zelle dar. Ein Spielfeld mit 5 Zeilen und
 * 6 Spalten hat den folgenden Aufabu ('|' steht für eine Bytegrenze):
 *
 *     1 2 3 4 5 6
 * 1.  - - - - - -
 * 2.  - -|- - - -
 * 3.  - - - -|- -
 * 4.  - - - - - -|
 * 5.  - - - - - -
 *     - -|
 *
 * Für ein Spielfeld der Größe 5x6 werden 4 Bytes benötigt. Die Zelle (1,5) 
 * wird mit dem 5. Bit dargestellt, d.h. im ersten Byte an der 5. Position. 
 * Die Zelle (3,6) wird mit dem 18. Bit dargestellt, d.h. im dritten Byte an 
 * der zweiten Position. Die beiden letzten Bits im 4. Byte sind frei, d.h., 
 * sie werden für das Spielfeld nicht benötigt.
 */
unsigned char generation[ALL_BYTES]; 

/**
 * Die nächste Generation wird genauso abgelegt wie die aktuelle Generation
 */
unsigned char next_generation[ALL_BYTES]; 


/* ============================================================================
 * Funktionsprototypen
 * ========================================================================= */

/**
 * Aufruf des Spiels - berechnet die Generationen ausgehend von der 
 * Anfangsgeneration bis zu einer maximalen Anzahl oder bis sich die 
 * Generationen nicht mehr ändern.
 * 
 * Die erste Generation muss vor Aufruf in der globalen Variablen #generation, 
 * bspw. mit set_first_generation, gesetzt worden sein. 
 *
 * @param max_generations   maximale Anzahl an Generationen, die berechnet 
 *                          werden sollen.
 */
void game_of_life(int max_generations);

/**
 * Initialisiert die aktuelle Generation mit einer Anfangsgeneration. Die
 * übergebene Zeichenkette enthält nacheinander die Zeilen der Generation. Eine
 * '1' bedeutet, dass die Zelle ein Lebewesen enthält, eine '0', dass die
 * Zelle kein Lebewesen enthält.
 * 
 * Es wird davon ausgegangen, dass der Vektor string #ALL_ROWS * #ALL_COLS + 
 * 1 Elemente hat.
 *
 * @param string    Zeichenkette mit der Generation.
 */
void set_generation_from_string(char string[]);

/**
 * Liefert die aktuelle Generation als String, in dem die Zellen zeilenweise
 * hintereinander abgelegt sind. Für eine Zelle mit einem Lebewesen enthält die
 * Zeichenkette eine '1', für eine Zelle ohne Lebewesen enthält sie eine '0'.
 * 
 * Es wird davon ausgegangen, dass der Vektor string #ALL_ROWS * #ALL_COLS + 
 * 1 Elemente hat.
 *
 * @param string    Zeichenkette, in der die Generation abgelegt wird.
 */
void get_generation_as_string(char string[]);

/**
 * Überführt die aktuelle Generation in die Folgegeneration gemäß der Regeln 
 * des Spiels "Game of Life" (siehe Modulkommentar)
 *
 * @return      true, wenn sich die Generation ändert. false, sonst.
 */
bool set_next_generation(void);

/**
 * Gibt den Inhalt der aktuellen Generation auf dem Bildschirm aus.
 */
void print_generation(void);

/**
 * Liefert den aktuellen Status (#ALIVE, #DEAD) der Zelle (row, column) in der
 * aktuellen Generation. Für Zellen außerhalb des Spielfelds wird der
 * Zustand DEAD geliefert.
 * 
 * @param row       Zeile der zu prüfenden Zelle
 * @param column    Spalte der zu prüfenden Zelle
 * @return          Status der zu prüfenden Zelle
 */
STATE get_state(int row, int column);

/**
 * Setzt die Zelle (row, column) in der nächsten Generation auf den
 * übergebenen Status (#ALIVE, #DEAD).
 *
 * Es wird davon ausgegangen, dass row, column  positive ganze Zahlen sind, die
 * die Spielfeldgröße (#ALL_ROWS, #ALL_COLS) nicht über- und unterschreiten.
 * 
 * @param row       Zeile der zu ändernden Zelle
 * @param column    Spalte der zu ändernden Zelle
 * @param state     Zustand, auf den die Zelle gesetzt werden soll.
 */
void set_next_state(int row, int column, STATE state);

/**
 * Liefert die Anzahl der lebenden Nachbarn der Zelle (row, column) in der
 * übergebenen Generation.
 * 
 * Es wird davon ausgegangen, dass row, column  positive ganze Zahlen sind, die 
 * die Spielfeldgröße (#ALL_ROWS, #ALL_COLS) nicht über- und unterschreiten.
 * 
 * @param row       Zeile des Spielfelds
 * @param column    Spalte des Spielfelds
 * @return          Anzahl der lebenden Nachbarn der Zelle (row, column)
 */
int count_living_neighbours(int row, int column);

/**
 * Gibt eine horizontale Rahmenlinie des Spielfelds am Bildschirm aus.
 */
void print_frameline(void);


/* ============================================================================
 * Funktionsdefinitionen
 * ========================================================================= */

/* ----------------------------------------------------------------------------
 * Funktion: game_of_life
 * ------------------------------------------------------------------------- */
void game_of_life(int max_generations)
{
    int generation = 0;   /* Nummer der aktuellen Generation */
    bool has_changed;     /* Zeigt an, ob sich zwei aufeinanderfolgende 
                           * Generationen unterscheiden */
    
    /* Ende, wenn Parameter max_generations kleiner oder gleich 0 ist */
    if (max_generations <= 0)
    {
        return;
    }
    
    do
    {
        /* Ausgabe der aktuellen Generation und Berechnen der jeweils nächsten 
         * Generation bis keine Änderung mehr eintritt oder maximale Anzahl 
         * erreicht ist. */        
        {
            /* Schleife, um die Ausgabe zu verlangsamen */
            int i;
            for (i = 0; i < 50000000; i++);
            
            /* Bildschirm säubern */
            printf("\e[1;1H\e[2J");
            fflush(stdout);
        }    
        
        generation++;
        printf("\nGeneration: %d\n", generation);
        print_generation();
        
        has_changed = set_next_generation();
        
    } while (generation < max_generations && has_changed);
}

/* ----------------------------------------------------------------------------
 * Funktion: set_generation_from_string
 * ------------------------------------------------------------------------- */
void set_generation_from_string(char string[])
{
    int index;      /* Laufvariable über den Zellen in der Liste cells */
    
    /* Initialisiere alle Bytes des Spielfelds mit 0
     * (entspricht DEAD für alle Zellen) */
    memset(next_generation, 0, ALL_BYTES);
    
    /* Setze die übergebenen Zellen auf ALIVE */
    for (index = 0; index < ALL_ROWS * ALL_COLS; index++)
    {
        set_next_state(index / ALL_COLS, index % ALL_COLS,
                       (string[index] == '1') ? ALIVE : DEAD);
    }

    memcpy(generation, next_generation, ALL_BYTES);
}

/* ----------------------------------------------------------------------------
 * Funktion: get_generation_as_string
 * ------------------------------------------------------------------------- */
void get_generation_as_string(char string[])
{
    int row;
    int column;
    int cell = 0;

    for (row = 0; row < ALL_ROWS; row++)
    {
        for (column = 0; column < ALL_COLS; column++)
        {
            string[cell] = (char) (get_state(row, column) + '0');
            cell = cell + 1;
        }
    }
    string[cell] = '\0';
}

/* ----------------------------------------------------------------------------
 * Funktion: set_next_generation
 * ------------------------------------------------------------------------- */
bool set_next_generation(void)
{
    int row;                /* aktuelle Zeile */
    int column;             /* aktuelle Spalte */
    int living_neighbours;  /* Anzahl lebender Nachbarn der aktuellen Zelle */
    STATE state_of_cell;    /* Status der aktuellen Zelle */
    bool has_changed;       /* Information, ob sich die nächste Generation zur
                             * aktuellen geändert hat.*/
    
    has_changed = false;
    
    /* Iteriere über alle Zellen des Spielfelds */
    for (row = 0; row < ALL_ROWS; row++)
    {
        for (column = 0; column < ALL_COLS; column++)
        {
            /* Berechne Anzahl der lebenden Nachbarn und Status der Zelle */
            living_neighbours = count_living_neighbours(row, column);
            state_of_cell = get_state(row, column);
            
            /* Berechne Zustand der Zelle in der nächsten Generation */
            if (state_of_cell == DEAD)
            {
                /* Ein Lebewesen entsteht bei genau drei lebenden Nachbarn */
                if (living_neighbours == 3)
                {
                    set_next_state(row, column, ALIVE);
                    has_changed = true;
                }
                else
                {
                    set_next_state(row, column, DEAD);
                }
            }
            else
            {
                /* Lebewesen überlebt bei zwei oder drei lebenden Nachbarn */
                if (living_neighbours == 2 || living_neighbours == 3)
                {
                    set_next_state(row, column, ALIVE);
                }
                else
                {
                    set_next_state(row, column, DEAD);
                    has_changed = true;
                }
            }
        }
    }
    
    /* Kopiert die nächste Generation auf die aktuelle Generation. */
    memcpy(generation, next_generation, ALL_BYTES);
    
    return has_changed;
}

/* ----------------------------------------------------------------------------
 * Funktion: get_state
 * ------------------------------------------------------------------------- */
STATE get_state(int row, int column)
{
    /* Position des Bits, das in einer Generation die Zelle (row, column)
     * repräsentiert. */
    unsigned int position_of_bit;
    
    /* Position des Bytes, in dem sich das aktuelle Bit (position_of_bit)
     * befindet. (das höchstwertige Bit ist 0, das niederwertigste 7) */
    unsigned int position_of_byte;
    
    /* Position des aktuellen Bits (position_of_bit) im aktuellen Byte
     * (position_of_byte) */
    unsigned int position_of_bit_in_byte;
    
    /* Bitmaske mit genau einer 1 an der Position des aktuellen Bits im
     * aktuellen Byte (position_of_bit_in_byte) */
    unsigned char alive_bitmask;
    
    /* Für Zellen außerhalb des Spielfelds wird der Zustand DEAD geliefert */
    if (row < 0 || column < 0 || row >= ALL_ROWS || column >= ALL_COLS)
    {
        return DEAD;
    }
    /* Berechne das Byte und das Bit, über die die Zelle repräsentiert wird. */
    position_of_bit = (unsigned int) row * ALL_COLS + column;
    position_of_byte = position_of_bit / BITS_PER_BYTE;
    position_of_bit_in_byte = position_of_bit % BITS_PER_BYTE;
    
    /* Erstelle Bitmaske, um den Zustand der Zelle abzufragen. */
    alive_bitmask = (unsigned char) 0x80 >> position_of_bit_in_byte;
    
    return ((generation[position_of_byte] & alive_bitmask) == alive_bitmask)
            ? ALIVE 
            : DEAD;
}

/* ----------------------------------------------------------------------------
 * Funktion: set_next_state
 * ------------------------------------------------------------------------- */
void set_next_state(int row, int column, STATE state)
{
    /* Position des Bits, das in einer Generation die Zelle (row, column)
     * repräsentiert. */
    unsigned int position_of_bit;
    
    /* Position des Bytes, in dem sich das aktuelle Bit (posiionOfBit)
     * befindet. */
    unsigned int position_of_byte;
    
    /* Position des aktuellen Bits (positionOfBit) im aktuellen Byte
     * (positionOfByte) */
    unsigned int position_of_bit_in_byte;
    
    /* Bitmaske mit genau einer 1 an der Position des aktuellen Bits im
     * aktuellen Byte (positionOfBitInByte) */
    unsigned char alive_bitmask;
    
    /* Berechne das Byte und das Bits, über die die Zelle repräsentiert wird. */
    position_of_bit = (unsigned int) row * ALL_COLS + column;
    position_of_byte = position_of_bit / BITS_PER_BYTE;
    position_of_bit_in_byte = position_of_bit % BITS_PER_BYTE;
    
    /* Erstelle Bitmaske, um den Zustand der Zelle abzufragen. */
    alive_bitmask = (unsigned char) 0x80 >> position_of_bit_in_byte;
    if ( state == ALIVE )
    {
        next_generation[position_of_byte] |= alive_bitmask;
    }
    else
    {
        next_generation[position_of_byte] &= ~alive_bitmask;
    }
}

/* ----------------------------------------------------------------------------
 * Funktion: count_living_neighbours
 * ------------------------------------------------------------------------- */
int count_living_neighbours(int row, int column)
{
    /* Zählt die lebenden Nachbarn rund um die Zelle (row, column). Für
     * Nachbarn, die außerhalb des Spielfelds liegen (bei Zellen am Rand)
     * liefert die Funktion getState den Zustand DEAD.
     */
    
    int a_row;       /* aktuelle Zeile */
    int a_column;    /* aktuelle Spalte */
    
    int living_neighbours = 0;
    
    /* Iteriere über alle Nachbarzellen der aktuellen Zelle. */
    for (a_row = row - 1; a_row <= row + 1; a_row++)
    {
        for (a_column = column - 1; a_column <= column + 1; a_column++)
        {
            /* Die aktuelle Zelle wird nicht betrachtet. */
            if ((a_row != row || a_column != column)
                     && get_state(a_row, a_column) == ALIVE)
            {
                living_neighbours++;
            }
        }
    }
    
    return living_neighbours;
}

/* ----------------------------------------------------------------------------
 * Funktion: print_generation
 * ------------------------------------------------------------------------- */
void print_generation(void)
{
    int row;       /* aktuelle Zeile */
    int column;    /* aktuelle Spalte */
    STATE state;   /* Zustand der aktuellen Zelle (row, column) */

    print_frameline();
    
    /* Ausgaben des Spielfeldes und aller weiteren Begrenzungslinien */
    for (row = 0; row < ALL_ROWS; row++)
    {
        /* Ausgeben einer Zeile mit Lebewesen */
        printf("|");  /* linker Rand */
        for (column = 0; column < ALL_COLS; column++)
        {
            state = get_state(row, column);
            printf(" %c |", (state == ALIVE) ? 'o' : ' ');
        }        
        printf("\n");
        
        if (row < ALL_ROWS)
        {
            print_frameline();
        }
        else
        {
            print_frameline();
        }
    }
    printf("\n");
}

/* ----------------------------------------------------------------------------
 * Funktion: print_frameline
 * ------------------------------------------------------------------------- */
void print_frameline(void)
{
    int column;
    
    printf("+");
    for (column = 0; column < ALL_COLS; column++)
    {
        printf("---+");
    }
    printf("\n");
}


/* ============================================================================
 * Testfunktionen
 * ========================================================================= */

/**
 * testet das Game of Life
 *
 * @return immer EXIT_SUCCESS
 */
int main(void)
{
    printf("Teste Game of Life...\n");

    set_generation_from_string("0100000000"
                               "0010000000"
                               "1110000000"
                               "0000000000"
                               "0000000000"
                               "0000000000"
                               "0000000000"
                               "0000000000"
                               "0000000000"
                               "0000000000");
    game_of_life(32);

    set_generation_from_string("0001100000"
                               "0010010000"
                               "0100001000"
                               "1000000100"
                               "1000000100"
                               "0100001000"
                               "0010010000"
                               "0001100000"
                               "0000000000"
                               "0000000000");
    game_of_life(106);

    return 0;
}
