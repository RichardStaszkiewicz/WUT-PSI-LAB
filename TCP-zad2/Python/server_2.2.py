import sys
import socket


# HOST='192.168.1.19'
# PORT=8000
# py server.py 192.168.1.19 8000
# py server.py 192.168.1.19 8000 [BUFSIZE]

def server(HOST,PORT,BUFSIZE=512):
    print(f"Will listen on {HOST}:{PORT}")
    s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    s.bind((HOST,PORT))
    s.listen(6)

    while True:
        connection, addr = s.accept()
        with connection:
            print(f"Connection accepted from {addr}")
            while True:
                message = connection.recv(BUFSIZE)
                if not message:
                    break
                print(f"Received {message.decode('utf-8')}")
                print(connection.send(message))
        print("Connection closed by client" )
       
if len(sys.argv)==4:
    server(sys.argv[1],int(sys.argv[2]),int(sys.argv[3]))
else:
    server(sys.argv[1],int(sys.argv[2]))