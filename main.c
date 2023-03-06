#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "helper.c"


// Constants
#define SIZE_FIRST_NAME 31          // 30
#define SIZE_LAST_NAME 31           // 30
#define SIZE_BIRTHDAY_STRING 11     // 10 dd.mm.yyyy
#define SIZE_MAIL 101               // 100
#define SIZE_PERSON_STR (SIZE_FIRST_NAME + SIZE_LAST_NAME + SIZE_MAIL + SIZE_BIRTHDAY_STRING + 10)
#define CSV_HEADER "firstName,lastName,mail,bdDay,bdMonth,bdYear\n"


// Global Variables
int measure_mode = 0;       // Additional information gets displayed, if the measure_mode is 1


// Struct
struct person {
    char first_name[SIZE_FIRST_NAME];
    char last_name[SIZE_LAST_NAME];
    char email[SIZE_MAIL];
    int bd_day;
    int bd_month;
    int bd_year;
    int age;

    struct person *next;
    struct person *prev;
};


// ==========================================================
// ===               PERSON-FUNCTIONS                     ===
// ==========================================================


/**
 * Create a person struct on the heap.
 * @param f_name First Name
 * @param l_name Last Name
 * @param mail E-Mail Address
 * @param bd_d Day of the birthday
 * @param bd_m Month of the birthday
 * @param bd_y Year of the birthday
 * @return Pointer to the created person
 */
struct person *person_create(char f_name[], char l_name[], char mail[], int bd_d, int bd_m, int bd_y) {
    // Check for faulty parameters
    if (f_name == NULL || l_name == NULL || mail == NULL)
        return NULL;

    // Allocate space on the heap
    struct person *p = (struct person *) malloc(sizeof(struct person));

    // Initialize list-pointer
    p->next = NULL;
    p->prev = NULL;

    // Copy data
    strcpy(p->first_name, f_name);
    strcpy(p->last_name, l_name);
    strcpy(p->email, mail);
    p->bd_day = bd_d;
    p->bd_month = bd_m;
    p->bd_year = bd_y;

    // Calculate age from birthday
    p->age = calculate_age(bd_d, bd_m, bd_y);

    // Return pointer to memory
    return p;
}


/**
 * Prints person to the console in one line
 * @param p Pointer to the person
 */
void person_print(struct person *p) {
    // Name & Mail
    printf("%s %s (%s)", p->first_name, p->last_name, p->email);

    // Birthday and Age
    printf("\t | %2.i.%2.i.%4.i [%i]", p->bd_day, p->bd_month, p->bd_year, p->age);

    // Pointer if in measure mode
    if (measure_mode == 1)
        printf("\t | PTR: %p - %p\n", p->prev, p->next);
    else
        printf("\n");
}


/**
 * Converts a person to the csv-format (","-seperated)
 * @param str Destination of the csv-format
 * @param p Pointer to the person that should be converted.
 */
void person_csv_line(char str[], struct person *p) {
    // Buffer for integer conversion
    char bd_d_buf[2 + 1] = "";
    char bd_m_buf[2 + 1] = "";
    char bd_y_buf[4 + 1] = "";

    // Convert int to string
    sprintf(bd_d_buf, "%i", p->bd_day);
    sprintf(bd_m_buf, "%i", p->bd_month);
    sprintf(bd_y_buf, "%i", p->bd_year);

    // Concatenate string
    strcat(str, p->first_name);
    strcat(str, ",");

    strcat(str, p->last_name);
    strcat(str, ",");

    strcat(str, p->email);
    strcat(str, ",");

    strcat(str, bd_d_buf);
    strcat(str, ",");

    strcat(str, bd_m_buf);
    strcat(str, ",");

    strcat(str, bd_y_buf);
    strcat(str, "\n");
}


// ==========================================================
// ===                LIST-FUNCTIONALITY                  ===
// ==========================================================


/**
 * Get the first element of a (double) linked list.
 * @param list Pointer to any element of the list.
 * @return Pointer to the first element of the list.
 */
