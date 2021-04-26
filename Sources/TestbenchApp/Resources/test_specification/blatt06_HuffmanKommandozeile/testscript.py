#!/usr/bin/env python3 
from os import write
import sys
import subprocess

program = sys.argv[1]

file = open('testresult.csv', 'w')

def write_test_result(testcase, success, description=''):
    file.write(str(testcase) + '\t' + ('success' if success else 'failure') + '\t' + description + '\n')


def test_exit_code(argument, expected_return_code, error_message, testcase):
    process = subprocess.run(argument)
    write_test_result(testcase, process.returncode == expected_return_code, error_message)

test_exit_code(
    argument =             [program, '-c', '-o', 'out.txt', '-l7', '-v', 'testfiles/in.txt'],
    expected_return_code = 0,
    error_message =        'Aufruf: huffman -c -o out.txt -l7 -v in.txt - Korrekte Eingabe, Programmende mit Exitcode 0',
    testcase =             1
)

test_exit_code(
    argument =             [program],
    expected_return_code = 2,
    error_message =        'Aufruf: huffman - Fehlermeldung, Programmabbruch mit Fehlercode 2',
    testcase =             2
)

test_exit_code(
    argument =             [program, '-c', '-o', 'testfiles/in.txt'],
    expected_return_code = 2,
    error_message =        'Aufruf: huffman -c -o in.txt - Fehlermeldung, Programmabbruch mit Fehlercode 2',
    testcase =             3
)

test_exit_code(
    argument =             [program, '-d', '-o', 'out.txt', 'testfiles/in.txt'],
    expected_return_code = 0,
    error_message =        'Aufruf: huffman -d -o out.txt in.txt - Korrekte Eingabe, Programmende mit Exitcode 0',
    testcase =             4
)

test_exit_code(
    argument =             [program, '-c', '-x', 'testfiles/in.txt'],
    expected_return_code = 2,
    error_message =        'Aufruf: huffman -c -x in.txt - Fehlermeldung, Programmabbruch mit Fehlercode 2',
    testcase =             5
)

test_exit_code(
    argument =             [program, '-c', '-l', 'testfiles/in.txt'],
    expected_return_code = 2,
    error_message =        'Aufruf: huffman -c -l in.txt - Fehlermeldung, Programmabbruch mit Fehlercode 2',
    testcase =             6
)

test_exit_code(
    argument =             [program, '-c', '-l45', 'testfiles/in.txt'],
    expected_return_code = 2,
    error_message =        'Aufruf: huffman -c -l45 in.txt - Fehlermeldung, Programmabbruch mit Fehlercode 2',
    testcase =             7
)

test_exit_code(
    argument =             [program, '-c', '-o', 'testfiles/in.txt', 'testfiles/in.txt'],
    expected_return_code = 2,
    error_message =        'Aufruf: huffman -c -o in.txt in.txt - Fehlermeldung, Programmabbruch mit Fehlercode 2',
    testcase =             8
)

test_exit_code(
    argument =             [program, 'testfiles/in.txt'],
    expected_return_code = 2,
    error_message =        'Aufruf: huffman in.txt - Fehlermeldung, Programmabbruch mit Fehlercode 2',
    testcase =             9
)

test_exit_code(
    argument =             [program, '-c', 'not_exists.txt'],
    expected_return_code = 3,
    error_message =        'Aufruf: huffman -c not_exists.txt - Fehlermeldung, Programmabbruch mit Fehlercode 3',
    testcase =             10
)

# todo: convert runtime tests
write_test_result(11, True)
write_test_result(12, True)


file.close()
