import socket

SERVER_IP = "127.0.0.1"   
SERVER_PORT = 5000

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect((SERVER_IP, SERVER_PORT))

print("Connected to TCP server")

for i in range(5):
    msg = input(f"Client message {i+1}: ")
    client.send(msg.encode())

    reply = client.recv(1024).decode()
    print("Server replied:", reply)

client.close()

