import sys
import socket

BUFSIZE = 512
# py client.py 192.168.1.19 9990 - testowanie python-python
# py client.py 192.168.1.19 9990 1- testowanie python-cpp

def client(sHOST,sPORT,CPP=0):
    s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)

    s.connect((sHOST,sPORT))
    for i in range(0,5):
        print(s.send(f"Message {i}".encode('utf-8')))
        if CPP==0:
            response = s.recv(BUFSIZE)
            print(str(response.decode('utf-8')))
        else:
            pass
            #Gdy server nic nie wysyła. np brak echo
    s.close()

if len(sys.argv)==4:
    client(sys.argv[1],int(sys.argv[2]),int(sys.argv[3]))
else:
    client(sys.argv[1],int(sys.argv[2]))