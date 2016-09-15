import abc

class Extractor(object):
	__metaclass__  = abc.ABCMeta
	
	continuous = 0
	discrete = 1
	irrelevant = 2

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
	def getMovementType(self):
		""" must return the movement type of this extractor:
			or Extractor.continuous or Extractor.discrete or Extractor.irrelevant
		"""

	@abc.abstractmethod
	def extractLiquid(self, rate, communications):
		"""must send instructions via communications object to extract liquid from the container
			communications object has the next api:
				*) nbytessend sendString(string) -- send the string to the machine, return the bytes sended;
				*) string receiveString() -- receive and returns a string from the machine (stops when \n is received), can block;
				*) string readUntil(endCharacter) -- returns a string received from the machine, stops when the endCharacter arrives;
				*) void synch() -- synchronize with the machine, not always necesary, only for protocols compatibles;
		"""