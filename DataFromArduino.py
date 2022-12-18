# import serial

# ser = serial.Serial('COM12', baudrate = 9600, timeout = 1)
# while 1:
#     ser_bytes = ser.readline()
#     # decoded_bytes = arduinoData[0:len(arduinoData) - 2].decode("utf-8")
#     # s1="".join(c for c in arduinoData if c.isdigit())
#     # some = arduinoData
#     decoded_bytes = ser_bytes[0:len(ser_bytes)-2].decode("utf-8")
#     # print(type(decoded_bytes))
#     if(decoded_bytes == "131"):
#         print("ДооооООо")

from tkinter import *
import serial.tools.list_ports
import functools
import math

ports = serial.tools.list_ports.comports()
serialObj = serial.Serial()

root = Tk()
root.config(bg='grey')

def initComPort(index):
    currentPort = str(ports[index])
    comPortVar = str(currentPort.split(' ')[0])
    print(comPortVar)
    serialObj.port = comPortVar
    serialObj.baudrate = 9600
    serialObj.open()

for onePort in ports:
    comButton = Button(root, text=onePort, font=('Calibri', '13'), height=1, width=45, command = functools.partial(initComPort, index = ports.index(onePort)))
    comButton.grid(row=ports.index(onePort), column=0)

dataCanvas = Canvas(root, width=600, height=400, bg='white')
dataCanvas.grid(row=0, column=1, rowspan=100)

vsb = Scrollbar(root, orient='vertical', command=dataCanvas.yview)
vsb.grid(row=0, column=2, rowspan=100, sticky='ns')

dataCanvas.config(yscrollcommand = vsb.set)

dataFrame = Frame(dataCanvas, bg="white")
dataCanvas.create_window((10,0),window=dataFrame,anchor='nw')

def freq_to_note(freq):
    freqe = int(freq)
    notes = ['A', 'A#', 'B', 'C', 'C#', 'D', 'D#', 'E', 'F', 'F#', 'G', 'G#']

    note_number = 12 * math.log2(freqe / 440) + 49  
    note_number = round(note_number)
        
    note = (note_number - 1 ) % len(notes)
    note = notes[note]
    
    return note


def checkSerialPort():
    if serialObj.isOpen() and serialObj.in_waiting:
        recentPacket = serialObj.readline()
        recentPacketString = recentPacket.decode('utf').rstrip('\n')
        note = freq_to_note(recentPacketString)
        Label(dataFrame, text=note, font=('Calibri','13'), bg='white').pack()

while True:
    root.update()
    checkSerialPort()
    dataCanvas.config(scrollregion=dataCanvas.bbox("all"))