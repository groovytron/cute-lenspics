import sys
from PyQt5.QtWidgets import QApplication
from lens_photomaton.widgets import CameraWidget


if __name__ == '__main__':
    app = QApplication(sys.argv)
    widget = CameraWidget()
    widget.show()
    sys.exit(app.exec_())
