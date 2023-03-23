import networkx as nx				# graphs and layouts
import matplotlib.pyplot as plt		# draw graphs
import csv 							# read graphs from file

# return a list of pairs of connected vertices in graph
def GetPairs(fileAddress):
	# result is adjacency list of vertices
	result=[]
	with open(fileAddress) as file:
		reader = csv.reader(file)
		for row in reader:
			result.append([s.strip() for s in row])
	return result

# draw graph from 'fileAddress' in a structure descibed in 'structure'
# param structure is in ['graph', 'tree']
def Draw(fileAddress, structure="graph"):
	assert structure in ["graph", "tree"]
	# create graph object
	myGraph=nx.Graph()
	# initialize list of edges from CSV
	edgeList=GetPairs(fileAddress)
	# initialize graph from adjacency list
	myGraph.add_edges_from(edgeList)


	if structure == "graph":
		# circular arrangement of nodes
		pos = nx.circular_layout(myGraph)
	elif structure == "tree":
		# k-ary tree
		pos = nx.nx_agraph.graphviz_layout(myGraph, prog="dot")

	# draw graph with nodes in evenly 
	# distributed coordinate positions
	# myTree = nx.balanced_tree(2, 5)
	nx.draw_networkx(myGraph, pos=pos)

	# show matplotlib plot
	plt.tight_layout()
	# plt.axis('circular')
	plt.show()

	# save result as a png
	nx.draw_networkx(myGraph, pos=pos)
	plt.savefig("out/GraphImage.png")
	# close plot
	plt.close()


# string address of file
graphFileAddress = 'data/graph.csv'
treeFileAddress = 'data/tree.csv'

Draw(graphFileAddress, structure="graph")
Draw(treeFileAddress, structure="tree")

