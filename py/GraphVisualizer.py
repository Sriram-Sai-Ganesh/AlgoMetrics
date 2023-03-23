import networkx as nx				# create graph object
import matplotlib.pyplot as plt		# draw graphs
import csv 							# read graphs from file
import pydot						# 
from networkx.drawing.nx_pydot import graphviz_layout	# pretty trees

# return a list of pairs of connected vertices in graph
def GetPairs(fileAddress):
	# result is adjacency list of pairs
	result=[]
	with open(fileAddress) as file:
		reader = csv.reader(file)
		for row in reader:
			result.append([s.strip() for s in row])
	return result


# takes a CSV file address as parameter
# draws an undirected unweighted graph with contents of file
def DrawUndirectedUnweightedGraph(fileAddress):
	# create graph object
	myGraph=nx.Graph()
	# initialize list of edges from CSV
	edgeList=GetPairs(fileAddress)
	# initialize graph from adjacency list
	myGraph.add_edges_from(edgeList)
	
	# calculate positions of graph nodes (coordinates of edges 
	# in the matplotlib plot) optimizing positions to 
	# obtain a circular node layout 
	pos = nx.circular_layout(myGraph)

	# draw graph with nodes in evenly 
	# distributed coordinate positions
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


# takes a CSV file address as parameter
# draws a k-ary tree with contents of file
def DrawTree(fileAddress):
	# create graph object
	myTree=nx.Graph()
	# initialize list of edges from CSV
	edgeList = GetPairs(fileAddress)
	# initialize graph from adjacency list
	myTree.add_edges_from(edgeList)
	# myTree = nx.balanced_tree(2, 5)
	# get positions of graph nodes in matplotlib window,
	# in order to draw as a tree
	pos = graphviz_layout(myTree, prog="dot")

	nx.draw_networkx(myTree, pos=pos)
	# show the matplotlib window
	plt.show()
	
	nx.draw_networkx(myTree, pos=pos)
	# save result as a png
	plt.savefig('out/TreeImage.png')
	# close plot
	plt.close()


# string address of file
graphFileAddress = 'data/graph.csv'
treeFileAddress = 'data/tree.csv'

# call 'draw' on the graph in the file
DrawUndirectedUnweightedGraph(graphFileAddress)

# draw a tree
DrawTree(treeFileAddress)

