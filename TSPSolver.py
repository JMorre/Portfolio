#!/usr/bin/python3

from which_pyqt import PYQT_VER
if PYQT_VER == 'PYQT5':
    from PyQt5.QtCore import QLineF, QPointF
elif PYQT_VER == 'PYQT4':
    from PyQt4.QtCore import QLineF, QPointF
else:
    raise Exception('Unsupported Version of PyQt: {}'.format(PYQT_VER))




import time
import numpy as np
from TSPClasses import *
import heapq
import itertools



class TSPSolver:
    def __init__( self, gui_view ):
        self._scenario = None
        self._bssf = None

    def setupWithScenario( self, scenario ):
        self._scenario = scenario


    ''' <summary>
        This is the entry point for the default solver
        which just finds a valid random tour.  Note this could be used to find your
        initial BSSF.
        </summary>
        <returns>results dictionary for GUI that contains three ints: cost of solution,
        time spent to find solution, number of permutations tried during search, the
        solution found, and three null values for fields not used for this
        algorithm</returns>
    '''

    def defaultRandomTour( self, time_allowance=60.0 ):
        results = {}
        cities = self._scenario.getCities()
        ncities = len(cities)
        foundTour = False
        count = 0
        bssf = None
        start_time = time.time()
        while not foundTour and time.time()-start_time < time_allowance:
            # create a random permutation
            perm = np.random.permutation( ncities )
            route = []
            # Now build the route using the random permutation
            for i in range( ncities ):
                route.append( cities[ perm[i] ] )
            bssf = TSPSolution(route)
            count += 1
            if bssf.cost < np.inf:
                # Found a valid route
                foundTour = True
        end_time = time.time()
        results['cost'] = bssf.cost if foundTour else np.inf
        results['time'] = end_time - start_time
        results['count'] = count
        results['soln'] = bssf
        results['max'] = None
        results['total'] = None
        results['pruned'] = None
        self._bssf = bssf
        return results
    
    

    def greedy( self,time_allowance=60.0 ):
        pass



    ''' <summary>
        This is the entry point for the branch-and-bound algorithm that you will implement
        </summary>
        <returns>results dictionary for GUI that contains three ints: cost of best solution,
        time spent to find best solution, total number solutions found during search (does
        not include the initial BSSF), the best solution found, and three more ints:
        max queue size, total number of states created, and number of pruned states.</returns>
    '''

    def branchAndBound( self, time_allowance=60.0 ):

        # begin by initializing all values, O(1)
        results = {}
        count = 0
        cmax = 0
        total = 0
        pruned = 0
        start_time = time.time()

        # find a default tour as prescribed.  It's open ended how long it will take, but it won't be as long as the rest of the algorithm for sure.
        # Potentially O(infinity), until truncated by time allowed.  Most likely O(nlog(n))
        self.defaultRandomTour(time_allowance)

        # continue initializing, O(n)
        cities = self._scenario.getCities()
        n = len(cities)

        # initialize the matrix for the first node, O(n^2)
        matrix = [ [ np.inf for i in range(n) ] for j in range(n) ]

        # initialize the values of the first level matrix. O(n^2)
        cost = 0
        for i in range(n):
            for j in range(n):
                if i != j: matrix[i][j] = cities[i].costTo(cities[j])

        # reduce and calculate the cost of the first level matrix.  O(n^2)
        cost += reduceRows(matrix)
        cost += reduceCols(matrix)

        # initialize the heap. O(1)
        heap = Heap()

        # add the first node to the heap.  Creating new nodes always takes O(n^2), from initializing the matrix.
        total += 1
        node = Node(n)
        node.copyMatrix(matrix)
        node.copyCost(cost)
        node.addCity(cities[0])
        heap.add(node)
        cmax = heap.size()

        # free the first matrix's space in memory
        del matrix

        # begin algorithm:  O(n-1)!(n^3), in the worst case.  It's hard to say what is likely to be the actual case though.
        while heap.notEmpty():
            if time.time() - start_time >= time_allowance:
                pruned += heap.size()
                break

            # pull the first node on the heap.  By design, this will the smallest cost values of the deepest nodes in the graph, satisfying both optimization considerations.
            # O(1)
            eNode = heap.top()

            # determine which city is being departed from in this node. O(n)
            lci = eNode.lastCityIndex()

            # evaluate all possible child nodes:  O(n^3)
            newNodes = []
            for e in range(n):
                # ignore the node if its infinity value indicates it cannot be reached anymore. O(1)
                if eNode.matrix[lci][e] != np.inf:

                    # create a new node corresponding to a valid child node that must be considered. O(n^2)
                    total += 1
                    newNode = Node(n)
                    newNode.copyNode(eNode)

                    # add the new city that it is going to reach. O(1)
                    newNode.addCity(cities[e])

                    # calculate the new node's cost, considering the destination cost, making the appropriate cells infinite, and calculating the reduction cost.
                    # O(n^2)
                    newNode.cost += newNode.matrix[lci][e]
                    newNode.matrix[e][lci] = np.inf
                    makeRowInf(newNode.matrix, lci)
                    makeColInf(newNode.matrix, e)
                    newNode.reduceMatrix()

                    # if the new node is too large, do nothing, and move on to the next cell. O(1)
                    # if it isn't too large, then consider: O(1)
                    if newNode.cost < self._bssf.cost:

                        # is the new node a final node, indicating a finished graph?  if so, replace the old best solution with it. O(1)
                        if len(newNode.tour) == n:
                            count += 1
                            self._bssf = TSPSolution(newNode.tour)

                            # iterate through the heap, finding any nodes that are now disqualified, and remove them.  O(n)
                            h = heap.size() - 1
                            while h >= 0:
                                if heap.costAt(h) >= self._bssf.cost:
                                    heap.removeAt(h)
                                    pruned += 1
                                h -= 1

                            # do the same iteration through the as of yet un added child nodes of this current eNode.  O(n)
                            h = len(newNodes) - 1
                            while h >= 0:
                                if newNodes[h].cost >= self._bssf.cost:
                                    newNodes.pop(h)
                                    pruned += 1
                                h -= 1

                        # if the node is not a finished solution, add it to the to be added nodes. O(1)
                        else: newNodes.append(newNode)

                    # otherwise, do nothing with it. O(1)
                    else: pruned += 1

            # sort the to be added nodes, so they go in with the optimal order. O(n)
            newNodes.sort(key = lambda x: x.cost, reverse = False)

            # add the new nodes to the heap.  O(n)
            for e in newNodes:
                heap.add(e)
                if heap.size() > cmax: cmax = heap.size()

        # finished.  Catalogue results and return.  O(1)
        end_time = time.time()
        results['cost'] = self._bssf.cost
        results['time'] = end_time - start_time
        results['count'] = count
        results['soln'] = self._bssf
        results['max'] = cmax
        results['total'] = total
        results['pruned'] = pruned
        return results



    def fancy( self,time_allowance=60.0 ):
        pass