struct person *list_first(struct person *list) {
    // Abort, if list is empty
    if (list == NULL)
        return NULL;

    // Got backwards through the list
    struct person *element = list;
    while (element->prev != NULL) element = element->prev;

    // Return first element
    return element;
}


/**
 * Get the last element of a (double) linked list.
 * @param list Pointer to any element of the list.
 * @return Pointer to the last element of the list.
 */
struct person *list_last(struct person *list) {
    // Abort, if list is empty
    if (list == NULL)
        return NULL;

    // Got forwards through the list
    struct person *element = list;
    while (element->next != NULL) element = element->next;

    // Return last element
    return element;
}


/**
 * Get the number of elements, stored in a (double) linked list.
 * @param list Pointer to any element of the list.
 * @return Number of elements. If the list is empty, 0 is returned.
 */
int list_count(struct person *list) {
    // If the list is empty, return 0.
    if (list == NULL)
        return 0;

    // Variables
    struct person *element = list_first(list);
    int count = 1;

    // Go through the list and increment count with each step
    while (element->next != NULL) {
        count += 1;
        element = element->next;
    }

    // Return element count
    return count;
}


/**
 * Returns a specific element from a (double) linked list by its index
 * @param list Pointer to any element of the list.
 * @param position Position of the element that should be returned.
 * @return Pointer to the requested element. Returns NULL, if the element couldn't be found.
 */
struct person *list_get(struct person *list, int position) {
    // Abort, if list is empty
    if (list == NULL)
        return NULL;

    // Variables - Use the first element of the list as the starting point.
    struct person *element = list_first(list);
    int i, count = list_count(list);

    // Return NULL, if the index is out of bound.
    if (position < 0 || position >= count)
        return NULL;

    // Go through the elements until position is reached
    for (i = 0; i < position; ++i) {
        element = element->next;
    }

    // Return element
    return element;
}


/**
 * Print all elements of the list.
 * @param list Pointer to any point of the (double) linked list.
 */
void list_print(struct person *list) {
    // Abort, if list is empty
    if (list == NULL) {
        printf("There are no elements in the list.\n");
        return;
    }

    // Variables
    int i, count = list_count(list);

    // Print each element
    for (i = 0; i < count; i++) {
        printf("%i) ", i);
        person_print(list_get(list, i));
    }
}


/**
 * Add an element to the end of the list.
 * @param list A pointer to any element of the list.
 * @param person A pointer to the element, that should be added.
 * @return Returns the first element of the list.
 */
struct person *list_add(struct person *list, struct person *person) {
    // Abort, if no element is passed
    if (person == NULL)
        return NULL;

    // NO ELEMENT IN LIST ...
    if (list == NULL) {
        // Set next and prev to default
        person->next = NULL;
        person->prev = NULL;

        // Return pointer to the list
        return person;
    }

    // ELEMENTS IN LIST ...
    // Get last element of list
    struct person *last = list_last(list);

    // Connect new element and set next/prev
    last->next = person;
    person->prev = last;
    person->next = NULL;

    // Return list
    return list_first(list);
}


/**
 * Remove an element from the list. The memory of the element is freed.
 * @param list A pointer to any element of the (double) linked list.
 * @param position Position of the element that should be deleted.
 * @return Pointer to the list. Returns NULL if the list is empty.
 */
struct person *list_delete(struct person *list, int position) {
    // Abort, if list is empty
    if (list == NULL)
        return NULL;

    // Variables
    int count = list_count(list);
    struct person *element = list_first(list);
    struct person *new_element = NULL;

    // One element in list
    if(count == 1){
        free(element);
        return NULL;
    }

    // Position out of bound => Return list without deleting
    if (position < 0 || position >= count)
        return list;

    // => CASE: First element should be removed
    if (position == 0) {
        new_element = element->next;
        element->next->prev = NULL;
        free(element);
        return new_element;
    }

