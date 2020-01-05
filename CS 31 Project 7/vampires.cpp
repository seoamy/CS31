// vampires.cpp

// Portions you are to complete are marked with a TODO: comment.
// We've provided some incorrect return statements (so indicated) just
// to allow this skeleton program to compile and run, albeit incorrectly.
// The first thing you probably want to do is implement the utterly trivial
// functions (marked TRIVIAL).  Then get Arena::display going.  That gives
// you more flexibility in the order you tackle the rest of the functionality.
// As you finish implementing each TODO: item, remove its TODO: comment.

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include <cctype>
using namespace std;

///////////////////////////////////////////////////////////////////////////
// Manifest constants
///////////////////////////////////////////////////////////////////////////

const int MAXROWS = 20;                // max number of rows in the arena
const int MAXCOLS = 20;                // max number of columns in the arena
const int MAXVAMPIRES = 100;           // max number of vampires allowed

const int NORTH = 0;
const int EAST  = 1;
const int SOUTH = 2;
const int WEST  = 3;
const int NUMDIRS = 4;

const int EMPTY      = 0;
const int HAS_POISON = 1;
const int DUMB_MOVE = 1000;

///////////////////////////////////////////////////////////////////////////
// Type definitions
///////////////////////////////////////////////////////////////////////////

class Arena;  // This is needed to let the compiler know that Arena is a
              // type name, since it's mentioned in the Vampire declaration.

class Vampire
{
  public:
      // Constructor
    Vampire(Arena* ap, int r, int c);

      // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;

      // Mutators
    void move();

  private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    int    m_poisoned;
    bool   m_turnSkipped;
};

class Player
{
  public:
      // Constructor
    Player(Arena* ap, int r, int c);

      // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;

      // Mutators
    string dropPoisonVial();
    string move(int dir);
    void   setDead();

  private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    bool   m_dead;
};

class Arena
{
  public:
      // Constructor/destructor
    Arena(int nRows, int nCols);
    ~Arena();

      // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     vampireCount() const;
    int     getCellStatus(int r, int c) const;
    int     numberOfVampiresAt(int r, int c) const;
    void    display(string msg) const;

      // Mutators
    void setCellStatus(int r, int c, int status);
    bool addVampire(int r, int c);
    bool addPlayer(int r, int c);
    void moveVampires();

  private:
    int      m_grid[MAXROWS][MAXCOLS];
    int      m_rows;
    int      m_cols;
    Player*  m_player;
    Vampire* m_vampires[MAXVAMPIRES];
    int      m_nVampires;
    int      m_turns;
    
    //the number of vampires to have ever been created
    // differs from m_nVampires because m_nVampires is the current count of living vampires
    int      m_totalVampires;
    
      // Helper functions
    void checkPos(int r, int c, string functionName) const;
    bool isPosInBounds(int r, int c) const;
};

class Game
{
  public:
      // Constructor/destructor
    Game(int rows, int cols, int nVampires);
    ~Game();

      // Mutators
    void play();

  private:
    Arena* m_arena;

      // Helper functions
    string takePlayerTurn();
};

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

int randInt(int lowest, int highest);
bool decodeDirection(char ch, int& dir);
bool attemptMove(const Arena& a, int dir, int& r, int& c);
bool recommendMove(const Arena& a, int r, int c, int& bestDir);
void clearScreen();

    // these are helper functions when using recommendMove
bool canMoveUp(int r);
bool canMoveDown(const Arena& a, int r);
bool canMoveLeft(int c);
bool canMoveRight(const Arena& a, int c);
int calculateThreat(const Arena& a, int r, int c);

///////////////////////////////////////////////////////////////////////////
//  Vampire implementation
///////////////////////////////////////////////////////////////////////////