class Node:
    def __init__( self, n ):
        self.cost = 0
        self.matrix = [ [ np.inf for i in range(n) ] for j in range(n) ]
        self.tour = []

    def copyMatrix( self, matrix ):
        n = len(matrix)
        for i in range(n):
            for j in range(n):
                self.matrix[i][j] = matrix[i][j]

    def copyCost( self, cost ):
        self.cost = cost

    def copyTour( self, tour ):
        self.tour.clear()
        for i in tour:
            self.tour.append(i)

    def copyNode( self, node ):
        self.copyMatrix(node.matrix)
        self.copyCost(node.cost)
        self.copyTour(node.tour)

    def addCity( self, city ):
        self.tour.append(city)

    def lastCityIndex( self ):
        return self.tour[len(self.tour) - 1]._index

    def reduceMatrix( self ):
        cost = reduceRows(self.matrix)
        self.cost += cost
        cost = reduceCols(self.matrix)
        self.cost += cost

class Heap:
    def __init__( self ):
        self.content = []

    def add( self, element ):
        self.content.append(element)

    def top( self ):
        return self.content.pop()

    def notEmpty( self ):
        if self.size() == 0: return False
        return True

    def costAt( self, i ):
        return self.content[i].cost

    def removeAt( self, i ):
        self.content.pop(i)

    def size( self ):
        return len(self.content)


# create the vector which contains what value must be subtracted from every entry in each row
# return the vector
def createReductionVectorRow( matrix ):
    n = len(matrix)
    vec = []
    for i in range(n):
        vec.append(np.inf)
    for i in range(n):
        for j in range(n):
            if matrix[i][j] < vec[i]: vec[i] = matrix[i][j]
    for i in range(n):
        if vec[i] == np.inf: vec[i] = 0
    return vec

# create the vector which contains what value must be subtracted from every entry in each column
# return the vector
def createReductionVectorCol( matrix ):
    n = len(matrix)
    vec = []
    for i in range(n):
        vec.append(np.inf)
    for i in range(n):
        for j in range(n):
            if matrix[i][j] < vec[j]: vec[j] = matrix[i][j]
    for i in range(n):
        if vec[i] == np.inf: vec[i] = 0
    return vec

# reduce every row in the matrix so its lowest element is 0
# return the cost of reduction (sum of sub vector)
def reduceRows( matrix ):
    n = len(matrix)
    vec = createReductionVectorRow( matrix )
    cost = 0
    for i in vec:
        if i < np.inf: cost += i
    for i in range(n):
        for j in range(n):
            matrix[i][j] -= vec[i]
    return cost

# reduce every column in the matrix so its lowest element is 0
# return the cost of reduction (sum of sub vector)
def reduceCols( matrix ):
    n = len(matrix)
    vec = createReductionVectorCol( matrix )
    cost = 0
    for i in vec:
        if i < np.inf: cost += i
    for i in range(n):
        for j in range(n):
            matrix[i][j] -= vec[j]
    return cost

# make the given row in the matrix infinity
def makeRowInf( matrix, i ):
    for j in range(len(matrix)):
        matrix[i][j] = np.inf

# make the given column in the matrix infinity
def makeColInf( matrix, j ):
    for i in range(len(matrix)):
        matrix[i][j] = np.inf
