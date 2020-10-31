#! venv/bin/python
""" Aim : Given a nested list of functional dependencies and alpha, the attribute set, return closure of alpha  """
from collections import deque

def set_to_string(inp):
    lst = list(inp)
    return ''.join(e for e in inp)

def find_attribute_closure_method1(fd, alpha):
    """ O(N^2) method where N = # of rows in F.D """
    print("Using method 1...")
    closure = set_to_string(set(alpha) )
    changes=True 
    iter_number = 1
    while(changes==True):
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
                    changes=True
        
    return ''.join(sorted(closure))

def find_attribute_closure_method2(fd, alpha):
    """ O(N) method where N is row count of F.D """
    # reference: Practice exercise 8.8 from book "Database System Concepts by A.S. , H.F.K. , S.S"
    print("Using method 2...")
    # preprocessing
    fd_count = [len(row[0]) for row in fd]
    appears = {}
    for i in range(0,len(fd)):
        for ch in fd[i][0]:
            appears[ch] = appears.get(ch,[])
            appears[ch].append(i)
    # print(appears)
    result = ''

    def cover(alph):
        nonlocal result # to access variables defined in the outer function
        for attr in alph:
            if attr not in result:
                result += attr 
                for idx in appears.get(attr, []):
                    fd_count[idx] = fd_count[idx]-1
                    if fd_count[idx]==0:
                        cover(fd[idx][1])

    cover(alpha)
    return ''.join(sorted(result))

def find_fd_closure(fd):
    """ Given a set F of functional dependencies, find F+ i.e. the closure of F """
    # copy original fd to another set
    f_closure = fd[:]
    res = []
    for row in fd:
        for ch in row[0]:
            res += ch 
        for ch in row[1]:
            res += ch
    
    res = ''.join(sorted(set(res))) 
    # print(res)
    def substring(strng):
        res = [strng[i: j] for i in range(len(strng)) 
        for j in range(i + 1, len(strng) + 1)] 
        return res 
    
    R_substr = substring(res)
    for alpha in R_substr:
        closure = find_attribute_closure_method2(fd,alpha)
        closure_substring = substring(closure)
        for f in closure_substring:
            f_closure.append([alpha, f])

    answer = set()
    for row in f_closure:
        answer.add(row[0]+"-->"+row[1])
    # print(answer)
    return answer 

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
    functional_dependencies = [['A','B'],['B','C']]
    
    # print(find_fd_closure(functional_dependencies))
    
    functional_dependencies = [['A','B'],['A','C'], ['CG','H'],['CG','I'], ['B','H']]
    
    functional_dependencies = [['1','2'],['3','45'],['13','6'],['5','7']]

    functional_dependencies = [['25','1'],['345','2'],['134','5'],['13','4'],['1','3']]

    alpha = '1' # the attribute set
    print("{} --> {}".format(alpha, find_attribute_closure_method1(functional_dependencies, alpha)))
    print("{} --> {}".format(alpha, find_attribute_closure_method2(functional_dependencies, alpha)))