from PySide6.QtCore import QTimer
from PySide6.QtWidgets import QMainWindow, QHBoxLayout, QVBoxLayout, QWidget, QGroupBox, QLabel, QPushButton, QLineEdit, QTextEdit
from PySide6.QtGui import QIcon, QPalette, QColor, QFont, QTextCursor
from PySide6.QtCore import Qt
import pyqtgraph as pg
from MySerial import MySerial
from main_window import MainWindow
from PySide6.QtWidgets import QApplication
from PySide6.QtGui import QScreen
import sys

class App(QMainWindow):

    def __init__(self):
        super().__init__()
        self.initUI()
    
    def initUI(self):
        # Setăm titlul și dimensiunea ferestrei
        self.setWindowTitle('Timer Example')
        self.setGeometry(100, 100, 200, 100)

        # Inițiem QTimer
        self.timer = QTimer(self)
        self.timer.timeout.connect(self.functia_mea)
        self.timer.start(1000)  # Timer-ul apelază functia_mea la fiecare 1000 ms (1 secundă)

    def functia_mea(self):
        print("Funcția a fost apelată.")

def main():
    app = QApplication(sys.argv)
    ex = App()
    ex.show()
    sys.exit(app.exec_())

if __name__ == '__main__':
    main()