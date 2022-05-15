import sys
import socket

BUFSIZE = 512
# py client.py 192.168.1.19 9990

def client(sHOST,sPORT):
    s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)

    s.connect((sHOST,sPORT))
    for i in range(0,5):
        s.sendall(f"Message {i}".encode('utf-8'))
        response = s.recv(BUFSIZE)
        print(str(response.decode('utf-8')))
    s.close()

client(sys.argv[1],int(sys.argv[2]))