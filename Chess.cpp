#include <SFML/Graphics.hpp> 
#include <iostream> 
#include <string> 

using namespace sf; 
using namespace std; 
//GAME ------LOGIC
const int SIZE = 8;
char board[SIZE][SIZE]; 
bool whiteTurn = true; 
bool gameOver = false; 

int absInt(int x)
{
    return x < 0 ? -x : x;
} 
bool isWhiteChar(char p) // check uppercase = white
{
    return (p >= 'A' && p <= 'Z');
} 
char toLowerChar(char p)  // to lower
{
    if (p >= 'A' && p <= 'Z')
    {
        return (char)(p - 'A' + 'a');
    }
    return p;
}
char toUpperChar(char p) // to upper
{
    if (p >= 'a' && p <= 'z')
    {
        return (char)(p - 'a' + 'A');
    }
    return p;
} 
void initializeBoard() 
{
    board[0][0] = board[0][7] = 'r'; 
    board[7][0] = board[7][7] = 'R'; 
    board[0][1] = board[0][6] = 'n'; 
    board[7][1] = board[7][6] = 'N'; 
    board[0][2] = board[0][5] = 'b';
    board[7][2] = board[7][5] = 'B';
    board[0][3] = 'q'; 
    board[7][3] = 'Q'; 
    board[0][4] = 'k';
    board[7][4] = 'K'; 
    for (int j = 0; j < 8; j++)
    {
        board[6][j] = 'P';
    }
    for (int j = 0; j < 8; j++)
    {
        board[1][j] = 'p';
    }
    for (int i = 2; i < 6; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            board[i][j] = ' '; // empty middle rows
        }
    }
    whiteTurn = true; // white starts
    gameOver = false;
}
bool isvalidrookmove(int sx, int sy, int dx, int dy) // rook move check
{
    if (sx == dx || sy == dy)  // same row or column
    {
        if (sx == dx && dy > sy)  // path clear right
        {
            for (int i = sy + 1; i < dy; i++)
            {
                if (board[sx][i] != ' ')
                {
                    return false;
                }
            }
        }
        if (sy == dy && dx > sx)// path clear down
        {
            for (int i = sx + 1; i < dx; i++)
            {
                if (board[i][sy] != ' ')
                {
                    return false;
                }
            }
        }
        if (sx == dx && dy < sy) // path clear left
        {
            for (int i = sy - 1; i > dy; i--)
            {
                if (board[sx][i] != ' ')
                {
                    return false;
                }
            }
        }
        if (sy == dy && dx < sx)// path clear up
        {
            for (int i = sx - 1; i > dx; i--)
            {
                if (board[i][sy] != ' ')
                {
                    return false;
                }
            }
        }
        return true; 
    }
    return false; 
}

bool isvalidbishopmove(int sx, int sy, int dx, int dy) // bishop move check
{
    int dif1 = sx - dx; // row diff
    int dif2 = sy - dy; // col diff
    if (absInt(dif1) == absInt(dif2)) // diagonal
    {
        if (dif1 < 0 && dif2 < 0)// down-right path
        {
            int i = sx + 1, j = sy + 1;
            for (; i < dx; i++)
            {
                if (board[i][j++] != ' ')
                {
                    return false;
                }
            }
        }
        else if (dif1 > 0 && dif2 < 0)// up-right path
        {
            int i = sx - 1, j = sy + 1;
            for (; i > dx; i--)
            {
                if (board[i][j++] != ' ')
                {
                    return false;
                }
            }
        }
        else if (dif1 < 0 && dif2 > 0)// down-left path
        {
            int i = sx + 1, j = sy - 1;
            for (; i < dx; i++)
            {
                if (board[i][j--] != ' ')
                {
                    return false;
                }
            }
        }
        else if (dif1 > 0 && dif2 > 0)// up-left path
        {
            int i = sx - 1, j = sy - 1;
            for (; i > dx; i--)
            {
                if (board[i][j--] != ' ')
                {
                    return false;
                }
            }
        }
        return true; 
    }
    return false; 
}

bool isvalidknightmove(int sx, int sy, int dx, int dy)// knight move check
{
    int rowDiff = absInt(dx - sx); // row 
    int colDiff = absInt(dy - sy); // col 
    if ((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2))// L-shape
    {
        return true;
    }
    return false; 
}

