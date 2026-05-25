from mrjob.job import MRJob
from mrjob.step import MRStep
from mrjob.protocol import RawValueProtocol
import csv


class Task3HiddenGems(MRJob):
    OUTPUT_PROTOCOL = RawValueProtocol
    # GLOBAL CONFIGURATION FOR THIS JOB
    JOBCONF = {
        # Force the framework to split input
        # files into 1MiB chunks (1048576 bytes)
        'mapreduce.input.fileinputformat.split.maxsize': '1048576',
        # Set default parallel reducers for aggregation phases
        'mapreduce.job.reduces': '4'
    }

    def steps(self):
        return [
            # PHASE 1: Parallel Aggregation
            MRStep(
                mapper=self.mapper_phase1,
                combiner=self.combiner_phase1,
                reducer=self.reducer_phase1
            ),
            # PHASE 2: Global Sorting
            MRStep(
                mapper=self.mapper_phase2_sort,
                reducer=self.reducer_phase2_sort
            )
        ]

    def mapper_phase1(self, _, line):
        try:
            row = next(csv.reader([line]))
        except Exception:
            return
        if not row or row[0] == 'userId':
            return
        movie_id = row[1]
        try:
            rating = float(row[2])
        except Exception:
            return
        yield movie_id, (rating, 1)

    def combiner_phase1(self, movie_id, values):
        total = 0.0
        count = 0
        for rating, c in values:
            total += rating
            count += c
        yield movie_id, (total, count)

    def reducer_phase1(self, movie_id, values):
        total = 0.0
        count = 0
        for rating_sum, c in values:
            total += rating_sum
            count += c
        if count == 0:
            return
        avg = total / count
        if 30 <= count <= 100 and avg >= 4.0:
            # Format keys so string lexicographical sorting matches numerical descending sort
            sort_key = "%09.5f|%09d|%09d" % (10.0 - avg, 10000000 - count, int(movie_id))
            yield sort_key, (avg, count, movie_id)

    def mapper_phase2_sort(self, sort_key, values):
        yield None, (sort_key, values)

    def reducer_phase2_sort(self, _, values_iterable):
        results = list(values_iterable)
        results.sort(key=lambda x: x[0])
        
        for sort_key, values in results:
            avg, count, movie_id = values
            avg_rounded = round(avg, 2)
            space_left = 7 - len(movie_id)
            space = ' ' * space_left
            yield None, '%s%s [%s, %d]' % (movie_id, space, avg_rounded, count)


if __name__ == '__main__':
    Task3HiddenGems.run()
