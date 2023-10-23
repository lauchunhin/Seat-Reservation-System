# Seat Reservation System

This project is a seat reservation system implemented in C++. It uses a bitmap to represent the seats and provides several functions to manipulate and query the state of the seats. Here is a brief description of each function:

1. **Initialize**: This function initializes the bitmap for seat reservation. It takes the number of seats and a reference to the bitmap as input and sets up the initial state of the seats.

2. **Query the current state of a seat**: This function returns the current state of a specific seat. It takes the number of seats, the bitmap, and the index of the seat as input.

3. **Print the bitmap to screen**: This function prints the current state of all seats to the screen. It takes the number of seats and the bitmap as input.

4. **Change the state of a seat to OCCUPIED**: This function sets a specific seat as occupied. It takes the number of seats, a reference to the bitmap, and the index of the seat as input.

5. **Change the state of a seat to EMPTY**: This function sets a specific seat as empty. It takes the number of seats, a reference to the bitmap, and the seat index as input.

6. **Calculate the closest distance from a seat to occupied seats**: This function calculates and returns the distance from a given seat to the nearest occupied centre. It takes the number of seats, the bitmap, and the seat index as input.

7. **Find the empty seat with maximum distance to the closest occupied seat**: This function finds and returns an empty seat that has a maximum distance to any occupied seat. It takes only two parameters: the number of seats and the bitmap.

The program runs in a loop, asking users for an option from 0-7 until they choose to exit by entering 0.

Here is an example output:

```
##################################################
# Printing the current state

00010010

! Returning to main menu.
##################################################
# Main Menu

1 Initialize
2 Query the current state of a seat
3 Print the bitmap to screen
4 Change the state of a seat to OCCUPIED
5 Change the state of a seat to EMPTY
6 Calculate the closest distance from a seat to occupied seats
7 Find the empty seat with maximum distance to closest occupied seat
0 Exit

? Please enter an option (0-7): 6
##################################################
# Calculating the closest distance to occupied seats

? Enter the index of queried seat:2
! The distance to closest occupied seat is 1.
! Returning to main menu.
##################################################
# Main Menu

1 Initialize
2 Query the current state of a seat
3 Print the bitmap to screen
4 Change the state of a seat to OCCUPIED
5 Change the state of a seat to EMPTY
6 Calculate the closest distance from a seat to occupied seats
7 Find the empty seat with maximum distance to closest occupied seat
0 Exit

? Please enter an option (0-7): 7
##################################################
# Finding an empty seat

! The empty seat with maximum distance to closest person is at 0.
! Returning to main menu.
##################################################
```

This project demonstrates how bit manipulation can be used effectively in real-world applications such as this seat reservation system.
