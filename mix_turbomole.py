from shutil import copyfile

def create_orbital_backup(directory):
    """
    Creates .bak files for the orbital files 'alpha' and 'beta'
    :param directory: calculation directory
    """
    copyfile(directory + '/alpha', directory + '/alpha.bak')
    copyfile(directory + '/beta', directory + '/beta.bak')
