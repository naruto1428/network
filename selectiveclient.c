#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<string.h>
#define cls() printf("Clearing")
struct frame {
int packet[40];
};
struct ack {
int acknowledge[40];
};
int main() {
int client_socket_fd;
struct sockaddr_in serveraddr;
socklen_t len;
    struct hostent * server;
    struct frame f1;
    int windowsize, totalpackets, totalframes, i = 0, j = 0, framesreceived = 0, k, m, n, l;
    int repacket[40];
    struct ack acknowledgement;
    char req[50];
client_socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    bzero((char * ) & serveraddr, sizeof(serveraddr));
serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(5018);
    server = gethostbyname("127.0.0.1");
    bcopy((char * ) server -> h_addr, (char * ) & serveraddr.sin_addr.s_addr, sizeof(server -> h_addr));
    printf("Sending request to the server\n");
    sendto(client_socket_fd, "HI IAM CLIENT.", sizeof("HI IAM CLIENT."), 0, (struct sockaddr * ) & serveraddr, sizeof(serveraddr));
    printf("\nWaiting for reply\n");
    recvfrom(client_socket_fd, req, sizeof(req), 0, (struct sockaddr * ) & serveraddr, & len);
    printf("The server has send:It %s \n", req);
    printf("\nEnter the window size \n");
    scanf("%d", & windowsize);
    printf("Sending window size\n");
    sendto(client_socket_fd, (char * ) & windowsize, sizeof(windowsize), 0, (struct sockaddr * ) & serveraddr, sizeof(serveraddr));
    cls();
    printf("\nWaiting for the server response\n");
    recvfrom(client_socket_fd, (char * ) & totalpackets, sizeof(totalpackets), 0, (struct sockaddr * ) & serveraddr, & len);
    printf("The total packets are:%d\n", totalpackets);
    sendto(client_socket_fd, "RECEIVED.", sizeof("RECEIVED."), 0, (struct sockaddr * ) & serveraddr, sizeof(serveraddr));
    recvfrom(client_socket_fd, (char * ) & totalframes, sizeof(totalframes), 0, (struct sockaddr * ) & serveraddr, & len);
    printf("The frames of windows are:\t%d\n", totalframes);
    sendto(client_socket_fd, "RECEIVED.", sizeof("RECEIVED."), 0, (struct sockaddr * ) & serveraddr, sizeof(serveraddr));
    printf("Starting the process of receiving:\n");
    l = 0;
    j = 0;
    while (l < totalpackets) {
        printf("Initializing the receiver buffer \n");
printf("The Expected frame is %d with packets:", framesreceived);
        for (m = 0; m < j; m++) {
            printf("%d", repacket[m]);
        }
        while (j < windowsize && i < totalpackets) {
            printf("%d", i);
            i++;
            j++;
        }
        printf("\nWaiting for the frame \n");
        recvfrom(client_socket_fd, (char * ) & f1, sizeof(f1), 0, (struct sockaddr * ) & serveraddr, & len);
        printf("Received frame %d \n\nEnter to send negative acknowledgement for the following packets.\n ", framesreceived);
        j = 0;
        m = 0;
        k = l;
while (m < windowsize && k < totalpackets) {
            printf("\nPacket:%d\n", f1.packet[m]);
            scanf("%d", & acknowledgement.acknowledge[m]);
            if (acknowledgement.acknowledge[m] == -1) {
                repacket[j] = f1.packet[m];
                j++;
            } else {
                l++;
            }
            m++;
            k++;
        }
        framesreceived++;
        sendto(client_socket_fd, (char * ) & acknowledgement, sizeof(acknowledgement), 0, (struct sockaddr * ) & serveraddr, sizeof(serveraddr));
 cls();
    }
    printf("\nAll frames received successfully.\n\nClosing connection with the server.\n ");
}