Vampire::Vampire(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "***** A vampire must be created in some Arena!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols())
    {
        cout << "***** Vampire created with invalid coordinates (" << r << ","
             << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_poisoned = 0;
    m_turnSkipped = false;
}

int Vampire::row() const
{
    return m_row;
}

int Vampire::col() const
{
    return m_col;
}

bool Vampire::isDead() const
{
    // returns true is vampire has been poisoned twice
    if (m_poisoned == 2)
        return true;
    else
        return false;
}

void Vampire::move()
{
    // if the vampire has been poisoned once and the turn has not been skpped yet, skip the turn.
    if (m_poisoned == 1 && !m_turnSkipped)
    {
        m_turnSkipped = true;
        return;
    }
  
    // if the vampire has not been poisoned yet or has been poisoned and previously skipped a turn
    // attempt to move in a random direction
    else if (m_poisoned == 0 || (m_poisoned == 1 && m_turnSkipped))
    {
        m_turnSkipped = false;
        int randDir = randInt(NORTH, WEST);
        if (attemptMove(*m_arena, randDir, m_row, m_col))
        {
            // if vampire lands on poison, increment poison count
            // set grid point to empty to show vampire has used the poison
            if (m_arena->getCellStatus(m_row, m_col) == HAS_POISON)
            {
                m_poisoned++;
                m_arena->setCellStatus(m_row, m_col, EMPTY);
            }
        }
    }
    else
        return;
}

///////////////////////////////////////////////////////////////////////////
//  Player implementation
///////////////////////////////////////////////////////////////////////////

Player::Player(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "***** The player must be created in some Arena!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
             << "," << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_dead = false;
}

int Player::row() const
{
    return m_row;
}

int Player::col() const
{
    return m_col;
}

string Player::dropPoisonVial()
{
    if (m_arena->getCellStatus(m_row, m_col) == HAS_POISON)
        return "There's already a poisoned blood vial at this spot.";
    m_arena->setCellStatus(m_row, m_col, HAS_POISON);
    return "A poisoned blood vial has been dropped.";
}

string Player::move(int dir)
{
    switch(dir)
    {
        // if direction is North and the row is greater than 1, decrement row
        case NORTH:
            if (row() > 1)
            {
                m_row --;
                // if there are vampire(s) at this location, player dies
                if (m_arena->numberOfVampiresAt(m_row, m_col) > 0)
                {
                    setDead();
                    return "Player walked into a vampire and died.";
                }
                // otherwise, move was succesful
                return "Player moved north.";
            }
            // if moving north is out of bounds, player does not move
            return "Player couldn't move; player stands.";
            break;
            
        // if direction is South and the row is less than the total amount of rows, increment row
        case SOUTH:
            if (row() < m_arena->rows())
            {
                m_row++;
                // if there are vampire(s) at this location, player dies
                 if (m_arena->numberOfVampiresAt(m_row, m_col) > 0)
                {
                    setDead();
                    return "Player walked into a vampire and died.";
                }
                // otherwise, move was succesful
                return "Player moved south.";
            }
            // if moving south is out of bounds, player does not move
            return "Player couldn't move; player stands.";
            break;
            
        // if direction is east and the col is less than the total amount of cols, increment col
        case EAST:
            if (col() < m_arena->cols())
            {
                m_col++;
                // if there are vampire(s) at this location, player dies
                if (m_arena->numberOfVampiresAt(m_row, m_col) > 0)
                {
                    setDead();
                    return "Player walked into a vampire and died.";
                }
                // otherwise, move was successful
                return "Player moved east.";
            }
            // if moving east is out of bounds, player does not move
            return "Player couldn't move; player stands.";
            break;
            
        // if direction is west and the col is greater than 1, decrement col
        case WEST:
            if(col() > 1)
            {
                m_col--;
                // if there are vampire(s) at this location, player dies
                if (m_arena->numberOfVampiresAt(m_row, m_col) > 0)
                {
                    setDead();
                    return "Player walked into a vampire and died.";
                }
                // otherwise, move was successful
                return "Player moved west.";
            }
            // if moving west is out of bounds, player does not move
            return "Player couldn't move; player stands.";
            break;
            
        default:
            return "Player couldn't move; player stands.";
            
    }
        
}

bool Player::isDead() const
{
    return m_dead;
}

void Player::setDead()
{
    m_dead = true;
}

///////////////////////////////////////////////////////////////////////////
//  Arena implementation
///////////////////////////////////////////////////////////////////////////

Arena::Arena(int nRows, int nCols)
{
    if (nRows <= 0  ||  nCols <= 0  ||  nRows > MAXROWS  ||  nCols > MAXCOLS)
    {
        cout << "***** Arena created with invalid size " << nRows << " by "
             << nCols << "!" << endl;
        exit(1);
    }
    m_rows = nRows;
    m_cols = nCols;
    m_player = nullptr;
    m_nVampires = 0;
    m_totalVampires = 0;
    m_turns = 0;
    for (int r = 1; r <= m_rows; r++)
        for (int c = 1; c <= m_cols; c++)
            setCellStatus(r, c, EMPTY);

    // initialize all vampires in array to nullptr
    for (int i = 0; i < MAXVAMPIRES; i++)
        m_vampires[i] = nullptr;
}

Arena::~Arena()
{
    //Deallocate the player and all remaining dynamically allocated vampires.
    delete m_player;
    for (int i = 0; i < MAXVAMPIRES; i++)
        delete m_vampires[i];
}

int Arena::rows() const
{
    return m_rows;
}

int Arena::cols() const
{
    return m_cols;
}

Player* Arena::player() const
{
    return m_player;
}

int Arena::vampireCount() const
{
    return m_nVampires;
}

int Arena::getCellStatus(int r, int c) const
{
    checkPos(r, c, "Arena::getCellStatus");
    return m_grid[r-1][c-1];
}

int Arena::numberOfVampiresAt(int r, int c) const
{
    int vCount = 0;
    
    // iterate through array of vampires
    for (int i = 0; i < MAXVAMPIRES; i++)
    {
        // if object at array of vampires is a Vampire object (not null)
        // and it has the same row and column as the parameter, increment count
        if (m_vampires[i] != nullptr && m_vampires[i]->row() == r && m_vampires[i]->col() == c)
            vCount++;
    }
    return vCount;
}

void Arena::display(string msg) const
{
    char displayGrid[MAXROWS][MAXCOLS];
    int r, c;
    
      // Fill displayGrid with dots (empty) and stars (poisoned blood vials)
    for (r = 1; r <= rows(); r++)
        for (c = 1; c <= cols(); c++)
            displayGrid[r-1][c-1] = (getCellStatus(r,c) == EMPTY ? '.' : '*');

      // Indicate each vampire's position
    for (r = 1; r <= rows(); r++)
    {
        for (c = 1; c <= cols(); c++)
        {
            // if a single vampire exists at grid point,
            // print out 'V' on the display grid
            if (numberOfVampiresAt(r, c) == 1)
                displayGrid[r-1][c-1] = 'V';
            
            // if more than one but less than 9 vampires exist at grid point,
            // print out converted character on the display grid
            else if (numberOfVampiresAt(r, c) > 1 && numberOfVampiresAt(r, c) < 9)
                displayGrid[r-1][c-1] = numberOfVampiresAt(r, c) + '0';
            
            // if 9 or more vampires exist at grid point,
            // print out only 9 on display grid
            else if (numberOfVampiresAt(r, c) >= 9)
                displayGrid[r-1][c-1] = '9';
        }
    }
    
      // Indicate player's position
    if (m_player != nullptr)
        displayGrid[m_player->row()-1][m_player->col()-1] = (m_player->isDead() ? 'X' : '@');

      // Draw the grid
    clearScreen();
    for (r = 1; r <= rows(); r++)
    {
        for (c = 1; c <= cols(); c++)
            cout << displayGrid[r-1][c-1];
        cout << endl;
    }
    cout << endl;

      // Write message, vampire, and player info
    if (msg != "")
        cout << msg << endl;
    cout << "There are " << vampireCount() << " vampires remaining." << endl;
    if (m_player == nullptr)
        cout << "There is no player!" << endl;
    else if (m_player->isDead())
        cout << "The player is dead." << endl;
    cout << m_turns << " turns have been taken." << endl;
}

void Arena::setCellStatus(int r, int c, int status)
{
    checkPos(r, c, "Arena::setCellStatus");
    m_grid[r-1][c-1] = status;
}

bool Arena::addVampire(int r, int c)
{
    if (! isPosInBounds(r, c))
        return false;

      // Don't add a vampire on a spot with a poisoned blood vial
    if (getCellStatus(r, c) != EMPTY)
        return false;

      // Don't add a vampire on a spot with a player
    if (m_player != nullptr  &&  m_player->row() == r  &&  m_player->col() == c)
        return false;

      // If there are MAXVAMPIRES existing vampires, return false.  Otherwise,
      // dynamically allocate a new vampire at coordinates (r,c).  Save the
      // pointer to newly allocated vampire and return true.
    if (m_nVampires == MAXVAMPIRES)
        return false;
    
    else
    {
        // add new vampire where there is the first nullptr (empty space)
        for (int i = 0; i < MAXVAMPIRES; i++)
        {
            if (m_vampires[i] == nullptr)
            {
                // dynamically allocate new vampire object
                m_vampires[i] = new Vampire(this, r, c);
                m_nVampires++;
                m_totalVampires++;
                return true;
            }
        }
        return false;
    }
}

bool Arena::addPlayer(int r, int c)
{
    if (! isPosInBounds(r, c))
        return false;

      // Don't add a player if one already exists
    if (m_player != nullptr)
        return false;

      // Don't add a player on a spot with a vampire
    if (numberOfVampiresAt(r, c) > 0)
        return false;

    // add new player into this arena
    m_player = new Player(this, r, c);
    return true;
}

void Arena::moveVampires()
{
    // Move all vampires
    for (int i = 0; i < m_totalVampires; i++)
    {
        if (m_vampires[i] != nullptr)
        {
            m_vampires[i]->move();
            // if vampire lands on grid point with both poisoned blood vial and player,
            // it drinks the vial and just before it dies, it kills the player
            // make sure to kill player first, then drink vial
            if (m_vampires[i]->row() == player()->row() && m_vampires[i]->col() == player()->col())
                player()->setDead();
     
            if (m_vampires[i]->isDead())
            {
                // deallocate dead dynamically allocated vampire
                delete m_vampires[i];
                m_vampires[i] = nullptr;
                m_nVampires--;
                
            }
        }
    }
    // Another turn has been taken
    m_turns++;
}

bool Arena::isPosInBounds(int r, int c) const
{
    return (r >= 1  &&  r <= m_rows  &&  c >= 1  &&  c <= m_cols);
}

void Arena::checkPos(int r, int c, string functionName) const
{
    if (r < 1  ||  r > m_rows  ||  c < 1  ||  c > m_cols)
    {
        cout << "***** " << "Invalid arena position (" << r << ","
             << c << ") in call to " << functionName << endl;
        exit(1);
    }
}

///////////////////////////////////////////////////////////////////////////
//  Game implementation
///////////////////////////////////////////////////////////////////////////

Game::Game(int rows, int cols, int nVampires)
{
    if (nVampires < 0)
    {
        cout << "***** Cannot create Game with negative number of vampires!" << endl;
        exit(1);
    }
    if (nVampires > MAXVAMPIRES)
    {
        cout << "***** Trying to create Game with " << nVampires
             << " vampires; only " << MAXVAMPIRES << " are allowed!" << endl;
        exit(1);
    }
    int nEmpty = rows * cols - nVampires - 1;  // 1 for Player
    if (nEmpty < 0)
    {
        cout << "***** Game created with a " << rows << " by "
             << cols << " arena, which is too small too hold a player and "
             << nVampires << " vampires!" << endl;
        exit(1);
    }

      // Create arena
    m_arena = new Arena(rows, cols);

      // Add player
    int rPlayer;
    int cPlayer;
    do
    {
        rPlayer = randInt(1, rows);
        cPlayer = randInt(1, cols);
    } while (m_arena->getCellStatus(rPlayer, cPlayer) != EMPTY);
    m_arena->addPlayer(rPlayer, cPlayer);

      // Populate with vampires
    while (nVampires > 0)
    {
        int r = randInt(1, rows);
        int c = randInt(1, cols);
        if (r == rPlayer && c == cPlayer)
            continue;
        m_arena->addVampire(r, c);
        nVampires--;
    }
}

Game::~Game()
{
    delete m_arena;
}

string Game::takePlayerTurn()
{
    for (;;)
    {
        cout << "Your move (n/e/s/w/x or nothing): ";
        string playerMove;
        getline(cin, playerMove);

        Player* player = m_arena->player();
        int dir;

        if (playerMove.size() == 0)
        {
            if (recommendMove(*m_arena, player->row(), player->col(), dir))
                return player->move(dir);
            else
                return player->dropPoisonVial();
        }
        else if (playerMove.size() == 1)
        {
            if (tolower(playerMove[0]) == 'x')
                return player->dropPoisonVial();
            else if (decodeDirection(playerMove[0], dir))
                return player->move(dir);
        }
        cout << "Player move must be nothing, or 1 character n/e/s/w/x." << endl;
    }
}

void Game::play()
{
    m_arena->display("");
    Player* player = m_arena->player();
    if (player == nullptr)
        return;
    while ( ! player->isDead()  &&  m_arena->vampireCount() > 0)
    {
        string msg = takePlayerTurn();
        m_arena->display(msg);
        if (player->isDead())
            break;
        m_arena->moveVampires();
        m_arena->display(msg);
    }
    if (player->isDead())
        cout << "You lose." << endl;
    else
        cout << "You win." << endl;
}

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function implementation
///////////////////////////////////////////////////////////////////////////

  // Return a uniformly distributed random int from lowest to highest, inclusive
int randInt(int lowest, int highest)
{
    if (highest < lowest)
        swap(highest, lowest);
    static random_device rd;
    static default_random_engine generator(rd());
    uniform_int_distribution<> distro(lowest, highest);
    return distro(generator);
}

bool decodeDirection(char ch, int& dir)
{
    switch (tolower(ch))
    {
      default:  return false;
      case 'n': dir = NORTH; break;
      case 'e': dir = EAST;  break;
      case 's': dir = SOUTH; break;
      case 'w': dir = WEST;  break;
    }
    return true;
}

  // Return false without changing anything if moving one step from (r,c)
  // in the indicated direction would run off the edge of the arena.
  // Otherwise, update r and c to the position resulting from the move and
  // return true.
bool attemptMove(const Arena& a, int dir, int& r, int& c)
{
    if (dir == NORTH)
    {
        if(r <= 1)
            return false;
    
        else
        {
            r--;
            return true;
        }
    }
    
    else if (dir == SOUTH)
    {
        if (r >= a.rows())
            return false;
        
        else
        {
            r++;
            return true;
        }
    }
    
    else if (dir == EAST)
    {
        if (c >= a.cols())
            return false;
        
        else
        {
            c++;
            return true;
        }
    }
    
    else if (dir == WEST)
    {
        if (c <= 1)
            return false;
        
        else
        {
            c--;
            return true;
        }
    }
    else
        return false;
}

// determines if moving up is within bounds
bool canMoveUp(int r)
{
    if (r <= 1)
        return false;
    else
        return true;
}

// determines if moving down is within bounds
bool canMoveDown(const Arena& a, int r)
{
    if (r >= a.rows())
        return false;
    else
        return true;
}

// determines if moving left is within bounds
bool canMoveLeft(int c)
{
    if (c <= 1)
        return false;
    else
        return true;
}

// determines if moving right is within bounds
bool canMoveRight(const Arena& a, int c)
{
    if (c >= a.cols())
        return false;
    else
        return true;
}

// calculates the danger level of surrounding vampires at point (r, c)
int calculateThreat(const Arena& a, int r, int c)
{
    int threat = 0;
    if (a.numberOfVampiresAt(r, c) > 0)
        threat+= DUMB_MOVE;
    if (canMoveUp(r) && a.numberOfVampiresAt(r-1, c) > 0)
        threat += a.numberOfVampiresAt(r-1, c);
    if (canMoveDown(a, r) && a.numberOfVampiresAt(r+1, c) > 0)
        threat += a.numberOfVampiresAt(r+1, c);
    if (canMoveLeft(c) && a.numberOfVampiresAt(r, c-1) > 0)
        threat += a.numberOfVampiresAt(r, c-1);
    if (canMoveRight(a, c) && a.numberOfVampiresAt(r, c+1) > 0)
        threat += a.numberOfVampiresAt(r, c+1);
    return threat;
}

  // Recommend a move for a player at (r,c):  A false return means the
  // recommendation is that the player should drop a poisoned blood vial and
  // not move; otherwise, this function sets bestDir to the recommended
  // direction to move and returns true.
bool recommendMove(const Arena& a, int r, int c, int& bestDir)
{
    int currentDanger = calculateThreat(a, r, c);
    int rightDanger;
    int leftDanger;
    int upDanger;
    int downDanger;
  
    // calculate the danger levels of each direction
    if (canMoveRight(a, c))
        rightDanger = calculateThreat(a, r, c+1);
    else
        rightDanger = DUMB_MOVE;
    
    if (canMoveLeft(c))
        leftDanger = calculateThreat(a, r, c-1);
    else
        leftDanger = DUMB_MOVE;
    
    if (canMoveUp(r))
        upDanger = calculateThreat(a, r-1, c);
    else
        upDanger = DUMB_MOVE;
    
    if (canMoveDown(a, r))
        downDanger = calculateThreat(a, r+1, c);
    else
        downDanger = DUMB_MOVE;
    
    // if it is not dangerous in all directions, stay in spot and drop vial
    if (rightDanger == 0 && leftDanger == 0 && upDanger == 0 && downDanger == 0 && currentDanger == 0)
        return false;
    
    // make an array of the danger levels and iterate through them to find the minimum danger level direction
    int dangers[] = {currentDanger, upDanger, downDanger, leftDanger, rightDanger};
    int min = dangers[1];
    for (int i = 0; i < NUMDIRS + 1; i++)
    {
        if (dangers[i] < min)
            min = dangers[i];
    }
    
    // compare all dangers and set the smallest danger equal to the safetest direction and return respective boolean
    if (min == rightDanger)
    {
        bestDir = EAST;
        return true;
    }
    
    else if (min == leftDanger)
    {
        bestDir = WEST;
        return true;
    }
    
    else if (min == upDanger)
    {
        bestDir = NORTH;
        return true;
    }
    
    else if (min == downDanger)
    {
        bestDir = SOUTH;
        return true;
    }
    
    else
        return false;
    
}

///////////////////////////////////////////////////////////////////////////
// main()
///////////////////////////////////////////////////////////////////////////

int main()
{
      // Create a game
      // Use this instead to create a mini-game:
      //Game g(3, 5, 2);
   Game g(10, 12, 40);

      // Play the game
    g.play();
}

///////////////////////////////////////////////////////////////////////////
//  clearScreen implementation
///////////////////////////////////////////////////////////////////////////

// DO NOT MODIFY OR REMOVE ANY CODE BETWEEN HERE AND THE END OF THE FILE!!!
// THE CODE IS SUITABLE FOR VISUAL C++, XCODE, AND g++/g31 UNDER LINUX.

// Note to Xcode users:  clearScreen() will just write a newline instead
// of clearing the window if you launch your program from within Xcode.
// That's acceptable.  (The Xcode output window doesn't have the capability
// of being cleared.)

#ifdef _MSC_VER  //  Microsoft Visual C++

#pragma warning(disable : 4005)
#include <windows.h>

void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD upperLeft = { 0, 0 };
    DWORD dwCharsWritten;
    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
                                                        &dwCharsWritten);
    SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // not Microsoft Visual C++, so assume UNIX interface

#include <iostream>
#include <cstring>
#include <cstdlib>

void clearScreen()  // will just write a newline in an Xcode output window
{
    static const char* term = getenv("TERM");
    if (term == nullptr  ||  strcmp(term, "dumb") == 0)
        cout << endl;
    else
    {
        static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
        cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
    }
}

#endif
