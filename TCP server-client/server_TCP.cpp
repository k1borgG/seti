#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <string>
#include <string>
#pragma comment (lib, "Ws2_32.lib")

using namespace std;

#define SRV_PORT 1234
#define BUF_SIZE 64
const string QUEST = "Input fio, hours of work, and amount of it";

struct client {
    string fio;
    int hours;
    int count;
} A;

int main() {
    cout << "Server is starting" << endl;
    char buff[1024];
    if (WSAStartup(0x0202, (WSADATA*)&buff[0]))
    {
        cout << "Error WSAStartup \n" << WSAGetLastError();
        return -1;
    }

    SOCKET s, s_new;
    int from_len, a;
    char buf[BUF_SIZE] = { 0 };

    sockaddr_in sin, from_sin;
    s = socket(AF_INET, SOCK_STREAM, 0);
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = 0;
    sin.sin_port = htons(SRV_PORT);

    bind(s, (sockaddr*)&sin, sizeof(sin));
    string msg1;
    listen(s, 3);

    while (1) {
        from_len = sizeof(from_sin);
        cout << "waiting for the client" << endl;;
        s_new = accept(s, (sockaddr*)&from_sin, &from_len);
        cout << "client connected! " << endl;
        string msg = QUEST;
        while (1) {
            send(s_new, (char*)&msg[0], msg.size(), 0);
            from_len = recv(s_new, (char*)&A, BUF_SIZE, 0);
            cout << A.fio << " " << A.hours << " " << A.count << endl;
            
            double d = 0;
            string answ;
            d = (A.count) / A.hours;
            string ds = to_string(d);
            if (d>0.25)
            {
                answ = "Your Average work koeficent = " + ds;
            }
            else
                answ = "You are fired!";

            send(s_new, (char*)&answ[0], answ.size(), 0);
            cout << answ;
            from_len = recv(s_new, (char*)&buf, BUF_SIZE, 0);
            buf[from_len] = 0;
            msg1 = (string)buf;
            if (msg1 == "2") break;
        }
        cout << endl;
        cout << "client is lost";
        cout << " " << endl;
        closesocket(s_new);
    }
    return 0;
}
