#include <iostream>
#include <random>
using namespace std;


/****************************
*   Function Declarations   *
****************************/

///   Input Function   ///
char DesiredDecisionPathInput (); // Inputs the desired decision path from the user, either 'A' or 'B'
void Decision ( unsigned&, char ); // Directs the user to the next path based of their input
void PrintDecisionPoint ( unsigned ); // Print's the current decision point

///   New Lab_5 Functions   ///
string DecisionPathOrnamentation ( string, unsigned );
unsigned RandomDecision ();
unsigned EndOrRestart ();


/********************
*   Main Function   *
********************/

int main()
{
    ///   Initialize the Variables   ///
    const unsigned START = 1;
    const unsigned END = 0;
    unsigned currentDecisionPath = START; // When 1 (START), the game starts from the beginning
    bool gameOverCheck = false;

    ///   Welcome Screen   ///
    cout << "Welcome to Choose Your Own Adventure!" << endl;
    cout << "\nPress enter to continue ...";
    cin.get();
    cout << "\n" << endl;

    ///   Beginning   ///
    while ( !gameOverCheck )
    {
        ///   Print the Current Decision Point   ///
        PrintDecisionPoint( currentDecisionPath );

        ///   Function Organizes and Runs the Adventure   ///
        Decision( currentDecisionPath, DesiredDecisionPathInput() ); // This is the default Adventure starting block

        ///   Checks if the End of the Game has been reached   ///
        if ( currentDecisionPath == END ) // 0 (END) will be passed by code when an endpoint has been reached
        {
            gameOverCheck = true; // Tell the while loop to end;
        }
    }

    ///   Game End! Congrats!   ///
    cout << "\nCongratulations! You have reached the end of the adventure!" << endl;

    return 0;
}


/*********************
*   Input Function   *
*********************/

char DesiredDecisionPathInput ()
{
    ///   Initialize Variable(s)   ///
    char decisionPointChoice = '\0';

    ///   Input User Decision   ///
    cout << "Enter 'A', 'B' or 'R': ";
    cin >> decisionPointChoice;

    ///   Failsafe for correct user Input   ///
    while ( cin.fail() || ( decisionPointChoice != 'A' && decisionPointChoice != 'B' && decisionPointChoice != 'R' ) )
    {
        system("clear");
        cout << "Enter 'A', 'B' or 'R': ";
        cin.clear();
        cin.ignore ( 256, '\n' );
        cin >> decisionPointChoice;
    }

    ///   A return of the input and secondary failsafe   ///
    if ( decisionPointChoice == 'A' || decisionPointChoice == 'B' ) // Options A or B
    {
        return decisionPointChoice;
    }
    else if ( decisionPointChoice == 'R' ) // Random Option
    {
        unsigned officialRandomDecision = RandomDecision();
        char randomDecision = '\0';

        if ( officialRandomDecision == 1 )
        {
            randomDecision = 'A';
        }
        else if ( officialRandomDecision == 2 )
        {
            randomDecision = 'B';
        }
        else
        {
            throw invalid_argument ( "An invalid decision path option was passed." );
        }

        return randomDecision;
    }
    else // Catch Exception
    {
        throw invalid_argument ( "An invalid decision path option was passed." );
    }
}


/*****************************
*   Decision Path Function   *
*****************************/

