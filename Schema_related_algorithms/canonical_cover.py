#! venv/bin/python
def canonical_cover(fd):
    """ Find canonical cover of a given F.D. """
    f_canonical = []
    to_include = [1]*len(fd)
    appears = dict() 
    for i in range(len(fd)):
        for ch in fd[i][0]:
            appears[ch] = appears.get(ch, []) 
            appears[ch].append(i)
        
    changes = True 
    while changes:
        changes = False
        """ Add code here """
    
    return f_canonical

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
    
    functional_dependencies = [['A','B'],['A','C'], ['CG','H'],['CG','I'], ['B','H']]
    
    functional_dependencies = [['1','2'],['3','45'],['13','6'],['5','7']]

    functional_dependencies = [['25','1'],['345','2'],['134','5'],['13','4'],['1','3']]
