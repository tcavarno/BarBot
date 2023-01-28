import serial
def main():
    ser = serial.Serial('/dev/ttyACM0',115200,timeout=1)

    while(True):
        ser.write("test".encode())
        s = ser.readlines()
        print(s.decode().strip())
        print("has")



if __name__ == "__main__":
    main()