    // => CASE: Last element should be deleted
    if (position == count - 1) {
        new_element = list_last(list);
        new_element->prev->next = NULL;
        free(new_element);
        return list;
    }

    // => CASE: Element in between should be deleted
    // Get element that should be deleted
    element = list_get(list, position);

    // Delete element and reconnect prev and next
    element->prev->next = element->next;
    element->next->prev = element->prev;
    free(element);

    return list;
}


/**
 * Delete all elements of the list
 * @param list List that should be dropped
 * @return NULL pointer representing the empty list
 */
struct person *list_drop(struct person *list) {
    // Abort if list is already empty
    if (list == NULL)
        return NULL;

    // Variables
    int i, count = list_count(list);

    // Delete every element
    for (i = 0; i < count; i++) {
        list = list_delete(list, i);
    }

    // Return empty list
    return NULL;
}


/**
 * Removes last element from list. The memory of the element does not get freed
 * @param list A pointer to any element of the list
 * @return A pointer to the removed element
 */
struct person *list_pop(struct person *list) {
    // Abort, if list is empty
    if (list == NULL)
        return NULL;

    // Variables
    struct person *element = list_last(list);

    // Return element, if list contains only this one element
    if (list_count(list) == 1)
        return list;

    // Disconnect last element
    if (element->prev != NULL)
        element->prev->next = NULL;
    element->prev = NULL;

    // Return pointer to disconnected element
    return element;
}


/**
 * Swaps to elements of a list
 * @param a Pointer to the first element.
 * @param b Pointer to the second element.
 * @return Pointer to the list.
 */
struct person *list_swap(struct person *a, struct person *b) {
    // Abort, if parameters have no right values
    if (a == NULL || b == NULL)
        return NULL;

    if (a == b)
        return list_first(a);

    // Separate Head and Tail
    struct person *head = NULL;
    struct person *tail = NULL;

    if (a->prev != NULL) {
        head = a->prev;
    }

    if (b->next != NULL) {
        tail = b->next;
    }

    // Switch elements, depending on, if elements are adjacent
    b->next = a->next == b ? a : a->next;
    a->prev = a->next == b ? b : b->prev;

    b->next->prev = b;
    a->prev->next = a;

    // Reconnect Head and Tail
    if (head != NULL) {
        head->next = b;
        b->prev = head;
    } else {
        b->prev = NULL;
    }

    if (tail != NULL) {
        tail->prev = a;
        a->next = tail;
    } else {
        a->next = NULL;
    }

    // Return first element of list
    return list_first(a);
}


/**
 * Combines two lists
 * @param list_a First list
 * @param list_b Second list
 * @return Pointer to the combined list
 */
struct person *list_combine(struct person *list_a, struct person *list_b) {
    // Default return: handle NULL
    if (list_a == NULL)
        return list_first(list_b);

    if (list_b == NULL)
        return list_first(list_a);

    if (list_a == NULL && list_b == NULL)
        return NULL;

    // Get elements of list that will be adjacent
    struct person *l = list_last(list_a);
    struct person *r = list_first(list_b);

    // Connect those elements
    l->next = r;
    r->prev = l;

    // Return pointer to the first element
    return list_first(list_a);
}


/**
 * Sort list ascending by age.
 * The function implements the quick sort algorithm with an average time complexity of n*log(n).
 * @param list Pointer to the unsorted list
 * @return Pointer to the sorted list
 */
struct person *list_sort_age_quick(struct person *list) {
    // If list is empty, it is already sorted
    if (list == NULL)
        return NULL;

    // Get count of elements and pivot element
    int count = list_count(list);
    int pivot = list_first(list)->age;

    // Anchor ----------------------------------------------------------------------
    if (count <= 2) {

        // Swap elements if the second is smaller
        if (count == 2 && list_first(list)->age > list_last(list)->age) {
            list_swap(list_first(list), list_last(list));
        }

        // Return sorted list
        return list;
    }

