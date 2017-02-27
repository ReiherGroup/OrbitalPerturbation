import argparse

from orbitalperturbation.gaussian_perturber import GaussianOrbitalPerturber


def run(checkpoint_file):
    gaussian_perturber = GaussianOrbitalPerturber(checkpoint_file)
    gaussian_perturber.perturb_orbitals()


def create_parser():
    arg_parser = argparse.ArgumentParser(description='Gaussian Orbital Perturber')
    arg_parser.add_argument('checkpoint_file', help='Gaussian checkpoint file (*.fchk)')

    return arg_parser


def main():
    parser = create_parser()
    args = parser.parse_args()
    run(checkpoint_file=args.checkpoint_file)


if __name__ == '__main__':
    main()
