#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <pthread.h> // for mulitthreading 
#include <ctype.h> // for isdigit
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

    if (pthread_mutex_lock(&thread_lock) != 0) { // LOCK 
        perror("mutex lock failed");
        //exit(EXIT_FAILURE);
    }

    for (int i = 0; i < deccount; i++)
        active_threads--;

    if (pthread_mutex_unlock(&thread_lock) != 0) { // UNLOCK 
        perror("mutex unlock failed");
        //exit(EXIT_FAILURE);
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

    //printf("entered hangman\n");
    int csock = *((int *)arg);

    struct hangman_letter start;    

    int retval = recv(csock, &start, sizeof(struct hangman_letter), 0); 
    if (retval <= 0) {
        perror("receive failed!\n");
        decrement(1);
        close(csock);
        exit(EXIT_FAILURE);
    }
    //printf("server recieved a yes and creates a thread\n");

    char word[8]; // used to be a char* 
    // if message length is 0, choose random word and send for the first time 
    if (start.chosen_letter == '\0') {
        //printf("entered first case\n");
        
        FILE *file;
        file = fopen("hangman_words.txt", "r");
        if (file == NULL) {
            perror("Error opening file");
        }

        int random_pos = rand() % 15; // generate a random index into the file of size 15 
        fseek(file, 0, SEEK_SET);

        for (int i = 0; i < random_pos; i++) {
            fscanf(file, "%s", word);
        }

        fscanf(file, "%s", word);
        fclose(file);

        // in a while loop, recieve letter, play hangman, increment incorrect guesses if needed, send back struct 
        struct server_msg send_back;
        // need to send blanks to the client IF first time (recieved blank char)
        // printf("word: %s\n", word);
        for (int i = 0; i < strlen(word); i++) {
            send_back.data[i] = '_';
        } 

        // set other fields 
        send_back.msg_flag = 0;
        send_back.word_len = strlen(word);
        strcpy(send_back.cword, word);
        send_back.num_incorrect = 0;

        // send back the struct 
        int retval1 = send(csock, (const struct server_msg*)&send_back, sizeof(send_back), 0);
        if (retval1 == -1) {
            perror("pre send failed!\n");
            decrement(1);
            close(csock);
            exit(EXIT_FAILURE);
        }
    }

    while(1) {

        //printf("looping to get the next letters...\n");

        struct hangman_letter guess;    
        
        // recv the letter guessed by client
        int retval = recv(csock, &guess, sizeof(struct hangman_letter), 0); 
        if (retval <= 0) { 
            perror("receive failed!\n");
            decrement(1);
            close(csock);
            //exit(EXIT_FAILURE);
            return 0;
        }

        //printf("recieved the letter\n");

        struct server_msg old_msg;

        // recv the same packet sent before from server
        int retval2 = recv(csock, &old_msg, sizeof(struct server_msg), 0); 
        if (retval2 <= 0) {
            perror("receive failed!\n"); 
            decrement(1);
            close(csock);
            //exit(EXIT_FAILURE);
            return 0;
        }
        //printf("recieved the old package\n");

        // declare struct to send back 
        struct server_msg send_back;
        
        // now, not the first time
        int num_blanks = 0;
        //printf("print strlen of old message : %ld\n", strlen(old_msg.data));
        strcpy(send_back.data, old_msg.data);

        int incorrect = 1; // if above 6, end game
        char wrong_letter[2];
        memset(wrong_letter, '\0', sizeof(wrong_letter)); // set memset to null terminator chars

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

        if (old_msg.num_incorrect + incorrect > 5) { // you lose 
            send_back.msg_flag = 1;
            strcpy(send_back.cword, word);
            //printf(">>>The word was %s\n", word);  
            strcpy(send_back.data, "You Lose!");
        }
        else if (num_blanks == 0) { // you won
            send_back.msg_flag = 1;
            strcpy(send_back.cword, word);
            //printf(">>>The word was %s\n", word); 
            strcpy(send_back.data, "You Win!");
        }
        else { // otherwise
            send_back.msg_flag = 0;
            send_back.word_len = strlen(word); 
            strcpy(send_back.cword, word);
            send_back.num_incorrect = old_msg.num_incorrect + incorrect;
            strcpy(send_back.incorrect_guesses, old_msg.incorrect_guesses);
            strcat(send_back.incorrect_guesses, wrong_letter); // error here 
        }

        // send 
        int retval3 = send(csock, (const struct server_msg*)&send_back, sizeof(send_back), 0);
        if (retval3 == -1) {
            perror("pre send failed!\n");
            decrement(1);
            close(csock);
            //exit(EXIT_FAILURE);
            return 0;
        }

        if ((num_blanks == 0) || (old_msg.num_incorrect + incorrect > 5)) {
            break;
        }
    } 

    //printf("Client disconnected\n");

    decrement(1);
    //printf("thread counter value after decrement, %d\n", active_threads);

    close(csock);
    return 0; 
}



int main(int argc, char *argv[]) { 

    init(); // initializing mutex lock 
    active_threads = 0;

    // tcp makes it so even if threads have same ip and port, they will have diff socket number (we'll see ab that lmao)
    int portno = 8086;

    // declarations
    int ssock;
    int csock; // client socket that will be initialized with accept 
    // can we use same sock var for each thread 

    struct sockaddr_in serv_addr, client_addr; // structures containing the IP address and port number to bind to
    socklen_t addrlen;  

    // for multithreading later 
    pthread_t thread_id[3]; 
    //int active_threads = 0; // i think you just keep a counter and increment everytime we thread and decrement it when a thread exits 
    int i = 0;

    // create 
    ssock = socket(AF_INET, SOCK_STREAM, 0); // create server socket descriptor 

    memset(&serv_addr,'\0', sizeof(serv_addr)); // wipe servaddr before populating next 
    // address structure initialization 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno); // - doesn't need to be ntoh?
    serv_addr.sin_addr.s_addr = INADDR_ANY; // setting IP address of server 


    // bind
    // here we attach the socket to given port and any local ip address 
    if (bind(ssock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("binding error\n");
        close(ssock); // which one do we close? ssock or csock? 
        exit(EXIT_FAILURE);
    } 

    // listen for potential connections (telling the os we r ready to accept)
    // 3 is max length of queue for completely established sockets waiting to be accepted 
    listen(ssock, 4); // are we sure ab this value 
    // printf("listening!\n");

    addrlen = sizeof(client_addr); 

    struct overload_msg om;
    while(1) { // now loop for client gamers 

        //printf("active thread count: %d\n", active_threads);
        om.overload = 0;


        //printf("active threads right before check < 3, %d\n", active_threads);
        //printf("overload bit before check %d\n", om.overload);
        //printf("BOOL VAL, %d\n", active_threads < 3);

        csock = accept(ssock, (struct sockaddr *) &client_addr, &addrlen);
        if (csock < 0) { 
            perror("accepting failed\n");
            decrement(1);
            close(csock); // which one do we close? ssock or csock? 
            exit(EXIT_FAILURE); 
        }

        if (active_threads < 3) { 
            // accept incoming connection 
            //printf("got past accept\n");
            // creating pthread for client socket csock
            if (pthread_create(&thread_id[i], NULL, hangman, &csock) != 0) { // creating a thread for our new client - run on hangman game 
                perror("pthread_create failed");
                exit(EXIT_FAILURE);
            }

            //printf("I am here, right after the pthread create call\n");

            i = (i + 1) % 3; // updating next pthread id 

            //printf("I am after the i updating\n");
        }
        else {
            // send server-overloaded message
            //printf("OVERLOAD BIT SET........"); 
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
    
    //close(ssock); 
}
