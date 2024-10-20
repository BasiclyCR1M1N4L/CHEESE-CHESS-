#include "chess.h"

Square::Square() {
  piece = EMPTY;
  color = NONE;
}
void Square::setSpace(Square *space) {
  color = space->getColor();
  piece = space->getPiece();
}

void Square::setEmpty() {
  color = NONE;
  piece = EMPTY;
}

Piece Square::getPiece() { return piece; }

Color Square::getColor() { return color; }

void Square::setPieceAndColor(Piece p, Color c) {
  piece = p;
  color = c;
}
void Board::printBoard() {
  using namespace std;
  cout << "   y: 0  1  2  3  4  5  6  7 " << endl << "x:" << endl;
  for (int i = 0; i < 8; i++) {
    cout << " " << i << "   ";
    for (int j = 0; j < 8; j++) {
      Piece p = array[i][j].getPiece();
      Color c = array[i][j].getColor();

      switch (p) {
      case KING:
        (c == WHITE) ? cout << " K " : cout << " k ";
        break;
      case QUEEN:
        (c == WHITE) ? cout << " Q " : cout << " q ";
        break;
      case BISHOP:
        (c == WHITE) ? cout << " B " : cout << " b ";
        break;
      case KNIGHT:
        (c == WHITE) ? cout << " H " : cout << " h ";
        break;
      case ROOK:
        (c == WHITE) ? cout << " R " : cout << " r ";
        break;
      case PAWN:
        (c == WHITE) ? cout << " P " : cout << " p ";
        break;
      case EMPTY:
        cout << " "
             << "\21"
             << " ";
        break;
      default:
        cout << "XXX";
        break;
      }
    }
    cout << endl;
  }
}

bool Board::doMove() {
  using namespace std;
  string move;
  int x1, x2, y1, y2;
  bool stop = false;
  while (!stop) {
    (turn == WHITE) ? cout << "White's turn" : cout << "Black's turn";
    cout << "type your move as a single 4 character string "
         << endl; // come back to this later

    cin >> move;
    x1 = move[0] - 48;
    y1 = move[1] - 48;
    x2 = move[2] - 48;
    y2 = move[3] - 48;
    if (getSquare(x1, y1)->getColor() == turn) {
      if (makeMove(x1, y1, x2, y2) == false) {
        cout << "Invalid move, try again!" << endl;
      } else {
        stop = true;
      }
    } else {
      cout << "Thats not your piece silly goose" << endl;
    }
  }
  if (getSquare(x2, y2)->getPiece() == KING) {
    if (getSquare(x1, y1)->getColor() == WHITE) {
      cout << "WHITE WINS" << endl;
      return false;
    } else {
      cout << "BLACK WINS" << endl;
      return false;
    }
  }
  if (turn == BLACK) {
    turn = WHITE;
  } else {
    turn = BLACK;
  }
  return true;
}

void Board::setBoard() {
  array[0][0].setPieceAndColor(ROOK, WHITE);
  array[1][0].setPieceAndColor(KNIGHT, WHITE);
  array[2][0].setPieceAndColor(BISHOP, WHITE);
  array[3][0].setPieceAndColor(QUEEN, WHITE);
  array[4][0].setPieceAndColor(KING, WHITE);
  array[5][0].setPieceAndColor(BISHOP, WHITE);
  array[6][0].setPieceAndColor(KNIGHT, WHITE);
  array[7][0].setPieceAndColor(ROOK, WHITE);

  array[0][7].setPieceAndColor(ROOK, BLACK);
  array[1][7].setPieceAndColor(KNIGHT, BLACK);
  array[2][7].setPieceAndColor(BISHOP, BLACK);
  array[3][7].setPieceAndColor(QUEEN, BLACK);
  array[4][7].setPieceAndColor(KING, BLACK);
  array[5][7].setPieceAndColor(BISHOP, BLACK);
  array[6][7].setPieceAndColor(KNIGHT, BLACK);
  array[7][7].setPieceAndColor(ROOK, BLACK);

  for (int i = 0; i < 8; i++) {
    array[i][6].setPieceAndColor(PAWN, BLACK);
    array[i][1].setPieceAndColor(PAWN, WHITE);
  }
  for (int i = 2; i < 6; i++) {
    for (int j = 0; j < 8; j++) {
      array[j][i].setPieceAndColor(EMPTY, NONE);
    }
  }
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      array[i][j].setX(i);
      array[i][j].setY(j);
    }
  }
}
bool Board::playGame() {
  printBoard();
  return doMove();
}

