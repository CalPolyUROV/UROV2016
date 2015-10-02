from PyQt4 import QtCore
from Generated.generatedGUI import  Ui_MainWindow

class VoltageTest(QtCore.QObject):
    def __init__(self, ui):
        self.ui = ui
        super(VoltageTest, self).__init__()

    @QtCore.pyqtSlot(int)
    def testVoltage(self, voltage):
       # voltage = self.ui.lcdNumber.value()
        self.ui.lcdNumber.display(voltage)