bool isvalidqueenmove(int sx, int sy, int dx, int dy) // queen move check
{
    int dif1 = sx - dx;
    int dif2 = sy - dy;
    if (abs(dif1) == abs(dif2))
    {
        if (dif1 < 0 && dif2 < 0)
        {
            int i = sx + 1, j = sy + 1;
            for (; i < dx; i++)
            {
                if (board[i][j++] != ' ')
                {
                    return false;
                }
            }
        }
        else if (dif1 > 0 && dif2 < 0)
        {
            int i = sx - 1, j = sy + 1;
            for (; i > dx; i--)
            {
                if (board[i][j++] != ' ')
                {
                    return false;
                }
            }
        }
        else if (dif1 < 0 && dif2 > 0)
        {
            int i = sx + 1, j = sy - 1;
            for (; i < dx; i++)
            {
                if (board[i][j--] != ' ')
                {
                    return false;
                }
            }
        }
        else if (dif1 > 0 && dif2 > 0)
        {
            int i = sx - 1, j = sy - 1;
            for (; i > dx; i--)
            {
                if (board[i][j--] != ' ')
                {
                    return false;
                }
            }
        }
        return true;
    }
    if (sx == dx || sy == dy)
    {
        if (sx == dx && dy > sy)
        {
            for (int i = sy + 1; i < dy; i++)
            {
                if (board[sx][i] != ' ')
                {
                    return false;
                }
            }
        }
        if (sy == dy && dx > sx)
        {
            for (int i = sx + 1; i < dx; i++)
            {
                if (board[i][sy] != ' ')
                {
                    return false;
                }
            }
        }
        if (sx == dx && dy < sy)
        {
            for (int i = sy - 1; i > dy; i--)
            {
                if (board[sx][i] != ' ')
                {
                    return false;
                }
            }
        }
        if (sy == dy && dx < sx)
        {
            for (int i = sx - 1; i > dx; i--)
            {
                if (board[i][sy] != ' ')
                {
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}

bool isvalidkingmove(int sx, int sy, int dx, int dy) // king move check
{
    int dif1 = sx - dx; // row diff
    int dif2 = sy - dy; // col diff
    if (absInt(dif1) == absInt(dif2))
    {
        if (absInt(dif1) == 1)// one-step diagonal
        {
            return true;
        }
    }
    if (sx == dx || sy == dy)
    {
        if (sx == dx && absInt(dif2) == 1)// one-step horizontal
        {
            return true;
        }
        if (sy == dy && absInt(dif1) == 1)// one-step vertical
        {
            return true;
        }
    }
    return false; 
}

bool isvalidpawnmove(int sx, int sy, int dx, int dy, bool turn) // pawn move check
{
    int dif = sx - dx; // row 
    int dif1 = sy - dy; // col
    if (turn)  // white's moves
    {
        if ((dif == 1 && dif1 == 0 && board[dx][dy] == ' ') || // one forward empty
            (sx == 6 && dif == 2 && dif1 == 0 && board[sx - 1][sy] == ' ' && board[dx][dy] == ' ') || // two forward from start
            (dif == 1 && absInt(dif1) == 1 && board[dx][dy] != ' ')) // capture diagonal
            return true; 
    }
    else // black's moves
    {
        if ((dif == -1 && dif1 == 0 && board[dx][dy] == ' ') || // one forward empty
            (sx == 1 && dif == -2 && dif1 == 0 && board[sx + 1][sy] == ' ' && board[dx][dy] == ' ') || // two from start
            (dif == -1 && absInt(dif1) == 1 && board[dx][dy] != ' ')) // capture
            return true; 
    }
    return false;
}

bool isValidMove(char boardArr[][8], int sx, int sy, int dx, int dy, bool turn) // generic move validator
{
    if (sx == dx && sy == dy) return false; // same square
    if (boardArr[sx][sy] == ' ') return false; // empty source
    if (turn == true) {
        char p = boardArr[sx][sy];
        if (!(p == 'R' || p == 'N' || p == 'B' || p == 'K' || p == 'Q' || p == 'P')) return false; // not white piece
    }
    else {
        char p = boardArr[sx][sy];
        if (!(p == 'r' || p == 'n' || p == 'b' || p == 'k' || p == 'q' || p == 'p')) return false; // not black piece
    }
    if (turn == true) {
        char t = boardArr[dx][dy];
        if (t == 'R' || t == 'N' || t == 'B' || t == 'K' || t == 'Q' || t == 'P') return false; // cannot capture own white
    }
    else {
        char t = boardArr[dx][dy];
        if (t == 'r' || t == 'n' || t == 'b' || t == 'k' || t == 'q' || t == 'p') return false; // cannot capture own black
    }

    char piece = boardArr[sx][sy]; // piece char
    if (piece == 'R' || piece == 'r') return isvalidrookmove(sx, sy, dx, dy); // rook logic
    if (piece == 'B' || piece == 'b') return isvalidbishopmove(sx, sy, dx, dy); // bishop logic
    if (piece == 'N' || piece == 'n') return isvalidknightmove(sx, sy, dx, dy); // knight logic
    if (piece == 'Q' || piece == 'q') return isvalidqueenmove(sx, sy, dx, dy); // queen logic
    if (piece == 'K' || piece == 'k') return isvalidkingmove(sx, sy, dx, dy); // king logic
    if (piece == 'P' || piece == 'p') return isvalidpawnmove(sx, sy, dx, dy, turn); // pawn logic
    return false; 
}

void makeMoveOnBoard(char boardArr[][8], int sx, int sy, int dx, int dy, bool turn) // update board array
{
    char movingPiece = boardArr[sx][sy]; 
    boardArr[dx][dy] = movingPiece;
    boardArr[sx][sy] = ' ';
}

void applyPromotion(int r, int c, char pieceChar)// place promoted piece
{
    board[r][c] = pieceChar; 
} 

void findKing(bool white, int& kr, int& kc) // locate king coordinates
{
    char k = white ? 'K' : 'k'; // king char by color
    kr = -1; kc = -1; // default not found
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j] == k)// set and return
            {
                kr = i; kc = j; return;
            } 
        }
    }
}

bool isSquareAttacked(int r, int c, bool byWhite)  // check if square under attack
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            char p = board[i][j]; // piece at source
            if (byWhite) 
            {
                if (!(p == 'R' || p == 'N' || p == 'B' || p == 'Q' || p == 'K' || p == 'P')) continue; // not white piece
            }
            else {
                if (!(p == 'r' || p == 'n' || p == 'b' || p == 'q' || p == 'k' || p == 'p')) continue; // not black piece
            }
            if (isValidMove(board, i, j, r, c, byWhite))// if that piece can move to square
            { // for pawn attacks
                if (board[i][j] == 'P' && r == i - 1 && (c == j - 1 || c == j + 1)) return true; // pawn attack white
                if (board[i][j] == 'p' && r == i + 1 && (c == j - 1 || c == j + 1)) return true; // pawn attack black
                return true; 
            }
        }
    }
    return false;
}

bool isInCheck(bool white) // is king in check
{
    int kr, kc; // king coords
    findKing(white, kr, kc); // find king
    if (kr == -1) return false; // no king
    return isSquareAttacked(kr, kc, !white); // attacked by opponent?
}

