from PySide6.QtWidgets import QMainWindow, QHBoxLayout, QVBoxLayout, QWidget, QGroupBox, QLabel, QPushButton, QLineEdit, QTextEdit
from PySide6.QtGui import QIcon, QPalette, QColor, QFont, QTextCursor
from PySide6.QtCore import Qt, QTimer
import pyqtgraph as pg
from MySerial import MySerial


class MainWindow(QMainWindow):
    promotie: str = "2023-2024"
    team: list[str] = [
        "IONASCU Bianca-Daniela",
        "TOADER Radu-Marian",
    ]
    serial: MySerial

    def __init__(self):
        super().__init__()

        # set serial
        self.serial = MySerial()
        self.serial.start("COM10", 115200)
        self.soundDataList = []
        self.timeList = []
        self.time = 0
        self.lightDataList = []
        
        # QTimer pentru apelul periodic undei functii de citire de pe serial
        self.timer = QTimer(self)
        self.timer.timeout.connect(self.read_data_timer)
        self.timer.start(100) # time for read

        self.setWindowTitle(f"Proiect Microprocesoare {self.promotie}")
        self.setWindowIcon(QIcon("./icon.png"))

        primary_layout = QVBoxLayout()
        secondary_layout = QHBoxLayout()
        tertiary_layout = QVBoxLayout()

        team_box = QGroupBox("Membrii echipei")
        bold_font = QFont()
        bold_font.setBold(True)
        team_box.setFont(bold_font)

        first_member = QLabel(f"Membru 1: {self.team[0]}")
        second_member = QLabel(f"Membru 2: {self.team[1]}")
        team_box_layout = QVBoxLayout()
        team_box_layout.addWidget(first_member, 1)
        team_box_layout.addWidget(second_member, 1)
        team_box.setLayout(team_box_layout)

        control_panel_box = QGroupBox("Control Panel")
        control_panel_box.setFont(bold_font)

        button1 = QPushButton("Change LED order")
        button1.clicked.connect(self.send_control_order)
        button2 = QPushButton("Play music")
        button2.clicked.connect(self.send_control_music)
        button4 = QPushButton("Get light status")
        button4.clicked.connect(self.get_light_status)
        button3 = QPushButton("Send")
        button3.clicked.connect(self.send_input)
        self.line_edit = QLineEdit()
        self.line_edit.setAlignment(Qt.AlignmentFlag.AlignBottom)
        line_edit_label = QLabel("Input:", parent=self.line_edit)
        control_panel_box_layout = QVBoxLayout()
        control_panel_box_layout.setSpacing(5)
        control_panel_box_layout.addWidget(button1, 1)
        control_panel_box_layout.addWidget(button2, 1)
        control_panel_box_layout.addWidget(button4, 1)

        control_panel_box_layout.addStretch()
        control_panel_box_layout.addWidget(line_edit_label)
        control_panel_box_layout.addWidget(self.line_edit, 1)
        control_panel_box_layout.addWidget(button3, 1)

        control_panel_box.setLayout(control_panel_box_layout)

        tertiary_layout.addWidget(team_box, 1)
        tertiary_layout.addWidget(control_panel_box, 5)

        #plot_widget = pg.PlotWidget()
        #plot_widget.plot(self.lightDataList, self.time)
        
        self.plot_widget = pg.PlotWidget()
        self.plot = self.plot_widget.plot(self.timeList, self.soundDataList)
        self.plot_widget.setYRange(0, 1)
        
        secondary_layout.addWidget(self.plot_widget, 3)
        secondary_layout.addLayout(tertiary_layout, 1)

        primary_layout.addLayout(secondary_layout, 4)
        self.text_edit = QTextEdit()
        self.text_edit.setReadOnly(True)

        debug_box = QGroupBox("Debug")
        debug_box_layout = QVBoxLayout()
        debug_box_layout.addWidget(self.text_edit, 1)
        debug_box.setLayout(debug_box_layout)

        primary_layout.addWidget(debug_box, 1)

        widget = QWidget()
        widget.setLayout(primary_layout)
        
        self.setCentralWidget(widget)

    def add_text_debug(self, text: str, control: int):
        if(control == 0):
            self.text_edit.insertPlainText(f"CONTROL: {text}\n")
        elif(control == 1):
            self.text_edit.insertPlainText(f"INPUT: {text}\n")
        else:
            self.text_edit.insertPlainText(f"UNKNOWN: {text}\n")
        self.text_edit.verticalScrollBar().setValue(self.text_edit.verticalScrollBar().maximum())

    def read_data_timer(self):
        receivedData = self.serial.receiveData(4)
        majorSound = chr(receivedData[0])
        minorSound1 = chr(receivedData[1])
        minorSound2 = chr(receivedData[2])
        soundData = float(f"{majorSound}.{minorSound1}{minorSound2}")
        lightData = chr(receivedData[3])
        
        print("Sound data", end='')
        print(soundData)
        print("Light data", end='')
        print(lightData)

        self.time += 1
        self.soundDataList.append(soundData)
        self.timeList.append(self.time)
        self.lightDataList.append(lightData)
        self.soundDataList = self.soundDataList[-100:]
        self.timeList = self.timeList[-100:]
        self.lightDataList = self.lightDataList[-100:]
        self.plot.setData(self.timeList, self.soundDataList)
                

    def send_input(self):
        input = self.line_edit.text()
        self.line_edit.clear()
        self.add_text_debug(input, 1)
        self.serial.sendData(input)

    def send_control_order(self):
        self.serial.sendData("c")
        self.add_text_debug("Change led order", 0)

    def send_control_music(self):
        self.serial.sendData("m")
        self.add_text_debug("Playing music...", 0)
        
    def get_light_status(self):
        # trebuie modificat
        received = self.lightDataList[-1]
        # activ pe 0
        if(received == b'0'):
            self.add_text_debug("Afara este lumina!", 2)
        else:
            self.add_text_debug("Afara este intuneric!", 2)
            
