import plotext as plt
#import scipy.io.wavfile
import numpy as np

#with open('fftmag.bin', mode='rb') as file: 
#    fileContent = file.read()   

#file.close()

f = open('fftmag.bin', 'rb')
arr = np.fromfile(f, dtype='f8')
f.close()
print(arr[:5])
#sample_rate, raw_audio = scipy.io.wavfile.read("JFJF_2023126_11158_2.wav")

y = plt.sin() # sinusoidal signal
#y=[0, 1, 2, 3, 2, 1, 0, -1, -2] 
#plt.plot(raw_audio)
plt.plot(arr[:1024])
plt.title("FFT Magnitude Plot")
plt.xlabel("Frequency Line")
plt.ylabel("Magnitude")
plt.show()