    // Step -------------------------------------------------------------------------
    struct person *left = NULL;
    struct person *right = NULL;
    struct person *removed = NULL;
    int i;

    // Divide at pivot element
    for (i = 0; i < count - 1; ++i) {
        // Remove last element from list
        removed = list_pop(list);

        // Compare it to the pivot-element and add it to the left or right sublist
        if (removed->age < pivot)
            left = list_add(left, removed);
        else
            right = list_add(right, removed);
    }

    // Sort sublist recursively
    left = list_sort_age_quick(left);
    right = list_sort_age_quick(right);

    // Add pivot-element in between and combine left and right sublist
    left = list_add(left, list);
    list = list_combine(left, right);

    // Return sorted list
    return list;
}


/**
 * Sort list ascending by age.
 * The function implements the bubble sort algorithm with an average time complexity of n^2.
 * @param list Pointer to the unsorted list
 * @return Pointer to the sorted list
 */
struct person *list_sort_age_bubble(struct person *list) {
    // Empty list is already sorted => Return NULL
    if (list == NULL)
        return NULL;

    // Variables
    int i, swapped, count = list_count(list);
    struct person *a, *b;

    // Repeat as long as at least one element was swapped
    do {
        swapped = 0;

        // Go through the list
        for (i = 0; i < count - 1; ++i) {
            // Get current and following element
            a = list_get(list, i);
            b = list_get(list, i + 1);

            // If age of the first element ist bigger, swap elements.
            if (a->age > b->age) {
                list = list_swap(a, b);
                swapped = 1;
            }
        }
    } while (swapped == 1);

    // Return sorted list
    return list;
}


/**
 * User dialog to add a custom person to the list.
 * @param list Pointer to the list, to which the person should be added.
 * @return Pointer to the person that was just added
 */
struct person *list_add_custom(struct person *list) {
    // Variables for user input
    char first_name[SIZE_FIRST_NAME] = "";
    char last_name[SIZE_LAST_NAME] = "";
    char mail[SIZE_MAIL] = "";
    char bd_str[SIZE_BIRTHDAY_STRING] = "";

    // User input
    printf("Enter the first name (Max. length: %i):\n", SIZE_FIRST_NAME - 1);
    read_string_input(first_name, SIZE_FIRST_NAME - 1);

    printf("\nEnter the last name (Max. length: %i):\n", SIZE_LAST_NAME - 1);
    read_string_input(last_name, SIZE_LAST_NAME - 1);

    printf("\nEnter the e-mail address (Max. length: %i):\n", SIZE_MAIL - 1);
    read_string_input(mail, SIZE_MAIL - 1);

    printf("\nEnter the birthday (dd.mm.yyyy):\n");
    read_string_input(bd_str, SIZE_BIRTHDAY_STRING - 1);

    //Create struct with entered information
    struct person *p = person_create(
            first_name,
            last_name,
            mail,
            parse_date_string(bd_str, 'd'),
            parse_date_string(bd_str, 'm'),
            parse_date_string(bd_str, 'y')
    );

    // Add person to list
    list_add(list, p);

    // Print information
    printf("\nThe following person was added to the list:\n=> ");
    person_print(p);

    // Return added person
    return p;
}


/**
 * Creates sample data with names from the names.txt file
 * @param list Pointer to the list to which the elements should be added
 * @param count Count of sample data elements
 * @return Pointer to the list with new data
 */
struct person *list_create_sample_data(struct person *list, int count) {
    // Variables
    struct person *list_d = NULL;
    char *ptr;
    char f_n[SIZE_FIRST_NAME] = "", l_n[SIZE_LAST_NAME] = "", mail[SIZE_MAIL] = "";

    // Create array that will hold names
    int size = (SIZE_LAST_NAME + SIZE_LAST_NAME + 1) * count;
    char *names = (char *) malloc(size);
    memset(names, 0, size);

    // Get names form file
    get_names(names, count);

    // Abort if error while retrieving files
    if (strlen(names) == 0) {
        printf("ERROR: File with names could not be found!\n");
        return NULL;
    }

