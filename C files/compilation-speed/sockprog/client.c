#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <ctype.h>
#include <arpa/inet.h> 

// program from 176a hw assignment 

struct hangman_letter {
    int msg_length;
    char chosen_letter;
};

struct server_msg {
    int msg_flag;
    int word_len;
    int num_incorrect;
    char cword[11];
    char incorrect_guesses[6];
    char data[11];
};

struct overload_msg {
    int overload;
};

int main(int argc, char *argv[]) {
    
    //server socket and ip are hardcoded to local host (home) (my machine) and 8080
    char *ip = "127.0.0.1"; 
    int portno = 8086; 

    int eofcheck = 0;

    // declarations 
    int sockfd; 
    struct sockaddr_in serv_addr; 
    socklen_t addrlen;  // data type for socket address length

    // create socket 
    sockfd = socket(AF_INET, SOCK_STREAM, 0); // defining the socket to be IPV4 and TCP

    memset(&serv_addr,'\0', sizeof(serv_addr)); 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno); // change the port to match the server (taken as arg)
    serv_addr.sin_addr.s_addr = inet_addr(ip); // setting IP address of server (taken as arg)

    // connect 
    addrlen = sizeof(serv_addr); 
    if (connect(sockfd, (struct sockaddr *)&serv_addr, addrlen) == -1) {
        perror("connection failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // receive server-overloaded message if needed
    struct overload_msg om;
    int m = recv(sockfd, (void*)&om, sizeof(om), 0); 
    if (m < 0) { 
        perror("receive failed!\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    if (om.overload == 1) {
        printf(">>>server-overloaded\n");
        close(sockfd);
        exit(0); 
    }

    // check if client wants to start game 
    char yn;
    printf(">>>Ready to start game? (y/n): "); 
    scanf(" %c", &yn);

    if (yn == 'n') {
        //printf("closed client side socket!\n");
        close(sockfd);
        exit(0);
    }

    // signaling game start 
    if (yn == 'y') { 
        struct hangman_letter pre_data; 
        pre_data.msg_length = 0;
        pre_data.chosen_letter = '\0';
        // never populated cword for pre data 

        //printf("sending something\n");

        int retval = send(sockfd, (const struct hangman_letter*)&pre_data, sizeof(pre_data), 0); // why we sending an empty buffer 
        if (retval == -1) {
            perror("pre send failed!\n");
            close(sockfd);
            exit(EXIT_FAILURE);
        }
    } 
    // what if they say no 

    while(1) { 
 
        // declare server message struct 
        struct server_msg msg; 

        //printf("waiting for a response from the server...\n");
        
        int n = recv(sockfd, (void*)&msg, sizeof(msg), 0); 
        if (n < 0) { // so recv is returning 0, means: no messages are available to be received and the peer has performed an orderly shutdown
            perror("receive failed!\n");
            close(sockfd);
            exit(EXIT_FAILURE);
        } 
        //printf("got response from the server...\n");

        if (msg.msg_flag != 0) {
            printf(">>>The word was %s\n", msg.cword);
        }

        printf(">>>"); 
        for (int i=0; i < strlen(msg.data); i++) {
            if ((i != strlen(msg.data) - 1) && (msg.msg_flag == 0)) {
                printf("%c ", msg.data[i]);
            }
            else {
                printf("%c", msg.data[i]);
            }
        } 
        printf("\n");

        if (msg.msg_flag != 0) {
            printf(">>>Game Over!\n");
            break;
        }

        // print the incorrects 
        printf(">>>Incorrect Guesses: ");
        for (int i=0; i < strlen(msg.incorrect_guesses); i++) {
            if (i != strlen(msg.incorrect_guesses) - 1) {
                printf("%c ", msg.incorrect_guesses[i]);
            }
            else {
                printf("%c", msg.incorrect_guesses[i]);
            }
        }
        printf("\n");
        printf(">>>");
        printf("\n");

        // now need to prompt again for user input and send it over 
        char guess[2]; 

        while(1) {
            printf(">>>Letter to guess: ");
            while (getchar() != '\n'); // clearing the input before taking input
            
            int eof = scanf("%s", guess); // got rid of & of guess

            if (eof == EOF) {
                printf("\n");
                eofcheck = 1; 
                close(sockfd);
                exit(0); 
            }

            // input validation 
            if (strlen(guess) == 1) {
                if (!isalpha(guess[0])) {
                    printf(">>>Error! Please guess one letter.\n");
                }
                else {
                    break;
                }
            }
            else {
                printf(">>>Error! Please guess one letter.\n");
            }
        }
        // all is good 
        
        struct hangman_letter reg_data; 
        reg_data.msg_length = 0;
        reg_data.chosen_letter = tolower(guess[0]);

        //printf("sending something\n");
        int retval = send(sockfd, (const struct hangman_letter*)&reg_data, sizeof(reg_data), 0);
        if (retval == -1) {
            perror("reg send failed! blabla\n"); 
            if (eofcheck != 1)
                close(sockfd);
            //printf("meow\n");
            exit(EXIT_FAILURE); 
        }

        // sending the same server message back
        int retval2 = send(sockfd, (const struct server_msg*)&msg, sizeof(msg), 0);
        if (retval2 == -1) {
            perror("reg send failed!\n"); 
            if (eofcheck != 1)
                close(sockfd);
            exit(EXIT_FAILURE);
        }

        //printf("sent something\n");
    }


    // close connection
    close(sockfd);
    //printf("client first\n");
    return 0;
}