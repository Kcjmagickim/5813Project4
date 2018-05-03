import sys

def LogID(lin):
    if (lin=="10"): return "System ID:"
    if (lin=="11"): return "System Version:"
    if (lin=="12"): return "Logger Initialized"
    if (lin=="13"): return "GPIO Initizlized"
    if (lin=="14"): return "System Initialized"
    if (lin=="15"): return "System Halted"
    if (lin=="16"): return "Info:"
    if (lin=="17"): return "Warning:"
    if (lin=="18"): return "Error:"
    if (lin=="19"): return "Profiling Started"
    if (lin=="20"): return "Profiling Result"
    if (lin=="21"): return "Profiling Completed"
    if (lin=="22"): return "Data Received: "
    if (lin=="23"): return "Starting Data Analysis . . ."
    if (lin=="24"): return "Number of alphabets:"
    if (lin=="25"): return "Number of numbers:"
    if (lin=="26"): return "Number of punctuations:"
    if (lin=="27"): return "Number of miscellaneous characters:"
    if (lin=="28"): return "Data Analysis Completed"
    if (lin=="29"): return "Heartbeat (1Hz)"
    if (lin=="30"): return "Core Dump:"
    else: return "Sth else"

def Timestamp(time,h,m,s):
    time = int(time) - 100
    s = int(s)
    m = int(m)
    h = int(h)
    if time<100:
        s += time
        if s>60:
            m+=1
            s-=60
    else:
        sec = time%100
        mi = time/100
        s += sec
        if s>60:
            m += 1
            s -= 60
        m+=mi
        if m>60:
            h += 1
            m -= 60
    return (str(h)+":"+str(m)+":"+str(s))     

def SRC(lin):
    if (lin=="13"): return "main.c"
    if (lin=="18"): return "port.c"
    if (lin=="15"): return "uart.c"
    if (lin=="11"): return "rtc.c"
    if (lin=="12"): return "logger.c"


h,m,s=input("Enter the execution time in for hh:mm:ss - ").split(':')
file = open("try1.txt", "r") 
while True:
    li = file.read(2)
    if not li: break
    lin = LogID(li)
    li = file.read(1)
    li = file.read(2)
    #mod = SRC(src)
    direc = SRC(li)
    #dosth
    li = file.readline()
    time = li[len(li)-4:len(li)-1]
    #print(time)
    ts = Timestamp(time,h,m,s)
    payload = li[4:len(li)-6]
    if (payload == "NA "):
        payload = ""
    checksum = li[len(li)-6:len(li)-5]
    if(checksum!="1"):
        print("Checksum failed. Aborting parsing")
        sys.exit()
    print(ts+" "+direc+" "+lin+" "+payload)
file.close()
