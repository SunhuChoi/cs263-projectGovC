#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <pthread.h> 
#include <ctype.h> 
#include <time.h>
#include "rand.h"

// program from 176a hw assignment 

// struct hangman_letter {
//     int msg_length;
//     char chosen_letter;
// };

// struct server_msg {
//     int msg_flag;
//     int word_len;
//     int num_incorrect;
//     char cword[11];
//     char incorrect_guesses[6];
//     char data[11];
// };

struct overload_msg {
    int overload;
};

pthread_mutex_t thread_lock;
int active_threads;

void *decrement(int deccount) {

    if (pthread_mutex_lock(&thread_lock) != 0) { 
        perror("mutex lock failed");
    }

    for (int i = 0; i < deccount; i++)
        active_threads--;

    if (pthread_mutex_unlock(&thread_lock) != 0) { 
        perror("mutex unlock failed");
    }
    return 0;
}

void *init() {
    pthread_mutex_init(&thread_lock, NULL);
    return 0;
}

void *hangman(void *arg) {

    // ---------------------------------------------------------------
    if (pthread_mutex_lock(&thread_lock) != 0) { // LOCK 
        perror("mutex lock failed");
        exit(EXIT_FAILURE);
    }
    // ---------------------------------------------------------------

    active_threads++; // we have one more gamer!

    // ---------------------------------------------------------------
    if (pthread_mutex_unlock(&thread_lock) != 0) { //UNLOCK
        perror("mutex unlock failed");
        exit(EXIT_FAILURE);
    }
    // ---------------------------------------------------------------

    int csock = *((int *)arg);

    struct hangman_letter start;    

    int retval = recv(csock, &start, sizeof(struct hangman_letter), 0); 
    if (retval <= 0) {
        perror("receive failed!\n");
        decrement(1);
        close(csock);
        exit(EXIT_FAILURE);
    }

    char word[8]; // used to be a char* 

    if (start.chosen_letter == '\0') {

        
        FILE *file;
        file = fopen("hangman_words.txt", "r");
        if (file == NULL) {
            perror("Error opening file");
        }

        int random_pos = rand() % 15; 
        fseek(file, 0, SEEK_SET);

        for (int i = 0; i < random_pos; i++) {
            fscanf(file, "%s", word);
        }

        fscanf(file, "%s", word);
        fclose(file);

        struct server_msg send_back;
        for (int i = 0; i < strlen(word); i++) {
            send_back.data[i] = '_';
        } 

        send_back.msg_flag = 0;
        send_back.word_len = strlen(word);
        strcpy(send_back.cword, word);
        send_back.num_incorrect = 0;

        int retval1 = send(csock, (const struct server_msg*)&send_back, sizeof(send_back), 0);
        if (retval1 == -1) {
            perror("pre send failed!\n");
            decrement(1);
            close(csock);
            exit(EXIT_FAILURE);
        }
    }

    while(1) {


        struct hangman_letter guess;    
        
        int retval = recv(csock, &guess, sizeof(struct hangman_letter), 0); 
        if (retval <= 0) { 
            perror("receive failed!\n");
            decrement(1);
            close(csock);
            return 0;
        }


        struct server_msg old_msg;

        int retval2 = recv(csock, &old_msg, sizeof(struct server_msg), 0); 
        if (retval2 <= 0) {
            perror("receive failed!\n"); 
            decrement(1);
            close(csock);
            return 0;
        }

        struct server_msg send_back;
        
        int num_blanks = 0;
        strcpy(send_back.data, old_msg.data);

        int incorrect = 1; 
        char wrong_letter[2];
        memset(wrong_letter, '\0', sizeof(wrong_letter)); 

        for (int i = 0; i < strlen(word); i++) {
            if (word[i] == guess.chosen_letter) {
                send_back.data[i] = word[i];
                incorrect = 0;
            }
        }
        if (incorrect == 1) {
            wrong_letter[0] = guess.chosen_letter;
        }

        for (int i = 0; i < strlen(word); i++) {
            if (send_back.data[i] == '_') {                
                num_blanks++;
            }
        }

        if (old_msg.num_incorrect + incorrect > 5) { 
            send_back.msg_flag = 1;
            strcpy(send_back.cword, word);
            strcpy(send_back.data, "You Lose!");
        }
        else if (num_blanks == 0) { 
            send_back.msg_flag = 1;
            strcpy(send_back.cword, word);
            strcpy(send_back.data, "You Win!");
        }
        else { 
            send_back.msg_flag = 0;
            send_back.word_len = strlen(word); 
            strcpy(send_back.cword, word);
            send_back.num_incorrect = old_msg.num_incorrect + incorrect;
            strcpy(send_back.incorrect_guesses, old_msg.incorrect_guesses);
            strcat(send_back.incorrect_guesses, wrong_letter); 
        }

        int retval3 = send(csock, (const struct server_msg*)&send_back, sizeof(send_back), 0);
        if (retval3 == -1) {
            perror("pre send failed!\n");
            decrement(1);
            close(csock);
            return 0;
        }

        if ((num_blanks == 0) || (old_msg.num_incorrect + incorrect > 5)) {
            break;
        }
    } 


    decrement(1);

    close(csock);
    return 0; 
}



int main(int argc, char *argv[]) { 

    init();
    active_threads = 0;

    int portno = 8086;

    // declarations
    int ssock;
    int csock;

    struct sockaddr_in serv_addr, client_addr;
    socklen_t addrlen;  

    pthread_t thread_id[3]; 
    int i = 0;

    ssock = socket(AF_INET, SOCK_STREAM, 0); 

    memset(&serv_addr,'\0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno); 
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(ssock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("binding error\n");
        close(ssock); 
        exit(EXIT_FAILURE);
    } 

    listen(ssock, 4); 

    addrlen = sizeof(client_addr); 

    struct overload_msg om;
    while(1) { 

        om.overload = 0;

        csock = accept(ssock, (struct sockaddr *) &client_addr, &addrlen);
        if (csock < 0) { 
            perror("accepting failed\n");
            decrement(1);
            close(csock); // which one do we close? ssock or csock? 
            exit(EXIT_FAILURE); 
        }

        if (active_threads < 3) { 
            if (pthread_create(&thread_id[i], NULL, hangman, &csock) != 0) { // creating a thread for our new client - run on hangman game 
                perror("pthread_create failed");
                exit(EXIT_FAILURE);
            }

            i = (i + 1) % 3; 
        }
        else {
            om.overload = 1;
        }

        int retval4 = send(csock, (const struct overload_msg*)&om, sizeof(om), 0);
        if (retval4 == -1) {
            perror("server overload message failed to send!\n");
            decrement(1);
            close(csock);
            exit(EXIT_FAILURE);
        }

    }
    
}
