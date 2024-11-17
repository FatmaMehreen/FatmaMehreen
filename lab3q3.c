#include <stdio.h> 
#include <string.h> // Library for string functions
#include <stdlib.h> 

#define NUM_TEAMS 10 // Maximum number of teams that can be enrolled
#define SQUAD_SIZE 10 // Maximum number of players in  team

// Structure to store DOB
typedef struct {
    int day, month, year; // Day, month, and year 
} age;

// Structure to store player details
typedef struct {
    char name[25], club[20], position[30]; // Player name, club name, and position
    int kitnumber; // Kit number of  player
    age dob; // Date of birth of the player
} player_t;

// Structure to store team details
typedef struct {
    char name[40]; // Team name
    player_t players[SQUAD_SIZE]; // Array of players in the team
    int size; // Current number of players in the team
} Team;

// Array to hold all teams
Team teams[NUM_TEAMS];
int num_teams = 0; // Count number of teams 

// Function prototypes
void display_menu(); 
void enroll_club(); 
void add_player(); 
void search_update(); 
void display_club_statistics(); 
void handle_error(); 

int main() {
    int choice; //store user choice
    while (1) { // Infinite loop to display menu
        display_menu(); 
        
        printf("Enter choice: ");
        scanf("%d", &choice);

     // select and go to those functions according to user choice
    if (choice == 1) {
        enroll_club(); // Enroll a new club
    } else if (choice == 2) {
        add_player(); // Add a player to an existing club
    } else if (choice == 3) {
        search_update(); // Search and update player information
    } else if (choice == 4) {
        display_club_statistics(); // Display statistics of a club
    } else {
        handle_error(); //  invalid input
        exit(0); // Exit the program
    }
    }
    return 0; 
}



// Display  main menu
void display_menu() {

    printf("\n  League Team Application  \n");
    printf("1. Enroll a new club\n");
    printf("2. Add a player to a club\n");
    printf("3. Search and update player\n");
    printf("4. Display club statistics\n");
    printf("Other: Exit\n"); 
}



// Function to enroll a new club
void enroll_club() {
    if (num_teams >= NUM_TEAMS) { // Check if maximum number of teams has been reached
        handle_error("sorry. Maximum clubs reached."); //if limit is reached
        return; 
    }
    getchar(); //clear input buffer
    printf("Enter club name: ");
    fgets(teams[num_teams].name, sizeof(teams[num_teams].name), stdin); //read club name
    teams[num_teams].name[strcspn(teams[num_teams].name, "\n")] = '\0'; // remove newline character
    teams[num_teams].size = 0; // Initialize number of players to 0
    num_teams++; // Increment number of teams
    printf("Club enrolled!!!.\n"); 
}



// Function to add a player to a club
void add_player() {
    int club_index;
    printf("Available clubs:\n");
    for (int i = 0; i < num_teams; i++) { // Loop to display all available clubs
        printf("%d. %s\n", i + 1, teams[i].name); // Display club index and name
    }
    printf("Select a club: ");
    scanf("%d", &club_index); // Read user choice
    club_index--;

    // Validate club selection and check if the club is full
    if (club_index < 0 || club_index >= num_teams || teams[club_index].size >= SQUAD_SIZE) {
        handle_error(); // Display error
        return;
    }

    // Read player details
    getchar(); // Clear the input buffer
    printf("Enter player's full name: ");
    fgets(teams[club_index].players[teams[club_index].size].name, sizeof(teams[club_index].players[teams[club_index].size].name), stdin);
    teams[club_index].players[teams[club_index].size].name[strcspn(teams[club_index].players[teams[club_index].size].name, "\n")] = '\0'; // Remove newline character

    if (strlen(teams[club_index].players[teams[club_index].size].name) == 0) { // Check if the name is empty
        handle_error(); // call error function
        return; 
    }

    // Read kit number
    printf("Enter kit number (1-99): ");
    scanf("%d", &teams[club_index].players[teams[club_index].size].kitnumber);

    // Read dob
    printf("Enter birth date (dd mm yyyy): ");
    scanf("%d %d %d", &teams[club_index].players[teams[club_index].size].dob.day, 
                      &teams[club_index].players[teams[club_index].size].dob.month, 
                      &teams[club_index].players[teams[club_index].size].dob.year);

    getchar(); // Clear input buffer
    // Read player position
    printf("Enter position: ");
    fgets(teams[club_index].players[teams[club_index].size].position, sizeof(teams[club_index].players[teams[club_index].size].position), stdin);
    teams[club_index].players[teams[club_index].size].position[strcspn(teams[club_index].players[teams[club_index].size].position, "\n")] = '\0'; // Remove newline character

    if (strlen(teams[club_index].players[teams[club_index].size].position) == 0) { // Check if position is empty
        handle_error(); // go to error function
        return; 
    }

    // Check for duplicate player names or kit numbers
    for (int i = 0; i < teams[club_index].size; i++) {
        if (strcmp(teams[club_index].players[i].name, teams[club_index].players[teams[club_index].size].name) == 0 ||
            teams[club_index].players[i].kitnumber == teams[club_index].players[teams[club_index].size].kitnumber) {
            handle_error(); 
            return; 
        }
    }

    teams[club_index].size++; // Increment number of players in the team
    printf("Player added\n"); // display message
}




