import serial
import time
import sys
'''
    Probaly should change this so that the pc user attempts to connect to the 
    mcu and the mcu sends a command ack. once the command ack is received then
    a state machine starts
'''
def ack(ser:serial.Serial):
    while(True):
        s = ser.readline()
        s = s.decode().strip()
        if s == "CONNECT_MCU":
            ser.write("CONNECT_ACK\n".encode())
            break
    print("\n\n Connected to the MCU!!!!\n\n")
    return True
            
def open_serial():
    ser = None
    try:
        ser = serial.Serial('/dev/ttyACM0',115200,timeout=1)
        print("Serial port opened. Waiting for ACK")
        ack(ser)
    except:
        print("Failed to Connect!!!!")

    return ("prompt",ser)

def prompt():
    print("\n\n-----------------------------------------------------")
    print("Welcome to the FlowTest Program! Valid Commands:")
    print("c -- Connect to the MCU")
    print("j xxxx -- Jog the fluid for xxxx number of ms")
    print("t xxxx -- Set the Target volume for PID in xxxx ml")
    print("p -- Start the PID Loop")
    print("-----------------------------------------------------\n\n")
    user_in = input()
    if(len(user_in) ==0):
        print("ERROR: Nothing Entered")
        return ("prompt",None)
    if(user_in == "c"):
        return ("connect",None)
    elif(user_in[0] == "j"):
        try:
            (state,val)= ("jog",int(user_in[2:]))
        except ValueError:
            print("ERROR: Invald Jog Time")
            return ("prompt",None) 
        return (state,val)
    elif(user_in[0] == "t"):
        try:
            (state,val)= ("target",int(user_in[2:]))
        except ValueError:
            print("ERROR: Invald Target Value")
            return ("prompt",None) 
        return (state,val)
    elif(user_in[0] == "p"):
        return ("pid",None)

    else:
        return ("prompt",None)


def jog(amount,ser: serial.Serial):
    print("\njogging the motor for " + str(amount) + " seconds\n")
    waiting_on_response = True
    while(waiting_on_response):
        command = "COMMAND_JOG/"+str(amount)+"\n"
        ser.write(command.encode())
        waiting_on_response = message_ack(ser,"JOG")
    return ("prompt",None)

def target(amount,ser: serial.Serial):
    print("\nSetting the target PID value to " + str(amount) + " ml\n")
    waiting_on_response = True
    while(waiting_on_response):
        command = "COMMAND_TARGET/"+str(amount)+"\n"
        ser.write(command.encode())
        waiting_on_response = message_ack(ser,"JOG")
    return ("prompt",None)

def pid(ser):
    print("Starting Pid")
    while(True):
        print("pid")
    return ("prompt",None)



def message_ack(ser: serial.Serial,s):
    count =0
    read =""
    while (read == "" and count < 3):
        print("Waiting for Ack")
        read = ser.readline().decode().strip()
        print(read)
        count +=1
    return read == ""
    

def main():
    ser = None
    state = "prompt"
    while(True):
        if(state == "prompt"):
            (state,val) = prompt()
        elif(state == "connect"):
            (state,ser) = open_serial()
        elif(state == "jog"):
            (state,val) = jog(val,ser)
        elif(state == "target"):
            (state,val) = target(val,ser)
        elif(state == "pid"):
            (state,val) = pid(ser)
        else:
            print("BAD STATE: Returning to Prompt")
            state = "prompt"
        

if __name__ == "__main__":
    main()