bool hasLegalMoves(bool white)  // any legal moves for side?
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            char p = board[i][j]; // piece
            if (white)
            {
                if (!(p == 'R' || p == 'N' || p == 'B' || p == 'Q' || p == 'K' || p == 'P')) continue; // not white
            }
            else
            {
                if (!(p == 'r' || p == 'n' || p == 'b' || p == 'q' || p == 'k' || p == 'p')) continue; // not black
            }
            for (int r = 0; r < 8; r++) 
            {
                for (int c = 0; c < 8; c++)
                {
                    if (isValidMove(board, i, j, r, c, white)) // possible move
                    {
                        char t1 = board[i][j], t2 = board[r][c]; // save
                        board[r][c] = t1; board[i][j] = ' '; // make move
                        bool check = isInCheck(white); // does it leave in check
                        board[i][j] = t1; board[r][c] = t2; // undo
                        if (!check)// legal found
                        {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false; 
}

bool isCheckmate(bool white)  // checkmate detection
{
    if (isInCheck(white) && !hasLegalMoves(white)) return true; // check + no moves
    return false; 
}
bool isStalemate(bool white)  // stalemate detection
{
    if (!isInCheck(white) && !hasLegalMoves(white)) return true; // not in check but no moves
    return false; 
}
//SFML ------ LOGIC
Sprite pieceSprites[32]; // sprite array for pieces
char pieceChars[32]; // char mapping for each sprite
int pieceR[32], pieceC[32]; // sprite board coordinates
bool pieceAlive[32]; // if sprite is alive
int pieceCount = 0; // number of sprites used

char capturedWhite[16]; // captured white pieces by black
char capturedBlack[16]; // captured black pieces by white
int capturedWhiteCount = 0; // count captured white
int capturedBlackCount = 0; // count captured black

Texture tex_white_pawn, tex_white_rook, tex_white_knight, tex_white_bishop, tex_white_queen, tex_white_king; // white textures
Texture tex_black_pawn, tex_black_rook, tex_black_knight, tex_black_bishop, tex_black_queen, tex_black_king; // black textures
Texture tex_prom_q, tex_prom_r, tex_prom_b, tex_prom_n; // promotion textures
Texture tex_menu_bg; // menu background texture

enum TextureIndex  // enum to identify textures
{
    TI_W_PAWN = 0, TI_W_ROOK, TI_W_KNIGHT, TI_W_BISHOP, TI_W_QUEEN, TI_W_KING,
    TI_B_PAWN, TI_B_ROOK, TI_B_KNIGHT, TI_B_BISHOP, TI_B_QUEEN, TI_B_KING,
    TI_INVALID = -1
};

int textureIndexForChar(char p)  // map piece char to texture enum
{
    switch (p)
    {
    case 'P': return TI_W_PAWN;
    case 'R': return TI_W_ROOK;
    case 'N': return TI_W_KNIGHT;
    case 'B': return TI_W_BISHOP;
    case 'Q': return TI_W_QUEEN;
    case 'K': return TI_W_KING;
    case 'p': return TI_B_PAWN;
    case 'r': return TI_B_ROOK;
    case 'n': return TI_B_KNIGHT;
    case 'b': return TI_B_BISHOP;
    case 'q': return TI_B_QUEEN;
    case 'k': return TI_B_KING;
    default: return TI_INVALID;
    }
}

Texture& getTextureByIndex(int idx)  // return texture reference by enum
{
    switch (idx) 
    {
    case TI_W_PAWN: return tex_white_pawn;
    case TI_W_ROOK: return tex_white_rook;
    case TI_W_KNIGHT: return tex_white_knight;
    case TI_W_BISHOP: return tex_white_bishop;
    case TI_W_QUEEN: return tex_white_queen;
    case TI_W_KING: return tex_white_king;
    case TI_B_PAWN: return tex_black_pawn;
    case TI_B_ROOK: return tex_black_rook;
    case TI_B_KNIGHT: return tex_black_knight;
    case TI_B_BISHOP: return tex_black_bishop;
    case TI_B_QUEEN: return tex_black_queen;
    case TI_B_KING: return tex_black_king;
    default: return tex_white_pawn; // fallback reference
    }
}

void buildSpritesFromBoard(float squareSize, float offsetX, float offsetY)  // create sprites from board
{
    pieceCount = 0; // reset count
    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            char p = board[r][c]; // piece at cell
            if (p == ' ') continue; // skip empty
            int tIdx = textureIndexForChar(p); // texture id
            if (tIdx == TI_INVALID) continue; 
            if (pieceCount >= 32) continue; 
            Texture& tex = getTextureByIndex(tIdx); // get texture
            pieceSprites[pieceCount].setTexture(tex); // set texture
            Vector2u ts = tex.getSize(); // texture size
            if (ts.x > 0 && ts.y > 0)
            {
                pieceSprites[pieceCount].setScale(squareSize / (float)ts.x, squareSize / (float)ts.y); // scale to square
            }
            FloatRect lb = pieceSprites[pieceCount].getLocalBounds(); // local bounds
            pieceSprites[pieceCount].setOrigin(lb.width / 2.f, lb.height / 2.f); // center origin
            pieceSprites[pieceCount].setPosition(offsetX + (c + 0.5f) * squareSize, offsetY + (r + 0.5f) * squareSize); // set position
            pieceChars[pieceCount] = p; // store char
            pieceR[pieceCount] = r; // store row
            pieceC[pieceCount] = c; // store col
            pieceAlive[pieceCount] = true; // mark alive
            pieceCount++; // increment
        }
    }
}

int findPieceAtPixel(int x, int y)  // find sprite index by pixel coords
{
    for (int i = 0; i < pieceCount; i++)
    {
        if (!pieceAlive[i]) continue;
        if (pieceSprites[i].getGlobalBounds().contains((float)x, (float)y)) return i; // found
    }
    return -1;
}

void refreshSprites(float squareSize, float offsetX, float offsetY)// rebuild sprites
{
    buildSpritesFromBoard(squareSize, offsetX, offsetY);
} 

int legalDestR[64], legalDestC[64]; // arrays holding legal dests
int computeLegalMovesFor(int sr, int sc, bool turn)  // compute legal moves excluding check
{
    int found = 0; // count
    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            if (isValidMove(board, sr, sc, r, c, turn)) // if piece can move there
            {
                char saveFrom = board[sr][sc]; // save from
                char saveTo = board[r][c]; // save to
                board[r][c] = saveFrom; // simulate move
                board[sr][sc] = ' '; // clear source
                bool leavesCheck = isInCheck(turn); // check if side is in check after move
                board[sr][sc] = saveFrom; // undo
                board[r][c] = saveTo; // undo
                if (!leavesCheck) 
                {
                    legalDestR[found] = r; // record r
                    legalDestC[found] = c; // record c
                    found++; // increment
                }
            }
        }
    }
    return found; 
}

