import subprocess
from shutil import copyfile


def cmd_exists(cmd):
    return subprocess.call("type " + cmd, shell=True,
                           stdout=subprocess.PIPE, stderr=subprocess.PIPE) == 0


def create_backup(file):
    copyfile(file, file + '.bak')
