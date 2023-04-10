#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

// maximum length of string
#define MAX_LENGTH 100
// maximum power of players
#define MAX_POWER 1000
// minimal value
#define MIN(ARG1, ARG2) (ARG1) < (ARG2) ? (ARG1) : (ARG2)

/**
 * Function that throws an error and closes files
 * @param fileIn Pointer to input file
 * @param fileOut Pointer to output file
*/
void error(FILE *fileIn, FILE *fileOut) {
    fclose(fileIn);
    fclose(fileOut);

    fileOut = fopen("output.txt", "w");
    fprintf(fileOut, "Invalid inputs\n");
    exit(0);
}


/**
 * Function that splits a string by symbol, writes it into array and returns amount of elements
 * @param str String that is needed to split
 * @param delim Symbol to split the string
 * @param dest Array where the split string will be
*/
int split(char *str, char *delim, char dest[][100]) {
    char *token = strtok(str, delim);
    int counter = 0;
    while (token != NULL) {
        strcpy(dest[counter++], token);
        token = strtok(NULL, delim);
    }
    return counter;
}

/**
 * Function that trims a string by "\n"
 * @param str String itself
*/
void trim(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

/**
 * Function that checks if there any non-english symbols in string
 * @param s String itself
*/
bool isString(char s[MAX_LENGTH]) {
    int size = (int)strlen(s) - 1;
    for (int i = 0; i < size; i++) {
        char elem = s[i];
        if (!isalpha(elem)) {
            return false;
        }
    }
    return true;
}

/**
 * Function that checks if the string satisfies the condition of name
 * @param s String itself
*/
bool isName(char s[MAX_LENGTH]) {
    int len = (int)strlen(s);
    return isString(s) && isupper(s[0]) && len >= 2 && len <= 20;
}

/**
 * Function that checks if the string contains a number
 * @param s String itself
*/
bool isNumber(char s[MAX_LENGTH]) {
    int size = (int)strlen(s) - 1;
    for (int i = 0; i < size; i++) {
        char elem = s[i];
        if (!isdigit(elem)) {
            return false;
        }
    }
    return true;
}


/**
 * Function that checks if the string contains a boolean
 * @param s String itself
*/
bool isBool(char s[MAX_LENGTH]) {
    return (!strcmp(s, "True\n") || !strcmp(s, "False\n"));
}

/**
 * Function that takes a string with "True" or "False" written and returns bool
 * @param s String itself
*/
void *getBool(char s[MAX_LENGTH]) {
    if (!strcmp(s, "True\n")) return (void *) true;
    if (!strcmp(s, "False\n")) return (void *) false;
    return NULL;
}

/**
 * Function that reads a string and writes it to an int variable and returns if a number is received
 * @param fileIn Pointer to input file
 * @param n Pointer to int value
 */
bool inputNumber(FILE *fileIn, int *n) {
    char s[MAX_LENGTH];
    fgets(s, MAX_LENGTH, fileIn);
    if (!isNumber(s)) return false;

    *n = atoi(s);
    return true;
}

// Structure of player
typedef struct {
    char name[200];
    int teamNumber;
    int power;
    bool visibility;
    bool active;
} Player;

// Structure of Team
typedef struct {
    int number;
    int power;
} Team;

/**
 * Comparator for Team sorting function
 * @param t1 First Team
 * @param t2 Second Team
*/
int teamCmp(void *team1, void *team2) {
    Team t1 = *(Team *) team1;
    Team t2 = *(Team *) team2;
    return t1.power - t2.power;
}

/**
 * Function that returns player by name
 * @param name Name of player to be checked
 * @param playersCount Amount of all players
 * @param players Array with all players
*/
Player *getPlayer(char name[], int playersCount, Player *players) {
    for (Player *p = players; p != players + playersCount; ++p) {
        if (!strcmp(p->name, name)) {
            return p;
        }
    }
    return NULL;
}

/**
 * Function that prints info about player in terminal
 * @param player Player itself
*/
void printPlayer(Player player) {
    printf("%s : Team=%d; power=%d; visibility=%d\n", player.name, player.teamNumber, player.power, player.visibility);
}

/**
 * Function that does attack action
 * @param player1 First player
 * @param player2 Second player
*/
void attack(Player *player1, Player *player2) {
    if (player1->power > player2->power) {
        player1->power = MIN(player1->power + (player1->power - player2->power), MAX_POWER);
        player2->power = 0;
    }
    if (player2->power > player1->power) {
        player2->power = MIN(player2->power + (player2->power - player1->power), MAX_POWER);
        player1->power = 0;
    }
    if (player1->power == player2->power) {
        player1->power = 0;
        player2->power = 0;
    }
}

/**
 * Function that does flip_visibility action
 * @param player First player
*/
void flipVisibility(Player *player) {
    player->visibility = !player->visibility;
}

/**
 * Function that does heal action
 * @param player1 First player
 * @param player2 Second player
*/
void heal(Player *player1, Player *player2) {
    int half = ceil(player1->power / 2.0);
    player1->power = half;
    player2->power = MIN(player2->power + half, MAX_POWER);
}

/**
 * Function that does super action
 * @param player1 First player
 * @param player2 Second player
*/
void super(Player *player1, Player *player2, Player *players, int *playersCount) {
    player1->active = false;
    player2->active = false;
    static int counter = 0;
    char name[100];
    sprintf(name, "S_%d", counter++);
    Player player = {.power = MIN(player1->power + player2->power,
                                  MAX_POWER), .visibility = true, .teamNumber = player1->teamNumber, .active = true};
    strcpy(player.name, name);

    players[(*playersCount)++] = player;

}

/**
 * Function that parses string and does action
 * @param s String that contains action
 * @param players Array with all players
 * @param playersCount Amount of all players
 * @param fileOut File where will be output
*/
void actions(char s[MAX_LENGTH], Player *players, int *playersCount, FILE *fileIn, FILE *fileOut) {
    char strings[3][MAX_LENGTH];
    int actionCount = split(s, " ", strings);

    // Proceeds if action is attack
    if (!strcmp(strings[0], "attack")) {
        if (actionCount != 3) {
            error(fileIn, fileOut);
        }

        Player *player1 = getPlayer(strings[1], *playersCount, players);
        Player *player2 = getPlayer(strings[2], *playersCount, players);

        if (!player1 || !player2) {
            error(fileIn, fileOut);
        }

        if (!player1->visibility) {
            fprintf(fileOut, "This player can't play\n");
            return;
        }


        if (!player1->power) {
            fprintf(fileOut, "This player is frozen\n");
            return;
        }

        if (!player2->visibility) {
            player1->power = 0;
            return;
        }

        attack(player1, player2);
        return;
    }

    // Proceeds if action is flip_visibility
    if (!strcmp(strings[0], "flip_visibility")) {
        if (actionCount != 2) {
            error(fileIn, fileOut);
        }

        Player *player = getPlayer(strings[1], *playersCount, players);

        if (!player) {
            error(fileIn, fileOut);
        }

        if (!player->power) {
            fprintf(fileOut, "This player is frozen\n");
            return;
        }

        flipVisibility(player);
        return;
    }

    // Proceeds if action is heal
    if (!strcmp(strings[0], "heal")) {
        if (actionCount != 3) {
            error(fileIn, fileOut);
        }

        Player *player1 = getPlayer(strings[1], *playersCount, players);
        Player *player2 = getPlayer(strings[2], *playersCount, players);

        if (!player1 || !player2) {
            error(fileIn, fileOut);
        }

        if (!player1->visibility) {
            fprintf(fileOut, "This player can't play\n");
            return;
        }

        if (!player1->power) {
            fprintf(fileOut, "This player is frozen\n");
            return;
        }

        if (player1 == player2) {
            fprintf(fileOut, "The player cannot heal itself\n");
            return;
        }

        if (player1->teamNumber != player2->teamNumber) {
            fprintf(fileOut, "Both players should be from the same team\n");
            return;
        }

        heal(player1, player2);
        return;
    }

    // Proceeds if action is super
    if (!strcmp(strings[0], "super")) {
        if (actionCount != 3) {
            error(fileIn, fileOut);
        }

        Player *player1 = getPlayer(strings[1], *playersCount, players);
        Player *player2 = getPlayer(strings[2], *playersCount, players);

        if (!player1 || !player2) {
            error(fileIn, fileOut);
        }


        if (!player1->visibility) {
            fprintf(fileOut, "This player can't play\n");
            return;
        }

        if (!player1->power) {
            fprintf(fileOut, "This player is frozen\n");
            return;
        }

        if (!strcmp(player1->name, player2->name)) {
            fprintf(fileOut, "The player cannot do super action with itself\n");
            return;
        }

        if (player1->teamNumber != player2->teamNumber) {
            fprintf(fileOut, "Both players should be from the same team\n");
            return;
        }

        super(player1, player2, players, playersCount);
        return;
    }

    // Proceeds if action is wrong
    error(fileIn, fileOut);
}


int main() {
    // Opening files
    FILE *fileIn = fopen("input.txt", "r");
    FILE *fileOut = fopen("output.txt", "w");

    // Checking if file exists
    if (fileIn == NULL)
        error(fileIn, fileOut);

    // Getting number of teams
    int n;
    if (!inputNumber(fileIn, &n) || (n < 1) || (n > 10)) error(fileIn, fileOut);

    // Getting captains
    char captains[n][MAX_LENGTH];
    for (int i = 0; i < n; i++) {
        if (feof(fileIn)) {
            error(fileIn, fileOut);
        }

        fgets(captains[i], MAX_LENGTH, fileIn);
        if (!isString(captains[i]) || !isName(captains[i])) {
            error(fileIn, fileOut);
        }
        trim(captains[i]);
    }

    // Getting number of players
    int m;
    if (!inputNumber(fileIn, &m) || (m < n) || (m > 100)) error(fileIn, fileOut);

    // Getting players
    Player players[m * 2];
    for (int i = 0; i < m; i++) {
        char name[20];
        int teamNumber;
        int power;
        char visibility[10];
        bool visible;

        // Checking if line exists
        if (feof(fileIn)) {
            error(fileIn, fileOut);
        }

        // Getting player's name
        fgets(name, MAX_LENGTH, fileIn);
        trim(name);
        if (!isString(name) || !isName(name)) {
            error(fileIn, fileOut);
        }

        // Getting player's Team number
        if (!inputNumber(fileIn, &teamNumber) || (teamNumber < 0) || (teamNumber >= n)) error(fileIn, fileOut);

        // Getting player's power
        if (!inputNumber(fileIn, &power) || (power < 0) || (power > 1000)) error(fileIn, fileOut);

        // Getting player's visibility
        fgets(visibility, MAX_LENGTH, fileIn);
        if (!isBool(visibility)) {
            error(fileIn, fileOut);
        }
        visible = getBool(visibility);

        // Creating player and adding it to array
        Player player = {.teamNumber = teamNumber, .visibility=visible, .power=power, .active=true};
        strcpy(player.name, name);
        players[i] = player;
    }

    // Getting actions
    char string[MAX_LENGTH];
    int s = 0;
    while (fgets(string, MAX_LENGTH, fileIn) != NULL) {
        s++;
        trim(string);
        actions(string, players, &m, fileIn, fileOut);
    }


    // Checking if amount of actions satisfies the condition
    if (s > 1000) {
        error(fileIn, fileOut);
    }

    // Counting power of each Team
    Team powers[n];
    for (int i = 0; i < n; i++) {
        powers[i].number = i;
        powers[i].power = 0;
    }
    for (int i = 0; i < m; i++) {
        Player player = players[i];
        if (player.active) {
            powers[player.teamNumber].power += player.power;
        }
    }

    // Getting Team with the biggest amount of power
    qsort(powers, n, sizeof(Team), teamCmp);
    if (powers[n - 1].power == powers[n - 2].power) {
        fprintf(fileOut, "It's a tie\n");
    } else {
        fprintf(fileOut, "The chosen wizard is %s\n", captains[powers[n - 1].number]);
    }

    // Closing files
    fclose(fileIn);
    fclose(fileOut);

    return 0;
}

