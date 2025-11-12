import socket


port = 5050
server1 = "172.19.32.1"
header = 64
format = 'utf-8'
disconnet_msg = "!DISCONNECT"


ADDR=(server1, port)

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

client.connect(ADDR)


def send(msg):
    message = msg.encode(format)
    msg_length = len(message)
    send_length = str(msg_length).encode(format)
    send_length += b' ' * (header - len(send_length))
    client.send(send_length)
    client.send(message)
    print(client.recv(2048).decode(format))


send("Hello world!")
send(disconnet_msg)