// Function to search and update player information
void search_update() {
    char search_name[30]; // Buffer for searching
    int found = 0; // Flag to indicate if a player was found

    getchar(); 
    printf("Enter player name or kit number to search: ");
    fgets(search_name, sizeof(search_name), stdin); // Read search input
    search_name[strcspn(search_name, "\n")] = '\0'; // Remove newline character

    for (int i = 0; i < num_teams; i++) { // Loop through all teams
        for (int j = 0; j < teams[i].size; j++) { // Loop through players in each team
            if (strcasecmp(teams[i].players[j].name, search_name) == 0 ||
                teams[i].players[j].kitnumber == atoi(search_name)) { // Check for match
                printf("Player found: %s, Kit: %d, Position: %s\n", 
                        teams[i].players[j].name, teams[i].players[j].kitnumber, 
                        teams[i].players[j].position);

                // Prompt to update the player's name
                getchar(); // Clear input buffer
                printf("Enter new player name (or press Enter to keep current): ");
                char new_name[30];
                fgets(new_name, sizeof(new_name), stdin);
                new_name[strcspn(new_name, "\n")] = '\0';
                if (strlen(new_name) > 0) {
                    strcpy(teams[i].players[j].name, new_name);
                }

                // Prompt to update the kit number
                printf("Enter new kit number (or 0 to keep current): ");
                int new_kit;
                scanf("%d", &new_kit);
                if (new_kit != 0) {
                    teams[i].players[j].kitnumber = new_kit;
                }

                // Prompt to update the date of birth
                printf("Enter new birth date (dd mm yyyy, or 0 0 0 to keep current): ");
                int new_day, new_month, new_year;
                scanf("%d %d %d", &new_day, &new_month, &new_year);
                if (new_day != 0 && new_month != 0 && new_year != 0) {
                    teams[i].players[j].dob.day = new_day;
                    teams[i].players[j].dob.month = new_month;
                    teams[i].players[j].dob.year = new_year;
                }

                // Prompt to update the position
                getchar(); // Clear input buffer
                printf("Enter new position (or press Enter to keep current): ");
                char new_position[20];
                fgets(new_position, sizeof(new_position), stdin);
                new_position[strcspn(new_position, "\n")] = '\0';
                if (strlen(new_position) > 0) {
                    strcpy(teams[i].players[j].position, new_position);
                }

                printf("Updated.\n"); // Confirmation message
                found = 1; // Set flag to indicate success
                return; 
            }
        }
    }

    if (!found) { // If no player was found
        handle_error("Player not found."); // Display error
    }
}


// Function to display club statistics
void display_club_statistics() {
    // Loop through each team
    for (int i = 0; i < num_teams; i++) {
        // Print name of current club
        printf("\nClub: %s\n", teams[i].name);
        // Print the number of players 
        printf("Players: %d\n", teams[i].size);
        
        int total_age = 0; // Variable to hold the sum of players' ages for average calculation

        // Loop through each player in the current team
        for (int j = 0; j < teams[i].size; j++) {
            // Calculate the age of the player by subtracting the birth year from the current year (2024)
            int age = 2024 - teams[i].players[j].dob.year;
            // Add the player's age to the total age for average calculation
            total_age += age;
            
            // Print the player's details: name, kit number, position, and age
            printf("Player: %s, Kit: %d, Position: %s, Age: %d\n",
                    teams[i].players[j].name, teams[i].players[j].kitnumber,
                    teams[i].players[j].position, age);
        }

        // Check if the club has any players
        if (teams[i].size > 0) {
            // Print the average age
            printf("Average age: %.2f\n", (float)total_age / teams[i].size);
        } else {
            // Print a message if there are no players in the club
            printf("No player enrolled.\n");
        }
    }
}



// Function to handle errors and print an error message
void handle_error() {
    printf("Error!! \n");// display error message
}
