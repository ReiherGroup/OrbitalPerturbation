# Examples

Below, we describe an example application of the perturbation approach for the methane molecule, where one of the hydrogen atoms has been pulled to a distance of 2 Angstrom from the carbon atom.
Normally, the initial calculation should deliver a higher-energy, closed-shell solution, and after one or several orbital perturbations the lower-energy, spin-broken solution should be found.

The corresponding coordinate file can be found [here](methane.xyz).

## Turbomole

1. Create the folder `example/turbomole` and `cd` into it.
2. `x2t ../methane.xyz > coord`
3. Generate the Turbomole control file: `define`. Thereby, make sure not to choose a closed-shell occupation ("DO YOU ACCEPT THIS OCCUPATION" -> "no", then select "s" for "singlet").
4. Perform an initial calculation: `dscf > dscf.out` or similar.
5. Perturb the orbitals: `turbomole_perturb .` (this executes the corresponding Python script).
6. Perform another calculation: `dscf > dscf_perturbed.out` one or several times.

## Gaussian

1. Go to the folder `example/gaussian`.
2. Perform an initial calculation: `g09 methane.inp`.
3. Perturb the orbitals: `gaussian_perturb methane.chk` (this executes the corresponding Python script).
4. Perform another calculation: `g09 methane_perturbed.inp` one or several times. There, `methane_perturbed.inp` is identical to `methane.inp` but for the keyword `Guess=Read`.
