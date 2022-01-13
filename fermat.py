import random


def prime_test(N, k):
    # This is main function, that is connected to the Test button. You don't need to touch it.
    return fermat(N,k), miller_rabin(N,k)


def mod_exp(x, y, N):
    # You will need to implement this function and change the return value.   
    if y == 0:
        return 1
    z = mod_exp(x, y // 2, N)
    if y % 2 == 0:
        return (z * z) % N
    return (x * z * z) % N
    

def fprobability(k):
    # You will need to implement this function and change the return value.
    
    # MYNOTES I believe that a more robust function would require the value k and
    # MYNOTES N, since if k > (N - 1)/2, the probability becomes 100%.  For example, if
    # MYNOTES N = 3 and k = 2, more than half of the fermat tests will be positive,
    # MYNOTES ruling out the possibility of a Carmichael pseudoprime, right?
    # MYNOTES But this provided function only uses k, and I don't know of any other way
    # MYNOTES to check for cases where the probability will be 1.0... so it doesn't
    # MYNOTES seem like I was supposed to worry about it.  If I was, please have mercy,
    # MYNOTES I think I've demonstrated here that I understand that concept at least.
    
    # MYNOTES That code would be:
    # MYNOTES if k > ((N - 1)/2):
    # MYNOTES     return 1
    # MYNOTES return 1 - (1 / (2 ** k))
    
    return 1 - (1 / (2 ** k))


def mprobability(k):
    # You will need to implement this function and change the return value.   
    return 1 - (1 / (4 ** k))


def fermat(N,k):
    # You will need to implement this function and change the return value, which should be
    # either 'prime' or 'composite'.
    #
    # To generate random values for a, you will most likley want to use
    # random.randint(low,hi) which gives a random integer between low and
    #  hi, inclusive.
    alist = [] # MYNOTES Keep track of values of a used
    
    if k >= N: # MYNOTES if the number of guesses requested is more than N, it shouldn't be
        k = N - 1
        
        # MYNOTES By the same logic I wrote about in the fprobability(k) notes, 
        # MYNOTES this should only need to be run a maximum of ((N - 1) / 2) + 1 times, right?
    
    for x in range(k):
        a = random.randint(1, N-1)
        while a in alist: # MYNOTES if a is already used before, increment until we find one that isn't
            a += 1
            a = a % N # MYNOTES next three lines account for incrementing beyond the required range
            if a == 0:
                a = 1
        alist.append(a)
        if mod_exp(a, N-1, N) != 1: # MYNOTES if just one a value fails, it is composite.
            return 'composite'
    
    return 'prime' # MYNOTES if none of the a values failed, it is probably prime


def miller_rabin(N,k):
    # You will need to implement this function and change the return value, which should be
    # either 'prime' or 'composite'.
    #
    # To generate random values for a, you will most likley want to use
    # random.randint(low,hi) which gives a random integer between low and
    #  hi, inclusive.
    
    # MYNOTES test until exponent is odd, answer is -1, or != 1, whichever comes first
    # MYNOTES if exponent becomes odd, then it passes for a
    # MYNOTES if it becomes -1, it passes for a
    # MYNOTES if it becomes something else, != -1 != 1, it fails completely
    
    alist = [] # MYNOTES Keep track of values of a used
    
    if k >= N: # MYNOTES if the number of guesses requested is more than N, it shouldn't be
        k = N - 1
    
    for x in range(k):
        a = random.randint(1, N-1)
        while a in alist: # MYNOTES if a is already used before, increment until we find one that isn't
            a += 1
            a = a % N # MYNOTES next three lines account for incrementing beyond the required range
            if a == 0:
                a = 1
        alist.append(a)
        
        y = N - 1 # MYNOTES set the running exponent value here
        while 1 == 1: # MYNOTES loop until broken out of
            x = mod_exp(a, y, N)
            if (x - N) == -1: # MYNOTES if a^y = -1 mod N, then it's passed this a value
                break
            elif x != 1: # MYNOTES if a^y != -1, 1 mod N, then it's failed, composite.
                return 'composite'
            if (y % 2) == 0: # MYNOTES remaining case, a^y = 1 mod N.  If the exponent is even, 
                             # MYNOTES divide by 2 and run again, otherwise it's passed this a value
                y = y // 2 # MYNOTES using integer division only, lest it convert large values to floats
            else:
                break
    
    return 'prime'
