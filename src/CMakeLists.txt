cmake_minimum_required(VERSION 3.3)
set (CMAKE_CXX_STANDARD 11)

project(OrbitalPerturbation)

# Import Eigen library
# First try CONFIG mode, if this does not work use the MODULE mode.
find_package(Eigen3 CONFIG)
if (NOT ${Eigen3_FOUND})
  list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
  find_package(Eigen3 REQUIRED)
endif()

set(HEADERS
    OrbitalPerturbation/SeedIO.h
    OrbitalPerturbation/Mixing.h
    OrbitalPerturbation/MolecularOrbitals.h
    OrbitalPerturbation/MolecularOrbitalsManipulation.h
    OrbitalPerturbation/RandomOrbitalMixer.h
    OrbitalPerturbation/SpinAdaptedMatrix.h
    OrbitalPerturbation/ScientificNumberFormatter.h
    OrbitalPerturbation/UniqueRandomNumbersGenerator.h
    OrbitalPerturbation/GaussianOrbitalFileWriter.h
    OrbitalPerturbation/GaussianOrbitalFileReader.h
    OrbitalPerturbation/TurbomoleNumberStringConverter.h
    OrbitalPerturbation/TurbomoleOrbitalFileReader.h
    OrbitalPerturbation/TurbomoleOrbitalFileWriter.h
    OrbitalPerturbation/TurbomoleOrbitalsMetaInformation.h
)

set(SOURCES
    OrbitalPerturbation/SeedIO.cpp
    OrbitalPerturbation/Mixing.cpp
    OrbitalPerturbation/MolecularOrbitals.cpp
    OrbitalPerturbation/MolecularOrbitalsManipulation.cpp
    OrbitalPerturbation/RandomOrbitalMixer.cpp
    OrbitalPerturbation/SpinAdaptedMatrix.cpp
    OrbitalPerturbation/ScientificNumberFormatter.cpp
    OrbitalPerturbation/GaussianOrbitalFileWriter.cpp
    OrbitalPerturbation/GaussianOrbitalFileReader.cpp
    OrbitalPerturbation/TurbomoleNumberStringConverter.cpp
    OrbitalPerturbation/TurbomoleOrbitalFileReader.cpp
    OrbitalPerturbation/TurbomoleOrbitalFileWriter.cpp
    OrbitalPerturbation/TurbomoleOrbitalsMetaInformation.cpp
)

add_library(orbital_perturbation STATIC ${HEADERS} ${SOURCES})
target_include_directories(orbital_perturbation PUBLIC ${EIGEN3_INCLUDE_DIR})
target_include_directories(orbital_perturbation PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(turbomole_perturbation main_turbomole.cpp)
add_executable(gaussian_perturbation main_gaussian.cpp)

target_link_libraries(turbomole_perturbation orbital_perturbation)
target_link_libraries(gaussian_perturbation orbital_perturbation)
