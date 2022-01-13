import sys
import re
from sys import stderr
from operator import add

from pyspark import SparkContext

def movieranks(line): # given an input uid ws movieid ws rank, return movieid-rank, [uid]
    vals = line.split()
    uid = None
    movieid = None
    rank = None
    for i in range(len(vals)):
        if i == 0:
            uid = vals[i]
        elif i == 1:
            movieid = vals[i]
        elif i == 2:
            rank = vals[i]
    if uid == None or movieid == None or rank == None:
        return None
    return (movieid + "-" + rank, [uid])

if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Usage: netflixcomparison <input text> <userid> <output>")
        exit(-1)
    sc = SparkContext(appName="NetflixComparison")
    sc.setLogLevel("WARN")  # LogLevel can be one of: "ALL", "DEBUG", "ERROR", "FATAL", "INFO", "OFF", "TRACE", "WARN"

    lines = sc.textFile(sys.argv[1], 1)

    uid = sys.argv[2]

    movieviewers = lines.map(lambda x: movieranks(x)) \
                        .filter(lambda x: x is not None) \
                        .reduceByKey(lambda a, b: a + b)

    def getuser(movie, uid): # given an input movieid-rank, [u1, u2...], return movieid-rank, [u1, u2...] for all lists that contain target user
        target = uid
        if target in movie[1]:
            return movie
        return None

    def sameusers(movie): # given an input movieid-rank, [u1, u2...], return a list [(u1, 1), (u2, 1) ...]
        ret = []
        for i in range(len(movie[1])):
            ret.append((movie[1][i], 1))
        return ret

    counts = movieviewers.map(lambda x: getuser(x, uid)) \
                         .filter(lambda x: x is not None) \
                         .map(lambda x: sameusers(x)) \
                         .flatMap(lambda list: list) \
                         .reduceByKey(add) \
                         .sortBy(lambda a: a[1], False)

    counts.saveAsTextFile(sys.argv[3])
    sc.stop()
