import serial
import json, pyaudio
from vosk import Model, KaldiRecognizer

symbols = [100000, 110000, 10111, 110110, 100110, 100010, 100001, 10110, 101011, 10100,
111101, 101000, 111000, 101100, 101110, 101010, 111100, 111010, 11100, 11110, 101001,
110100, 110010, 100100, 111110, 100011, 101101, 111011, 11101, 10101, 110011, 110101]

alph = ' абвгдеёжзийклмнопрстуфхцчшщъыьэюя'


def text_to_syms(text):
    res = []
    
    for i in text:
        res.append(symbolsi[alph.find(i)])
    
    return res


model = Model('')

rec = KaldiRecognizer(model, 1600)
p = pyaudio.pyaudio
stream = p.open(format=pyaudio.paInt16, channels=1, rate=1600, input=True, frames_per_buffer=8000)
stream.start_stream()


def listen():
    while True:
        data = stream.read(4000, exception_on_overflaw=False)
        
        if (rec.AcceptWaveform(data)) and (len(data) > 0):
            answer = json.loads(rec.Result())
            if answer['text']:
                yield answer['text']





ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
ser.reset_input_buffer()
while True:
    for text in listen():
        print(text)
    if ser.in_waiting > 0:
        line = ser.readline().decode('utf-8').rstrip()
        print(text_to_syms(line))