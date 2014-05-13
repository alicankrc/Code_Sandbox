#    File:    Calculator.py
#    Author:  Marvin Smith
#    Date:    4/18/2014
#    
#    Purpose:  Simple Calculator Add-On
#

#  PyQt4
from PyQt4 import QtGui
from PyQt4.QtCore import *

#  Plugin Base
import PluginBase

#  Calculator Plug-In
class Calculator(PluginBase.PluginBase):
	
	#  Infix stack
	infixStack  = []

	#  Cursor to where in the dialog we are.  
	infixCursor = 0;

	#  This maps operators to their matching priority
	operatorDictionary = { '+':2, '-':2, '%':2, '*':4, '/':4, '^':5 };

	
	#  Constructor
	def __init__(self, parent = None):
		
		#  Create parent
		PluginBase.PluginBase.__init__(self, parent);

		#  Create Base Layout
		self.mainLayout = QtGui.QVBoxLayout();

		#  Create the main UI
		self.initUI()

		#  Set the main layout
		self.setLayout( self.mainLayout );


	#  Open the dialog box
	def openDialog(self):
		
		self.show();
		 
	
	#  Initialize the User Interface
	def initUI(self):
		
		#  set the title
		self.setWindowTitle('Calculator');
		
		#  Create the main layout
		self.mainLayout = QtGui.QVBoxLayout();

		#  Create the main editor
		self.buildCalculatorDisplay();
	
		#  Create button panel
		self.buildButtonPanel();

		#  Set the layout
		self.setLayout(self.mainLayout);
	


	#  Create the main display
	def buildCalculatorDisplay(self):

		#  Create main widget
		self.displayWidget = QtGui.QWidget();
		self.displayLayout = QtGui.QVBoxLayout();

		#  Create the editor
		self.displayEdit   = QtGui.QTextEdit();
		self.displayEdit.setReadOnly(True);
		self.displayEdit.installEventFilter(self);
		self.displayLayout.addWidget( self.displayEdit );

		#  Grab the cursor
		self.displayCursor = self.displayEdit.textCursor();
		self.displayCursor.insertText("Command > ");

		#  Set the layout
		self.displayWidget.setLayout( self.displayLayout );
		self.mainLayout.addWidget(self.displayWidget);

	
	#  Create the button panel
	def buildButtonPanel(self):
		
		# create main widget
		self.buttonPanelWidget = QtGui.QWidget();
		self.buttonPanelLayout = QtGui.QGridLayout();

		# process
		self.buttonPanelEnterButton = QtGui.QToolButton();
		self.buttonPanelEnterButton.setText("Enter");
		self.buttonPanelEnterButton.setFixedWidth(100);
		self.buttonPanelEnterButton.setFixedHeight(60);
		self.buttonPanelEnterButton.clicked.connect(self.calculate);
		self.buttonPanelLayout.addWidget(self.buttonPanelEnterButton, 0, 0 );


		#  clear
		self.buttonPanelClearButton = QtGui.QToolButton();
		self.buttonPanelClearButton.setText('Clear');
		self.buttonPanelClearButton.setFixedWidth(100);
		self.buttonPanelClearButton.setFixedHeight(60);
		self.buttonPanelClearButton.clicked.connect(self.clearDisplay);
		self.buttonPanelLayout.addWidget(self.buttonPanelClearButton, 0, 1);
		
		#  set widget
		self.buttonPanelWidget.setLayout(self.buttonPanelLayout);
		self.mainLayout.addWidget(self.buttonPanelWidget);
	

	# Process Keyboard Inputs
	def eventFilter(self, obj, event):

		if event.type() == QEvent.KeyPress:
			
			#  Process Data
			if event.key() == Qt.Key_Enter or event.key() == 13 or event.key() == Qt.Key_Return:
				self.calculate();
			
			# Add number keys
			elif event.key() < 255 and self.isValidOperandCharacter(chr(event.key())):
				self.displayCursor.insertText(chr(event.key()));
				self.infixStack.append(chr(event.key()));
				self.infixCursor += 1
			
			#  Add main operators
			elif event.key() < 255 and self.isValidOperatorCharacter(chr(event.key())):
				self.displayCursor.insertText(chr(event.key()));
				self.infixStack.append(chr(event.key()));
				self.infixCursor += 1

			#  Add Parenthesis
			elif event.key() == ord('(') or event.key() == ord(')'):
				self.displayCursor.insertText(chr(event.key()));
				self.infixStack.append(chr(event.key()));
				self.infixCursor += 1
			
			#  Add exponent
			elif event.key() == ord('^'):
				self.displayCursor.insertText(chr(event.key()));
				self.infixStack.append(chr(event.key()));
				self.infixCursor += 1
		
			#  Process a spacebar
			elif event.key() == ord(' '):
				self.displayCursor.insertText(chr(event.key()));
				self.infixStack.append(chr(event.key()));
				self.infixCursor += 1
				
			#  Remove a key
			elif event.key() == Qt.Key_Backspace:
				if self.infixCursor > 0:
					self.infixCursor -= 1
					self.infixStack = self.infixStack[:self.infixCursor] + self.infixStack[(self.infixCursor+1):];
					self.displayCursor.deletePreviousChar();


		return False;


	def calculate(self):

		#  Convert the infix notation to postfix notation
		postfixStack = self.convertInfixToPostfix(self.cleanInfix(self.infixStack));
		
		#  Compute a solution
		solution = self.solvePostfix(postfixStack);

		#  Set the console to the solution
		self.displayCursor.insertText("\nSolution: " + solution + "\n");
		self.displayCursor.insertText("\nCommand > ");
		self.displayEdit.ensureCursorVisible();

		#  Reset the stack
		self.infixStack = []
		self.infixCursor = 0;

		

	def cleanInfix(self, data):
		
		output = []
		for x in data:
			if self.isValidCharacter(x):
				output.append(x);

		return output;

	
	def isValidCharacter(self, data):
		if self.isValidOperandCharacter(data):
			return True;
		elif self.isValidOperatorCharacter(data):
			return True;
		else:
			return False;
	

	#------------------------------------------------------------#
	#-     Test if the input character is a valid operand       -#
	#------------------------------------------------------------#
	def isValidOperandCharacter(self, data):
		if data >= '0' and data <= '9':
			return True;
		return False;
	
	
	#---------------------------------------------------------#
	#-    Test if the input character is a valid operator    -#
	#---------------------------------------------------------#
	def isValidOperatorCharacter(self, data):
		if data == '+' or data == '-' or data == '*' or data == '/' or data == '%':
			return True;
		return False;

	
	#------------------------------------------------------#
	#-    Convert the infix notation array to postfix     -#
	#------------------------------------------------------#
	def convertInfixToPostfix( self, infixData ):
		
		#  Create output
		postfixData = [];

		#  List of operators
		operatorStack = [];
		tempOperand = ''
		
		#  Iterate over the infix notation elements
		for i in xrange(0, len(infixData)):
			
			print 'starting loop ', i
			print '  infix  : ', infixData
			print '  postfix: ', postfixData
			print '  opstack: ', operatorStack
			print '  temp op: ', tempOperand
			print ''

			# if we have an integer, add it to the temporary value
			if self.isValidOperandCharacter(infixData[i]):	
				tempOperand += infixData[i];

			#  Otherwise, annotate the end of the operator and add to the stack
			else:
				#  Make sure the operand is of valid length
				if len(tempOperand) <= 0:
					raise Exception('error here')
				
				postfixData.append(tempOperand);
				tempOperand = ''

				# If the item is an operator, then add it to the operator stack
				print '-> ii: (',infixData[i],")"
				if len(operatorStack) == 0 or self.operatorALessThanB(operatorStack[-1], infixData[i]) == True:
					operatorStack.append(infixData[i]);
				else:
					while len(operatorStack) > 0 and self.operatorALessThanB(operatorStack[-1], infixData[i]) == False:
						postfixData.append(operatorStack[-1]);
						operatorStack = operatorStack[0:len(operatorStack)-1];

					postfixData.append(infixData[i]);

		#  Add any remaining operands
		if not tempOperand == '':
			postfixData.append(tempOperand);
			tempOperand=''

		#  Append the operator stack to the output
		while len(operatorStack) > 0:
			postfixData.append(operatorStack[-1])
			operatorStack = operatorStack[:len(operatorStack)-1];
		

		print('PostfixData: ', postfixData)
		return postfixData

	
	#--------------------------------------------------------------------#
	#-   Test if the precedence of Operator A is less than operator B   -#
	#--------------------------------------------------------------------#
	def operatorALessThanB( self, a, b):
		if self.operatorDictionary[a] < self.operatorDictionary[b]:
			return True;
		else:
			return False;


	def solvePostfix(self, postfixStack):
		
		#  Start popping values until we hit an operator
		operandStack = []
		
		postfixData = postfixStack;
		while len(postfixData) > 0:
			
			#  Pop next value
			value = postfixData[0];
			postfixData = postfixData[1:];
			
			#  If the value is an operand, add it to the stack
			if self.isOperand(value):
				operandStack.append(float(value));

			#  Otherwise, apply the operator
			else:
				op1 = operandStack[-2];
				op2 = operandStack[-1];
				operandStack = operandStack[:len(operandStack)-2]


				result = self.applyOperation( op1, op2, value);
				operandStack.append(result);
		
		return str(operandStack[0]);



	#-------------------------------------------------------#
	#-    Apply the operator against the input operands    -#
	#-------------------------------------------------------#
	def applyOperation(self, op1, op2, value):
		
		#  Multiplication
		if value == '*':
			return op1*op2;

		#  Division
		if value == '/':
			return op1/op2;

		#  Modulo
		if value == '%':
			return op1%op2;

		#  Addition
		if value == '+':
			return op1+op2;

		#  Subtraction
		if value == '-':
			return op1-op2;

		raise Exception('Unknown operator: ' + value );


	def isOperand(self, data):
		
		try:
			value = float(data);
		except:
			return False;
		return True;
	
	def isOperator(self,data):
		return self.isValidOperatorCharacter(data);


	#  Get the icon size to show on the toolbar
	def getButtonIconSize(self):
		return QSize(70,70);

	#   Get the text to display on the tool button
	def getButtonText(self):
		return 'Calculator'
	
	#  Get the filepath to the calculator image
	def getButtonIconPath(self):
		return 'calculator.png';
	

	#  Clear all contents on the display
	def clearDisplay(self):
		
		#  Wipe out the display
		self.displayEdit.clear();
		self.displayCursor = self.displayEdit.textCursor();
		self.displayCursor.insertText("Command > ");

