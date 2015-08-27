#!/usr/bin/env python3
import socket
import serial
import sys
from time import sleep

arduino = None
try:
	print("Connecting to Arduino...")
	arduino = serial.Serial("COM3", 9600)
except serial.serialutil.SerialException:
	sys.exit("Error: Could not connect to Arduino.")

sleep(2)
arduino.write(b'\x99\x61')
print("Connected to Arduino.")
print("Switches not working? Make sure that your desk has MIDI enabled.")
print("WARNING: LSC maXim desks have a bug that causes a system reset on the desk if MIDI is enabled when turning it off. Remember to turn MIDI off before you turn off the desk!")

def handshake(address):
	if arduino is None:
		desksocket.sendto(b'\x00',addr)
	else:
		desksocket.sendto(b'\xCC',addr)

UDP_IP = "127.0.0.1"
UDP_PORT = 41585

desksocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM);
desksocket.bind((UDP_IP, UDP_PORT));
print("Server started on port {0}".format(str(UDP_PORT)));

while True:
	data, addr = desksocket.recvfrom(1024);
	if data == bytes("handshake","utf-8"):
		print("A client has sent a connection request, performing handshake...")
		handshake(addr)
		print("Handshake complete.");
	elif data[0] == 0x90 or data[0] == 0x80:
		arduino.write(data)