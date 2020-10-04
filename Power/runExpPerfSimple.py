import os
import numpy as np
print("cd")
print("cd Compression_Energy_Experiment/compressors/ZFP_Power/")
print("make all")
dataSetPath = "/users/gfwilki/Compression_Energy_Experiment/data/"
dataSetName = [x for x in os.listdir(dataSetPath)] # <- Set specific data sets here
#dataSetName.remove("template_data.txt")

Compressor = "ZFP"
dimension = " 0,0,26,1800,3600 "
Operation = "compress"

CPUMin = 0.8
CPUMax = 2.25
CPUStep = 0.05
num_cores = 40
for i in range(num_cores):
	print("wrmsr -p" + str(i) + " 0x1a0 0x4000850089")
abs_err_vals = ["1e-1", "1e-2", "1e-3", "1e-4"]
for abs_err in abs_err_vals:
	for file in dataSetName:
		if file is not dataSetPath:
			curRecFile = Compressor + "_" + file + "_" + abs_err + ".txt"
			print("touch " + curRecFile)
			for freq in np.arange(CPUMin, CPUMax, CPUStep):
				print("echo " + str(freq) + " >> " + curRecFile)
				print("cpupower frequency-set -g userspace")
				print("cpupower frequency-set -f " + str(freq) + "GHz")
				print("perf stat -o data.txt -e power/energy-pkg/ /users/gfwilki/Compression_Energy_Experiment/ZFP_Power/simple " + dataSetPath + file + dimension + abs_err )
				print("grep -E \'Joules|time\' ./data.txt >> " + curRecFile)
				print("perf record /users/gfwilki/Compression_Energy_Experiment/ZFP_Power/simple " + dataSetPath + file + dimension + abs_err)
				curPerfFile = Compressor + "_" + file + "_" + abs_err + "_" + str(freq) + "_perfData.txt"
				print("perf report > " + curPerfFile)
				print("mv ./" + curPerfFile + " ~/")
				print("rm perf.data")
			print("mv ./" + curRecFile + " ~/")
