import glob
import os.path
import sys
from PyQt4 import uic

UI_FILES = 'XML/*.ui'

def compile_ui():
   uifiles = glob.glob(UI_FILES)
   if len(uifiles) == 0:
      print 'none!'
      return 
   with open('Generated/generatedGUI.py', 'w+b') as pyfile:
	for uifile in uifiles:
	   uic.compileUi(uifile, pyfile)
   pyfile.close()

if __name__ == '__main__':
   compile_ui()
