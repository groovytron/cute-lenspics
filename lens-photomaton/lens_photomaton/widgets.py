from PyQt5 import QtCore, QtGui, uic
from PyQt5.QtWidgets import QWidget, QListWidgetItem, QFileDialog
from PyQt5.QtGui import QImage, QPixmap, QPainter, QFont, QColor
from PyQt5.QtCore import QTimer, QPoint
import cv2
import re
from .forms.ui_camera_widget import Ui_CameraWidget

class CameraWidget(QWidget, Ui_CameraWidget):
    def __init__(self):
        super(CameraWidget, self).__init__()

        self.camera = None
        self.video_process = None
        self.image_text = "No serial number found"
        self.save_dir_name = ""

        self.setupUi(self)
        self.init_ui()
        self.connect_signals()
        # self.set_save_directory()

    def init_ui(self):
        # self.cameraList.setEnabled(False)
        # self.pictureButton.setEnabled(False)
        self.inputText.setText("Enter a serial number")
        self.imageLabel.setText("No camera feed")

        cameras_count = self.count_cameras()

        for i in range(cameras_count):
            camera_list_item = QListWidgetItem("Camera %i" % i)
            self.cameraList.addItem(camera_list_item)

    def connect_signals(self):
        self.cameraList.currentRowChanged.connect(self.set_camera)
        self.pictureButton.clicked.connect(self.save_picture)
        self.inputText.textChanged.connect(self.update_label)

    def set_save_directory(self):
        self.save_dir_name = str(
            QFileDialog.getExistingDirectory(self, "Select Directory"))

    def check_serial_number(self):
        return re.search('F\d{8}', self.inputText.text())

    def update_label(self, text):
        match = self.check_serial_number()

        if match is not None:
            self.image_text = match.group(0)
            self.inputText.setText(self.image_text)
        else:
            self.image_text = "No serial number found"

    def set_camera(self, camera_id):
        self.camera = cv2.VideoCapture(camera_id)
        self.timer = QTimer()
        self.timer.timeout.connect(self.display_video_stream)
        self.timer.start(30)

    def display_video_stream(self):
        """Read frame from camera and repaint QLabel widget.
        """
        _, frame = self.camera.read()
        frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        frame = cv2.flip(frame, 1)
        image = QImage(frame, frame.shape[1], frame.shape[0], frame.strides[0],
                       QImage.Format_RGB888)
        qpixmap = QPixmap.fromImage(image)
        qpixmap.scaledToWidth(780)
        self.imageLabel.setPixmap(qpixmap)
        painter = QPainter(self.imageLabel.pixmap())
        painter.setFont(QFont("Arial", 24))
        painter.setPen(QColor(255, 0, 0))
        painter.drawText(QPoint(20, 30), self.image_text)

    def save_picture(self):
        match = self.check_serial_number()
        if match is not None:
            self.image_text = match.group(0)
            save_path = self.image_text

            if self.save_dir_name != "":
                save_path = self.save_dir_name + "/" + self.image_text

            self.imageLabel.pixmap().save(save_path + ".png")

    def count_cameras(self):
        max_tested = 10
        for i in range(max_tested):
            temp_camera = cv2.VideoCapture(i)
            if temp_camera.isOpened():
                temp_camera.release()
                continue
            return i
