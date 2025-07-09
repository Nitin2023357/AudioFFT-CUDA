// main.cpp

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <cmath>
#include <fftw3.h>
#include <sndfile.h>

namespace fs = std::filesystem;

const std::string INPUT_DIR = "input_data";
const std::string OUTPUT_DIR = "output_data";

void processAudioFile(const std::string& inputPath, const std::string& outputPath) {
    // Open WAV file
    SF_INFO sfinfo;
    SNDFILE* infile = sf_open(inputPath.c_str(), SFM_READ, &sfinfo);
    if (!infile) {
        std::cerr << "Failed to open file: " << inputPath << std::endl;
        return;
    }

    std::vector<float> buffer(sfinfo.frames * sfinfo.channels);
    sf_readf_float(infile, buffer.data(), sfinfo.frames);
    sf_close(infile);

    // Convert to mono if stereo
    std::vector<double> mono(sfinfo.frames);
    for (int i = 0; i < sfinfo.frames; ++i) {
        mono[i] = static_cast<double>(buffer[i * sfinfo.channels]);
    }

    // FFT input/output
    int N = sfinfo.frames;
    double* in = fftw_alloc_real(N);
    fftw_complex* out = fftw_alloc_complex(N / 2 + 1);
    std::copy(mono.begin(), mono.end(), in);

    fftw_plan plan = fftw_plan_dft_r2c_1d(N, in, out, FFTW_ESTIMATE);
    fftw_execute(plan);

    // Save to CSV
    std::ofstream fout(outputPath);
    if (!fout) {
        std::cerr << "Failed to write file: " << outputPath << std::endl;
        return;
    }
    for (int i = 0; i < N / 2 + 1; ++i) {
        double magnitude = std::sqrt(out[i][0] * out[i][0] + out[i][1] * out[i][1]);
        fout << magnitude << "\n";
    }

    fout.close();
    fftw_destroy_plan(plan);
    fftw_free(in);
    fftw_free(out);
}

int main() {
    // Create output folder if it doesn't exist
    if (!fs::exists(OUTPUT_DIR)) {
        fs::create_directory(OUTPUT_DIR);
    }

    for (const auto& entry : fs::directory_iterator(INPUT_DIR)) {
        if (entry.path().extension() == ".wav") {
            std::string inputPath = entry.path().string();
            std::string filename = entry.path().filename().string();
            std::string outputPath = OUTPUT_DIR + "/fft_" + filename + ".csv";

            std::cout << "Processing " << filename << "...\n";
            processAudioFile(inputPath, outputPath);
        }
    }

    std::cout << "All audio files processed.\n";
    return 0;
}
