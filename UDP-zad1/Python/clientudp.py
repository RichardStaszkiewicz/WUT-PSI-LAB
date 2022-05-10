import socket
import time

HOST='192.168.1.13'
PORT=9900
SERVER = '192.168.1.18'
PORT_S = 8000
BUFSIZE = 1024

def client():
    s = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
    s.bind((HOST,PORT))

    for i in range(0,6):
        message = "abcd".encode('utf-8')
        s.sendto(message,(SERVER,PORT_S))
        data, address = s.recvfrom(BUFSIZE)
        print(f"{data.decode('utf-8')}")
        time.sleep(1)

    s.close()


client()
