## This code is used to optimized RFC parameters.  It runs over a small dataset,
## and tries multiple parameter values for RFC classifiers, iteratively selecting better
## ones to try to improve recall score, while preserving precision and accuracy.
## Results from this code should not be considered a definitive answer to which
## parameters are best, but they can be used to indicate promising combinations.

## it will run for around an hour to compute 5 random seeds


import numpy as np
import pandas as pd
import copy
from sklearn.ensemble import RandomForestClassifier
from sklearn.model_selection import train_test_split
from sklearn.metrics import recall_score, precision_score
from sklearn.metrics import roc_auc_score
from rfc_methods import remove_line_downtime
from rfc_methods import define_target
from rfc_methods import remove_line_downtime
from rfc_methods import DEFECT_TAGS
import warnings

# Use just one file, to test faster
FILES = ['ommitted']



## main process ##

# read in all files to one dataframe

iterfiles = iter(FILES)
data = pd.read_csv(FILES[0], index_col = 'ommitted')
next(iterfiles)
for file in iterfiles:
    data = pd.concat([data, pd.read_csv(file, index_col = 'ommitted')])

# filter downtime, duplicates
data = remove_line_downtime(data)
data = data.drop_duplicates()

# Create target variable (y) and feature set (X)

# create target variable
# a column that includes all 1's in the 30s (by default) before a defect cluster, and 0's otherwise
y = define_target(data)

# the dataset minus all defect tags
X = copy.deepcopy(data.drop(DEFECT_TAGS, axis = 1))

# free memory
del(data)



# Define list of parameters
P = [[10], # n_estimators, set to low fast value
    ['gini', 'entropy'], # criterion
    [None, 1, 2, 3, 5, 10, 20, 50, 100, 150, 200, 500, 1000], # max_depth
    [2, 1e-7, 1e-6, 1e-5, 1e-4, 1e-3, 1e-2, 0.1, 0.2, 0.5, 0.75, 1.0, 5, 10, 20, 100, 500, 1000], # min_samples_split
    [1, 1e-7, 1e-6, 1e-5, 1e-4, 1e-3, 1e-2, 0.1, 0.2, 0.5, 2, 5, 10, 20, 100, 500, 1000], # min_samples_leaf
    [0.0, 1e-7, 1e-6, 1e-5, 1e-4, 1e-3, 1e-2, 0.1, 0.2, 0.5], # min_weight_fraction_leaf
    ['sqrt', 'log2', None, 1e-7, 1e-6, 1e-5, 1e-4, 1e-3, 1e-2, 0.1, 0.2, 0.5, 0.75, 1.0, 1, 2, 5, 10, 20], # max_features
    [None, 2, 3, 5, 10, 20, 50, 100, 150, 200, 500, 1000], # max_leaf_nodes
    [0.0, 1e-7, 1e-6, 1e-5, 1e-4, 1e-3, 1e-2, 0.1, 0.2, 0.5, 0.75, 1.0, 2.0, 5.0, 10.0], # min_impurity_decrease
    [None, "balanced", "balanced_subsample"], # class_weight
    [0.0, 1e-7, 1e-6, 1e-5, 1e-4, 1e-3, 1e-2, 0.1, 0.2, 0.5, 0.75, 1.0, 2.0, 5.0, 10.0]] # ccp_alpha

# function to fetch scores for a list of parameters: it defines, fits, and runs a model using predefined datasets
def test_recall(params, X_train, X_test, y_train, y_test, r):
    rfc = RandomForestClassifier(n_estimators = params[0],
                                 criterion = params[1],
                                 max_depth = params[2],
                                 min_samples_split = params[3],
                                 min_samples_leaf = params[4],
                                 min_weight_fraction_leaf = params[5],
                                 max_features = params[6],
                                 max_leaf_nodes = params[7],
                                 min_impurity_decrease = params[8],
                                 random_state = r,
                                 class_weight = params[9],
                                 ccp_alpha = params[10])
    rfc.fit(X_train, y_train)
    y_pred = rfc.predict(X_test)
    re = recall_score(y_test, y_pred)
    p = precision_score(y_test, y_pred)
    a = rfc.score(X_test, y_test)
    return roc_auc_score(y_test, rfc.predict_proba(X_test)[:,1]), re, p, a

# try every option defined in P for some given parameter, and select the one with best results.
# line 9 in this function is key: it defines minimum viable values for accuracy, precision, and AOC score, and seeks to maximize recall
def get_best_option(prevrecall, preva, prevp, prevs, index, baseparams, X_train, X_test, y_train, y_test, r):
    print("\t\tcomputing param " + str(index))
    ret = baseparams[index]
    newparams = copy.deepcopy(baseparams)
    for i, o in enumerate(P[index]):
        print("\t\t\tcomputing option " + str(i), end = '')
        newparams[index] = o
        score, recall, p, a = test_recall(newparams, X_train, X_test, y_train, y_test, r)
        print(": " + str(score) + " - " + str(a) + ", " + str(recall) + ", " + str(p), end = '')
        if recall > prevrecall and (a > 0.98 or a > preva) and (p > 0.95 or p > prevp) and (score > 0.98 or score > prevs):
            ret = o
            prevrecall = recall
            print(" - better")
        else: print(" ")
    return ret

# suppress sklearn warnings that occur while using precision metrics
def warn(*args, **kwargs):
    pass
warnings.warn = warn

# define initial datasets, parameter values, and recall score
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size = 0.3, random_state = 0)
best = [P[0][0], P[1][0], P[2][0], P[3][0], P[4][0], P[5][0], P[6][0], P[7][0], P[8][0], P[9][0], P[10][0]]
prevs, prev_recall, prevp, preva = test_recall(best, X_train, X_test, y_train, y_test, 0)

# try for 5 random seeds
for r in range(5):
    print("random seed " + str(r))
    done = False
    # optimize parameters until two runs produce the same parameter list
    # the method runs roughly as follows: start with a pre set list of parameter values.  Then, for each parameter
    # individually, find the option that increases scores the best.  After all parameters are evaluated, set the
    # list of parameter values to be all their best options.
    # Then run it again, and only stop when the parameter values don't change between runs.
    while not done:
        print("\tcomputing new parameters")
        prevbest = copy.deepcopy(best)
        # test every parameter
        for i, p in enumerate(P):
            best[i] = get_best_option(prev_recall, preva, prevp, prevs, i, prevbest, X_train, X_test, y_train, y_test, r)
        score, new_recall, p, a = test_recall(best, X_train, X_test, y_train, y_test, r)
        # report new scores
        print("\tnew scores: " + str(score) + " - " + str(a) + ", " + str(new_recall) + ", " + str(p))
        print(str(best))
        if new_recall == prev_recall: done = True
        prev_recall = new_recall
