import random


def prime_test(N, k):

    return fermat(N,k), miller_rabin(N,k)


def mod_exp(x, y, N):

    if y == 0:
        return 1
    z = mod_exp(x, y // 2, N)
    if y % 2 == 0:
        return (z * z) % N
    return (x * z * z) % N
    

def fprobability(k):

    #  I believe that a more robust function would require the value k and
    #  N, since if k > (N - 1)/2, the probability becomes 100%.  For example, if
    #  N = 3 and k = 2, more than half of the fermat tests will be positive,
    #  ruling out the possibility of a Carmichael pseudoprime, right?
    #  But this provided function only uses k, and I don't know of any other way
    #  to check for cases where the probability will be 1.0.
    
    #  That code would be:
    #  if k > ((N - 1)/2):
    #      return 1
    #  return 1 - (1 / (2 ** k))
    
    return 1 - (1 / (2 ** k))


def mprobability(k):

    return 1 - (1 / (4 ** k))


def fermat(N,k):

    alist = [] # Keep track of values of a used
    
    if k >= N: #  if the number of guesses requested is more than N, it shouldn't be
        k = N - 1
        
        #  By the same logic I wrote about in the fprobability(k) notes, 
        #  this should only need to be run a maximum of ((N - 1) / 2) + 1 times
    
    for x in range(k):
        a = random.randint(1, N-1)
        while a in alist: #  if a is already used before, increment until we find one that isn't
            a += 1
            a = a % N #  next three lines account for incrementing beyond the required range
            if a == 0:
                a = 1
        alist.append(a)
        if mod_exp(a, N-1, N) != 1: #  if just one a value fails, it is composite.
            return 'composite'
    
    return 'prime' #  if none of the a values failed, it is probably prime


def miller_rabin(N,k):
    
    #  test until exponent is odd, answer is -1, or != 1, whichever comes first
    #  if exponent becomes odd, then it passes for a
    #  if it becomes -1, it passes for a
    #  if it becomes something else, != -1 != 1, it fails completely
    
    alist = [] #  Keep track of values of a used
    
    if k >= N: #  if the number of guesses requested is more than N, it shouldn't be
        k = N - 1
    
    for x in range(k):
        a = random.randint(1, N-1)
        while a in alist: #  if a is already used before, increment until we find one that isn't
            a += 1
            a = a % N #  next three lines account for incrementing beyond the required range
            if a == 0:
                a = 1
        alist.append(a)
        
        y = N - 1 #  set the running exponent value here
        while 1 == 1: #  loop until broken out of
            x = mod_exp(a, y, N)
            if (x - N) == -1: #  if a^y = -1 mod N, then it's passed this a value
                break
            elif x != 1: #  if a^y != -1, 1 mod N, then it's failed, composite.
                return 'composite'
            if (y % 2) == 0: #  remaining case, a^y = 1 mod N.  If the exponent is even, 
                             #  divide by 2 and run again, otherwise it's passed this a value
                y = y // 2 #  using integer division only, lest it convert large values to floats
            else:
                break
    
    return 'prime'
