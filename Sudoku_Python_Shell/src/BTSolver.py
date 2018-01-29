import SudokuBoard
import Variable
import Domain
import Trail
import Constraint
import ConstraintNetwork
import time

class BTSolver:

    ######### Constructors Method #########
    def __init__(self, gb, var_sh, val_sh, cc):
        self.network = ConstraintNetwork.ConstraintNetwork(gb)
        self.trail = Trail.masterTrailVariable
        self.hassolution = False
        self.gameboard = gb

        self.varHeuristics = var_sh
        self.valHeuristics = val_sh
        self.cChecks = cc

    ######### Implement These Methods #########

    def forwardChecking(self):
        """
           TODO:  Implement forward checking.
        """
        pass

    def arcConsistency(self):
        """
            TODO: Implement Maintaining Arc Consistency.
        """
        return False


    def assignmentsCheck(self):
        """
            default consistency check. Ensures no two variables are assigned to the same value.
            @return true if consistent, false otherwise.
        """
        for v in self.network.variables:
            if v.isAssigned():
                for vOther in self.network.getNeighborsOfVariable(v):
                    if v.getAssignment() == vOther.getAssignment():
                        return False
        return True

    def getfirstUnassignedVariable(self):
        """
            default next variable selection heuristic. Selects the first unassigned variable.
            @return first unassigned variable. null if no variables are unassigned.
        """
        for v in self.network.variables:
            if not v.isAssigned():
                return v
        return None

    def getMRV(self):
        """
            TODO: Implement MRV heuristic
            @return variable with minimum remaining values that isn't assigned, null if all variables are assigned.
        """
        pass

    def getDegree(self):
        """
            TODO: Implement Degree heuristic
            @return variable constrained by the most unassigned variables, null if all variables are assigned.
        """
        pass

    def MRVwithTieBreaker(self):
        """
            TODO: Implement MRV with Degree heuristic Tie Breaker
        """
        pass

    def getValuesInOrder(self, v):
        """
            Default value ordering.
            @param v Variable whose values need to be ordered
            @return values ordered by lowest to highest.
        """
        values = v.domain.values
        return sorted(values)


    def getValuesLCVOrder(self, v):
        """
            TODO: LCV heuristic
        """
        pass

    ######### Accessors Method #########
    def getSolution(self):
        return self.network.toSudokuBoard(self.gameboard.p, self.gameboard.q)

    # @return time required for the solver to attain in seconds
    def getTimeTaken(self):
        return self.endTime - self.startTime

    ######### Engine Methods #########
    def solve(self, level = 0):
        if self.hassolution:
            return

        # Select unassigned variable
        v = self.selectNextVariable()

        # check if the assigment is complete
        if (v == None):
            for var in self.network.variables:
                if not var.isAssigned():
                    raise ValueError("Something happened with the variable selection heuristic")
            self.hassolution = True
            return

        for i in self.getNextValues(v):

            self.trail.placeTrailMarker()
            v.updateDomain(Domain.Domain(i))

            # move to the next assignment
            if self.checkConsistency():
                self.solve(level + 1)

            if self.hassolution:
                return

            # if this assignment failed at any stage, backtrack
            self.trail.undo()

    def checkConsistency(self):
        '''which consistency check to run but it is up to you when implementing the heuristics to break ties using the other heuristics passed in'''
        if self.cChecks == "forwardChecking":
            return self.forwardChecking()
        if self.cChecks == "arcConsistency":
            return self.arcConsistency()
        else:
            return self.assignmentsCheck()

    def selectNextVariable(self):
        """
            Selects the next variable to check.
            @return next variable to check. null if there are no more variables to check.
        """
        if self.varHeuristics == "MinimumRemainingValue":
            return self.getMRV()
        elif self.varHeuristics == "Degree":
            return self.getDegree()
        elif self.varHeuristics == "MRVwithTieBreaker":
            return self.MRVwithTieBreaker()
        else:
            return self.getfirstUnassignedVariable()

    def getNextValues(self, v):
        """
            Value Selection Heuristics. Orders the values in the domain of the variable
            passed as a parameter and returns them as a list.
            @return List of values in the domain of a variable in a specified order.
        """
        if self.valHeuristics == "LeastConstrainingValue":
            return self.getValuesLCVOrder(v)
        else:
            return self.getValuesInOrder(v)