int main() {
    RenderWindow window(VideoMode(1100, 650), "Chess Game", Style::Default); // create window
    window.setFramerateLimit(60); // set fps cap

    float boardSize = (window.getSize().x < window.getSize().y ? window.getSize().x : window.getSize().y) * 0.75f; // compute board size
    float squareSize = boardSize / 8.f; // size per square
    float offsetX = ((float)window.getSize().x - boardSize) / 2.f - 40.f; // left offset for board
    float offsetY = ((float)window.getSize().y - boardSize) / 2.f; // top offset for board

    if (!tex_menu_bg.loadFromFile("pieces/menu_background.png"))// load menu bg
    {
        cout << "Warning: menu_background.png not found\n"; 
    } 
    Sprite menuBG(tex_menu_bg); // menu sprite
    if (tex_menu_bg.getSize().x > 0)
    {
        menuBG.setScale((float)window.getSize().x / (float)tex_menu_bg.getSize().x, (float)window.getSize().y / (float)tex_menu_bg.getSize().y); // scale bg
    }

    bool texOK = true; // track texture loading
    if (!tex_white_pawn.loadFromFile("pieces/white-pawn.png")) { cout << "Missing white-pawn.png\n"; texOK = false; } // load each
    if (!tex_white_rook.loadFromFile("pieces/white-rook.png")) { cout << "Missing white-rook.png\n"; texOK = false; }
    if (!tex_white_knight.loadFromFile("pieces/white-knight.png")) { cout << "Missing white-knight.png\n"; texOK = false; }
    if (!tex_white_bishop.loadFromFile("pieces/white-bishop.png")) { cout << "Missing white-bishop.png\n"; texOK = false; }
    if (!tex_white_queen.loadFromFile("pieces/white-queen.png")) { cout << "Missing white-queen.png\n"; texOK = false; }
    if (!tex_white_king.loadFromFile("pieces/white-king.png")) { cout << "Missing white-king.png\n"; texOK = false; }

    if (!tex_black_pawn.loadFromFile("pieces/black-pawn.png")) { cout << "Missing black-pawn.png\n"; texOK = false; }
    if (!tex_black_rook.loadFromFile("pieces/black-rook.png")) { cout << "Missing black-rook.png\n"; texOK = false; }
    if (!tex_black_knight.loadFromFile("pieces/black-knight.png")) { cout << "Missing black-knight.png\n"; texOK = false; }
    if (!tex_black_bishop.loadFromFile("pieces/black-bishop.png")) { cout << "Missing black-bishop.png\n"; texOK = false; }
    if (!tex_black_queen.loadFromFile("pieces/black-queen.png")) { cout << "Missing black-queen.png\n"; texOK = false; }
    if (!tex_black_king.loadFromFile("pieces/black-king.png")) { cout << "Missing black-king.png\n"; texOK = false; }

    if (!tex_prom_q.loadFromFile("pieces/white-queen.png")) { cout << "Missing prom_q.png\n"; texOK = false; } // promotion icons
    if (!tex_prom_r.loadFromFile("pieces/white-rook.png")) { cout << "Missing prom_r.png\n"; texOK = false; }
    if (!tex_prom_b.loadFromFile("pieces/white-bishop.png")) { cout << "Missing prom_b.png\n"; texOK = false; }
    if (!tex_prom_n.loadFromFile("pieces/white-knight.png")) { cout << "Missing prom_n.png\n"; texOK = false; }

    Font font; // font object
    bool haveFont = font.loadFromFile("C:/Windows/Fonts/arial.ttf") || font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf") || font.loadFromFile("menu_font.ttf") || font.loadFromFile("arial.ttf"); // try many

    Text title; // title text
    if (haveFont)
    {
        title = Text("Chess", font, 72); // set title
        title.setFillColor(Color::White); // white color
    }

    RectangleShape startButton(Vector2f(220.f, 70.f)); // start button rect
    startButton.setFillColor(Color::Black); // black background
    startButton.setPosition((float)window.getSize().x - 50.f - 220.f, (float)window.getSize().y - 50.f - 70.f); // position
    Text startText; // start label
    if (haveFont)
    {
        startText = Text("START", font, 32); // set text
        startText.setFillColor(Color::White); // white text
        FloatRect tb = startText.getLocalBounds(); // bounds
        startText.setOrigin(tb.left + tb.width / 2.f, tb.top + tb.height / 2.f); // center origin
        startText.setPosition(startButton.getPosition().x + startButton.getSize().x / 2.f, startButton.getPosition().y + startButton.getSize().y / 2.f); // center on button
    }

    RectangleShape restartBtn(Vector2f(160.f, 50.f)); // restart button shape
    restartBtn.setFillColor(Color::Black); // black
    restartBtn.setPosition((float)window.getSize().x - 50.f - 160.f, (float)window.getSize().y - 50.f - 50.f); // pos
    Text restartText; // restart label
    if (haveFont) 
    {
        restartText = Text("RESTART", font, 20); // text
        restartText.setFillColor(Color::White); // color
        FloatRect tr = restartText.getLocalBounds(); // bounds
        restartText.setOrigin(tr.left + tr.width / 2.f, tr.top + tr.height / 2.f); // origin center
        restartText.setPosition(restartBtn.getPosition().x + restartBtn.getSize().x / 2.f, restartBtn.getPosition().y + restartBtn.getSize().y / 2.f); // center
    }
    RectangleShape endBtn(Vector2f(160.f, 50.f)); // end button
    endBtn.setFillColor(Color::Black); // color
    endBtn.setPosition((float)window.getSize().x - 50.f - 160.f, (float)window.getSize().y - 50.f - 110.f); // pos
    Text endText; // end label
    if (haveFont)
    {
        endText = Text("END GAME", font, 20); // text
        endText.setFillColor(Color::White); // color
        FloatRect te = endText.getLocalBounds(); // bounds
        endText.setOrigin(te.left + te.width / 2.f, te.top + te.height / 2.f); // center origin
        endText.setPosition(endBtn.getPosition().x + endBtn.getSize().x / 2.f, endBtn.getPosition().y + endBtn.getSize().y / 2.f); // center
    }

    Sprite promSprites[4]; // promotion sprites array
    promSprites[0].setTexture(tex_prom_q); // queen icon
    promSprites[1].setTexture(tex_prom_r); // rook icon
    promSprites[2].setTexture(tex_prom_b); // bishop icon
    promSprites[3].setTexture(tex_prom_n); // knight icon

    initializeBoard(); // set board
    buildSpritesFromBoard(squareSize, offsetX, offsetY); // build sprites

    enum GameState { MENU, GAME, RESULT_MENU }; // game states
    GameState state = MENU; // start in menu

    int selectedPieceIndex = -1; // selected sprite index
    float origX = 0.f, origY = 0.f; // original pixel pos
    int sel_r = -1, sel_c = -1; // selected board coords
    int legalCount = 0; // legal move count
    bool showingPromotion = false; // promotion popup flag
    int promo_r = -1, promo_c = -1; // promotion square

    string resultText = ""; // result message

    auto layoutPromotion = [&](float sq) // layout prom icons
        {
        float iconSize = sq * 1.0f; // icon size
        float totalW = iconSize * 4.f + 20.f; // total width
        float px = (float)window.getSize().x / 2.f - totalW / 2.f; // left of box
        float py = (float)window.getSize().y / 2.f - (iconSize + 40.f) / 2.f; // top of box
        for (int i = 0; i < 4; i++) 
        {
            Vector2u ts = promSprites[i].getTexture()->getSize(); // texture size
            if (ts.x > 0 && ts.y > 0) promSprites[i].setScale(iconSize / (float)ts.x, iconSize / (float)ts.y); // scale icon
            FloatRect lb = promSprites[i].getLocalBounds(); // bounds
            promSprites[i].setOrigin(lb.width / 2.f, lb.height / 2.f); // center origin
            promSprites[i].setPosition(px + 10.f + iconSize / 2.f + i * (iconSize + 2.f), py + (iconSize + 40.f) / 2.f); // set pos
        }
        };
    layoutPromotion(squareSize); // call layout once

    bool prevCheckWhite = false; // previous check flag white
    bool prevCheckBlack = false; // previous check flag black

    while (window.isOpen())
    { // main loop
        Event e; // event object
        while (window.pollEvent(e)) 
        { // poll events
            if (e.type == Event::Closed) window.close(); // close event

            if (e.type == Event::Resized)  // handle resize
            {
                window.setView(View(FloatRect(0.f, 0.f, (float)e.size.width, (float)e.size.height))); // update view
                boardSize = ((float)window.getSize().x < (float)window.getSize().y ? (float)window.getSize().x : (float)window.getSize().y) * 0.75f; // recompute
                squareSize = boardSize / 8.f; // recompute square
                offsetX = ((float)window.getSize().x - boardSize) / 2.f - 40.f; // recompute offsets
                offsetY = ((float)window.getSize().y - boardSize) / 2.f;
                if (tex_menu_bg.getSize().x > 0)
                {
                    menuBG.setScale((float)window.getSize().x / (float)tex_menu_bg.getSize().x, (float)window.getSize().y / (float)tex_menu_bg.getSize().y); // scale menu
                }
                startButton.setPosition((float)window.getSize().x - 50.f - 220.f, (float)window.getSize().y - 50.f - 70.f); // update start pos
                if (haveFont) startText.setPosition(startButton.getPosition().x + startButton.getSize().x / 2.f, startButton.getPosition().y + startButton.getSize().y / 2.f); // update start text pos
                {
                    restartBtn.setPosition((float)window.getSize().x - 50.f - 160.f, (float)window.getSize().y - 50.f - 50.f); // update restart pos
                }
                if (haveFont) restartText.setPosition(restartBtn.getPosition().x + restartBtn.getSize().x / 2.f, restartBtn.getPosition().y + restartBtn.getSize().y / 2.f); // update restart text pos
                {
                    endBtn.setPosition((float)window.getSize().x - 50.f - 160.f, (float)window.getSize().y - 50.f - 110.f); // update end pos
                }
                if (haveFont) endText.setPosition(endBtn.getPosition().x + endBtn.getSize().x / 2.f, endBtn.getPosition().y + endBtn.getSize().y / 2.f); // update end text pos
                {
                    refreshSprites(squareSize, offsetX, offsetY); // refresh sprites for new sizes
                }
                layoutPromotion(squareSize); // relayout promotion icons
            }

            if (state == MENU) // menu input
            {
                if (e.type == Event::MouseButtonPressed && e.mouseButton.button == Mouse::Left)  // click
                {
                    int mx = e.mouseButton.x, my = e.mouseButton.y; // mouse pos
                    if (startButton.getGlobalBounds().contains((float)mx, (float)my)) 
                    { // click start
                        initializeBoard(); // reset board
                        capturedWhiteCount = capturedBlackCount = 0; // reset captures
                        refreshSprites(squareSize, offsetX, offsetY); // refresh sprites
                        state = GAME; // go to game state
                        showingPromotion = false; // clear promotion
                        gameOver = false; // clear game over
                        resultText = ""; // clear result text
                        prevCheckWhite = prevCheckBlack = false; // clear check flags
                    }
                }
            }
            else if (state == GAME)  // game input
            {
                if (showingPromotion)  // promotion popup active
                {
                    if (e.type == Event::MouseButtonPressed && e.mouseButton.button == Mouse::Left)  // click to choose promotion
                    {
                        int mx = e.mouseButton.x, my = e.mouseButton.y; // mouse
                        for (int i = 0; i < 4; i++)
                        {
                            if (promSprites[i].getGlobalBounds().contains((float)mx, (float)my)) // clicked icon
                            {
                                char chosen = 'Q'; // default queen
                                if (i == 0) chosen = 'Q'; // queen
                                if (i == 1) chosen = 'R'; // rook
                                if (i == 2) chosen = 'B'; // bishop
                                if (i == 3) chosen = 'N'; // knight
                                if (!whiteTurn) chosen = toLowerChar(chosen); // lowercase if black
                                applyPromotion(promo_r, promo_c, chosen); // apply promotion
                                showingPromotion = false; // hide popup
                                whiteTurn = !whiteTurn; // flip turn after promotion
                                refreshSprites(squareSize, offsetX, offsetY); // rebuild sprites
                                if (isCheckmate(whiteTurn)) // check test
                                {
                                    gameOver = true; 
                                    if (whiteTurn) resultText = "Black won by checkmate";
                                    else resultText = "White won by checkmate";
                                    cout << resultText << "\n"; 
                                } 
                                else if (isStalemate(whiteTurn))// stalemate 
                                {
                                    gameOver = true;
                                    resultText = "Draw by stalemate";
                                    cout << resultText << "\n";
                                } 
                                if (isInCheck(whiteTurn) && ((whiteTurn && !prevCheckWhite) || (!whiteTurn && !prevCheckBlack))) // print check
                                {
                                    cout << (whiteTurn ? "White" : "Black") << " is in check.\n";
                                } 
                                break; 
                            }
                        }
                    }
                    continue; 
                }

                if (gameOver)  // game over input
                {
                    if (e.type == Event::MouseButtonPressed && e.mouseButton.button == Mouse::Left)  // click restart/end
                    {
                        int mx = e.mouseButton.x, my = e.mouseButton.y; // mouse pos
                        if (restartBtn.getGlobalBounds().contains((float)mx, (float)my))  // restart clicked
                        {
                            initializeBoard(); capturedWhiteCount = capturedBlackCount = 0; refreshSprites(squareSize, offsetX, offsetY); gameOver = false; whiteTurn = true; resultText = ""; prevCheckWhite = prevCheckBlack = false; // reset game
                        }
                        else if (endBtn.getGlobalBounds().contains((float)mx, (float)my))  // end clicked
                        {
                            state = RESULT_MENU; // go to result menu
                        }
                    }
                    continue;
                }

                if (e.type == Event::MouseButtonPressed && e.mouseButton.button == Mouse::Left)  // pick up piece
                {
                    int mx = e.mouseButton.x, my = e.mouseButton.y; // mouse
                    int idx = findPieceAtPixel(mx, my); // find sprite under mouse
                    if (idx >= 0) 
                    {
                        char pc = pieceChars[idx]; // piece char
                        bool isWhite = isWhiteChar(pc); // piece color
                        if ((whiteTurn && isWhite) || (!whiteTurn && !isWhite))
                        { // if it's current player's piece
                            selectedPieceIndex = idx; // set selection
                            origX = pieceSprites[idx].getPosition().x; // remember orig pos
                            origY = pieceSprites[idx].getPosition().y; // remember orig pos
                            sel_r = pieceR[idx]; // board row
                            sel_c = pieceC[idx]; // board col
                            legalCount = computeLegalMovesFor(sel_r, sel_c, whiteTurn); // compute legal destinations
                        }
                    }
                }

                if (e.type == Event::MouseMoved)  // dragging sprite with mouse
                {
                    if (selectedPieceIndex != -1)
                    {
                        pieceSprites[selectedPieceIndex].setPosition((float)e.mouseMove.x, (float)e.mouseMove.y); // follow cursor
                    }
                }

                if (e.type == Event::MouseButtonReleased && e.mouseButton.button == Mouse::Left)  // drop piece
                {
                    if (selectedPieceIndex != -1)
                    {
                        int mx = e.mouseButton.x, my = e.mouseButton.y; // mouse pos
                        float relX = (float)mx - offsetX; // relative x to board
                        float relY = (float)my - offsetY; // relative y to board
                        int tc = (int)(relX / squareSize); // target col
                        int tr = (int)(relY / squareSize); // target row
                        bool moved = false; // whether move executed
                        if (tc >= 0 && tc < 8 && tr >= 0 && tr < 8)  // inside board?
                        {
                            for (int k = 0; k < legalCount; k++)  // iterate legal moves
                            {
                                if (legalDestR[k] == tr && legalDestC[k] == tc)  // match legal dest
                                {
                                    char fromChar = board[sel_r][sel_c]; // src piece char
                                    char toChar = board[tr][tc]; // dest piece char
                                    if (toChar != ' ')  // if capture
                                    {
                                        if (isWhiteChar(toChar)) {
                                            if (capturedWhiteCount < 16) capturedWhite[capturedWhiteCount++] = toChar; // record captured white
                                        }
                                        else {
                                            if (capturedBlackCount < 16) capturedBlack[capturedBlackCount++] = toChar; // record captured black
                                        }
                                    }
                                    makeMoveOnBoard(board, sel_r, sel_c, tr, tc, whiteTurn); // change board
                                    bool promotionNeeded = false; // promotion flag
                                    if ((fromChar == 'P' && tr == 0) || (fromChar == 'p' && tr == 7)) promotionNeeded = true; // check pawn row
                                    if (promotionNeeded) 
                                    {
                                        showingPromotion = true; // show promo popup
                                        promo_r = tr; promo_c = tc; // store promo cell
                                        refreshSprites(squareSize, offsetX, offsetY); // rebuild sprites
                                    }
                                    else 
                                    {
                                        whiteTurn = !whiteTurn; // flip turn
                                        refreshSprites(squareSize, offsetX, offsetY); // rebuild sprites
                                        if (isCheckmate(whiteTurn))  // checkmate after move
                                        {
                                            gameOver = true;
                                            if (whiteTurn) resultText = "Black won by checkmate"; else resultText = "White won by checkmate";
                                            cout << resultText << "\n"; // print to console
                                        }
                                        else if (isStalemate(whiteTurn))  // stalemate
                                        {
                                            gameOver = true;
                                            resultText = "Draw by stalemate";
                                            cout << resultText << "\n";
                                        }
                                        else 
                                        {
                                            if (isInCheck(whiteTurn))  // report checks
                                            {
                                                cout << (whiteTurn ? "White" : "Black") << " is in check.\n";
                                            }
                                        }
                                    }
                                    moved = true; // mark moved
                                    break; // done with legal moves loop
                                }
                            }
                        }
                        if (!moved)
                        {
                            pieceSprites[selectedPieceIndex].setPosition(origX, origY); // snap back if not moved
                        }
                        selectedPieceIndex = -1; // clear selection
                        sel_r = sel_c = -1; // clear coords
                        legalCount = 0; // clear legal moves
                    }
                }
            } // end GAME branch

            if (state == RESULT_MENU)  // result menu inputs
            {
                if (e.type == Event::MouseButtonPressed && e.mouseButton.button == Mouse::Left)  // click anywhere
                {
                    int mx = e.mouseButton.x, my = e.mouseButton.y; // mouse pos
                    if (startButton.getGlobalBounds().contains((float)mx, (float)my))  // click start
                    {
                        initializeBoard(); // reset
                        capturedWhiteCount = capturedBlackCount = 0; // reset captures
                        refreshSprites(squareSize, offsetX, offsetY); // rebuild
                        state = GAME; // go to game
                        gameOver = false; // clear
                        showingPromotion = false; // clear
                        resultText = ""; // clear text
                        prevCheckWhite = prevCheckBlack = false; // clear
                    }
                    else 
                    {
                        state = MENU; // go back to menu
                    }
                }
            }
        } // end event polling

        window.clear(); // clear screen

        if (haveFont)
        {
            FloatRect tbounds = title.getLocalBounds(); // title bounds
            title.setOrigin(tbounds.width, tbounds.top); // origin at right
            title.setPosition((float)window.getSize().x - 20.f, 20.f); // position title right top
        }

        if (state == MENU)  // draw menu
        {
            if (tex_menu_bg.getSize().x > 0) window.draw(menuBG); // draw bg if present
            window.draw(startButton); // draw start button rect
            if (haveFont)// draw title & label 
            {
                window.draw(title);
                window.draw(startText); 
            }
        }
        else if (state == GAME) // draw game scene
        {
            RectangleShape gameBG(Vector2f((float)window.getSize().x, (float)window.getSize().y)); // background shape
            gameBG.setFillColor(Color(50, 50, 50)); // dark gray
            window.draw(gameBG); // draw bg

            for (int r = 0; r < 8; r++)  // draw board squares
            {
                for (int c = 0; c < 8; c++) 
                {
                    RectangleShape sq(Vector2f(squareSize, squareSize)); // square shape
                    sq.setPosition(offsetX + c * squareSize, offsetY + r * squareSize); // position
                    if ((r + c) % 2 == 0) sq.setFillColor(Color(245, 239, 227)); // light
                    else sq.setFillColor(Color(127, 15, 15)); // dark
                    window.draw(sq); // draw square
                }
            }

            int wkr, wkc, bkr, bkc; // king positions
            findKing(true, wkr, wkc); // find white king
            findKing(false, bkr, bkc); // find black king
            if (isInCheck(true) && wkr != -1)  // highlight white king square if in check
            {
                RectangleShape ks(Vector2f(squareSize, squareSize));
                ks.setPosition(offsetX + wkc * squareSize, offsetY + wkr * squareSize);
                ks.setFillColor(Color(200, 30, 30, 200)); // red transparent
                window.draw(ks);
            }
            if (isInCheck(false) && bkr != -1) // highlight black king square if in check
            {
                RectangleShape ks(Vector2f(squareSize, squareSize));
                ks.setPosition(offsetX + bkc * squareSize, offsetY + bkr * squareSize);
                ks.setFillColor(Color(200, 30, 30, 200)); // red transparent
                window.draw(ks);
            }

            if (haveFont)  // draw coordinates around board
            {
                Text t("", font, 18); // temp text
                t.setFillColor(Color::White); // white color
                for (int r = 0; r < 8; r++) 
                {
                    t.setString(to_string(8 - r)); // rank numbers
                    FloatRect b = t.getLocalBounds(); // bounds
                    t.setOrigin(b.width, b.height / 2.f); // align right
                    t.setPosition(offsetX - 10.f, offsetY + (r + 0.5f) * squareSize); // left of board
                    window.draw(t); // draw rank
                }
                for (int c = 0; c < 8; c++)
                {
                    string s; s.push_back((char)('A' + c)); // file letters
                    t.setString(s); // set string
                    FloatRect b = t.getLocalBounds(); // bounds
                    t.setOrigin(b.width / 2.f, 0.f); // origin center
                    t.setPosition(offsetX + (c + 0.5f) * squareSize, offsetY + 8.f * squareSize + 5.f); // below board
                    window.draw(t); // draw file letter
                }
            }

            for (int k = 0; k < legalCount; k++) // highlight legal move squares
            {
                RectangleShape hl(Vector2f(squareSize, squareSize)); // highlight rect
                hl.setPosition(offsetX + legalDestC[k] * squareSize, offsetY + legalDestR[k] * squareSize); // pos
                hl.setFillColor(Color(120, 255, 100, 140)); // green translucent
                window.draw(hl); // draw highlight
            }

            for (int i = 0; i < pieceCount; i++)  // draw piece sprites
            {
                if (pieceAlive[i]) window.draw(pieceSprites[i]); // draw if alive
            }

            float capSize = squareSize * 0.65f; // captured piece size
            float spacing = 6.f; // spacing between captured icons

            for (int i = 0; i < capturedWhiteCount; i++) // draw captured white pieces (top area)
            {
                int row = i / 5; // row index downward
                int col = i % 5; // col index
                float x = offsetX - 10.f - (col + 1) * (capSize + spacing); // x pos left of board
                float y = offsetY + row * (capSize + spacing); // y pos
                int tidx = textureIndexForChar(capturedWhite[i]); // texture id
                if (tidx == TI_INVALID) continue; // skip invalid
                Texture& t = getTextureByIndex(tidx); // get texture
                Sprite s; s.setTexture(t); // temp sprite
                Vector2u ts = t.getSize(); // size
                if (ts.x > 0 && ts.y > 0) s.setScale(capSize / (float)ts.x, capSize / (float)ts.y); // scale
                s.setPosition(x, y); // set pos
                window.draw(s); // draw captured piece
            }

            for (int i = 0; i < capturedBlackCount; i++)  // draw captured black pieces (bottom area)
            {
                int row = i / 5; // row index upward
                int col = i % 5; // col
                float x = offsetX - 10.f - (col + 1) * (capSize + spacing); // x pos
                float y = offsetY + boardSize - (row + 1) * (capSize + spacing); // y pos near bottom
                int tidx = textureIndexForChar(capturedBlack[i]); // texture id
                if (tidx == TI_INVALID) continue; // skip invalid
                Texture& t = getTextureByIndex(tidx); // texture
                Sprite s; s.setTexture(t); // sprite
                Vector2u ts = t.getSize(); // size
                if (ts.x > 0 && ts.y > 0) s.setScale(capSize / (float)ts.x, capSize / (float)ts.y); // scale
                s.setPosition(x, y); // set pos
                window.draw(s); // draw
            }

            if (showingPromotion)  // draw promotion popup overlay
            {
                RectangleShape overlay(Vector2f((float)window.getSize().x, (float)window.getSize().y)); // overlay full screen
                overlay.setFillColor(Color(0, 0, 0, 150)); // semi-transparent black
                window.draw(overlay); // draw overlay
                float iconSize = squareSize * 1.0f; // icon size
                float totalW = iconSize * 4.f + 20.f; // box width
                float totalH = iconSize + 40.f; // box height
                float px = (float)window.getSize().x / 2.f - totalW / 2.f; // x pos center
                float py = (float)window.getSize().y / 2.f - totalH / 2.f; // y pos center
                RectangleShape box(Vector2f(totalW, totalH)); // box shape
                box.setPosition(px, py); // position box
                box.setFillColor(Color(40, 40, 40, 230)); // dark box color
                window.draw(box); // draw box
                if (haveFont) {
                    Text tt("Choose promotion", font, 20); // instruction text
                    tt.setFillColor(Color::White); // white text
                    FloatRect bb = tt.getLocalBounds(); // bounds
                    tt.setOrigin(bb.width / 2.f, bb.height / 2.f); // center origin
                    tt.setPosition(px + totalW / 2.f, py + 16.f); // text pos
                    window.draw(tt); // draw text
                }
                for (int i = 0; i < 4; i++) window.draw(promSprites[i]); // draw promotion icons
            }

            if (haveFont)  // draw turn indicator text
            {
                Text turnText((whiteTurn ? "White's turn" : "Black's turn"), font, 22); // choose text
                turnText.setFillColor(Color::White); // white color
                turnText.setPosition(20.f, 10.f); // pos top-left
                window.draw(turnText); // draw
            }

            if (gameOver && haveFont)  // draw result and buttons if game over
            {
                Text rt(resultText, font, 36); // result text
                rt.setFillColor(Color::White); // white
                FloatRect br = rt.getLocalBounds(); // bounds
                rt.setOrigin(br.width / 2.f, br.height / 2.f); // center origin
                rt.setPosition((float)window.getSize().x / 2.f, 40.f); // pos top-center
                window.draw(rt); // draw result
                window.draw(restartBtn); // draw restart button
                window.draw(restartText); // draw restart label
                window.draw(endBtn); // draw end button
                window.draw(endText); // draw end label
            }

            bool nowW = isInCheck(true); // check current white check state
            bool nowB = isInCheck(false); // check current black check state
            prevCheckWhite = nowW; // update prev flags
            prevCheckBlack = nowB;
        }
        else if (state == RESULT_MENU) // draw result menu
        {
            if (tex_menu_bg.getSize().x > 0) window.draw(menuBG); // draw background
            if (haveFont)
            {
                Text mt("Thank You For Playing!", font, 36); // message text
                mt.setFillColor(Color::White); // white color
                mt.setPosition(20.f, 100.f); // left margin
                window.draw(mt); // draw message
                window.draw(restartBtn); // draw small start (play again)
                window.draw(restartText); // draw label
            }
        }

        window.display(); // present frame
    }

    return 0; 
}
