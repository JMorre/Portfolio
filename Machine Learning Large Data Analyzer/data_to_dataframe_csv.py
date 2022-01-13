# raw data file names (csv files): fill this list with all the raw csv files you're working with
FILES = ['ommitted']

# output file names: adjust this to set up formatting for what output your files will take
OUTPUT_FILES = []
for F in FILES: OUTPUT_FILES.append('../data/DF_' + F[11:])



# read a raw data file and convert it to the proper clean DateTime index format, saved in variable 'data', then saved to file

# options:
TIME_STEP = '1s' # time step: 50ms, 1s, 1m, etc. our models ran on 1 second data files, but this file can use any timestep
FILL_MISSING_TIMES = True # do you want to fill in missing times?
FILL_MISSING_VALUES = True # do you want to forward fill NaN values?
SAVE_CSV = True # do you want to save the dataframe as a CSV?



import pandas as pd

i = 1

for FILE, OUTPUT_FILE in zip(FILES, OUTPUT_FILES):
    print("Reading file " + str(i) + ": " + FILE + "...")
    i += 1
    data = pd.read_csv(FILE).drop(columns = 'description') # read file
    print("Done.")

    print("Rounding data to DateTimes...")
    data.time = pd.to_datetime(data.time).dt.round(TIME_STEP) # convert time column to DateTimes and round to nearest interval
    print("Done.")

    print("Reformatting table...")
    data = data.pivot_table(index = 'time', columns = 'tag', values = 'value').rename_axis(None, axis = 1) # convert data format to combine time values
    print("Done.")

    if FILL_MISSING_TIMES:
        print("Filling missing times...")
        data = data.reindex(pd.date_range(start = data.index[0], end = data.index[-1], freq = TIME_STEP), fill_value = None) # create new index with all time stamps included, make it the dataframe's index
        data.index.name = 'time' # set name for new index
        print("Done.")

    if FILL_MISSING_VALUES:
        print("Filling missing values...")
        data = data.fillna(method = 'ffill') # fill missing values forward
        data = data.fillna(method = 'bfill') # if any values still missing, fill backward
        print("Done.")

    if SAVE_CSV:
        print("Saving to file...")
        data.to_csv(OUTPUT_FILE) # save to file
        print("Done.")