void Decision ( unsigned& currentDecisionPath, char desiredPath )
{
    ///   Initialize Constants   ///
    const unsigned BEFORE = 0;
    const unsigned AFTER = 1;

    ///   Begin Directing to New Decision Paths   ///
    switch ( currentDecisionPath )
    {
        case 1: // Path 1
            if ( desiredPath == 'A' )
            {
                currentDecisionPath = 3; // Updates the Decision Path to Path 3
            }
            else if ( desiredPath == 'B' )
            {
                currentDecisionPath = 2; // Updates the Decision Path to Path 2
            }
            else
            {  // Note, this should never be thrown in this context but is a backup/default for this else statement
                throw invalid_argument ( "An invalid decision path option was passed." );
            }
            break;

        case 2: // Path 2
            if ( desiredPath == 'A' )
            {
                currentDecisionPath = 3; // Updates the Decision Path to Path 3
            }
            else if ( desiredPath == 'B' ) //Ending 1
            {
                cout << "You return safely, but learned nothing new..." << endl;

                currentDecisionPath = EndOrRestart(); // Ends the game (0) or Restart (1)
            }
            else
            {  // Note, this should never be thrown in this context but is a backup/default for this else statement
                throw invalid_argument ( "An invalid decision path option was passed." );
            }
            break;

        case 3: // Path 3
            if ( desiredPath == 'A' )
            {
                ///   Output the Aside state   ///
                cout << "\n" << DecisionPathOrnamentation("You pull a \"Galaxy Quest\", take of your helmet, ", BEFORE) << endl
                     << "and take a deep breath, you're fine. " << endl
                     << DecisionPathOrnamentation("You observe your surroundings.", AFTER);

                ///   Continue   ///
                currentDecisionPath = 4; // Updates the Decision Path to Path 4
            }
            else if ( desiredPath == 'B' )
            {
                currentDecisionPath = 4; // Updates the Decision Path to Path 4
            }
            else
            {  // Note, this should never be thrown in this context but is a backup/default for this else statement
                throw invalid_argument ( "An invalid decision path option was passed." );
            }
            break;

        case 4: // Path 4
            if ( desiredPath == 'A' )
            {
                currentDecisionPath = 5; // Updates the Decision Path to Path 5
            }
            else if ( desiredPath == 'B' ) //Ending 2
            {
                cout << "\nYou take soil samples and return to your pod." << endl
                     << "Today's work is done." << endl;
                currentDecisionPath = EndOrRestart(); // Ends the game (0) or Restart (1)
            }
            else
            {  // Note, this should never be thrown in this context but is a backup/default for this else statement
                throw invalid_argument ( "An invalid decision path option was passed." );
            }
            break;

        case 5: // Path 5
            if ( desiredPath == 'A' ) //Ending 3
            {
                cout << "\nYou try to run, but are caught by the creature and killed." << endl;
                currentDecisionPath = EndOrRestart(); // Ends the game (0) or Restart (1)
            }
            else if ( desiredPath == 'B' ) //Ending 4
            {
                cout << "\nYou find no-where to hide and are caught by the creature and killed." << endl;
                currentDecisionPath = EndOrRestart(); // Ends the game (0) or Restart (1)
            }
            else
            {  // Note, this should never be thrown in this context but is a backup/default for this else statement
                throw invalid_argument ( "An invalid decision path option was passed." );
            }
            break;

        default: // Game Exception
            cout << "\nError: Game ended prematurely by default case on line: " << __LINE__ << endl;
            currentDecisionPath = 0; // Ends the game as a fallback in case of error
            break;
    }
}


/*********************
*   Print Function   *
*********************/

