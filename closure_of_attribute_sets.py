#! venv/bin/python
""" Aim : Given a nested list of functional dependencies and alpha, the attribute set, return closure of alpha  """
from collections import deque

def set_to_string(inp):
    lst = list(inp)
    return ''.join(e for e in inp)

""" O(N^2) method where N = # of rows in F.D """
def find_cover_method1(fd, alpha):
    print("Using method 1...")
    closure = set_to_string(set(alpha) )
    # print(closure)
    changes=True 
    iter_number = 1
    while(changes==True):
        # print("Iteration number: ",iter_number)
        iter_number+=1
        changes=False
        for row in fd:
            found = True 
            for ch in row[0]:
                if ch not in closure:
                    found = False
            
            if found==True: #  if row[0] in closure:
                before_size=len(closure)
                closure+= row[1]
                closure = set_to_string(set(closure))
                after_size = len(closure)
                if(after_size>before_size):
                    # print(row[0], row[1])
                    # print("Became: ", closure)
                    changes=True
        
    return ''.join(sorted(closure))

""" O(N) method where N is row count of F.D """
def find_cover_method2(fd, alpha):
    print("Using method 2...")
    # preprocessing
    fd_count = [len(row[0]) for row in fd]
    # print("fd_count: ", fd_count)
    appears = {}
    for i in range(0,len(fd)):
        for ch in fd[i][0]:
            appears[ch] = appears.get(ch,[])
            appears[ch].append(i)
    # print(appears)
    result = ''

    def cover(alph):
        nonlocal result # to access variables defined in the outer function
        # print("APLHA: ",alph)
        # print("RES: ", result)
        for attr in alph:
            # print(attr)
            if attr not in result:
                result += attr 
                # print("added {} to {}".format(attr, result))
                for idx in appears.get(attr, []):
                    # print(attr,appears[attr])
                    # print("At idx: ", idx)
                    fd_count[idx] = fd_count[idx]-1
                    if fd_count[idx]==0:
                        # print("going to ", idx)
                        # print("result before: ", result)
                        cover(fd[idx][1])

    cover(alpha)
    return ''.join(sorted(result))

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
    
    functional_dependencies = [['1','2'],['3','45'],['13','6'],['5','7']]

    functional_dependencies = [['25','1'],['345','2'],['134','5'],['13','4'],['1','3']]

    alpha = '1' # the attribute set
    print("{} --> {}".format(alpha, find_cover_method1(functional_dependencies, alpha)))
    print("{} --> {}".format(alpha, find_cover_method2(functional_dependencies, alpha)))