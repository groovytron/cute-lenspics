import sys
from PyQt5.QtWidgets import QApplication, QMainWindow
from lens_photomaton.widgets import MainWindow

if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = MainWindow()
    sys.exit(app.exec_())
