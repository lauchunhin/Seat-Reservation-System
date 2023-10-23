#include <iostream>
#include <limits>
using namespace std;

// Global Constants
const int LONGLONG_SIZE = 64;
const long long ONE = 1;
// End of Global Constants

// Helper Functions
// Returns true if input is in range [low,high]
bool input_inRange(int high, int low, int input){
    return ((high >= input && low <= input)); 
}

// calculate the nth power of base 2
long long base2_power(char num, int exponent){
    long long result = 1;
    int num_value = num - '0';
    while (exponent != 0) {
        result *= 2;
        --exponent;
    }
    return num_value*result;
}


// Initialize the seat reservation system
int initialize(int numSeats, unsigned long long &bitmap)
{
    bitmap = 0;
    if(!input_inRange(LONGLONG_SIZE, 1, numSeats)){
        cout << "Error: Number of seats out of range." << endl;
        return -1;
    }
    else {
        for (int i = 1; i-1 < numSeats; i++){
            char state = ' ';
            cin >> state;
            if (state != '0' && state != '1'){
                cout << "Error: Illegal state input." << endl;
                return -1;
            }
            else{
                bitmap += base2_power(state, numSeats-i);
            }
        }
        return 0;
    }
}

// Query the current state of a seat
int getSeatState(int numSeats, unsigned long long bitmap, int seatIndex)
{
    if (!input_inRange(numSeats-1, 0, seatIndex)){
        return -1;
    }
    else {
        int k = numSeats - seatIndex;
        return (bitmap >> (k - 1) & 1);
    }
}

// Print the bitmap to screen
void printSeats(int numSeats, unsigned long long bitmap)
{
    for (int i = 0; i < numSeats; i++){
        cout << getSeatState(numSeats, bitmap, i);
    }
    cout << endl;
}

// Change the state of a sera to OCCUPIED
int setSeatOccupied(int numSeats, unsigned long long &bitmap, int seatIndex)
{
    if (!input_inRange(numSeats-1, 0, seatIndex)){
        return -1;
    }
    else if (getSeatState(numSeats, bitmap, seatIndex)) {
        return -1;
    }
    else {
        int k = numSeats - seatIndex;
        bitmap |= ONE << (k - 1);
        return 0;
    }
}

// Change the state of a sera to EMPTY
int setSeatEmpty(int numSeats, unsigned long long &bitmap, int seatIndex)
{
    if (!input_inRange(numSeats-1, 0, seatIndex)){
        return -1;
    }
    else if (!getSeatState(numSeats, bitmap, seatIndex)) {
        return -1;
    }
    else {
        int k = numSeats - seatIndex;
        bitmap &= ~(ONE << (k - 1));
        return 0;
    }
}

// Calculate the closest distance from a seat to occupied seats
int getSeatDistance(int numSeats, unsigned long long bitmap, int seatIndex)
{
    if (!input_inRange(numSeats-1, 0, seatIndex)){
        return -1;
    }
    else {
        // the seat is already occupied
        if (getSeatState(numSeats, bitmap, seatIndex)){
            return 0;
        }
        // the seat is empty
        else {
            // Some seats are occupied
            if (bitmap^0){
                bool left_occupied, right_occupied = false;
                int distance_left, distance_right;
                // check if there is occupied seat on the left side
                for (int i = seatIndex - 1; i >= 0 ; i--){
                    if (getSeatState(numSeats, bitmap, i)){
                        left_occupied = true;
                        distance_left = seatIndex - i;
                        break;
                    }
                    else {
                        continue;
                    }
                }
                // check if there is occuupied seat on the right side
                for (int j = seatIndex + 1; j <= numSeats-1 ; j++){
                    if (getSeatState(numSeats, bitmap, j)){
                        right_occupied = true;
                        distance_right = j - seatIndex;
                        break;
                    }
                    else {
                        continue;
                    }
                }
                if (left_occupied && right_occupied){
                    if (distance_left <= distance_right){
                        return distance_left;
                    }
                    else {
                        return distance_right;
                    }
                }
                else if (left_occupied){
                    return distance_left;
                }
                else{
                    return distance_right;
                }
            }
            // no occupied seat on both sides / all empty seats
            else {
                cout << "No seats are occupied." << endl;
                return numSeats;
            }
        }
    }
}

// Find the empty seat with maximum distance to closest occupied seat
int findSeat(int numSeats, unsigned long long bitmap)
{
    int max_distance = 0;
    int max_seat = 0;
    for (int i = 0; i < numSeats; i++){
        if (getSeatDistance(numSeats, bitmap, i) > max_distance){
            max_seat = i;
            max_distance = getSeatDistance(numSeats, bitmap, i);
        }
        else {
            continue;
        }
    }
    return max_seat;
}


