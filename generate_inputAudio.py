import os
import shutil
import numpy as np
from scipy.io import wavfile

# Constants
output_dir = "input_data"
sample_rate = 44100  # 44.1 kHz
duration = 2  # seconds
frequency = 440  # Hz (A4 note)
num_files = 100

# Remove old input_data folder if it exists
if os.path.exists(output_dir):
    shutil.rmtree(output_dir)

# Recreate a clean input_data directory
os.makedirs(output_dir, exist_ok=True)

# Generate 100 synthetic .wav files
for i in range(num_files):
    t = np.linspace(0, duration, int(sample_rate * duration), endpoint=False)
    waveform = 0.5 * np.sin(2 * np.pi * frequency * t)
    waveform_int16 = np.int16(waveform * 32767)
    filename = os.path.join(output_dir, f"audio_{i}.wav")
    wavfile.write(filename, sample_rate, waveform_int16)

print(f"{num_files} audio files generated in '{output_dir}/'")
