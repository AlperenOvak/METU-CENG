from mrjob.job import MRJob
from mrjob.step import MRStep
from mrjob.protocol import RawValueProtocol
import csv


class Task5HarshCritics(MRJob):
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
        user_id = row[0]
        try:
            rating = float(row[2])
        except Exception:
            return
        yield user_id, (rating, 1)

    def combiner_phase1(self, user_id, values):
        total = 0.0
        count = 0
        for rating, c in values:
            total += rating
            count += c
        yield user_id, (total, count)

    def reducer_phase1(self, user_id, values):
        total = 0.0
        count = 0
        for rating_sum, c in values:
            total += rating_sum
            count += c
        if count == 0:
            return
        avg = total / count
        if count >= 50 and avg < 2.5:
            sort_key = "%09.5f|%09d|%09d" % (avg, 10000000 - count, int(user_id))
            yield sort_key, (avg, count, user_id)

    def mapper_phase2_sort(self, sort_key, values):
        yield None, (sort_key, values)

    def reducer_phase2_sort(self, _, values_iterable):
        results = list(values_iterable)
        results.sort(key=lambda x: x[0])
        
        for sort_key, values in results:
            avg, count, user_id = values
            avg_rounded = round(avg, 2)
            yield None, '%s [%s, %d]' % (user_id, avg_rounded, count)


if __name__ == '__main__':
    Task5HarshCritics.run()
