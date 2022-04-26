import socket

HOST='192.168.1.19'
PORT=8000
BUFSIZE=1024

def server():
    print(f"Will listen on {HOST}:{PORT}")

    s = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
    s.bind((HOST,PORT))

    while True:
        data, address = s.recvfrom(BUFSIZE)
        print(f"Message: {data.decode('utf-8')} from: {address}")
        if not data:
            print("No data")
            break
        s.sendto("received".encode('utf-8'),address)

    s.close()

server()