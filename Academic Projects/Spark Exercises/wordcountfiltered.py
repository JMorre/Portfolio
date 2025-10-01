# eliminate all chapter and verse numbers from the count
# eliminate punctuation
# case insensitive
# sort by number of occurences

import sys
import re
from sys import stderr
from operator import add

from pyspark import SparkContext

def wordsFromLine(line):
    return filter(None, re.split('[^a-z]', line.lower()))

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: wordcount_v2 <input> <output>")
        exit(-1)
    sc = SparkContext(appName="WordCountAgain")
    sc.setLogLevel("WARN")  # LogLevel can be one of: "ALL", "DEBUG", "ERROR", "FATAL", "INFO", "OFF", "TRACE", "WARN"

    lines = sc.textFile(sys.argv[1], 1)
    counts = lines.flatMap(wordsFromLine) \
                  .map(lambda x: (x, 1)) \
                  .reduceByKey(add) \
                  .sortBy(lambda a: a[1], False)
    print("Saving output\n")
    output = counts.collect()
    for (word, count) in output:
        print("%s: %i" % (word, count))

    counts.saveAsTextFile(sys.argv[2])
    sc.stop()
