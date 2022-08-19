# NOTE
This is a program made for a group university assignment. This is not all my own work, there were two other collaborators.

# Gym Membership Database
Welcome to C-ensus - a C based program designed for reception staff to aid with membership management. 

## Compilation:
In order to compile, use the make file supplied. Simply type `make` into the 
terminal in the root directory. This will compile all the files into object 
files and create a program file named `main.out` in the root directory.

## Execution:
Using the `main.out` file, there are three options:
1. To run the program in 'add member' mode, type:
```
./main.out add
```
2. To run the program in 'edit details' mode, type:
```
./main.out edit
```
3. To see the contents of the encrypted database without any decryption, type:
```
./main.out print_encrypted
```

## Usage:
### `add`:
By design, the add mode doesn't load in the database. In order to use this
mode, select `add member` and enter the member's details. If you wish to view
the entered details again, select `display members`. Finally, in order to save
the details to the database, select `save members`.  

Warning: If the program is exited before the details have been saved, the data
wil be lost.

### `edit`:
This mode allows for member data to be edited, the database first needs to be
loaded in though and this is done through selecting `read database`. After that
the database contents can be displayed, searched, edited, or deleted as needed.
There should be some pre-loaded data in the database upon loading.  

Warning: any changes to the data will not be saved to the database unless the
`save members` option is selected.

### `print_encrypted`:
This mode is purely for use when investigating the functionality of the
program. It simply reads the database and prints the member's data without
decrypting the elements.

