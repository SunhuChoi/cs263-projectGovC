#include <stdio.h>

struct hangman_letter {
    int msg_length;
    char chosen_letter;
    int msg_lengtkjh;
};

struct server_msg {
    int msg_flag;
    int word_len;
    int num_incorrect;
    char cword[11];
    char incorrect_guesses[6];
    char data[11];
};
