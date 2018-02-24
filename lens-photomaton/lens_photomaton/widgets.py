from PyQt5 import QtCore, QtGui, uic
from PyQt5.QtWidgets import (QMainWindow, QWidget, QListWidgetItem,
                             QFileDialog, QAction, qApp, QMessageBox)
from PyQt5.QtGui import QImage, QPixmap, QPainter, QFont, QColor, QIcon
from PyQt5.QtCore import QTimer, QPoint, QFileInfo
import cv2
import re
from .forms.ui_camera_widget import Ui_CameraWidget


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.statusBar().showMessage(
            'Choose a directory where pictures will be saved.')
        self.setWindowTitle('Lens Photomaton')
        self.camera_widget = CameraWidget(self)
        self.setCentralWidget(self.camera_widget)
        self.create_menubar()
        self.show()

    def create_menubar(self):
        save_dir_action = QAction('Set &working directory', self)
        save_dir_action.setShortcut('Ctrl+W')
        save_dir_action.setStatusTip(
            'Set the directory where pictures will be saved')
        save_dir_action.triggered.connect(
            self.camera_widget.set_save_directory)

        exit_action = QAction('&Exit', self)
        exit_action.setShortcut('Ctrl+Q')
        exit_action.setStatusTip('Exit application')
        exit_action.triggered.connect(qApp.quit)

        menu_bar = self.menuBar()

        file_menu = menu_bar.addMenu('&File')
        file_menu.addAction(save_dir_action)
        file_menu.addAction(exit_action)


class CameraWidget(QWidget, Ui_CameraWidget):
    def __init__(self, main_window):
        super(CameraWidget, self).__init__()
        self.main_window = main_window
        self.camera = None
        self.video_process = None
        self.image_text = "No serial number found"
        self.save_dir_name = ""

        self.setupUi(self)
        self.init_ui()
        self.connect_signals()
        # self.set_save_directory()

    def init_ui(self):
        self.cameraList.setEnabled(False)
        self.pictureButton.setEnabled(False)
        self.clearButton.setEnabled(False)
        self.inputText.setEnabled(False)
        self.imageLabel.setText("No camera feed")

        cameras_count = self.count_cameras()

        for i in range(cameras_count):
            camera_list_item = QListWidgetItem("Camera %i" % i)
            self.cameraList.addItem(camera_list_item)

    def connect_signals(self):
        self.cameraList.currentRowChanged.connect(self.set_camera)
        self.pictureButton.clicked.connect(self.save_picture)
        self.clearButton.clicked.connect(self.clear_input)
        self.inputText.textChanged.connect(self.update_label)

    def clear_input(self):
        self.inputText.clear()
        self.inputText.setFocus()

    def set_save_directory(self):
        self.save_dir_name = str(
            QFileDialog.getExistingDirectory(self, "Select Directory"))
        self.cameraList.setEnabled(True)
        self.update_controls()

    def update_controls(self):
        self.clearButton.setEnabled(self.cameraList.isEnabled())
        self.pictureButton.setEnabled(self.cameraList.isEnabled())
        self.inputText.setEnabled(self.cameraList.isEnabled())

        if self.cameraList.isEnabled() and self.camera is not None:
            self.inputText.setFocus()
            self.main_window.statusBar().showMessage(
                'You can now start scanning and save your pictures.')
        else:
            self.main_window.statusBar().showMessage('Choose a camera')

    def check_serial_number(self):
        return re.search('F\d{8}', self.inputText.text())

    def update_label(self, text):
        match = self.check_serial_number()
        self.inputText.setText(text.upper())

        if match is not None:
            self.image_text = match.group(0)
            self.inputText.setText(self.image_text)
        else:
            self.image_text = "No serial number found"

    def set_camera(self, camera_id):
        self.camera = cv2.VideoCapture(camera_id)
        self.main_window.statusBar().showMessage(
            'You can now start scanning and save your pictures.')
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
            image_name = self.image_text + ".png"
            save_path = image_name

            if self.save_dir_name != "":
                save_path = self.save_dir_name + "/" + image_name

            file_to_check = QFileInfo(save_path)

            if file_to_check.exists() and file_to_check.isFile():
                reply = QMessageBox.question(
                    self, 'File already exists',
                    'This file already exists. Do you want to overwrite it?',
                    QMessageBox.Yes | QMessageBox.No, QMessageBox.No)

                if reply == QMessageBox.No:
                    self.main_window.statusBar().showMessage(
                        'Save canceled for lens %s' % match.group(0))
                    return

            self.imageLabel.pixmap().save(save_path)
            self.main_window.statusBar().showMessage(
                'Picture saved in %s' % save_path)
            self.clear_input()
        else:
            self.main_window.statusBar().showMessage(
                'Please enter a valid serial number before saving')
            self.inputText.setFocus()

    def count_cameras(self):
        max_tested = 10
        for i in range(max_tested):
            temp_camera = cv2.VideoCapture(i)
            if temp_camera.isOpened():
                temp_camera.release()
                continue
            return i
