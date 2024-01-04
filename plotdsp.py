import plotext as plt
import scipy.io.wavfile

sample_rate, raw_audio = scipy.io.wavfile.read("JFJF_2023126_11158_2.wav")

#y = plt.sin() # sinusoidal signal
#y=[0, 1, 2, 3, 2, 1, 0, -1, -2] 
plt.plot(raw_audio)
plt.title("Scatter Plot")
plt.show()
