/* ============================================================================
 * Includes
 * ========================================================================= */

#include "huffman_common.h"
#include "io.h"
#include "huffman.h"


/* ============================================================================
 * Funktions-Prototypen
 * ========================================================================= */

/**
 * Liest Zeichen und schreibt Bits. Ist das Zeichen < 95 wird ein 1-Bit 
 * geschrieben, ansonsten ein 0-Bit.
 */
static void do_rd_chars_wr_bits(void);

/**
 * Liest Bits und schreibt Zeichen. Ist das gelesene Bit ein 0-Bit, 
 * wird das Zeichen "0" geschrieben. Ist das gelesene Bit ein 1-Bit, 
 * wird das Zeichen "1" geschrieben.
 */
static void do_rd_bits_wr_chars(void);

/* ============================================================================
 * Funktions-Definitionen
 * ========================================================================= */

extern void test_rd_chars_wr_bits(char in[], char out[])
{
    init_in(in);
    init_out();

    do_rd_chars_wr_bits();

    get_out_buffer(out);
}

extern void test_rd_bits_wr_chars(char in[], char out[])
{
    init_in(in);
    init_out();

    do_rd_bits_wr_chars();

    get_out_buffer(out);
}

static void do_rd_chars_wr_bits(void)
{
    while (has_next_char())
    {
        if (read_char() < 'a')
        {
            write_bit(BIT1);
        }
        else
        {
            write_bit(BIT0);
        }
    }
}

static void do_rd_bits_wr_chars(void)
{
    while (has_next_bit())
    {
        if (read_bit() == BIT1)
        {
            write_char('1');
        }
        else
        {
            write_char('0');
        }
    }
}
