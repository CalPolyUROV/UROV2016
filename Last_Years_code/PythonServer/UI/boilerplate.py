__author__ = 'Aaron'

import sys
import random
import time
from PyQt4 import QtGui, QtCore
from Generated.generatedGUI import  Ui_MainWindow
from UI.main import Server
from UI.voltageTest import VoltageTest
from UI.connection import connectSignals


class Example(QtGui.QMainWindow):
    def __init__(self):
        super(Example, self).__init__()

        self.initUI()



    def initUI(self):
        self.statusBar().showMessage('Ready')
        self.setGeometry(300, 300, 250, 150)
        self.setWindowTitle('Statusbar')
        self.show()



def main():
    app = QtGui.QApplication(sys.argv)
    ex = Example()
    ui = Ui_MainWindow()
    ex.show()
    ui.setupUi(ex)
    server = Server()
    v = VoltageTest(ui)
    def run():
        time.sleep(0.5)
        server.update()
        server.x.connect(v.testVoltage)
        print "FINISHED CONNECTING SIGNAL"
        print "COCKSUCKING MOTHERFUCKING PYQT"
    while True:
        ex.show()
        ui.setupUi(ex)
        run()
        QtGui.qApp.processEvents()
    #sys.exit(app.exec_())


if __name__ == '__main__':
    main()