void PrintDecisionPoint ( unsigned currentDecisionPath )
{
    ///   Initialize Constants   ///
    const unsigned BEFORE = 0;
    const unsigned AFTER = 1;

    cout << endl; // adds a space before all Decision Path outputs

    ///   Begin Printing Decision Point Choices   ///
    switch (currentDecisionPath)
    {
        case 1: // Path 1
            ///   Starting Decision Path   ///
            cout << DecisionPathOrnamentation("You land on a distant planet. Do you ", BEFORE) << endl
                 << "A) Leave your pod and explore, " << endl
                 << "B) Look nervously out the window, or " << endl
                 << DecisionPathOrnamentation("R) Random decision.", AFTER) << endl;
            cout << endl;
            break;

        case 2: // Path 2
            cout << DecisionPathOrnamentation( "You see nothing but dirt and rocks outside. Do you ", BEFORE) << endl
                 << "A) Leave your pod and explore, " << endl
                 << "B) Start the engines and return to the space station, or " << endl
                 << DecisionPathOrnamentation("R) Random decision.", AFTER) << endl;
            cout << endl;
            break;

        case 3: // Path 3
            cout << DecisionPathOrnamentation("You venture into the unknown and leave the pod. Do you ", BEFORE) << endl
                 << "A) Take off your helmet to see if you can breathe, " << endl
                 << "B) Leave it on and observe your surrounding, or " << endl
                 << DecisionPathOrnamentation("R) Random decision.", AFTER) << endl;
            cout << endl;
            break;

        case 4: // Path 4
            cout << DecisionPathOrnamentation("You notice a small object moving aways off, Do you ", BEFORE) << endl
                 << "A) Walk towards it, " << endl
                 << "B) Take soil samples, or " << endl
                 << DecisionPathOrnamentation("R) Random decision.", AFTER) << endl;
            cout << endl;
            break;

        case 5: // Path 5
            cout << DecisionPathOrnamentation( "You observe it for a moment, it is small and dense, ", BEFORE) << endl
                 << "seems very much like a moving rock. " << endl
                 << "Then you hear a large creature, coming fast. " << endl
                 << "The small creature quickens it's pace. Do you " << endl
                 << "A) Run, " << endl
                 << "B) Try to hide, or " << endl
                 << DecisionPathOrnamentation("R) Random decision.", AFTER) << endl;
            cout << endl;
            break;

        default:
            cout << "\nError: Game ended prematurely by default case on line: " << __LINE__ << endl;
            break;
    }
}


/*******************************************
*   Decision Path Ornamentation Function   *
*******************************************/

string DecisionPathOrnamentation( string outputString, unsigned beforeOrAfter )
{
    ///   Initialize Constants   ///
    const unsigned BEFORE = 0;
    const unsigned AFTER = 1;

    ///   Text location assignment variable and secondary failsafe   ///
    if ( beforeOrAfter == BEFORE ) // Adds # ornamentation before the text block
    {
        for ( unsigned i = 0; i < outputString.size() - 1; i++ ) //The -1 is to account for the extra space at the end of the strings
        {
            cout << "#";
        }
        cout << endl;

        return outputString;
    }
    else if( beforeOrAfter == AFTER ) // Adds # ornamentation after the text block
    {
        cout << outputString << endl;
        for ( unsigned i = 0; i < outputString.size(); i++ )
        {
            cout << "#";
        }

    }
    else // Catch Exception
    {
        throw invalid_argument ( "An invalid integer option was passed." );
    }

    return "";
}


/*******************************
*   Random Decision Function   *
*******************************/

///   NOTE: We did not use srand(time(0)) and rand().                                         ///
///   Instead we used an improved randomization process/function from the <random> library.   ///
unsigned RandomDecision ()
{
    ///   Use random library to effectively randomize the dice rolls   ///
    random_device rd;
    mt19937 mt(rd());
    uniform_real_distribution<> randomDistribution(1, 3); // Roll between 1 and 2 (exclusive 3)

    return static_cast<unsigned>(randomDistribution(mt));
}


/***********************************
*   End or Restart Game Function   *
***********************************/

unsigned EndOrRestart ()
{
    ///   Initialize Variables   ///
    char endOrRestartDecision = '\0';
    const unsigned RESTART = 1;
    const unsigned END = 0;

    ///   Restart or End Input   ///
    cout << "\n" << "Would you like to play again?" << endl
         << "Enter 'Y' for Yes or 'N' for No: ";
    cin >> endOrRestartDecision;

    ///   Failsafe for correct user Input   ///
    while ( cin.fail() || ( endOrRestartDecision != 'Y' && endOrRestartDecision != 'N' ) )
    {
        cout << "\n" << "Would you like to play again?" << endl
             << "Enter 'Y' for Yes or 'N' for No: ";
        cin.clear();
        cin.ignore ( 256, '\n' );
        cin >> endOrRestartDecision;
    }

    if (endOrRestartDecision == 'Y')
    {
        return RESTART;
    }
    else if (endOrRestartDecision == 'N')
    {
        return END;
    }
    else
    {
        throw invalid_argument ( "An invalid integer option was passed." );
    }
}
