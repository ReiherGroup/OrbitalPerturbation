import sys
from shutil import copyfile

def create_orbital_backup(directory):
    """
    Creates .bak files for the orbital files 'alpha' and 'beta'
    :param directory: calculation directory
    """
    copyfile(directory + '/alpha', directory + '/alpha.bak')
    copyfile(directory + '/beta', directory + '/beta.bak')

def read_number_electrons(directory):
    """
    :param directory:
    :return:
    """
    control_file = directory + '/control'


args = sys.argv
if len(args) != 2:
    print("Usage: python mix_turbomole.py <calculation_directory>")
    sys.exit()

calculation_directory = args[1]
create_orbital_backup(calculation_directory)


