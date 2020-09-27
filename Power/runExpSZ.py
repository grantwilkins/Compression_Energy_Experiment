import os
import numpy as np
print("cd")
print("cd Compression_Injection-Power_Experiment/")
print("make")
dataSetPath = "/users/gfwilki/Compression_Injection-Power_Experiment/data/SDRBENCH_Data/cesm/"
dataSetName = [x for x in os.listdir(dataSetPath)] # <- Set specific data sets here
#dataSetName.remove("template_data.txt")

Compressor = "SZ"
dimensions=" 0,0,26,1800,3600 "
config_path = "/users/gfwilki/Compression_Injection-Power_Experiment/config/sz_abs_"


CPUMin = 0.8
CPUMax = 2.25
CPUStep = 0.05
num_cores = 40
for i in range(num_cores):
	print("wrmsr -p" + str(i) + " 0x1a0 0x4000850089")
abs_err_vals = ["1e1", "1e2", "1e3", "1e4"]
for abs_err in abs_err_vals:
	for file in dataSetName:
		if file is not dataSetPath:
			curRecFile = Compressor + "_" + file + "_" + abs_err + ".txt"
			print("touch " + curRecFile)
			for freq in np.arange(CPUMin, CPUMax, CPUStep):
				print("echo " + str(freq) + " >> " + curRecFile)
				print("cpupower frequency-set -g userspace")
				print("cpupower frequency-set -f " + str(freq) + "GHz")
				print("perf stat -o data.txt -e power/energy-pkg/ /users/gfwilki/Compression_Injection-Power_Experiment/comp_inj " + dataSetPath + file + dimensions + config_path + abs_err + ".config 0 0")
				print("grep -E \'Joules|time\' ./data.txt >> " + curRecFile)
				print("perf record /users/gfwilki/Compression_Injection-Power_Experiment/comp_inj " + dataSetPath + file + dimensions + config_path + abs_err + ".config 0 0")
				curPerfFile = Compressor + "_" + file + "_" + abs_err + "_" + str(freq) + "_perfData.txt"
				print("perf report > " + curPerfFile)
				print("mv ./" + curPerfFile + " ~/")
				print("rm perf.data")
			print("mv ./" + curRecFile + " ~/")
