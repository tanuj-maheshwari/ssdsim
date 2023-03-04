import numpy as np
import matplotlib.pyplot as plt
import sys

WRITE = "0"
READ = "1"
DELETE = "2"
tracefile = open(sys.argv[1], 'r')

nrequests = 0
nreadrequest = 0
nwriterequest = 0
ndeleterequest=0
req_time = []
req_size_r = []
req_size_w = []
req_size_d=[]
start_time = 0
end_time = 0

# get characteristic data
for line in tracefile:
    incoming_time = float(line.split()[0])
    disk_id = line.split()[1]
    address = line.split()[2]
    size = float(line.split()[3])
    ope = line.split()[4]

    nrequests = nrequests + 1
    req_time.append(incoming_time)
    if ope == READ:
        req_size_r.append(size/2.0) # convert sector to KB, 1 sector = 512 B
        nreadrequest = nreadrequest + 1
    elif ope == WRITE:
        req_size_w.append(size/2.0)
        nwriterequest = nwriterequest + 1
    elif ope == DELETE:
        req_size_d.append(size/2.0)
        ndeleterequest = ndeleterequest + 1
    # processing first data
    if nrequests == 1:
        start_time = incoming_time / 1000000000 # convert to second
    end_time = incoming_time / 1000000000

diff = []
for i in range(len(req_time)-1):
    diff.append(req_time[i+1]-req_time[i])

np_diff = np.array(diff)    
np_size_r = np.array(req_size_r)
np_size_w = np.array(req_size_w)
np_size_d = np.array(req_size_d)
duration = end_time-start_time

print("int-arrival time ", np.average(np_diff)/1000000.0, " ms")
if nreadrequest > 0:
    print("avg.read size ", np.average(np_size_r), " KB")
if nwriterequest > 0:
    print("avg.write size ", np.average(np_size_w), " KB")
if ndeleterequest > 0:
    print("avg.delete size ", np.average(np_size_d), " KB")
print("read (%) ", nreadrequest/nrequests*100.0 , "%")
print("write (%) ", nwriterequest/nrequests*100.0, "%")
print("delete (%) ", ndeleterequest/nrequests*100.0, "%")
print("read size (MB) ", np.sum(np_size_r)/1000.0)
print("write size (MB) ", np.sum(np_size_w)/1000.0)
print("delete size (MB) ", np.sum(np_size_d)/1000.0)
print("read BW ", np.sum(np_size_r)/duration/1000, "MB/s")
print("write BW ", np.sum(np_size_w)/duration/1000, "MB/s")
print("delete BW ", np.sum(np_size_d)/duration/1000, "MB/s")
print("start time ", start_time)
print("end time ", end_time, "s")
print("duration ", duration, "s")
print("read IOPS ", nreadrequest/duration)
print("write IOPS ", nwriterequest/duration)
print("delete IOPS ", ndeleterequest/duration)

# creating io rate graph
np_time = np.array(req_time)
min_scd_time = int(np_time[0]/1000000000)
max_scd_time = int(np_time[nrequests-1]/1000000000.0)
iorate,_ = np.histogram(np_time, bins=max_scd_time-min_scd_time+1)
plt.plot(iorate)
plt.ylabel("IOPS")
plt.xlabel("time (s)")
plt.ylim(top=500)
plt.show()
