## Main code for running RFC classifier.  Optimized parameter values found using parameter_optimizer.py, and removing options that hurt precision too much

import numpy as np
import pandas as pd
import datetime
import copy
from sklearn.ensemble import RandomForestClassifier
from sklearn.model_selection import train_test_split
from sklearn.metrics import recall_score, precision_score
from rfc_methods import define_target, remove_line_downtime, DEFECT_TAGS, TAG_DESC
import heapq
import pickle
import warnings

FILES = ['../data/DF_Jan3_Jan10_1s.csv', '../data/DF_Jan20_1s.csv', '../data/DF_Jan21_1s.csv',
         '../data/DF_Jan22_1s.csv', '../data/DF_Jan23_1s.csv', '../data/DF_Jan25_1s.csv',
         '../data/DF_Apr8.csv', '../data/DF_Apr9_10.csv']

## main process ##

# suppress sklearn warnings that occur while using precision metrics
def warn(*args, **kwargs):
    pass
    return
warnings.warn = warn

# read in all files to one dataframe

print("Reading data...")
iterfiles = iter(FILES)
data = pd.read_csv(FILES[0], index_col = 'time')
next(iterfiles)
for file in iterfiles:
    data = pd.concat([data, pd.read_csv(file, index_col = 'time')])
print("Done.")

# filter downtime, duplicates
print("Cleaning data...")
data = remove_line_downtime(data)
data = data.drop_duplicates()
print("Done.")


# Create target variable (y) and feature set (X)

# create target variable
# a column that includes all 1's in the 30s (by default) before a defect cluster, and 0's otherwise
print("Initializing model...")
y = define_target(data)

# the dataset minus all defect tags
X = copy.deepcopy(data.drop(DEFECT_TAGS, axis = 1))

print("Defined " + str(np.sum(y)) + " 1's out of " + str(len(X)) + " total time points.")

# free memory
del(data)


# Define and fit the model

# Create the model
rfc = RandomForestClassifier(
                             ##n_estimators = 100,
                             criterion = 'entropy',
                             #max_depth = 10,
                             min_samples_split = 10,
                             min_samples_leaf = 5,
                             ##min_weight_fraction_leaf = 0.0,
                             max_features = 20,
                             ##max_leaf_nodes = None,
                             #min_impurity_decrease = 0.001,
                             class_weight = 'balanced_subsample',
                             ##ccp_alpha = 0.0,
                             )

# Split the dataset into train and test sets
# TODO: experiment with different data splits: random sampling may not be ideal for datasets that are sequential?
# It may have a tendency to overfit.
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size = 0.3)
print("Done.")

# Fit the model - might take a while (10 - 20 minutes)
print("Training model...\nThis may take up to 30 minutes to complete")
rfc.fit(X_train, y_train)
print("Done.")

# save the RFC model to a file that can be read in using methods outlined in readme.txt
print("Saving model...")
model_file = '../output/RFC_model.sav'
pickle.dump(rfc, open(model_file, 'wb'))
print("Saved.")


# Create predictions and use them to generate score

print("Computing scores...")
y_pred = rfc.predict(X_test)
recall = recall_score(y_test, y_pred)
prec = precision_score(y_test, y_pred)
score = rfc.score(X_test, y_test)
"{:.2f}".format(round(recall, 3))
print("accuracy: {:.2f}".format(score, 3) + ", recall: {:.2f}".format(recall, 3) + ", precision: {:.2f}".format(prec, 3))


# Ask the model what features are the most important

# initialize objects
print("Evaluating features...")
results = {}
importances = np.zeros(X.shape[1])

# loop through each 'e' (decision tree) within the model, and sum up the importance it reports for every feature
for e in rfc.estimators_:
    importances += e.feature_importances_

# get all 72 top importance features, sorted by best
best = heapq.nlargest(72, enumerate(importances), key = lambda x: x[1])
content = 'Tag,Description,Score\n'
for i, b in enumerate(best):
    best[i] = list(b)
    best[i][0] = X.columns[best[i][0]]
    content += (best[i][0] + "," + TAG_DESC[best[i][0]] + "," + str(best[i][1]) + "\n")

# save the tag name, importance score
with open('../output/tag_scores.csv', 'w', newline = '') as file:
    file.write(content[:-1])
    file.close()

print("tags in order of importance score saved")

print("All done.")
