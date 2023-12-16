from PySide6.QtWidgets import QMainWindow, QHBoxLayout, QVBoxLayout, QWidget, QGroupBox, QLabel, QPushButton, QLineEdit, QTextEdit
from PySide6.QtGui import QIcon, QPalette, QColor, QFont, QTextCursor
from PySide6.QtCore import Qt
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

        plot_widget = pg.PlotWidget()
        hour = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
        temperature = [30, 32, 34, 32, 33, 31, 29, 32, 35, 45]
        plot_widget.plot(hour, temperature)
        
        secondary_layout.addWidget(plot_widget, 3)
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

    def add_text_debug(self, text: str, control: bool):
        if(control is True):
            self.text_edit.insertPlainText(f"CONTROL: {text}\n")
        else:
            self.text_edit.insertPlainText(f"INPUT: {text}\n")
        self.text_edit.verticalScrollBar().setValue(self.text_edit.verticalScrollBar().maximum())

    def send_input(self):
        input = self.line_edit.text()
        self.line_edit.clear()
        self.add_text_debug(input, False)
        self.serial.sendData(input)

    def send_control_order(self):
        self.serial.sendData("c")
        self.add_text_debug("Change led order", True)

    def send_control_music(self):
        self.serial.sendData("m")
        self.add_text_debug("Playing music...", True)
        
    def get_light_status(self):
        self.serial.sendData("l")
        received = self.serial.receiveData(1)
        # activ pe 0
        if(received == b'0'):
            self.add_text_debug("Afara este lumina!", True)
        else:
            self.add_text_debug("Afara este intuneric!", True)
            
