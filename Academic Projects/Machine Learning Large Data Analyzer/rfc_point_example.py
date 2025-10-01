# This code block defines the function to receive an RFC Classifier object and pandas series
# NOTE: The pandas series MUST be a 90 length series with labels corresponding to the tags we've been working with
# returns 1 or 0
#
# I imagine this could be adapted to run in real time with the line; as machine components are being measured, package
# their most recent measurements into a series with tags as labels, then send to this function in real time.
# If lots of 1's in succession are predicted, you can expect defects to be imminent.
# THIS IS NOT TESTED FOR THAT APPLICATION.  I don't know how well it would work.

import pandas as pd
from rfc_methods import DEFECT_TAGS

def evaluate_point(rfc, data_point):
    return rfc.predict(data_point.to_frame().T.drop(ommitted, axis = 1))[0]



# This block demonstrates how to read from file a saved RFC Classifier object into memory

import pickle

print("Reading RFC model...")
rfc = pickle.load(open('../output/RFC_model.sav', 'rb'))
print("Done.")



# This block, for example purposes, reads a CSV data file and selects a single point, then predicts its output class

FILES = ['ommitted']

print("Reading data...")
iterfiles = iter(FILES)
data = pd.read_csv(FILES[0], index_col = 'ommitted')
next(iterfiles)
for file in iterfiles:
    data = pd.concat([data, pd.read_csv(file, index_col = 'ommitted')])
print("Done.")

print("Selecting point...")
data_point = data.iloc[0]
print("Done.")

print("Evaluating point...")
print(evaluate_point(rfc, data_point))
