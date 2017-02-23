# Perturbation of the Molecular Orbitals to Steer SCF Calculations toward Lower Energy

This repository contains utilities to perturb the molecular orbitals produced by different quantum chemical software.
Restarting calculations from perturbed molecular orbitals may steer the self-consistent field convergence toward other SCF solutions of lower energy.

The actual perturbation of the orbitals is implemented in C++.
For this, different executables exist for the different quantum chemical programs, and they modify the corresponding checkpoint files or molecular orbital files.
These executables can either be compiled from the source code in this repository, or downloaded directly (Linux only).

Python scripts are provided to automatize the use of the C++ programs.

Specific information to the supported quantum chemical software can be read below.


## Background

It can happen that self-consistent field calculations converge to a non-global energy minimum.
In such cases, it is helpful to perturb the molecular orbitals following a randomized scheme, as a different guess for the electronic density may lead to another SCF solution.
Doing this can be especially important in interactive explorations of chemical reactivity or in ab initio molecular dynamics.
The perturbation scheme is a vital component of our real-time quantum chemistry software (http://www.reiher.ethz.ch/research/haptic-quantum-chemistry).

A more detailed discussion of the topic, algorithm and applications can be found in 
Algorithm and applications described in [doi:10.1021/acs.jctc.7b00011](https://dx.doi.org/10.1021/acs.jctc.7b00011).


## Supported quantum chemical packages

### Turbomole

http://www.turbomole-gmbh.com/

### Gaussian

http://gaussian.com/