    // Split string and convert to int
    ptr = strtok(names, "\n");

    // Split string on \n and create sample data for each name
    while (ptr != NULL) {

        // Separate first and last name by last space
        strcpy(f_n, ptr);

        ptr = strrchr(ptr, ' ') + 1;
        strcpy(l_n, ptr);

        int cut = (int) (strlen(f_n) - strlen(l_n)) - 1;
        f_n[cut] = 0;

        // Concatenate sample mail
        memset(mail, 0, sizeof(mail));
        strcat(mail, f_n);
        strcat(mail, ".");
        strcat(mail, l_n);
        strcat(mail, "@test.de");

        // Create person and add it to list
        list_d = list_add(
                list_d,
                person_create(f_n, l_n, mail, random(1, 31), random(1, 12), random(1900, 2023))
        );

        ptr = strtok(NULL, "\n");
    }

    // Free memory that holds the names
    free(names);

    // Append list and return
    return list_combine(list, list_d);
}


// ==========================================================
// ===                  FILE-HANDLING                     ===
// ==========================================================


/**
 * Read data.csv and import elements from it
 * @param list Pointer to the list in which the elements should be added
 * @return Pointer to the list
 */
struct person *file_read(struct person *list) {
    printf("Loading from file ...!\n");

    // Variables
    char c;
    char path[PATH_MAX] = "";
    char buffer[SIZE_PERSON_STR] = "";
    char f_n[SIZE_FIRST_NAME] = "", l_n[SIZE_LAST_NAME] = "", mail[SIZE_MAIL] = "";
    char bd_d[2 + 1] = "", bd_m[2 + 1] = "", bd_y[4 + 1] = "";
    struct person *list_d = NULL;
    FILE *stream;

    // Get current working directory
    get_current_directory(path, "data.csv");

    // Open read stream
    stream = fopen(path, "r");

    if (stream != NULL) {
        // Read header
        fgets(buffer, sizeof(buffer), stream);

        // Read file til EOF
        while (fgets(buffer, sizeof(buffer), stream) != NULL) {
            if (buffer[0] != '\n') {
                // Remove newline at end
                buffer[strcspn(buffer, "\n")] = 0;

                // Split the line
                strcpy(f_n, strtok(buffer, ","));
                strcpy(l_n, strtok(NULL, ","));
                strcpy(mail, strtok(NULL, ","));
                strcpy(bd_d, strtok(NULL, ","));
                strcpy(bd_m, strtok(NULL, ","));
                strcpy(bd_y, strtok(NULL, ","));

                // Create list element and add to list
                list_d = list_add(list_d, person_create(f_n, l_n, mail, atoi(bd_d), atoi(bd_m), atoi(bd_y)));
            }
        }
        printf("SUCCESS: File content was loaded!\n\n");

        // If other data already exists:
        if (list_count(list) > 0) {
            printf("Should the read data be appended or replaced?\n");
            printf("[a] - append data to existing.\n");
            printf("[o] - override existing data.\n");

            // Read input
            c = read_single_char();

            if (c == 'a') {
                // Append new data
                return list_combine(list, list_d);
            } else if (c == 'o') {
                // Override existing data
                return list_combine(list_drop(list), list_d);
            } else {
                // Abort execution
                printf("Input was not a valid option!\n\n");
            }
        } else {
            // No existing data => add file data without asking
            return list_combine(list, list_d);
        }
    } else {
        printf("ERROR: No file found!\n");
    }
    return list;
}


/**
 * Saves current list as a .csv file
 * @param list Pointer to the list that should be saved
 */
