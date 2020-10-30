#! venv/bin/python
import closure 

""" Aim: Given an attribute set and a functional dependency set, check if it is a super key or not """

def check_super_key(fd, key):
    """ For an input key in a functional dependency, return True if it is a super key else false """
    # find total number of attributes in the whole FD
    res = []
    for row in fd:
        for ch in row[0]:
            res += ch  
        for ch in row[1]:
            res += ch  
    
    res = set(res)
    n = len(res)

    # find closure of key and check if its length == n
    closr = closure.find_attribute_closure_method2(fd, key)
    if len(closr)==n:
        return True 
    else:
        return False  

if __name__ == "__main__":
        # input functional dependencies
    functional_dependencies = [['A','C'],
                                                 ['AB', 'DE'],
                                                 ['AB', 'CDI'],
                                                 ['AC', 'J'],
                                                 ['J','B']] # A --> C,  AB-->DE, ...
    
    functional_dependencies = [['A','BCE'],
                                                 ['AB', 'DE'],
                                                 ['BI', 'J']] # A --> BCE,  AB-->DE, ...
    
    functional_dependencies = [['A','B'],['A','C'], ['CG','H'],['CG','I'], ['B','H']]
    alpha = 'AH' # the attribute set
    print("{} --> {}".format(alpha, check_super_key(functional_dependencies, alpha)))
    
    functional_dependencies = [['1','2'],['3','45'],['13','6'],['5','7']]

    functional_dependencies = [['25','1'],['345','2'],['134','5'],['13','4'],['1','3']]

