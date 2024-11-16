#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NUM_TEAMS 10
#define SQUAD_SIZE 5


typedef struct {
    int day, month, year; 
} age;

typedef struct {
    char name[30], club[40], position[30]; 
    int kitnumber; 
    age dob; 
} player_t;

typedef struct {
    char name[40]; 
    player_t players[SQUAD_SIZE]; 
    int size; 
} Team;


Team teams[NUM_TEAMS];
int num_teams = 0; 

// Function prototypes
void display_menu();
void enroll_club();
void add_player();
void search_update();
void display_club_statistics();
void handle_error(const char *msg);

int main() {
    while (1) {
        display_menu();
    }
    return 0;
}

// Display the menu
void display_menu() {
    int choice;
    printf("\n=== Sports Club Management Menu ===\n");
    printf("1. Enroll a new club\n");
    printf("2. Add a player to a club\n");
    printf("3. Search and update player\n");
    printf("4. Display club statistics\n");
    printf("Other: Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1: enroll_club(); break;
        case 2: add_player(); break;
        case 3: search_update(); break;
        case 4: display_club_statistics(); break;
        default: printf("Exiting program.\n"); exit(0);
    }
}

// Enroll new clubs
void enroll_club() {
    if (num_teams >= NUM_TEAMS) {
        handle_error("Maximum clubs reached.");
        return;
    }
    getchar(); 
    printf("Enter club name: ");
    fgets(teams[num_teams].name, sizeof(teams[num_teams].name), stdin);
    teams[num_teams].name[strcspn(teams[num_teams].name, "\n")] = '\0';
    teams[num_teams].size = 0; 
    num_teams++;
    printf("Club enrolled successfully.\n");
}

// Adding a player to the club
void add_player() {
    int club_index;
    printf("Available clubs:\n");
    for (int i = 0; i < num_teams; i++) {
        printf("%d. %s\n", i + 1, teams[i].name);
    }
    printf("Select a club: ");
    scanf("%d", &club_index);
    club_index--; 
    if (club_index < 0 || club_index >= num_teams || teams[club_index].size >= SQUAD_SIZE) {
        handle_error("Invalid club selection or squad is full.");
        return;
    }

    player_t *p = &teams[club_index].players[teams[club_index].size];
    getchar(); 

    
    printf("Enter player's full name: ");
    fgets(p->name, sizeof(p->name), stdin);
    p->name[strcspn(p->name, "\n")] = '\0';

    if (strlen(p->name) == 0) {
        handle_error("Player name cannot be empty.");
        return;
    }

    printf("Enter kit number (1-99): ");
    scanf("%d", &p->kitnumber);

    printf("Enter birth date (dd mm yyyy): ");
    scanf("%d %d %d", &p->dob.day, &p->dob.month, &p->dob.year);

    getchar(); 
    printf("Enter position: ");
    fgets(p->position, sizeof(p->position), stdin);
    p->position[strcspn(p->position, "\n")] = '\0';

    if (strlen(p->position) == 0) {
        handle_error("Position cannot be empty.");
        return;
    }

    // Check for duplicates
    for (int i = 0; i < teams[club_index].size; i++) {
        if (strcmp(teams[club_index].players[i].name, p->name) == 0 ||
            teams[club_index].players[i].kitnumber == p->kitnumber) {
            handle_error("Duplicate player or kit number.");
            return;
        }
    }

    teams[club_index].size++;
    printf("Player added successfully.\n");
}

// Search and update player
void search_update() {
    char search_name[30];
    int found = 0;

    getchar(); 
    printf("Enter player name or kit number to search: ");
    fgets(search_name, sizeof(search_name), stdin);
    search_name[strcspn(search_name, "\n")] = '\0'; // Remove newline

    for (int i = 0; i < num_teams; i++) {
        for (int j = 0; j < teams[i].size; j++) {
            if (strcasecmp(teams[i].players[j].name, search_name) == 0 ||
                teams[i].players[j].kitnumber == atoi(search_name)) {
                printf("Player found: %s, Kit: %d, Position: %s\n", 
                        teams[i].players[j].name, teams[i].players[j].kitnumber, 
                        teams[i].players[j].position);

                printf("Enter new kit number: ");
                scanf("%d", &teams[i].players[j].kitnumber);
                printf("Update successful.\n");
                found = 1;
                return;
            }
        }
    }

    if (!found) {
        handle_error("Player not found.");
    }
}

// Display club statistics
void display_club_statistics() {
    for (int i = 0; i < num_teams; i++) {
        printf("\nClub: %s\n", teams[i].name);
        printf("Players: %d\n", teams[i].size);
        int total_age = 0;

        for (int j = 0; j < teams[i].size; j++) {
            int age = 2024 - teams[i].players[j].dob.year; 
            total_age += age;
            printf("Player: %s, Kit: %d, Position: %s, Age: %d\n", 
                    teams[i].players[j].name, teams[i].players[j].kitnumber, 
                    teams[i].players[j].position, age);
        }

        if (teams[i].size > 0) {
            printf("Average age: %.2f\n", (float)total_age / teams[i].size);
        } else {
            printf("No players enrolled.\n");
        }
    }
}

// Handle errors
void handle_error(const char *msg) {
    printf("Error: %s\n", msg);
}

