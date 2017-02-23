cmake_minimum_required(VERSION 3.3)

project(OrbitalPerturbation)

find_package(Eigen3 REQUIRED)

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
target_include_directories(orbital_perturbation PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(orbital_perturbation PUBLIC Eigen3::Eigen)

add_executable(turbomole_perturbation main_turbomole.cpp)
add_executable(gaussian_perturbation main_gaussian.cpp)

target_link_libraries(turbomole_perturbation orbital_perturbation)
target_link_libraries(gaussian_perturbation orbital_perturbation)
