import serial

serial_port = 'COM16'
baud_rate = 115200
filename = "logger.txt"

f = open(filename, "a+")

ser = serial.Serial(serial_port, baud_rate)

while True:
	line = ser.readline()
	line = line.decode("utf-8")
	print(line)
	f.write(line)
