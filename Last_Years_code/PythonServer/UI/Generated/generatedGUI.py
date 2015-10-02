# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'XML\metagui.ui'
#
# Created: Sat Apr 18 10:49:36 2015
#      by: PyQt4 UI code generator 4.11.3
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

try:
    _fromUtf8 = QtCore.QString.fromUtf8
except AttributeError:
    def _fromUtf8(s):
        return s

try:
    _encoding = QtGui.QApplication.UnicodeUTF8
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig, _encoding)
except AttributeError:
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig)

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName(_fromUtf8("MainWindow"))
        MainWindow.resize(604, 349)
        self.centralwidget = QtGui.QWidget(MainWindow)
        self.centralwidget.setObjectName(_fromUtf8("centralwidget"))
        self.lcdNumber = QtGui.QLCDNumber(self.centralwidget)
        self.lcdNumber.setGeometry(QtCore.QRect(30, 30, 231, 51))
        self.lcdNumber.setObjectName(_fromUtf8("lcdNumber"))
        self.lcdNumber_2 = QtGui.QLCDNumber(self.centralwidget)
        self.lcdNumber_2.setGeometry(QtCore.QRect(30, 120, 231, 51))
        self.lcdNumber_2.setObjectName(_fromUtf8("lcdNumber_2"))
        self.label = QtGui.QLabel(self.centralwidget)
        self.label.setGeometry(QtCore.QRect(210, 10, 46, 13))
        self.label.setObjectName(_fromUtf8("label"))
        self.label_2 = QtGui.QLabel(self.centralwidget)
        self.label_2.setGeometry(QtCore.QRect(210, 100, 46, 13))
        self.label_2.setObjectName(_fromUtf8("label_2"))
        self.lcdNumber_3 = QtGui.QLCDNumber(self.centralwidget)
        self.lcdNumber_3.setGeometry(QtCore.QRect(30, 210, 64, 23))
        self.lcdNumber_3.setObjectName(_fromUtf8("lcdNumber_3"))
        self.lcdNumber_4 = QtGui.QLCDNumber(self.centralwidget)
        self.lcdNumber_4.setGeometry(QtCore.QRect(130, 210, 64, 23))
        self.lcdNumber_4.setObjectName(_fromUtf8("lcdNumber_4"))
        self.lcdNumber_5 = QtGui.QLCDNumber(self.centralwidget)
        self.lcdNumber_5.setGeometry(QtCore.QRect(30, 260, 64, 23))
        self.lcdNumber_5.setObjectName(_fromUtf8("lcdNumber_5"))
        self.lcdNumber_6 = QtGui.QLCDNumber(self.centralwidget)
        self.lcdNumber_6.setGeometry(QtCore.QRect(130, 260, 64, 23))
        self.lcdNumber_6.setObjectName(_fromUtf8("lcdNumber_6"))
        self.label_3 = QtGui.QLabel(self.centralwidget)
        self.label_3.setGeometry(QtCore.QRect(30, 190, 46, 20))
        self.label_3.setObjectName(_fromUtf8("label_3"))
        self.label_4 = QtGui.QLabel(self.centralwidget)
        self.label_4.setGeometry(QtCore.QRect(130, 190, 46, 13))
        self.label_4.setObjectName(_fromUtf8("label_4"))
        self.label_5 = QtGui.QLabel(self.centralwidget)
        self.label_5.setGeometry(QtCore.QRect(30, 240, 46, 13))
        self.label_5.setObjectName(_fromUtf8("label_5"))
        self.label_6 = QtGui.QLabel(self.centralwidget)
        self.label_6.setGeometry(QtCore.QRect(130, 240, 46, 13))
        self.label_6.setObjectName(_fromUtf8("label_6"))
        self.pushButton = QtGui.QPushButton(self.centralwidget)
        self.pushButton.setGeometry(QtCore.QRect(460, 20, 111, 21))
        self.pushButton.setObjectName(_fromUtf8("pushButton"))
        self.pushButton_2 = QtGui.QPushButton(self.centralwidget)
        self.pushButton_2.setGeometry(QtCore.QRect(460, 50, 111, 21))
        self.pushButton_2.setObjectName(_fromUtf8("pushButton_2"))
        self.pushButton_3 = QtGui.QPushButton(self.centralwidget)
        self.pushButton_3.setGeometry(QtCore.QRect(460, 100, 111, 21))
        self.pushButton_3.setObjectName(_fromUtf8("pushButton_3"))
        self.pushButton_4 = QtGui.QPushButton(self.centralwidget)
        self.pushButton_4.setGeometry(QtCore.QRect(460, 140, 111, 21))
        self.pushButton_4.setObjectName(_fromUtf8("pushButton_4"))
        self.lcdNumber_7 = QtGui.QLCDNumber(self.centralwidget)
        self.lcdNumber_7.setGeometry(QtCore.QRect(280, 30, 161, 31))
        self.lcdNumber_7.setObjectName(_fromUtf8("lcdNumber_7"))
        self.lcdNumber_8 = QtGui.QLCDNumber(self.centralwidget)
        self.lcdNumber_8.setGeometry(QtCore.QRect(280, 90, 161, 31))
        self.lcdNumber_8.setObjectName(_fromUtf8("lcdNumber_8"))
        self.lcdNumber_9 = QtGui.QLCDNumber(self.centralwidget)
        self.lcdNumber_9.setGeometry(QtCore.QRect(280, 140, 161, 31))
        self.lcdNumber_9.setObjectName(_fromUtf8("lcdNumber_9"))
        self.label_7 = QtGui.QLabel(self.centralwidget)
        self.label_7.setGeometry(QtCore.QRect(410, 10, 46, 13))
        self.label_7.setObjectName(_fromUtf8("label_7"))
        self.label_8 = QtGui.QLabel(self.centralwidget)
        self.label_8.setGeometry(QtCore.QRect(380, 70, 46, 13))
        self.label_8.setText(_fromUtf8(""))
        self.label_8.setObjectName(_fromUtf8("label_8"))
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtGui.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 604, 21))
        self.menubar.setObjectName(_fromUtf8("menubar"))
        self.menuUROV = QtGui.QMenu(self.menubar)
        self.menuUROV.setObjectName(_fromUtf8("menuUROV"))
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtGui.QStatusBar(MainWindow)
        self.statusbar.setObjectName(_fromUtf8("statusbar"))
        MainWindow.setStatusBar(self.statusbar)
        self.menubar.addAction(self.menuUROV.menuAction())

        self.retranslateUi(MainWindow)
        QtCore.QObject.connect(self.pushButton, QtCore.SIGNAL(_fromUtf8("clicked()")), self.pushButton_2.animateClick)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow", None))
        self.label.setText(_translate("MainWindow", "CURRENT", None))
        self.label_2.setText(_translate("MainWindow", "VOLTAGE", None))
        self.label_3.setText(_translate("MainWindow", "M1", None))
        self.label_4.setText(_translate("MainWindow", "M2", None))
        self.label_5.setText(_translate("MainWindow", "M3", None))
        self.label_6.setText(_translate("MainWindow", "M4", None))
        self.pushButton.setText(_translate("MainWindow", "Solenoid 1", None))
        self.pushButton_2.setText(_translate("MainWindow", "Solenoid 2", None))
        self.pushButton_3.setText(_translate("MainWindow", "Electromagnet 1", None))
        self.pushButton_4.setText(_translate("MainWindow", "Push-button Motor", None))
        self.label_7.setText(_translate("MainWindow", "Depth", None))
        self.menuUROV.setTitle(_translate("MainWindow", "UROV", None))

