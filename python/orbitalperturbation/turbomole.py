import argparse

from orbitalperturbation.turbomole_perturber import TurbomoleOrbitalPerturber


def run(directory):
    turbomole_perturber = TurbomoleOrbitalPerturber(directory)
    turbomole_perturber.perturb_orbitals()


def create_parser():
    arg_parser = argparse.ArgumentParser(description='Turbomole Orbital Perturber')
    arg_parser.add_argument('directory', help='directory of the Turbomole calculation')

    return arg_parser


def main():
    parser = create_parser()
    args = parser.parse_args()
    run(directory=args.directory)


if __name__ == '__main__':
    main()
