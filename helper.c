#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>


/**
 * Calculates the age at the current date
 * @param bd_d Day of the birthday
 * @param bd_m Month of the birthday
 * @param bd_y Year of the birthday
 * @return Age in years
 */
int calculate_age(int bd_d, int bd_m, int bd_y) {
    // Variables
    time_t current_time;
    int current_month, current_day, age;

    // Get current time
    time(&current_time);

    // Extract month and day
    current_month = gmtime(&current_time)->tm_mon + 1;
    current_day = gmtime(&current_time)->tm_mday;

    // Year difference
    age = gmtime(&current_time)->tm_year + 1900 - bd_y;

    // Reduce age depending on month and day
    age -= current_month < bd_m || current_month == bd_m && current_day < bd_d ? 1 : 0;

    // Return age
    return age;
}


/**
 * Create a random integer between to values
 * @param min Lower boundary
 * @param max Upper boundary
 */
int random(int min, int max) {
    return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}


/**
 * Reads a single char as input. If more is entered in the console, the rest gets ignored
 * @return First entered char
 */
char read_single_char() {
    // Variables
    char c, ct;

    // Read first char
    c = (char) getchar();

    // Read and ignore following chars => clearing keyboard buffer
    while ((ct = (char) getchar()) != '\n' && ct != EOF) {}

    // Return first char
    return c;
}


/**
 * Reads text from the console to string
 * @param str String in which the read content is stored
 * @param max_length Max length of the input. Anything long will be cut.
 */
void read_string_input(char str[], int max_length) {
    // Variables
    char c, ct;
    int i;

    for (i = 0; i < max_length; i++) {
        // Read char
        c = (char) getchar();

        // Return if input is shorter
        if (c == '\n' || c == EOF)
            return;

        str[i] = c;
    }

    // Read and ignore following chars => clearing keyboard buffer
    while ((ct = (char) getchar()) != '\n' && ct != EOF) {}
}


/**
 * Read a positive number from the console. Other, non numeric, characters will be ignored (e.g. -1j2b4 => 124).
 * @param min minimal clipping
 * @param max maximal clipping
 * @return Inputted number
 */
int read_number(int min, int max) {
    // Variables
    int num = 0, i, offset = 0;
    char ct, c;
    char str[20 + 1] = "";

    // Scan number
    for (i = 0; i < 20; i++) {
        // Read char
        c = (char) getchar();

        // Break if input is shorter
        if (c == '\n' || c == EOF)
            break;

        if (isdigit(c) == 0) {
            // NOT a digit
            offset += 1;
        } else {
            // Digit
            str[i - offset] = c;
        }
    }

    // Read and ignore following chars => clearing keyboard buffer
    if (!(c == '\n' || c == EOF))
        while ((ct = (char) getchar()) != '\n' && ct != EOF) {}

    // Convert to int
    num = atoi(str);

    // Clip number to min and max and return
    return num < min ? min : (num > max ? max : num);
}


/**
 * Parses a date string to integer values
 * @param str String in the date-format dd.mm.yyyy
 * @param mode 'd' for the day, 'm' for the month and 'y' for the year
 * @return Number representing the day, month or year
 */
int parse_date_string(char str[], char mode) {
    // Variables
    int i = 0;
    int date[3] = {-1, -1, -1};
    char delimiter[] = ".-/";
    char d[10 + 1] = "";
    char *ptr;

    // Copy string
    strcpy(d, str);

    // Split string and convert to int
    ptr = strtok(d, delimiter);

    while (ptr != NULL) {
        date[i] = atoi(ptr);
        ptr = strtok(NULL, delimiter);
        i++;
    }

    // Validation -----------------------------
    // Day
    if (date[0] > 31 || date[0] < 1) {
        date[0] = -1;
    }

    // Month
    if (date[1] > 12 || date[1] < 1) {
        date[1] = -1;
    }

    // Year
    if (date[2] < 0) {
        date[2] = -1;
    }

    // Return desired number
    switch (mode) {
        case 'd':
            return date[0];
        case 'm':
            return date[1];
        default:
            return date[2];
    }
}


/**
 * Clears console by writing 50 blank lines
 */
void clear_screen() {
    int i;
    for (i = 0; i < 50; ++i) {
        printf("\n");
    }
}


/**
 * Concatenates the current directory with a filename (or path)
 * @param path Combined path
 * @param filename Ending, added to the path
 */
void get_current_directory(char *path, char *filename) {
    // Get current working directory and append filename
    char cwd[PATH_MAX] = "";
    getcwd(cwd, sizeof(cwd));
    strcat(path, cwd);
    strcat(path, "\\");
    strcat(path, filename);
}


/**
 * Creates a string with n names, seperated by \n
 * @param names String that will hold the names
 * @param count Count n of names
 */
void get_names(char names[], int count) {
    // Variables
    char path[PATH_MAX] = "";
    char buffer[100] = "";
    int i;
    FILE *stream;

    // Get current working directory
    get_current_directory(path, "names.txt");

    // Open read stream
    stream = fopen(path, "r");

    if (stream != NULL) {

        // Read n lines and concat names to the array
        for (i = 0; i < count; ++i) {
            fgets(buffer, sizeof(buffer), stream);
            strcat(names, buffer);
        }

        // Close file
        fclose(stream);
    }
}