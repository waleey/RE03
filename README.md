# RE03 – A Geant4 Simulation Example

This repository contains a Geant4-based simulation project. Follow the steps below to install dependencies, build the project, and run the simulation.

## 🔧 Prerequisites

### 1. Install Geant4

Before building this project, you must install [Geant4](https://geant4.web.cern.ch/support/download).

👉 Follow the official guide here:  
[Geant4 Installation Instructions](https://geant4-userdoc.web.cern.ch/UsersGuides/InstallationGuide/html/index.html)

After installation, configure your environment (adjust the path as needed):

```
source /path/to/geant4-install/bin/geant4.sh
```

## 📥 Clone the Repository

Use Git to clone this repository:

```
git clone https://github.com/waleey/RE03.git
cd RE03
```

## 🛠️ Build the Project

Create a build directory, run CMake, and compile using all available processor cores:

```
cd /path/to/RE03/
mkdir build
cd build
cmake ..
make -j$(nproc)
```

> 💡 Note: Make sure Geant4 is sourced in your environment before running `cmake`.

## 🚀 Run the Simulation

After building, run the executable from the build directory:

```
./RE03
```

## 📄 License

This project is open-source and available under the [MIT License](LICENSE).
