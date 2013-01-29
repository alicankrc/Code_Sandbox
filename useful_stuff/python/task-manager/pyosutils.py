import os, sys

def ls( dirname, filters = [] ):

	output = []
	
	#  Make sure the contents exist
	if os.path.exists( dirname ) == False:
		return []

	#  List the directory contents
	files = os.listdir(dirname)
	for filename in files:
		# Check for extension filters
		if len(filters) <= 0:
			output.append(dirname + '/' + filename)
		else:
			for filter in filters:
				if filter in filename:
					output.append( dirname + '/' + filename)
					continue

	return output

def rm( filename ):
	
	os.remove(filename)

