

#define ERROR -1

#ifndef GAME_BOARD_H
#define GAME_BOARD_H 1
typedef struct GameBoards GameBoard;

typedef struct GameCell Cell;
#include "LinkedList.h"
#endif

int getGameBoardSize(GameBoard *gameBoard);

int isBoardEmpty(GameBoard * gameBoard);

void clearRandom(GameBoard *gameBoard, int y, List * generateLst);

int fillRandom(GameBoard *gameBoard, int x, List * fillLst);

void makeBoardEmpty(GameBoard * gameBoard);

int checkBoardErrors(GameBoard *gameBoard);

void printGameBoard(GameBoard *gameBoard, int withStars);

GameBoard *createEmptyBoard(int rows, int columns);

GameBoard *copyGameBoard(GameBoard *oldGameBoard);

int validateCellValue(GameBoard *gameBoard, int value);

int validateCellIndex(GameBoard *gameBoard, int column, int row);

int validateCellFixed(GameBoard *gameBoard, int column, int row);

int setCellValue(GameBoard *gameBoard, int column, int row, int value);

int validateSet(const GameBoard * gameBoard, int row, int column, int value);

int setCellFixed(GameBoard *gameBoard, int column, int row, int isFixed);

int isCellFixed(GameBoard *gameBoard, int column, int row, int isSave);

int getCellValue(GameBoard *gameBoard, int column, int row);

int getCellError(GameBoard *gameBoard, int column, int row);

int markCellError(GameBoard *gameBoard, int column, int row);

int markCellUnError(GameBoard *gameBoard, int column, int row);

int markCellError(GameBoard *gameBoard, int column, int row);

int setValueToCell(GameBoard *gameBoard, int column, int row, int value);

void deleteBoard(GameBoard *gameBoard);

void getNumberOfRowsString(char *string, GameBoard *gameBoard);

void getNumberOfBlocksString(char *string, GameBoard *gameBoard);

void getRowValuesString(char *string, GameBoard *gameBoard, int row, int isSave);

int getNumberOfColumns(GameBoard *gameBoard);

int getNumberOfRows(GameBoard *gameBoard);

int getNumberOfBlockColumn(GameBoard *gameBoard);

int getNumberOfRowsBlock(GameBoard *gameBoard);

int isBoardFull(GameBoard *gameBoard);

void setAllFilledFixed(GameBoard *gameBoard);

Cell *getCell(GameBoard *gameBoard, int column, int row);
