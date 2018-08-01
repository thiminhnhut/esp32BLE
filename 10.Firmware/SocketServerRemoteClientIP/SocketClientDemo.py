import socket

sock = socket.socket()

host = "192.168.0.103" #ESP32 IP in local network
port = 80             #ESP32 Server Port

sock.connect((host, port))
sock.send("Hello ESP32 Socket Server")
sock.close()
