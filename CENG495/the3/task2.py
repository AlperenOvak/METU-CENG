from mrjob.job import MRJob
from mrjob.step import MRStep
from mrjob.protocol import RawValueProtocol
import csv


class Task2AveragePerMovie(MRJob):
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
            MRStep(
                mapper=self.mapper_phase1,
                combiner=self.combiner_phase1,
                reducer=self.reducer_phase1
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
        avg_rounded = round(avg, 2)
        space_padding = ' ' * (7 - len(str(int(movie_id))))
        yield None, '%s%s\t%s' % (int(movie_id), space_padding, avg_rounded)


if __name__ == '__main__':
    Task2AveragePerMovie.run()
