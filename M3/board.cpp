#include "board.h"

using std::vector;

const vector<vector<Cell>> Board::BOARD_1 =
{
    { BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, BLOCKED, EMPTY, BLOCKED, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED }
};

const vector<vector<Cell>> Board::BOARD_2 =
{
    { BLOCKED, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY }
};

Board::Board()
{
    //Initialises an empty board
    this->board = new std::vector<std::vector<Cell>>(DEFAULT_BOARD_DIMENSION, std::vector<Cell>(DEFAULT_BOARD_DIMENSION, EMPTY));
}

Board::~Board()
{
    delete this->board;
}

void Board::load(int boardId)
{
    const std::vector<std::vector<Cell>>* chosenTemplate;

    if (boardId == 0 || boardId == 1) {
        chosenTemplate = &BOARD_1;
    } else {
        chosenTemplate = &BOARD_2;
    }

    for (int i = 0; i < DEFAULT_BOARD_DIMENSION; i++) {
        for (int j = 0; j < DEFAULT_BOARD_DIMENSION; j++) {
            (*board)[i][j] = (*chosenTemplate)[i][j];
        }
    }
}

/*
 * also handles range checking of position
*/
bool Board::placePlayer(Position position)
{
    bool success = false;
    if (position.x >= 0 && position.x < DEFAULT_BOARD_DIMENSION 
        && position.y >= 0 && position.y < DEFAULT_BOARD_DIMENSION) {
        if ((*board)[position.y][position.x] == EMPTY) {
            (*board)[position.y][position.x] = PLAYER;
            success = true;
        }
    }

    return success;
}

PlayerMove Board::movePlayerForward(Player* player)
{
    PlayerMove moveStatus = PLAYER_MOVED;
    Position nextPos = player->getNextForwardPosition();
    
    if (nextPos.x > DEFAULT_BOARD_DIMENSION - 1 || nextPos.y > DEFAULT_BOARD_DIMENSION - 1
    || nextPos.x < 0 || nextPos.y < 0) {
        moveStatus = OUTSIDE_BOUNDS;
    } else if ((*board)[nextPos.y][nextPos.x] == BLOCKED) {
        moveStatus = CELL_BLOCKED;
    } else {
        (*board)[player->position.y][player->position.x] = EMPTY;
        player->updatePosition(nextPos);
        (*board)[player->position.y][player->position.x] = PLAYER;
    }

    return moveStatus;
}

void Board::display(Player* player)
{
    std::cout << std::endl;
    
    //output column headings
    for (int i = 0; i < DEFAULT_BOARD_DIMENSION + 1; i++) {
        std::cout << LINE_OUTPUT;
        if (i > 0) {
            std::cout << i - 1;
        } else {
            std::cout << " ";
        }
    }
    std::cout << LINE_OUTPUT <<std::endl;

    //print out rows
    for (int i = 0; i < DEFAULT_BOARD_DIMENSION; i++) { 
        for (int j = -1; j < DEFAULT_BOARD_DIMENSION; j++) { 
            std::cout << LINE_OUTPUT;
            if (j == -1) {
                // output the row numbers first
                std::cout << i;
            } else {
                // print out contents of board
                Cell currentCell = (*this->board)[i][j];

                if (currentCell == EMPTY) { 
                    std::cout << EMPTY_OUTPUT;
                } else if (currentCell == BLOCKED) {
                    std::cout << BLOCKED_OUTPUT;
                } else {
                    // display player
                    player->displayDirection();
                }
            }
        }
        std::cout << LINE_OUTPUT << std::endl;
    }
    std::cout << std::endl;
}



