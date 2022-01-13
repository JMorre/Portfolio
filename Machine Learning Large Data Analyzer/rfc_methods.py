import numpy as np
import pandas as pd
import datetime

# List of tags
# ommitted

# Dictionary for tags to descriptions
# ommitted


# This function recieves a dataframe read from a DF csv file, and then determines
# all of the indexes where the tag 'ommitted' is below a
# certain value.  That value is ommitted by default (since ommitted), but
# can be set to something else.
# TODO: there are still defects that occur sometimes just before and after the factory has
# ommitted.  This function is taking out chunks of data where ommitted
# but we probably want it to also remove 5 seconds or so on either side of those chunks of
# time to account for these defects.  Find an efficient way to accomplish that
def remove_line_downtime(data, ommitted=ommitted):
    return data.drop(data[data['ommitted'] < ommitted].index)


# This function recieves a dataframe with ommitted removed, then determines at each point
# how many defects occurred since the last point.  So we have a sum of defect changes, which
# is returned as a single column pandas series (ommitted, indicating it is the change
# in defects at each point)
def get_defect_columns(data):
    defects = data[ommitted]
    delta_defect_column = np.sum((defects - defects.shift()), axis = 1).astype(int)
    delta_defect_column = pd.Series(delta_defect_column, index = data.index)
    delta_defect_column.iloc[0] = 0
    return delta_defect_column

# This function recieves a dataframe OR defects column as returned by get_defect_columns.  If
# no defects column is included, it will run get_defects_column on the data to generate one.
# It then iterates through the defects column and determines where 'clusters' of defects are occurring.
# There are 3 other variables involved here that can be overridden:
# target_length: how much time (in seconds) directly before a defect cluster should be assigned the variable 1?
# cluster_tolerance: how much time (in seconds) can come between defects before they are considered part of different clusters?
# cluster_threshold: how many defects need to be included in a cluster for it to be considered a cluster?
# TODO: this implementation could potentially be more efficient.  I don't yet know how to vectorize it or take advantage
# of other pandas functions to speed up processing, but it has potential to be faster.
# also, after ommitted is removed, this function could potentially make the output variable span across gaps, which
# is not how it should be.  Accounting for this could help improve accuracy.
def define_target(data = None, defects = None, target_length = 30, cluster_tolerance = 5, cluster_threshold = 5):
    if defects is None: # if no delta defect column is provided: create it
        defects = get_defect_columns(data)
    defects.index = pd.to_datetime(defects.index) # convert the index to datetime objects

    # initialize variables
    dcount = 0
    scount = 0
    start = defects.index[0]
    prev = defects.index[0]
    iprev = defects.index[0]
    clusters = []

    # iterate over every time-value pair in the delta defect column
    for index, val in defects.items():
        # if the value indicates a defect occurred:
        if val > 0:
            if dcount == 0: start = index # if this is the first defect in the current prospective cluster, set "start" to this time
            dcount += val # add the value to the current prospective cluster's defect counter
            prev = index # set "prev", indicating that this is the current endpoint of the prospective cluster
            scount = 0 # reset the consecutive non-defect counter

        # if the defect counter is nonzero, then there is currently a prospective cluster to consider:
        if dcount > 0:
            scount += 1 # increment the consecutive non-defect counter

            # if end of object, or the non-defect counter exceeds the cluster_tolerance variable, then we need to package or reject this prospective cluster
            if scount > cluster_tolerance or index == defects.index[-1]:
                # if there are enough defects included in this cluster to package it, then we do so
                if dcount > cluster_threshold:
                    clusters.append((start, prev, dcount))
                # reset the defect counter, indicating that we've finished processing the prospective cluster
                dcount = 0

    # initialize other variables
    defects[:] = 0
    target_time = datetime.timedelta(seconds = target_length) # a timedelta object corresponding to our desired target variable length
    one_sec = datetime.timedelta(seconds = 1)

    # iterate over each defined cluster
    for cluster in clusters:
        start = cluster[0] - target_time # define the start time of our target (output) variable's 1's
        if start < defects.index[0]: start = defects.index[0] # default to first value if out of bounds
        while not start in defects.index: start += one_sec # if the "start" point is part of the ommitted downtime, then find the nearest up-time instead
        defects[start:cluster[0]] = 1 # everywhere from "start" as calculated to just before the start point of the cluster is set to 1

    # return the new binary target variable, corresponding to 30 (default) second "critical moments" before defects are created in clusters
    return defects