bool Board::moveKing(Square *thisKing, Square *thatSpace) {
  if (abs(thatSpace->getX() - thisKing->getX()) == 1) {
    if (abs(thatSpace->getY() - thisKing->getY()) == 1) {
      thatSpace->setSpace(thisKing);
      thisKing->setEmpty();
      return true;
    } else
      return false;
  } else
    return false;
}

bool Board::moveQueen(Square *thisQueen, Square *thatSpace) {
  int queenX = thisQueen->getX();
  int queenY = thisQueen->getY();
  int thatX = thatSpace->getX();
  int thatY = thatSpace->getY();
  int yInc;
  int xInc;
  bool invalid = false;
  if (queenX != thatX || queenY != thatY) {
    if (queenX == thatX) {
      yInc = (thatY - queenY) / abs(thatY - queenY);
      for (int i = queenY + yInc; i != thatY; i += yInc) {
        if (array[thatX][i].getPiece() != EMPTY) {
          invalid = true;
        }
      }
    }
    // if the  QueenY != thatY
    else {
      if (queenY == thatY) {
        xInc = (thatX - queenX) / abs(thatX - queenX);
        for (int i = queenX + xInc; i != thatX; i += xInc) {
          if (array[i][thatY].getPiece() != EMPTY) {
            invalid = true;
          }
        }
      } else {
        if (abs(queenX - thatX) == abs(queenY - thatY)) {
          xInc = (thatX - queenX) / abs(thatX - queenX);
          yInc = (thatY - queenY) / abs(thatY - queenY);
          for (int i = 1; i < abs(queenX - thatX); i++) {
            if (array[queenX + i * xInc][queenY + i * yInc].getColor() !=
                NONE) {
              return false;
            }
          }
        } else {
          return false;
        }
      }
    }
  }
  if (invalid == false) {
    thatSpace->setSpace(thisQueen);
    thisQueen->setEmpty();
    return true;
  } else {
    return false;
  }
}
bool Board::moveRook(Square *thisRook, Square *thatSpace) {
  int rookX = thisRook->getX();
  int rookY = thisRook->getY();
  int thatX = thatSpace->getX();
  int thatY = thatSpace->getY();
  bool invalid = false;
  if (rookX != thatX || rookY != thatY) {
    if (rookX == thatX) {
      int y = (thatY - rookY) / (abs(thatY - rookY));
      for (int i = rookY + y; i != thatY; i += y) {
        if (array[i][thatY].getColor() != NONE) {
          return false;
        }
      }
    } else {
      if (rookY == thatY) {
        int xInc = (thatX - rookX) / (abs(thatX - rookX));
        for (int i = rookX + xInc; i != thatX; i += xInc) {
          if (array[thatX][i].getColor() != NONE) {
            return false;
          }
        }

      } else {
        return false;
      }
    }
  }
  if (invalid == false) {
    thatSpace->setSpace(thisRook);
    thisRook->setEmpty();
    return true;
  } else {
    std::cout << "that is an invalid move for rook" << std::endl;
    return false;
  }
}
bool Board::moveBishop(Square *thisBishop, Square *thatSpace) {
  int bishopX = thisBishop->getX();
  int bishopY = thisBishop->getY();
  int thatX = thatSpace->getX();
  int thatY = thatSpace->getY();
  bool invalid = false;
  // Square *s;
  if (abs(bishopX - thatX) == abs(bishopY - thatY)) {
    int xInc = (thatX - bishopX) / (abs(thatX - bishopX));
    int yInc = (thatY - bishopY) / (abs(thatY - bishopY));
    for (int i = 1; i < abs(bishopX - thatX); i++) {
      if (array[bishopX + xInc * i][bishopY + yInc * i].getColor() != NONE) {
        return false;
      }
    }
  } else {
    return false;
  }
  if (invalid == false) {
    thatSpace->setSpace(thisBishop);
    thisBishop->setEmpty();
    return true;
  } else {
    return false;
  }
}
bool Board::moveKnight(Square *thisKnight, Square *thatSpace) {
  int knightX = thisKnight->getX();
  int knightY = thisKnight->getY();
  int thatX = thatSpace->getX();
  int thatY = thatSpace->getY();
  if ((abs(knightX - thatX) == 2 && abs(knightY - thatY) == 1) ||
      (abs(knightX - thatX) == 1 && abs(knightY - thatY) == 2)) {
    thatSpace->setSpace(thisKnight);
    thisKnight->setEmpty();
    return true;
  } else {
    return false;
  }
}
bool Board::movePawn(Square *thisPawn, Square *thatSpace) {
  using namespace std;
  // bool invalid = false;
  int pawnX = thisPawn->getX();
  int pawnY = thisPawn->getY();
  int thatX = thatSpace->getX();
  int thatY = thatSpace->getY();
  if (thisPawn->getColor() == WHITE) {
    if (pawnX == thatX && thatY == pawnY + 1 && thatSpace->getColor() == NONE) {
      thatSpace->setSpace(thisPawn);
    } else {
      if ((pawnX + 1 == thatX || pawnX - 1 == thatX) && pawnY + 1 == thatY &&
          thatSpace->getColor() == BLACK) {
        thatSpace->setSpace(thisPawn);
        thisPawn->setEmpty();
        return true;
      } else {
        return false;
      }
    }
  } else {
    if (thisPawn->getColor() == BLACK) {
      if (pawnX == thatX && thatY == pawnY - 1 &&
          thatSpace->getColor() == NONE) {
        thatSpace->setSpace(thisPawn);
        thisPawn->setEmpty();
        return true;
      } else {
        if ((pawnX + 1 == thatX || pawnX - 1 == thatX) && pawnY - 1 == thatY &&
            thatSpace->getColor() == WHITE) {
          thatSpace->setSpace(thisPawn);
          thisPawn->setEmpty();
          return true;
        } else {
          return false;
        }
      }
    } else {
      return false;
    }
  }
  return false;
}

