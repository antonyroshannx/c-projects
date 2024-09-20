#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_INPUT_SIZE 100
#define MAX_MEMORY_SIZE 1000
#define MAX_WORDS 10
#define MAX_WORD_LENGTH 50

// Convert a string to lowercase
void to_lowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

// Split a string into words
void split_into_words(char *input, char words[MAX_WORDS][MAX_WORD_LENGTH], int *count) {
    char *token = strtok(input, " ");
    while (token != NULL && *count < MAX_WORDS) {
        strncpy(words[*count], token, MAX_WORD_LENGTH - 1);  // Prevent buffer overflow
        words[*count][MAX_WORD_LENGTH - 1] = '\0';  // Ensure null-terminated string
        (*count)++;
        token = strtok(NULL, " ");
    }
}

// Retrieve chatbot's memory from a file
void load_memory(char *memory) {
    FILE *file = fopen("chatbot_memory.txt", "r");
    if (file != NULL) {
        fgets(memory, MAX_MEMORY_SIZE, file);
        fclose(file);
    } else {
        memory[0] = '\0';  // Initialize to empty if file not found
    }
}

// Save chatbot's memory to a file
void save_memory(const char *memory) {
    FILE *file = fopen("chatbot_memory.txt", "w");
    if (file != NULL) {
        fputs(memory, file);
        fclose(file);
    }
}

// Handle solar system responses
int handle_solar_system_responses(const char *word) {
    if (strcmp(word, "sun") == 0) {
        printf("Bot: The Sun is the star at the center of the Solar System.\n");
        return 1;
    } else if (strcmp(word, "mercury") == 0) {
        printf("Bot: Mercury is the smallest planet in the Solar System.\n");
        return 1;
    } else if (strcmp(word, "venus") == 0) {
        printf("Bot: Venus is the hottest planet in the Solar System.\n");
        return 1;
    } else if (strcmp(word, "earth") == 0) {
        printf("Bot: Earth is the only planet known to support life.\n");
        return 1;
    } else if (strcmp(word, "mars") == 0) {
        printf("Bot: Mars is known as the Red Planet due to its reddish appearance.\n");
        return 1;
    } else if (strcmp(word, "jupiter") == 0) {
        printf("Bot: Jupiter is the largest planet in the Solar System.\n");
        return 1;
    } else if (strcmp(word, "saturn") == 0) {
        printf("Bot: Saturn is famous for its beautiful ring system.\n");
        return 1;
    } else if (strcmp(word, "uranus") == 0) {
        printf("Bot: Uranus rotates on its side, unlike other planets.\n");
        return 1;
    } else if (strcmp(word, "neptune") == 0) {
        printf("Bot: Neptune is known for its intense blue color and strong winds.\n");
        return 1;
    }
    return 0;
}

// Process memory-related commands
int handle_memory_commands(const char *input, char *memory) {
    if (strstr(input, "remember") != NULL) {
        strcpy(memory, strchr(input, ' ') + 1);  // Copy after the word "remember"
        save_memory(memory);
        printf("Bot: I'll remember that!\n");
        return 1;
    } else if (strstr(input, "what do you remember") != NULL) {
        if (strlen(memory) > 0) {
            printf("Bot: You told me: %s\n", memory);
        } else {
            printf("Bot: I don't remember anything yet.\n");
        }
        return 1;
    }
    return 0;
}

// General responses for greetings or farewells
int handle_general_responses(const char *input, char words[MAX_WORDS][MAX_WORD_LENGTH], int word_count) {
    if (strcmp(words[0], "hello") == 0 || strcmp(words[0], "hi") == 0) {
        printf("Bot: Hello! How can I help you today?\n");
        return 1;
    } else if (word_count >= 2 && strcmp(words[0], "how") == 0 && strcmp(words[1], "are") == 0) {
        printf("Bot: I'm just a bot, but I'm doing great! How about you?\n");
        return 1;
    } else if (strcmp(words[0], "bye") == 0) {
        printf("Bot: Goodbye! Have a nice day!\n");
        return 1;
    }
    return 0;
}

// Match user input with predefined responses
void respond(const char *input, char *memory) {
    char temp_input[MAX_INPUT_SIZE];
    strcpy(temp_input, input);
    to_lowercase(temp_input);

    // Split input into words
    char words[MAX_WORDS][MAX_WORD_LENGTH];
    int word_count = 0;
    split_into_words(temp_input, words, &word_count);

    // General responses
    if (handle_general_responses(input, words, word_count)) {
        return;
    }
    // Check for memory-related commands
    if (handle_memory_commands(input, memory)) {
        return;
    }
    // Check for solar system-related responses
    if (handle_solar_system_responses(words[0])) {
        return;
    }

    // If no match is found
    printf("Bot: I'm not sure how to respond to that.\n");
}

int main() {
    char input[MAX_INPUT_SIZE];
    char memory[MAX_MEMORY_SIZE] = "";

    // Load memory from previous conversations
    load_memory(memory);

    printf("Bot: Hello! I am your AI chatbot. You can talk to me!\n");

    // Main chat loop
    while (1) {
        printf("You: ");
        fgets(input, MAX_INPUT_SIZE, stdin);
        input[strcspn(input, "\n")] = '\0';  // Remove the newline character

        // Exit if user says "bye"
        if (strstr(input, "bye") != NULL) {
            respond(input, memory);
            break;
        }

        // Respond to user input
        respond(input, memory);
    }

    return 0;
}
