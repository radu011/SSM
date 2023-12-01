import serial

class MySerial():
    port: str
    baudRate: int
    connection: serial.Serial

    def __init__(self):
        pass

    def start(self, port:str, baudRate:int):
        self.port = port
        self.baudRate = baudRate
        self.connection = serial.Serial(port=self.port, baudrate=self.baudRate)
        self.connection.close()
        self.connection.open()

    def sendData(self, data: str) -> int:
        return self.connection.write(bytes(data, 'utf-8'))

    def receiveData(self, noBytes: int) -> str:
        return self.connection.read(noBytes)
    
    def receiveDataLine(self) -> str:
        return self.connection.readline()
    
    def stop(self):
        self.port = ''
        self.baudRate = 0
        self.connection.close()
        self.connection = None


# def main():
#     conn = MySerial()
#     conn.start(port = "COM10", baudRate = 115200)
#     conn.sendData("m")
#     #print(conn.receiveData(conn, 4))


# if __name__ == "__main__":
#     main()

