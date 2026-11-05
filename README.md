# 🎬 V2A: Real-Time Video-to-ASCII Renderer (C++ / OpenCV)

A high-performance command-line utility written in C++ that transforms video files and live webcam streams into colored **ASCII art animation** in real-time. 

The engine processes video buffers frame-by-frame, maps pixel luminance matrix data to standard ASCII glyphs, and leverages **24-bit TrueColor ANSI escape sequences** to project vivid console-rendered frames with low CPU overhead.

---

### ✨ Features / Возможности

- **Live Webcam & File Streaming:** Supports processing both static local video files and hardware-connected camera streams dynamically via `cv::VideoCapture`.
- **TrueColor ANSI Coding:** Features full 24-bit RGB text colorization (`\033[38;2;R;G;Bm`), turning matrix vectors into crisp, colored terminal terminal views.
- **Custom Precision Downscaling:** Features interactive real-time resolution scaling (Lanczos4/Nearest algorithms) to perfectly fit variable terminal sizes without breaking frame aspect ratios.
- **Cross-Platform Base:** Tailored conditional macros (`#ifdef _WIN32 / __linux__`) to support clean frame clears across terminal environments.
- **OpenCV 5+ Ecosystem Ready:** Upgraded and maintained layout to stay compliant with modern OpenCV specifications and thread handling.

---

### 🛠️ Technical Breakdown / Как это устроено

For each incoming video frame, the rendering workflow processes buffers asynchronously:
`[Frame Capture] -> [BGR to Grayscale Sync] -> [LANCZOS4 Downsampling] -> [Luminance Mapping] -> [24-bit RGB Vector Extraction] -> [ANSI Terminal Flush]`

- **Luminance Mapping Equation:** Grayscale pixel values ($0-255$) are mapped directly to a customizable density string (`.,'-~:;=<!?*#$@`) to dynamically pick structural contrast symbols based on lighting intensity.
- **Double Buffer Array Optimization:** Keeps performance clean by packaging image structures into unified high-speed vectors (`vFrame` and `cFrame`), preventing memory allocation leaks between continuous terminal loop updates.

---

### 🚀 How to Compile & Run / Компиляция и запуск

You must have **OpenCV libs** installed on your system environment to run the executable.

#### Linux (Arch Linux Verified 64-bit)
```bash
# Requires OpenCV 5+ system libraries installed (if you REALLY want to recompile it.)
g++ -O3 vidtoascii_linuxbuild.cpp -o V2A -I/usr/include/opencv5/ -L/usr/lib -lopencv_core -lopencv_videoio -lopencv_imgproc -lopencv_highgui
./v2a <path_to_video.mp4>
# Or use live webcam input:
./v2a webcam
```

#### Windows (Tested on Win10 64-bit)
Place the required OpenCV `.dll` runtimes inside the same build folder where the compiled `.exe` is located.
```cmd
v2a.exe <path_to_video.mp4>
```

---

### 🚧 Future Roadmap
- Implement non-blocking terminal I/O to read dynamic hotkeys (like instant termination via the `Q` key) without waiting for frame syncs.
- Perhaps, improve Windows version.

---

### 📄 License & Notes

- **License:** **GNU GPLv3** — Feel free to use, break, and explore!
- **Note from the author:** Windows version remains un-colorized and completely obsolete because static cross-platform builds are a massive hassle. *Son, I'm crine...* 😭🙏🏻

---
