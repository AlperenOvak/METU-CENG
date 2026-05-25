from mrjob.job import MRJob
from mrjob.step import MRStep
import csv


class Task1CountRatings(MRJob):
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
        rating = row[2]
        yield rating, 1

    def combiner_phase1(self, rating, counts):
        yield rating, sum(counts)

    def reducer_phase1(self, rating, counts):
        yield float(rating), sum(counts)


if __name__ == '__main__':
    Task1CountRatings.run()