void file_write(struct person *list) {
    // Varaiables
    int i;
    int count = list_count(list);
    char path[PATH_MAX];
    char str[SIZE_PERSON_STR] = "";
    FILE *stream;

    // Get current working directory
    get_current_directory(path, "data.csv");

    // Open write stream
    stream = fopen(path, "w");

    // If success: write
    if (stream != NULL) {
        // Print header to file
        fprintf(stream, "%s", CSV_HEADER);

        for (i = 0; i < count; ++i) {
            // Get person formatted as csv line and print it to file
            memset(str, 0, sizeof(str));
            person_csv_line(str, list_get(list, i));
            fprintf(stream, "%s", str);
        }

        // Close file
        fclose(stream);
    }
}


// ==========================================================
// ===                      GENERAL                       ===
// ==========================================================


/**
 * Display main menu
 * @param list Pointer to the list for which the menu be opened
 */
void menu(struct person *list) {
    // Variables
    char c;
    clock_t t;

    // Print Menu-Items
    printf(measure_mode ? "Menu (Measure-Mode) ----------------------------------------\n"
                        : "Menu -------------------------------------------------------\n");
    printf("[0] - Print list to console.\n");
    printf("[1] - Count elements in list.\n");
    printf("[2] - Delete element from list.\n\n");

    printf("[s] - Save to file.\n");
    printf("[l] - Add data from file.\n");
    printf("[c] - Add (custom) element to list.\n");
    printf("[n] - Add sample data to list.\n\n");

    printf("[q] - Sort with quicksort.\n");
    printf("[b] - Sort with bubble-sort.\n\n");

    printf("[d] - Drop list.\n\n");

    printf("[m] - Toggle measure mode.\n");
    printf("[e] - Exit program.\n\n");

    printf("Enter your selection and press enter ...\n");

    // Read input and clear console
    c = read_single_char();
    clear_screen();

    // Start timer if in measure mode
    if (measure_mode == 1)
        t = clock();

    // Execute selected part
    switch (c) {
        case '0':
            list_print(list);
            break;

        case '1':
            printf("Elements in List: %i\n", list_count(list));
            break;

        case '2':
            printf("Enter the index of the element that should be deleted.\n");
            list = list_delete(list, read_number(0, 1000000));
            break;

        case 's':
            file_write(list);
            break;

        case 'l':
            list = file_read(list);
            break;

        case 'c':
            list = list_add_custom(list);
            break;

        case 'n':
            printf("Enter a number between 0 and 100000 to determine how many data samples should be created:\n");
            list = list_create_sample_data(list, read_number(0, 100000));
            break;

        case 'q':
            list = list_sort_age_quick(list);
            break;

        case 'b':
            list = list_sort_age_bubble(list);
            break;

        case 'd':
            list = list_drop(list);
            break;

        case 'm':
            measure_mode = (measure_mode + 1) % 2;
            t = clock();
            break;

        case 'e':
            exit(0);

        default:
            printf("Couldn't find selected option!\n");
            break;
    }

    // Display execution time when in measure mode
    if (measure_mode == 1) {
        t = clock() - t;
        double time_taken = ((double) t) / CLOCKS_PER_SEC;
        printf("\nThe last execution took %f seconds to complete.\n\n", time_taken);
    }else{
        printf("\n");
    }

    // Return to menu when execution finished
    menu(list);
}


/**
 * Parses the arguments
 * @param argc Argument count
 * @param argv Array of argument strings
 */
struct person * parse_args(int argc, char * argv[], struct person *list){
    int i;

    // Go thought all arguments
    for (i = 1; i < argc; ++i) {

        // Compare argument and execute
        if(strcmp(argv[i],"-mm") == 0){
            // Measure Mode
            measure_mode = 1;

        } else if(strcmp(argv[i],"-fl") == 0){
            // Autoload from file
            list = file_read(list);

        } else if(strcmp(argv[i],"-sd") == 0){
            // Auto sample data
            list = list_create_sample_data(list, atoi(argv[i + 1]));
            i += 1;
        }
    }

    return list;
}


int main(int argc, char * argv[]) {

    // Create empty list
    struct person *list = NULL;

    // Parse args
    list = parse_args(argc, argv, list);

    // Open menu
    menu(list);

    return 0;
}


