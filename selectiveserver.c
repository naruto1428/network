#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/stat.h>
#define cls() printf("Clearing")
struct frame {
    int packet[40];
};
struct ack {
    int acknowledge[40];
};
int main() {
    int socket_fd;
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t len;
    struct frame f1;
    int windowsize, totalpackets, totalframes, i = 0, j = 0, framessend = 0, k, m, n, l;
    int repacket[40];
    struct ack acknowledgement;
    char req[50];
socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
bzero((char * ) & serveraddr, sizeof(serveraddr));
serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(5018);
    serveraddr.sin_addr.s_addr = INADDR_ANY;
bind(socket_fd, (struct sockaddr * ) & serveraddr, sizeof(serveraddr));
bzero((char * ) & clientaddr, sizeof(clientaddr));
len = sizeof(clientaddr);
    printf("\nWaiting for client connetion \n");
    recvfrom(socket_fd, req, sizeof(req), 0, (struct sockaddr * ) & clientaddr, & len);
    printf("\nClient connection obtained\t%s\n", req);
    printf("\nSending request for window size\n");
    sendto(socket_fd, "REQUEST FOR WINDOW SIZE", sizeof("REQUST FOR WINDOW SIZE"), 0, (struct sockaddr * ) & clientaddr, sizeof(clientaddr));
    printf("\nWaiting for the window size\n");
    recvfrom(socket_fd, (char * ) & windowsize, sizeof(windowsize), 0, (struct sockaddr * ) & clientaddr, & len);
cls();
printf("The window size obtained as: \t%d\n", windowsize);
    printf("\nObtaining packets from network layer\n");
    printf("\nTotal packets obtained \t%d\n", (totalpackets = windowsize * 5));
    printf("\nTotal frames or windows to be transmitted\t%d\n", (totalframes = 5));
    printf("\nSending total number of packets\n");
    sendto(socket_fd, (char * ) & totalpackets, sizeof(totalpackets), 0, (struct sockaddr * ) & clientaddr, sizeof(clientaddr));
    recvfrom(socket_fd, req, sizeof(req), 0, (struct sockaddr * ) & clientaddr, & len);
    printf("\nSending total number of frames\n");
    sendto(socket_fd, (char * ) & totalframes, sizeof(totalframes), 0, (struct sockaddr * ) & clientaddr, sizeof(clientaddr));
    recvfrom(socket_fd, req, sizeof(req), 0, (struct sockaddr * ) & clientaddr, & len);
    printf("\nPress enter to start the process\n");
    fgets(req, 2, stdin);
cls();
j = 0;
    l = 0;
    while (l < totalpackets) {
        bzero((char * ) & f1, sizeof(f1));
        printf("Initializing the transmit buffer \n");
        printf("The frame to be send is %d with packets\n", framessend);
        for (m = 0; m < j; m++) {
            printf("%d", repacket[m]);
            f1.packet[m] = repacket[m];
        }
        while (j < windowsize && i < totalpackets) {
            printf("%d", i);
            f1.packet[j] = i;
            i++;
            j++;
        }
        printf("Sending frame %d\n", framessend);
        sendto(socket_fd, (char * ) & f1, sizeof(f1), 0, (struct sockaddr * ) & clientaddr, sizeof(clientaddr));
        printf("Waiting for the acknowledgement\n");
 recvfrom(socket_fd, (char * ) & acknowledgement, sizeof(acknowledgement), 0, (struct sockaddr * ) & clientaddr, & len);
 cls();
        j = 0;
        m = 0;
        k = 0;
        n = 1;
        while (m < windowsize && n < totalpackets) {
            if (acknowledgement.acknowledge[m] == -1) {
                printf("\nNegetive acknowledgement received for packet:%d\n", f1.packet[m]);
k = 1;
                repacket[j] = f1.packet[m];
                j++;
            } else {
                l++;
            }
            m++;
            n++;
        }
        if (k == 0) {
            printf("\nPositive acknowledgement received for all packets, waiting for frame: %d\n ", framessend);
        }
        framessend++;
        printf("\nPress enter to proceed\n");
        fgets(req, 2, stdin);
        cls();
    }
    printf("All frames sent successfully.\nClosing connection with client");
    close(socket_fd);
}

