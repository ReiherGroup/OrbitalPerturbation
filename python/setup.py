from setuptools import setup


def readme():
    with open('README.md') as f:
        return f.read()


setup(name='orbitalperturbation',
      version='1.0',
      description='Utility for the perturbation of molecular orbitals delivered by standard quantum chemical packages',
      long_description=readme(),
      classifiers=['Programming Language :: Python :: 3.5'],
      url='https://github.com/ReiherGroup/OrbitalPerturbation',
      author='Alain C. Vaucher',
      entry_points={
          'console_scripts': ['turbomole_perturb = orbitalperturbation.turbomole:main',
                              'gaussian_perturb = orbitalperturbation.gaussian:main'
                              ],
      },
      packages=['orbitalperturbation'],
      include_package_data=True,
      zip_safe=False)
