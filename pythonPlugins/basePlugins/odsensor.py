import abc

class OdSensor(object):
	__metaclass__  = abc.ABCMeta

	@abc.abstractmethod
	def __init__(self, params):
		"""constructor"""

	@abc.abstractmethod
	def getParamsType(self):
		"""must return a list with the types expected at the params variable in the init function"""

	@abc.abstractmethod
	def getInstructions(self):
		""" must return a string with the instructions to make this component"""

	@abc.abstractmethod
	def readOD(self, communications):
		"""must return a real number with the optical density read by the sensor, 
		communication with the machine must be done via communications object
		ommunications object has the next api:
				*) nbytessend sendString(string) -- send the string to the machine, return the bytes sended;
				*) string receiveString() -- receive and returns a string from the machine (stops when \n is received), can block;
				*) string readUntil(endCharacter) -- returns a string received from the machine, stops when the endCharacter arrives;
				*) void synch() -- synchronize with the machine, not always necesary, only for protocols compatibles;
		"""
