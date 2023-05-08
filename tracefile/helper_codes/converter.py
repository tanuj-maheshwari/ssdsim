# code to convert microsoft csv tracefiles into below format
import csv
import sys
input_file = sys.argv[1]

if input_file.endswith("csv")==0:
    input_file+='.csv'
output_file = f'{input_file[:-4]}.txt'

with open(input_file, 'r') as csv_file, open(output_file, 'w') as txt_file:
    csv_reader = csv.reader(csv_file, delimiter=',')
    next(csv_reader)  # skip header row
    for row in csv_reader:
        time = int(float(row[0]) * 10000000)  # convert time to integer microseconds
        lsn = int(row[2])
        size = int(row[3])
        diskid = 0
        operation = 1 if row[1] == 'R' else 0
        txt_file.write(f"{time}\t{diskid}\t{lsn}\t{size}\t{operation}\n")
