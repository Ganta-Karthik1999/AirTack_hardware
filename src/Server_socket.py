import socket
import threading
import time


port = 5050
header = 64

format = 'utf-8'

disconnet_msg = "!DISCONNECT"
# server = "192.168.20.1"


server1 = socket.gethostbyname(socket.gethostname())

create_socket= socket.socket(socket.AF_INET, socket.SOCK_STREAM)

create_socket.bind((server1, port))

def handle_client_connection(conn,addr):
    print(f"[NEW CONNECTION] {addr} connected.")
    connected =True
    while connected:
           data_lenght = conn.recv(header).decode(format)
           if data_lenght:
                data_lenght = int(data_lenght)
                data = conn.recv(data_lenght).decode(format)

                if data == disconnet_msg:
                    connected = False
                    print(f"[{addr}] disconnected.")
                print(f"[{addr}] {data}")
                conn.send("Msg received".encode(format))
    conn.close()    

def start():
    create_socket.listen()
    print(f"[L ISTENING] Server is listening on {server1}:{port}")
    while True:
        conn, addr = create_socket.accept()
        thread = threading.Thread(target=handle_client_connection, args=(conn, addr))
        thread.start()
        print(f"[ACTIVE CONNECTIONS] {threading.active_count() - 1}")
        
         
print("server is starting...")
start()