bool Board::makeMove(int x1, int y1, int x2, int y2) {
  using namespace std;
  if (x1 < 0 || x1 > 7 || y1 < 0 || y1 > 7 || x2 < 0 || x2 > 7 || y2 < 0 ||
      y2 > 8) {
    cout << "One of your coordinates is out of bounds" << endl;
    return false;
  }
  Square *thisSpace = getSquare(x1, y1);
  Square *thatSpace = getSquare(x2, y2);
  if (thisSpace->getColor() == thatSpace->getColor() &&
      thatSpace->getColor() != NONE) {
    cout << "Invalid move: cannot land on your own piece" << endl;
  }
  switch (thisSpace->getPiece()) {
  case KING:
    return moveKing(thisSpace, thatSpace);
    break;
  case QUEEN:
    return moveQueen(thisSpace, thatSpace);
    break;
  case ROOK:
    return moveRook(thisSpace, thatSpace);
    break;
  case BISHOP:
    return moveBishop(thisSpace, thatSpace);
    break;
  case KNIGHT:
    return moveKnight(thisSpace, thatSpace);
    break;
  case PAWN:
    return movePawn(thisSpace, thatSpace);
    break;
  case EMPTY:
    cout << "You do not have a piece there" << endl;
  }
  return false;
}
// bishop, knight, rook, pawn,