void run_init(int &numSeats, unsigned long long &bitmap)
{
    cout << "##################################################" << endl;
    cout << "# Initializing" << endl;
    cout << endl;
    int initResult = 0;
    do
    {
        cout << "? Enter the total number of seats:";
        cin >> numSeats;
        cout << "? Enter the initial state of seats:" << endl;
        initResult = initialize(numSeats, bitmap);
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (initResult < 0);
    cout << "! Initialization succeeded!" << endl;
}

void run_getSeatState(int numSeats, unsigned long long bitmap)
{

    int seatIndex;
    int seatState;
    cout << "##################################################" << endl;
    cout << "# Query the current state of a seat" << endl;
    cout << endl;
    cout << "? Enter the index of queried seat:";
    cin >> seatIndex;
    seatState = getSeatState(numSeats, bitmap, seatIndex);
    if (seatState < 0)
    {
        cout << "! Error: Seat index out of bounds. Query failed." << endl;
    }
    else if (seatState == 0)
    {
        cout << "! The queried seat is empty." << endl;
    }
    else if (seatState == 1)
    {
        cout << "! The queried seat is occupied." << endl;
    }
}

void run_printSeats(int numSeats, unsigned long long bitmap)
{
    cout << "##################################################" << endl;
    cout << "# Printing the current state" << endl;
    cout << endl;
    printSeats(numSeats, bitmap);
    cout << endl;
}

void run_setSeatOccupied(int numSeats, unsigned long long &bitmap)
{

    cout << "##################################################" << endl;
    cout << "# Marking a seat as occupied" << endl;
    cout << endl;
    int seatIndex;
    int result;
    cout << "? Enter the index of target seat:";
    cin >> seatIndex;
    result = setSeatOccupied(numSeats, bitmap, seatIndex);
    if (result < 0)
    {
        cout << "! Error: Failed to set seat state, seat index out of bounds or seat already occupied." << endl;
    }
    else
    {
        cout << "! Seat state set." << endl;
    }
}

void run_setSeatEmpty(int numSeats, unsigned long long &bitmap)
{
    cout << "##################################################" << endl;
    cout << "# Marking a seat as empty" << endl;
    cout << endl;
    int seatIndex;
    int result;
    cout << "? Enter the index of target seat:";
    cin >> seatIndex;
    result = setSeatEmpty(numSeats, bitmap, seatIndex);
    if (result < 0)
    {
        cout << "! Error: Failed to set seat state, seat index out of bounds or seat is already empty." << endl;
    }
    else
    {
        cout << "! Seat state set." << endl;
    }
}

void run_getSeatDist(int numSeats, unsigned long long bitmap)
{
    cout << "##################################################" << endl;
    cout << "# Calculating the closest distance to occupied seats" << endl;
    cout << endl;
    int seatIndex;
    int distance;
    cout << "? Enter the index of queried seat:";
    cin >> seatIndex;
    distance = getSeatDistance(numSeats, bitmap, seatIndex);
    if (distance < 0)
    {
        cout << "! Error: Seat index out of bounds. Query failed." << endl;
    }
    else
    {
        cout << "! The distance to closest occupied seat is " << distance << "." << endl;
    }
}

void run_findSeat(int numSeats, unsigned long long bitmap)
{
    cout << "##################################################" << endl;
    cout << "# Finding an empty seat" << endl;
    cout << endl;
    int seatIndex = findSeat(numSeats, bitmap);
    if (seatIndex == -1)
    {
        cout << "! No empty seats left" << endl;
    }
    else
    {
        cout << "! The empty seat with maximum distance to closest person is at " << seatIndex << "." << endl;
    }
}

void run_option()
{
    int numSeats = 0;
    unsigned long long bitmap = 0;
    int option;
    cout << "==================================================" << endl;
    cout << "= Welcome to COMP2011 PA1 Seat Management System =" << endl;
    cout << "==================================================" << endl;

    run_init(numSeats, bitmap);

    while (true)
    {
        cout << "##################################################" << endl;
        cout << "# Main Menu" << endl;
        cout << endl;
        cout << "1 Initialize" << endl;
        cout << "2 Query the current state of a seat" << endl;
        cout << "3 Print the bitmap to screen" << endl;
        cout << "4 Change the state of a seat to OCCUPIED" << endl;
        cout << "5 Change the state of a seat to EMPTY" << endl;
        cout << "6 Calculate the closest distance from a seat to occupied seats" << endl;
        cout << "7 Find the empty seat with maximum distance to closest occupied seat" << endl;
        cout << "0 Exit" << endl;
        cout << endl;
        cout << "? Please enter an option (0-7): ";
        cin >> option;
        switch (option)
        {
        case 0:
            cout << "! Bye Bye." << endl;
            return;
        case 1:
            run_init(numSeats, bitmap);
            break;
        case 2:
            run_getSeatState(numSeats, bitmap);
            break;
        case 3:
            run_printSeats(numSeats, bitmap);
            break;
        case 4:
            run_setSeatOccupied(numSeats, bitmap);
            break;
        case 5:
            run_setSeatEmpty(numSeats, bitmap);
            break;
        case 6:
            run_getSeatDist(numSeats, bitmap);
            break;
        case 7:
            run_findSeat(numSeats, bitmap);
            break;
        default:
            cout << "Illegal Choice, please try again." << endl;
            break;
        }
        cout << "! Returning to main menu." << endl;
    }
}

int main()
{
    run_option();
    return 0;
}