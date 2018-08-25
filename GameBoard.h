//
// Created by Shai Leibovich on 20/08/2018.
//

#ifndef FINALPROJECT_GAMEBOARD_H
#define FINALPROJECT_GAMEBOARD_H

#endif //FINALPROJECT_GAMEBOARD_H


typedef struct GameBoards GameBoard;
typedef struct GameCell Cell;

int checkBoardErrors(GameBoard *gameBoard);

void printGameBoard(GameBoard *gameBoard, int withStars);

GameBoard * createEmptyBoard(int rows, int columns);

int validateCellValue(GameBoard *gameBoard, int column, int row, int value);

int validateCellIndex(GameBoard *gameBoard, int column, int row);

int validateCellFixed(GameBoard *gameBoard, int column, int row);

int setCellValue(GameBoard *gameBoard, int column, int row, int value);

int setCellFixed(GameBoard *gameBoard, int column, int row, int isFixed);

int isCellFixed(GameBoard *gameBoard, int column, int row);

int getCellValue(GameBoard *gameBoard, int column, int row);

int getCellError(GameBoard *gameBoard, int column, int row);

int makrCellError(GameBoard *gameBoard, int column, int row);

int markCellUnError(GameBoard *gameBoard, int column, int row);

int setValueToCell(GameBoard *gameBoard, int column, int row, int value);

void deleteBoard(GameBoard *gameBoard);

void getNumberOfRowsString(char *string, GameBoard *gameBoard);

void getNumberOfBlocksString(char *string, GameBoard *gameBoard);

void getRowValuesString(char *string, GameBoard *gameBoard, int row);

int getNumberOfColumns(GameBoard * gameBoard);

int getNumberOfRows(GameBoard * gameBoard);

int getNumberOfBlockColumn(GameBoard * gameBoard);

int getNumberOfRowsBlock(GameBoard * gameBoard);