import socket

SERVER_IP = "127.0.0.1"   
SERVER_PORT = 6000

client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

print("UDP client ready")

for i in range(5):
    msg = input(f"Client message {i+1}: ")
    client.sendto(msg.encode(), (SERVER_IP, SERVER_PORT))

    reply, addr = client.recvfrom(1024)
    print("Server replied:", reply.decode())

client.close()

