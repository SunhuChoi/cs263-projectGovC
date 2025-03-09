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
    
    char *ip = "127.0.0.1"; 
    int portno = 8086; 

    int eofcheck = 0;

    int sockfd; 
    struct sockaddr_in serv_addr; 
    socklen_t addrlen;  

    sockfd = socket(AF_INET, SOCK_STREAM, 0); 

    memset(&serv_addr,'\0', sizeof(serv_addr)); 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno); 
    serv_addr.sin_addr.s_addr = inet_addr(ip); 

    addrlen = sizeof(serv_addr); 
    if (connect(sockfd, (struct sockaddr *)&serv_addr, addrlen) == -1) {
        perror("connection failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

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

    char yn;
    printf(">>>Ready to start game? (y/n): "); 
    scanf(" %c", &yn);

    if (yn == 'n') {
        close(sockfd);
        exit(0);
    }

    if (yn == 'y') { 
        struct hangman_letter pre_data; 
        pre_data.msg_length = 0;
        pre_data.chosen_letter = '\0';

        int retval = send(sockfd, (const struct hangman_letter*)&pre_data, sizeof(pre_data), 0); 
        if (retval == -1) {
            perror("pre send failed!\n");
            close(sockfd);
            exit(EXIT_FAILURE);
        }
    } 

    while(1) { 
 
        struct server_msg msg; 
        
        int n = recv(sockfd, (void*)&msg, sizeof(msg), 0); 
        if (n < 0) { 
            perror("receive failed!\n");
            close(sockfd);
            exit(EXIT_FAILURE);
        } 

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

        char guess[2]; 

        while(1) {
            printf(">>>Letter to guess: ");
            while (getchar() != '\n');
            
            int eof = scanf("%s", guess); 

            if (eof == EOF) {
                printf("\n");
                eofcheck = 1; 
                close(sockfd);
                exit(0); 
            }

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
        
        struct hangman_letter reg_data; 
        reg_data.msg_length = 0;
        reg_data.chosen_letter = tolower(guess[0]);

        int retval = send(sockfd, (const struct hangman_letter*)&reg_data, sizeof(reg_data), 0);
        if (retval == -1) {
            perror("reg send failed!\n"); 
            if (eofcheck != 1)
                close(sockfd);
            exit(EXIT_FAILURE); 
        }

        int retval2 = send(sockfd, (const struct server_msg*)&msg, sizeof(msg), 0);
        if (retval2 == -1) {
            perror("reg send failed!\n"); 
            if (eofcheck != 1)
                close(sockfd);
            exit(EXIT_FAILURE);
        }
    }

    close(sockfd);
    return 0;
}