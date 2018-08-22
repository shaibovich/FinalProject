//
// Created by Shai Leibovich on 22/08/2018.
//

#ifndef FINALPROJECT_UTILS_H
#define FINALPROJECT_UTILS_H

#endif //FINALPROJECT_UTILS_H
void printEnterCommand();

void printCellIsFixed();

void printStartGame();

void printInvalidCommand();

void printFilNotOpened(int isSolved);

void printErrorValidation();

void printValueOutOfRange();

void printSolutionErroneous();

void printPuzzleSolved();

void printBoardContainsError();

void printValidationPassed();

void printValidationFailed();

void printBoardNotEmpty();

void printGeneratorFailed();

void printNoMovesToUndo();

void printUndoValue(int x, int y, int oldValue, int newValue);

void printNoMovesToRedo();

void printredoValue(int x, int y, int oldValue, int newValue);

void printFileCannotBeCreated();

void printSaveTo(int x);

void printCellAlreadyContains();

void hintCell(int value);

void printNumberOfsolutions(int num);

void printGoodBoard();

void printBadPuzzle();

void printSetCell(int x, int y, int value);

void printBoardReset();

void printExit();