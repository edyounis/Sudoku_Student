

class Domain:
    def __init__(self, value_or_values):
        """
            Represents the domain of a variable, i.e. the possible values that each
            variable may assign.
        """
        self.values = []
        if type(value_or_values) is int:
            self.values.append(value_or_values)
        else: # type list
            self.values = value_or_values

        self.modified = False

    ######### Constructors/Modified Method #########
    def copy(self, values):
        self.values = values

    def add(self, num):
        self.values.append(num)

    def remove(self, num):
        if num in self.values:
            self.modified = True
            self.values.remove(num)
            return True
        else:
            return False

    ######### Accessors Method #########
    def contains(self, v):
        """
            Checks if a value exists within the domain
            @param value to check
            @return true if <tt>value</tt> exists within the domain, false otherwise.
        """
        return v in self.values

    def size(self):
        return len(self.values)

    def isEmpty(self):
        """ return true if no values are contained in the domain. """
        return not self.values

    def isModified(self):
        """
            Returns whether or not the domain has been modified.
            return true if the domain has been modified.
        """
        return self.modified

    ######### String Representation #########
    def __str__(self):
        """
            String Representation method to print Domain values encapsulated
            inside {}
        """
        output = "{"
        for i in range(len(self.values) - 1):
            output += str(self.values[i]) + ", "
        try:
            output += str(self.values[-1])
        except:
            pass

        output += "}"
        return output
        # return str(self.values)
