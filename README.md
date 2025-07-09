# Audio FFT Processing on GPU using CUDA and FFTW

---

## Overview

This project demonstrates GPU-accelerated Fast Fourier Transform (FFT) processing on a large set of audio files using **CUDA** with the **FFTW** library and **libsndfile** for audio I/O. The goal is to leverage GPU acceleration to efficiently compute FFTs on `.wav` audio files and save the magnitude spectrum as `.csv` files.

This project was developed as part of the "CUDA at Scale for the Enterprise" module and provides a solid foundation for scalable signal processing using modern C++ and GPU programming.

---

## Project Structure

```
AudioFFT-CUDA/
├── input_data/            # Contains input .wav audio files
├── output_data/           # Contains output .csv files with FFT magnitude
├── main.cpp               # Main C++ program performing audio FFT processing
├── generate_audio.py      # Python script to generate synthetic input audio files
├── Makefile               # Build automation for compiling and cleaning
├── run.sh                 # Shell script for simplified build and run
├── README.md              # Project documentation (this file)
├── requirements.txt       # Python dependencies for audio generation (CuPy, SciPy, etc.)
```

---

## Key Concepts

- FFT using FFTW and CUDA acceleration  
- Audio I/O using libsndfile  
- Automated audio generation using Python  
- Build automation via Makefile and run.sh  
- Batch processing of multiple audio files  

---

## Requirements

- NVIDIA GPU with CUDA support (T4, A100, etc.)  
- CUDA Toolkit installed  
- FFTW library installed  
- libsndfile library installed  
- Python 3.7+ (for generating input audio files)  
- CuPy, NumPy, SciPy Python packages (for audio generation)

---

## Installation and Setup

1. Install CUDA Toolkit and verify GPU support.  
2. Install FFTW and libsndfile libraries on your system. For example, on Ubuntu:

```bash
sudo apt-get install libfftw3-dev libsndfile1-dev
```

3. Install Python dependencies:

```bash
pip install -r requirements.txt
```

---

## How to Run the Project

### Generate Input Audio Files (Python)

Run the audio generation script to create 100 synthetic `.wav` files:

```bash
python3 generate_audio.py
```

### Build the C++ Project

Use the Makefile to compile the C++ code:

```bash
make
```

This compiles `main.cpp` and generates `audiofft.exe` (or `audiofft` on Linux).

### Run the FFT Processing

Execute the compiled binary to process all `.wav` files in `input_data/` and save FFT results to `output_data/`:

```bash
./audiofft.exe
```

Alternatively, use the provided shell script:

```bash
./run.sh
```

---

## Output

- The program processes each `.wav` file and outputs a `.csv` file containing the FFT magnitude spectrum.  
- Output files are saved in `output_data/` with filenames like `fft_audio_0.wav.csv`.

---

## Makefile Commands

- `make` — compile the C++ project  
- `make clean` — remove executables and output CSV files

---

## Supported Environments

- OS: Linux, Windows (with compatible CUDA setup)  
- GPU: NVIDIA GPUs with CUDA 11.x or later  
- Compiler: g++ with C++11 support or higher

---

## How FFT is Performed

The steps in `main.cpp` are:

1. Read `.wav` files using libsndfile  
2. Convert stereo audio to mono if necessary  
3. Transfer audio data to GPU memory  
4. Perform FFT using FFTW and CUDA  
5. Calculate magnitude spectrum  
6. Save magnitude data as CSV files on disk  

---

## Credits

Developed by Nitin Giri as part of the CUDA at Scale Enterprise course. This project showcases efficient GPU-based FFT processing of audio data using modern C++ and CUDA.

---

## License

This project is intended for educational purposes and does not currently include an open-source license.

---
