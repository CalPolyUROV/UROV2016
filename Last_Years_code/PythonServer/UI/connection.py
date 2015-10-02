from voltageTest import VoltageTest


def connectSignals(ui):
    ui.pushButton_2.clicked.connect(VoltageTest.testVoltage, (ui, kwargs))
    print "CS : ", kwargs['voltage']
    ui.pushButton.clicked.connect(Process.openServerSubProcess)