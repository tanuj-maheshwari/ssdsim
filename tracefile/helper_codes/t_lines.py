# extracts the first t lines from the tracefiles(without counting delete request)
import sys

if len(sys.argv) != 3:
    print("Usage: python program.py input_file t")
else:
    input_file = sys.argv[1]
    t = int(sys.argv[2])
    output_file = input_file[:-4] +"_"+ str(t) + ".txt"

    with open(input_file, "r") as f1, open(output_file, "w") as f2:
        count = 0
        for line in f1:
            if line.strip().endswith('2'):
                f2.write(line)
            else:
                f2.write(line)
                count += 1
                if count == t:
                    break
